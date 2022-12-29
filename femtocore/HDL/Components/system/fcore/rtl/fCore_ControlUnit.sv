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

module fCore_ControlUnit #(
    parameter PC_WIDTH = 12,
    OPCODE_WIDTH = 5,
    MAX_CHANNELS = 255,
    INSTRUCTION_WIDTH=32,
    EFI_IMPLEMENTED = 0
)(
    input wire clock,
    input wire reset,
    input wire run,
    input wire efi_done,
    input wire [15:0] program_size,
    output reg efi_start,
    input wire core_stop,
    input wire [2*INSTRUCTION_WIDTH-1:0] wide_instruction_in,
    input wire [$clog2(MAX_CHANNELS)-1:0] n_channels,
    output reg [PC_WIDTH-1: 0] program_counter,
    output reg [INSTRUCTION_WIDTH-1:0] load_data,
    output reg decoder_enable,
    output reg dma_enable,
    output reg done,
    output reg fault,
    axi_stream.master instruction_stream
    );

    reg [$clog2(MAX_CHANNELS)-1:0] channel_counter;

    reg [$clog2(MAX_CHANNELS)-1:0] ch_addr;
    reg load_blanking = 0;

    reg [INSTRUCTION_WIDTH-1:0] load_instr;

    wire [OPCODE_WIDTH-1:0] opcode;
    assign opcode = wide_instruction_in[OPCODE_WIDTH-1:0];


    wire [INSTRUCTION_WIDTH-1:0] instr_1;
    assign instr_1 = wide_instruction_in[INSTRUCTION_WIDTH-1:0];

    wire [INSTRUCTION_WIDTH-1:0] instr_2;
    assign instr_2 = wide_instruction_in[2*INSTRUCTION_WIDTH-1:INSTRUCTION_WIDTH];

    wire [OPCODE_WIDTH-1:0] next_opcode;
    assign next_opcode = instr_2[OPCODE_WIDTH-1:0];

    always@(posedge clock)begin
        ch_addr <= channel_counter;
    end

    enum reg [2:0] {IDLE = 3'b000,
                    PREFETCH = 3'b001,
                    RUN = 3'b010,
                    EFI_CALL = 3'b011,
                    FAULT = 3'b100
                    } state = IDLE;

    always@(posedge clock)begin
        case(state)
            IDLE:begin
                load_blanking <= 0;
                program_counter <= 0;
                channel_counter <= 0;
                decoder_enable <= 0;
                efi_start <= 0;
                done <= 0;
                dma_enable <= 1;
                if(run) begin
                    dma_enable <= 0;
                    state <= RUN;
                end
            end
            PREFETCH:begin
                state <= RUN;
                decoder_enable <= 1;
                dma_enable <= 0;
                program_counter <= program_counter+1;
            end
            RUN:begin
                dma_enable <= 0;
                decoder_enable <= 1;
                if(opcode == fcore_isa::EFI & EFI_IMPLEMENTED==1)begin
                    state <= EFI_CALL;
                    efi_start <= 1;
                end else if((channel_counter == n_channels-1) | (opcode == fcore_isa::LDC) & ~load_blanking)begin
                    program_counter <= program_counter+1;
                    channel_counter <= 0;
                end else begin
                    channel_counter <= channel_counter+1;
                end
                if(channel_counter>program_size-1)begin
                    state <= FAULT;
                end
                if(core_stop)begin
                    done <= 1;
                    state <= IDLE;
                end
            end
            EFI_CALL:begin
                efi_start <= 0;
                if(efi_done)begin
                    if((channel_counter == n_channels-1) | (opcode == fcore_isa::LDC) & ~load_blanking)begin
                        program_counter <= program_counter+1;
                        channel_counter <= 0;
                    end else begin
                        channel_counter <= channel_counter+1;
                    end
                    state <= RUN;
                end
            end
        endcase

        if(state==RUN)begin
             
            if(load_blanking)begin
                instruction_stream.data <= load_instr;
            end else if(opcode == fcore_isa::LDC)begin
                load_blanking <= 1;
                load_instr <= instr_1;
                instruction_stream.data <= instr_1;
                load_data <= instr_2;
            end else if(~load_blanking)begin
                instruction_stream.data <= instr_1;
            end 
            if(load_blanking & ch_addr==n_channels-1) begin
                load_blanking <= 0;            
            end
            instruction_stream.dest <= ch_addr;
            instruction_stream.user <= program_counter;
        end
    end

    
endmodule
