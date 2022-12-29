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
`include "interfaces.svh"

module timebase_shifter_core #(parameter COUNTER_WIDTH = 16)(
        input wire clockIn,
        input wire reset,
        input wire enable,
        input wire load,
        input wire [COUNTER_WIDTH-1:0] count_in,
        output wire [COUNTER_WIDTH-1:0] count_out
    );



    reg [COUNTER_WIDTH-1:0] count = {COUNTER_WIDTH{1'b0}};
    
    assign count_out = count;
    
    always @(posedge clockIn) begin 
        if (~reset)
            count <= {COUNTER_WIDTH{1'b0}};
        else if(enable) begin
            count <= count - 1'b1;
        end else begin
            if(load) count <= count_in;
        end
    end
    
endmodule