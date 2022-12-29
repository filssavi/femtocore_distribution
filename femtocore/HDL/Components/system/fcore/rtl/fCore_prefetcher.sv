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
import fcore_isa::*;

module fCore_prefetcher #(parameter INSTRUCTION_WIDTH = 16, OPCODE_WIDTH = 5, MAX_CHANNELS = 255)(
    input wire clock,
    input wire reset,
    input wire run,
    input wire [2*INSTRUCTION_WIDTH-1:0] instruction_in,
    input wire [$clog2(MAX_CHANNELS)-1:0] channel_address_in,
    input wire [$clog2(MAX_CHANNELS)-1:0] n_channels,
    output reg [INSTRUCTION_WIDTH-1:0] instruction_out,
    output reg [INSTRUCTION_WIDTH-1:0] load_data,
    output reg [$clog2(MAX_CHANNELS)-1:0] channel_address_out,
    output wire immediate_advance,
    output wire efi_call
    );

    reg load_blanking = 0;

    wire [OPCODE_WIDTH-1:0] opcode;
    assign opcode = instruction_in[OPCODE_WIDTH-1:0];


    wire [INSTRUCTION_WIDTH-1:0] instr_1;
    assign instr_1 = instruction_in[INSTRUCTION_WIDTH-1:0];

    wire [INSTRUCTION_WIDTH-1:0] instr_2;
    assign instr_2 = instruction_in[2*INSTRUCTION_WIDTH-1:INSTRUCTION_WIDTH];

    assign immediate_advance = (opcode == fcore_isa::LDC) & ~load_blanking;

    assign efi_call = opcode == fcore_isa::EFI;

    always_ff@(posedge clock)begin
        if(run)begin
            load_blanking <= 0;
        end
        if(opcode == fcore_isa::LDC)begin
            load_blanking <= 1;
            instruction_out <= instr_1;
            load_data <= instr_2;
        end else if(~load_blanking)begin
            instruction_out <= instr_1;
        end
        if(load_blanking & channel_address_in==n_channels-1) begin
            load_blanking <= 0;  
            instruction_out <= instr_1;              
        end
        channel_address_out <= channel_address_in;
    end



endmodule
