// Copyright 2021 Filippo Savi
// Author: Filippo Savi <filssavi@gmail.com>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
`timescale 10 ns / 1 ns
`include "interfaces.svh"

module ad2s1210_fault_handler (
    input wire clock,
    input wire reset,
    input wire start,
    input wire [7:0] sample_delay, 
    input wire [7:0] sample_length,
    axi_stream.master spi_transfer,
    output reg mode,
    output reg sample, 
    output reg done
);
    


    enum logic [2:0] {
        idle_state =                   3'b000,
        first_sample_state =           3'b001,
        start_shift_address_in_state = 3'b010,
        wait_address_in_state =        3'b011,
        start_read_fault_state =       3'b100,
        wait_read_fault_state =        3'b101,
        wait_before_resample =         3'b110,
        second_sample_state =          3'b111 
    } state;

    reg [15:0] fc_counter;

    always@(posedge clock)begin : fc_fsm
        if(!reset)begin
            state <= idle_state;
            sample <= 1;
            done <= 0;
            fc_counter <= 0;
            spi_transfer.data <= 0;
            spi_transfer.valid <= 0;
            mode <= 0;
        end else begin
            case (state)
                idle_state: begin
                    done <= 0;
                    if(start)begin
                        sample <= 0;
                        fc_counter <= 0;
                        state <= first_sample_state;
                    end
                end        
                first_sample_state:begin
                    if(fc_counter == sample_length-1)begin
                        sample <= 1;
                        spi_transfer.data <= 'hff;
                        fc_counter <= 0;
                        mode <= 1;
                        state <= start_shift_address_in_state;
                    end else begin
                        fc_counter <= fc_counter+1;
                    end
                end
                start_shift_address_in_state: begin
                    if(fc_counter ==sample_delay)begin
                        if(~spi_transfer.ready) begin
                            state <= wait_address_in_state;
                            fc_counter <= 0;
                            spi_transfer.valid <= 0;
                        end
                        spi_transfer.valid <= 1;
                    end else begin
                        fc_counter <= fc_counter+1;
                    end
                end
                wait_address_in_state:begin
                    spi_transfer.valid <= 0;
                    if(spi_transfer.ready)begin
                        state<= start_read_fault_state;
                        spi_transfer.data <= 'h0;
                    end
                end
                start_read_fault_state: begin
                    if(fc_counter == 20)begin
                        if(~spi_transfer.ready) begin
                            state <= wait_read_fault_state;
                            fc_counter <= 0;
                            spi_transfer.valid <= 0;
                        end
                        spi_transfer.valid <= 1;

                    end else begin
                        spi_transfer.valid  <=0;
                        fc_counter <= fc_counter+1;
                    end 
                end
                wait_read_fault_state: begin
                    spi_transfer.data <= 0;
                    spi_transfer.valid <= 0;
                    if(spi_transfer.ready & ~spi_transfer.valid) begin
                        fc_counter <= 0;
                        state <= wait_before_resample;
                    end 
                end
                wait_before_resample: begin
                    if(fc_counter ==sample_delay)begin
                        state <= second_sample_state;
                        fc_counter <= 0;
                        mode <= 0;
                        sample <= 0;
                    end else begin
                        fc_counter <= fc_counter+1;
                    end
                    
                end
                second_sample_state:begin
                    if(spi_transfer.ready & ~spi_transfer.valid)begin
                        if(fc_counter == sample_length-1)begin
                            sample <= 1;
                            done <= 1;
                            fc_counter <= 0;
                            state <= idle_state;
                        end else begin
                            fc_counter <= fc_counter+1;
                        end
                    end
                end
            endcase
        end
    end




endmodule