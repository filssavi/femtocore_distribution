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

module TauControlUnit #(parameter BASE_ADDRESS = 'h43c00000)(
    input wire     clock,
    input wire     reset,
    axi_lite.slave axi_in,
    output reg     disable_direct_chain_mode,
    output reg     disable_inverse_chain_mode,
    output reg     soft_reset
);


    reg [31:0] cu_write_registers [8:0];
    reg [31:0] cu_read_registers [8:0];

    axil_simple_register_cu #(
        .N_READ_REGISTERS(9),
        .N_WRITE_REGISTERS(9),
        .REGISTERS_WIDTH(32),
        .ADDRESS_MASK('hf)
    ) CU (
        .clock(clock),
        .reset(reset),
        .input_registers(cu_read_registers),
        .output_registers(cu_write_registers),
        .axil(axi_in)
    );

    assign disable_direct_chain_mode = cu_write_registers[0][0];
    assign disable_inverse_chain_mode = cu_write_registers[0][1];
    assign soft_reset =  cu_write_registers[0][2];

    assign cu_read_registers[0] = cu_write_registers[0];

endmodule