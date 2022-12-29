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
module true_dp_ram #(parameter DATA_WIDTH=32, parameter ADDR_WIDTH=8) (
    input wire  clock,
    
    input wire [(ADDR_WIDTH-1):0] addr_a,
    input wire [(DATA_WIDTH-1):0] data_a_w,
    output reg [(DATA_WIDTH-1):0] data_a_r, 
    input wire we_a,

    input wire [(ADDR_WIDTH-1):0] addr_b,
    input wire [(DATA_WIDTH-1):0] data_b_w,
    output reg [(DATA_WIDTH-1):0] data_b_r,
    input wire we_b

);

    reg [DATA_WIDTH-1:0] memory [2**ADDR_WIDTH-1:0];

    initial begin
        for (integer ram_index = 0; ram_index < 2**ADDR_WIDTH; ram_index = ram_index + 1)
            memory[ram_index] = {DATA_WIDTH{1'b0}};
    end

    always_ff @(posedge clock) begin
        if(we_a) begin
            memory[addr_a] <= data_a_w;
        end else begin
            data_a_r <= memory[addr_a];
        end
    end

    always_ff @(posedge clock) begin
        if(we_b) begin
            memory[addr_b] <= data_b_w;
        end else begin
            data_b_r <= memory[addr_b];
        end
    end

endmodule