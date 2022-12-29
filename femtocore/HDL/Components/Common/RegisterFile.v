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

module RegisterFile
#(parameter DATA_WIDTH=32, parameter ADDR_WIDTH=8)
(
    input wire reset,
    input [(DATA_WIDTH-1):0] data_a,
    input [(ADDR_WIDTH-1):0] addr_a,
    input we_a, clk,
    output reg [(DATA_WIDTH-1):0] q_a
);

    // Declare the RAM variable
    reg [DATA_WIDTH-1:0] ram[2**ADDR_WIDTH-1:0];
    integer i;  

    // Port A 
    always @ (posedge clk) begin
        if (we_a) begin
            ram[addr_a] <= data_a;
            q_a <= data_a;
        end else begin
            q_a <= ram[addr_a];
        end
    end 

endmodule