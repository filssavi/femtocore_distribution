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

module fCore_pipeline_tracker #(
    OPCODE_WIDTH = 4,
    REG_ADDR_WIDTH=4
) (
    input wire clock,
    input wire reset,
    input wire [REG_ADDR_WIDTH-1:0] op_dest,
    input wire [REG_ADDR_WIDTH-1:0] writeback_addr,
    input wire [REG_ADDR_WIDTH-1:0] operand_a,
    input wire [REG_ADDR_WIDTH-1:0] operand_b,
    input wire [REG_ADDR_WIDTH-1:0] operand_c
    
);

    bit [(1<<REG_ADDR_WIDTH)-1:0] dirty_registers = 0;


    always_ff@(posedge clock)begin
        dirty_registers[writeback_addr] <= 0;
        dirty_registers[op_dest] <= 1;
    end


endmodule