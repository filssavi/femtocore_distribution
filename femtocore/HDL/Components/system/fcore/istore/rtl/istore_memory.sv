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
`include "interfaces.svh"

module istore_memory #(parameter DATA_WIDTH_A=32, DATA_WIDTH_B=64, parameter ADDR_WIDTH=8, FAST_DEBUG="FALSE", INIT_FILE = "") (
    input wire clock_in,
    input wire clock_out,
    input wire reset,
    input wire [(DATA_WIDTH_A-1):0] data_a,
    output reg [(DATA_WIDTH_B-1):0] data_b,
    input wire [(ADDR_WIDTH-1):0] addr_a,
    input wire [(ADDR_WIDTH-1):0] addr_b,
    input wire we_a
);

  reg [DATA_WIDTH_A-1:0] ram [2**ADDR_WIDTH-1:0];
 
    integer ram_index;
    generate
        if(FAST_DEBUG=="TRUE")begin
            always@(posedge clock_out)begin
                if(~reset)begin
                    $display("LOAD FCORE 2 PROGRAM FROM: %s", INIT_FILE);
                    $readmemh(INIT_FILE, ram);
                end
            end
        end else begin
            initial begin
                for (ram_index = 0; ram_index < 2**ADDR_WIDTH; ram_index = ram_index + 1)
                    ram[ram_index] = {DATA_WIDTH_A{1'b0}};
            end
        end
    endgenerate


    always @(posedge clock_in) begin
        if (we_a)
            ram[addr_a] <= data_a;
    end

    always @(posedge clock_out) begin
        data_b[31:0] <= ram[addr_b];
        data_b[63:32]<= ram[addr_b+1];
    end
    
endmodule