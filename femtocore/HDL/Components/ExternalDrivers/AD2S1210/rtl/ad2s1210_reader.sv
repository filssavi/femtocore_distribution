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

module ad2s1210_reader (
    input wire clock,
    input wire reset,
    input wire start,
    input wire transfer_type,
    input wire [7:0] sample_length,
    input wire [7:0] sample_delay,
    input wire [31:0] spi_data_in,
    axi_stream.master spi_transfer,
    output reg [1:0] mode,
    output reg sample,
    axi_stream.master data_out
);



    reg [7:0] reader_counter;
    reg read_type;

    enum logic [2:0] {
        idle_state    = 3'b000,
        sample_state  = 3'b001,
        read_state    = 3'b010,
        backoff_state = 3'b011
    } reader_state;

    always@(posedge clock)begin
        if(!reset)begin
            sample <= 1;
            reader_state <= idle_state;
            read_type <= 0;
            reader_counter <= 0;
            spi_transfer.valid <= 0;
            spi_transfer.data <= 0;
            mode <= 0;
            data_out.data <= 0;
            data_out.valid <= 0;
            data_out.dest <= 0;
            data_out.user <= 0;   
        end else begin
            case(reader_state)
                    idle_state: begin
                        if(start)begin
                            read_type <= transfer_type;
                            reader_state <= sample_state;    
                        end
                    end
                    sample_state: begin
                        if(reader_counter == sample_length-1)begin
                            sample <= 1;
                            reader_counter <= 0;
                            reader_state <= read_state;
                        end else begin
                            sample <= 0;
                            if(read_type)begin
                                mode <= 2'b10;
                            end else begin
                                mode <= 2'b00;
                            end
                            reader_counter <= reader_counter+1;
                            reader_state <= sample_state;
                        end
                    end
                    read_state: begin
                        reader_counter <= 0;
                        if(reader_counter ==sample_delay)begin
                             if(spi_transfer.ready & ~spi_transfer.valid) begin
                                spi_transfer.data <= 0;
                                spi_transfer.valid <= 1;
                                reader_counter <= 0;
                                reader_state <= backoff_state;
                            end else begin
                                reader_state <=read_state;
                            end
                        end else begin
                            reader_counter <= reader_counter+1;
                            reader_state <= read_state;
                        end
                    end
                    backoff_state: begin
                        spi_transfer.valid <= 0;
                        if(spi_transfer.ready & ~spi_transfer.valid)begin
                            if(reader_counter == 1)begin
                                data_out.data <= {8'b0,spi_data_in[31:8]};
                                data_out.valid <= 1;
                                data_out.dest <= read_type;
                                data_out.user <= spi_data_in[7:0];    
                            end else begin
                                data_out.valid <= 0;
                            end

                            if(reader_counter == sample_length-1)begin
                                reader_counter <= 0;
                                reader_state <= idle_state;
                            end else begin
                                reader_counter <= reader_counter+1;
                                reader_state <= backoff_state;
                            end
                        end
                    end
                endcase
        end
    end



endmodule