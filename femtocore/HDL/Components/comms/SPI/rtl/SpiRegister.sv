// Copyright 2021 University of Nottingham Ningbo China
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

module SpiRegister #(parameter N_CHANNELS=3)(
    input logic clock,
    input logic shift_clock, 
    input logic reset,
    input logic enable,
    input logic serial_in,
    input logic latching_edge,
    input logic register_direction,
    input logic [4:0] spi_transfer_length,
    input logic register_load,
    input logic [31:0] parallel_in,
    output logic parallel_out_valid,
    output logic [31:0] parallel_out,
    output logic serial_out
);
    localparam serial_msb_out_first = 0, serial_lsb_out_first = 1;

    logic shr_data_valid_lock = 0;   
    logic [31:0] shift_reg;

    always@(posedge clock)begin
        parallel_out <= shift_reg;
        parallel_out_valid <= !enable & shr_data_valid_lock;
    end
    
    
    reg previous_sclk;
    always@(posedge clock)begin
        if(~reset) begin
            serial_out <=0;
            previous_sclk <= 0;
        end else begin 
            if(previous_sclk==latching_edge & shift_clock==~latching_edge)begin
                if(!register_load && enable) begin
                    if(register_direction==serial_lsb_out_first) begin
                        serial_out <= shift_reg[0];
                    end else begin
                        serial_out <= shift_reg[spi_transfer_length-1];
                    end
                end else begin
                    serial_out <= 0;
                end
            end

            previous_sclk <= shift_clock;
        end
    end

    reg previous_inner_sclk;
    always@(posedge clock)begin
        if(~reset) begin
            previous_inner_sclk <= 0;
            shr_data_valid_lock <=0;
            shift_reg <=0;
        end else begin
            shr_data_valid_lock <= 1;
            if(register_load) begin
                shift_reg <= parallel_in;
            end else if(previous_inner_sclk==latching_edge & shift_clock==~latching_edge)begin
                if(enable) begin
                    if(register_direction==serial_lsb_out_first) begin
                        shift_reg <= shift_reg >> 1;
                        shift_reg[spi_transfer_length] <= serial_in;
                    end else begin
                        shift_reg <= shift_reg << 1;
                        shift_reg[0] <= serial_in;
                    end
                end
            end
            previous_inner_sclk <= shift_clock;
        end
    end

endmodule