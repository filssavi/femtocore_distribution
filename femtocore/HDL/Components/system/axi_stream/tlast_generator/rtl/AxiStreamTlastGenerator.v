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

`timescale 10ns / 1ns
//`include "interfaces.svh"

module tlast_generator(
        input wire clock,
        input wire reset, 
        input wire [15:0] period,
        //input AXI stream
        input wire in_valid,
        input wire [31:0] in_data,
        output wire in_ready,
        //output AXI stream
        output reg out_valid,
        output reg [31:0] out_data,
        input wire out_ready,
        output reg out_tlast,
        output wire [15:0] current_sample
    );


    reg [15:0] tlast_counter;
    assign current_sample = tlast_counter;
    assign in_ready = out_ready;

    always@(posedge clock)begin
        if(~reset)begin
            out_tlast <= 0;
            out_valid <= 0;
            tlast_counter <= 0;
        end else begin
            out_valid <= in_valid;
            out_data[31:0] <= in_data[31:0];
            if(in_valid)begin
                if(tlast_counter==period-1)begin
                    tlast_counter <= 0;
                    out_tlast <= 1;
                end else begin
                    tlast_counter <= tlast_counter+1;
                end
            end else begin
                out_tlast <= 0;
            end
        end
    end


endmodule
