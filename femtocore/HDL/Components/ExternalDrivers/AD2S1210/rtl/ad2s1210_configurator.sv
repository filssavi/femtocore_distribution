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

module ad2s1210_configurator (
    input wire clock,
    input wire reset,
    input wire start,
    input reg [7:0] config_address[0:14],
    input reg [7:0] config_data[0:14],
    axi_stream.master spi_transfer,
    output reg done
);


       
    enum logic [1:0]{
        idle = 2'b00,
        send_address = 2'b01,
        send_data    = 2'b10
    } state;

    reg [3:0] configuration_counter;

    always@(posedge clock)begin : configuration_FSM
        if(!reset)begin
            state <= idle;
            done <= 0;
            configuration_counter <= 4;
            spi_transfer.valid <= 0;
            spi_transfer.data <= 0;
        end else begin
            case (state)
                idle:begin
                    if(start)begin
                        state <= send_address;
                    end else begin
                        state <= idle;
                    end
                    done <= 0;
                end
                send_address: begin
                    if(configuration_counter==13 & spi_transfer.ready & ~spi_transfer.valid)begin
                        done <= 1;
                        state <= idle;
                        configuration_counter <= 4;
                    end else if(configuration_counter==13 & spi_transfer.valid) begin
                        spi_transfer.valid <= 0;
                    end else begin
                        if(spi_transfer.ready & ~spi_transfer.valid) begin
                            spi_transfer.data <= config_address[configuration_counter];
                            spi_transfer.valid <= 1;
                            state <=send_data;
                        end else begin
                            state <=send_address;
                            spi_transfer.valid <= 0;
                        end
                    end
                end
                send_data: begin
                    if(spi_transfer.ready & ~spi_transfer.valid) begin
                        spi_transfer.data <= config_data[configuration_counter];
                        spi_transfer.valid <= 1;
                        configuration_counter <= configuration_counter+1;
                        state <= send_address;
                    end else begin
                        spi_transfer.valid <= 0;
                        state <= send_data;
                    end
                end
            endcase
        end
    end
    


endmodule