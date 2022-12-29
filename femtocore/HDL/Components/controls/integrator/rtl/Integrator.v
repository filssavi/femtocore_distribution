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
//`include "interfaces.svh"

module Integrator #(parameter DATA_WIDTH = 16)(
    input wire clock,
    input wire reset,
    input wire input_valid,
    input wire signed [DATA_WIDTH-1:0] limit_int_up,
    input wire signed [DATA_WIDTH-1:0] limit_int_down,
    input wire signed [DATA_WIDTH-1:0] error_in,
    output wire signed[DATA_WIDTH-1:0] out
); 

    reg signed [DATA_WIDTH-1:0] integral_memory;
    wire signed [DATA_WIDTH-1:0] next_memory_value;
  
    assign next_memory_value = error_in+integral_memory;
    assign out = integral_memory;
  
    always @(posedge clock)begin
        if(~reset) begin
            integral_memory <= 0;
        end else begin
            if(input_valid)begin
                if($signed(next_memory_value) > $signed(limit_int_up)) begin 
                    integral_memory <= limit_int_up;
                end else if($signed(next_memory_value) < $signed(limit_int_down)) begin
                    integral_memory <= limit_int_down;
                end else begin
                    integral_memory <= next_memory_value;
                end
            end
        end
    end
   
endmodule