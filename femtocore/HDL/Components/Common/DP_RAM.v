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

module DP_RAM
#(parameter DATA_WIDTH=32, parameter ADDR_WIDTH=8)
(
    input wire  clk,
    input wire [(DATA_WIDTH-1):0] data_a,
    output reg [(DATA_WIDTH-1):0] data_b,
    input wire [(ADDR_WIDTH-1):0] addr_a,
    input wire [(ADDR_WIDTH-1):0] addr_b,
    input wire we_a,
    input wire en_b
);

  reg [DATA_WIDTH-1:0] ram [2**ADDR_WIDTH-1:0];
 
    integer ram_index;
    initial begin
        for (ram_index = 0; ram_index < 2**ADDR_WIDTH; ram_index = ram_index + 1)
            ram[ram_index] = {DATA_WIDTH{1'b0}};
    end

  always @(posedge clk) begin
    if (we_a)
      ram[addr_a] <= data_a;
    if (en_b)
      data_b <= ram[addr_b];
  end

endmodule