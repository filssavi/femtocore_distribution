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

module fCore_decoder #(
    parameter INSTRUCTION_WIDTH = 16,
    MAX_CHANNELS = 255,
    DATAPATH_WIDTH = 16,
    PC_WIDTH = 12, 
    OPCODE_WIDTH = 4,
    REG_ADDR_WIDTH=4,
    IMMEDIATE_WIDTH=12,
    CHANNEL_ADDR_WIDTH = 8
)(
    input wire clock,
    input wire reset,
    input wire enable,
    input wire [$clog2(MAX_CHANNELS)-1:0] n_channels,
    input wire [REG_ADDR_WIDTH-1:0] writeback_addr,
    input wire [INSTRUCTION_WIDTH-1:0] load_data,
    output reg [OPCODE_WIDTH-1:0] exec_opcode,
    output reg core_stop,
    axi_stream.slave instruction_stream,
    axi_stream.master operand_a_if,
    axi_stream.master operand_b_if,
    axi_stream.master operand_c_if,
    axi_stream.master operation_if
    );

    fcore_operations current_operation;

    wire [OPCODE_WIDTH-1:0] opcode;
    assign opcode = instruction_stream.data[OPCODE_WIDTH-1:0];

    wire [REG_ADDR_WIDTH-1:0] operand_a;
    assign operand_a = instruction_stream.data[OPCODE_WIDTH+REG_ADDR_WIDTH-1:OPCODE_WIDTH];

    wire [REG_ADDR_WIDTH-1:0] operand_b;
    assign operand_b = instruction_stream.data[OPCODE_WIDTH+2*REG_ADDR_WIDTH-1:OPCODE_WIDTH+REG_ADDR_WIDTH];

    wire [REG_ADDR_WIDTH-1:0] alu_dest;
    assign alu_dest = instruction_stream.data[OPCODE_WIDTH+3*REG_ADDR_WIDTH-1:OPCODE_WIDTH+2*REG_ADDR_WIDTH];

    wire [IMMEDIATE_WIDTH-1:0] load_reg_val;
    assign load_reg_val = instruction_stream.data[OPCODE_WIDTH+REG_ADDR_WIDTH+12:OPCODE_WIDTH+REG_ADDR_WIDTH];
                    
    wire [CHANNEL_ADDR_WIDTH-1:0] channel_address;
    assign channel_address = instruction_stream.dest;
    

    fCore_pipeline_tracker #(
        .OPCODE_WIDTH(OPCODE_WIDTH),
        .REG_ADDR_WIDTH(OPCODE_WIDTH)
    ) pipeline_tracker (
        .clock(clock),
        .reset(clock),
        .writeback_addr(writeback_addr),
        .op_dest(operand_a_if.user),
        .operand_a(operand_a_if.dest),
        .operand_b(operand_b_if.dest),
        .operand_c(operand_c_if.dest)
    );


    always@(posedge clock)begin
        core_stop <= 0;
        exec_opcode <= 0;
        operand_a_if.valid <= 0;
        operand_b_if.valid <= 0;
        operand_c_if.valid <= 0;
        operation_if.valid <= 0;
        if(enable)begin
            exec_opcode <= opcode;
            $cast(current_operation, opcode);
            case(opcode)
                fcore_isa::ADD: begin
                    operand_a_if.dest <= operand_a+(2**REG_ADDR_WIDTH*channel_address);
                    operand_a_if.user <= alu_dest+(2**REG_ADDR_WIDTH*channel_address);
                    operand_a_if.valid <= 1;
                    operand_b_if.dest <= operand_b+(2**REG_ADDR_WIDTH*channel_address);
                    operand_b_if.user <= alu_dest+(2**REG_ADDR_WIDTH*channel_address);
                    operand_b_if.valid <= 1;
                    operation_if.data <= 0;
                    operation_if.valid <= 1;
                end
                fcore_isa::SUB: begin
                    operand_a_if.dest <= operand_a+(2**REG_ADDR_WIDTH*channel_address);
                    operand_a_if.user <= alu_dest+(2**REG_ADDR_WIDTH*channel_address);
                    operand_a_if.valid <= 1;
                    operand_b_if.dest <= operand_b+(2**REG_ADDR_WIDTH*channel_address);
                    operand_b_if.user <= alu_dest+(2**REG_ADDR_WIDTH*channel_address);
                    operand_b_if.valid <= 1;
                    operation_if.data <= 1;
                    operation_if.valid <= 1;
                end
                fcore_isa::MUL: begin
                    operand_a_if.dest <= operand_a+(2**REG_ADDR_WIDTH*channel_address);
                    operand_a_if.user <= alu_dest+(2**REG_ADDR_WIDTH*channel_address);
                    operand_a_if.valid <= 1;
                    operand_b_if.dest <= operand_b+(2**REG_ADDR_WIDTH*channel_address);
                    operand_b_if.user <= alu_dest+(2**REG_ADDR_WIDTH*channel_address);
                    operand_b_if.valid <= 1;
                    operand_b_if.user <= operand_b+(2**REG_ADDR_WIDTH*channel_address);
                end
                fcore_isa::REC: begin
                    operand_a_if.dest <= operand_a+(2**REG_ADDR_WIDTH*channel_address);
                    operand_a_if.user <= operand_b+(2**REG_ADDR_WIDTH*channel_address);
                    operand_a_if.valid <= 1;
                end
                fcore_isa::FTI:begin
                    operand_b_if.dest <= operand_a+(2**REG_ADDR_WIDTH*channel_address);
                    operand_b_if.user <= operand_b+(2**REG_ADDR_WIDTH*channel_address);
                    operand_b_if.valid <= 1;
                end
                fcore_isa::ITF:begin
                    operand_a_if.dest <= operand_a+(2**REG_ADDR_WIDTH*channel_address);
                    operand_a_if.user <= operand_b+(2**REG_ADDR_WIDTH*channel_address);
                    operand_a_if.valid <= 1;
                end
                fcore_isa::LDC:begin
                    operand_a_if.dest <= load_data;
                    operand_a_if.user <= operand_a+(2**REG_ADDR_WIDTH*(channel_address));
                    operand_a_if.valid <= 1;
                end
                fcore_isa::LDR: begin
                    operand_a_if.dest <= load_reg_val;
                    operand_a_if.user <= operand_a+(2**REG_ADDR_WIDTH*channel_address);
                    operand_a_if.valid <= 1;
                end
                fcore_isa::BGT:begin
                    operand_a_if.dest <= operand_a+(2**REG_ADDR_WIDTH*channel_address);
                    operand_a_if.user <= alu_dest+(2**REG_ADDR_WIDTH*channel_address);
                    operand_a_if.valid <= 1;
                    operand_b_if.dest <= operand_b+(2**REG_ADDR_WIDTH*channel_address);
                    operand_b_if.user <= alu_dest+(2**REG_ADDR_WIDTH*channel_address);
                    operand_b_if.valid <= 1;
                    operation_if.data <= 'b100100;
                    operation_if.valid <= 1;
                end
                fcore_isa::BLE:begin
                    operand_a_if.dest <= operand_a+(2**REG_ADDR_WIDTH*channel_address);
                    operand_a_if.user <= alu_dest+(2**REG_ADDR_WIDTH*channel_address);
                    operand_a_if.valid <= 1;
                    operand_b_if.dest <= operand_b+(2**REG_ADDR_WIDTH*channel_address);
                    operand_b_if.user <= alu_dest+(2**REG_ADDR_WIDTH*channel_address);
                    operand_b_if.valid <= 1;
                    operation_if.data <= 'b011100;
                    operation_if.valid <= 1;
                end
                fcore_isa::BEQ:begin
                    operand_a_if.dest <= operand_a+(2**REG_ADDR_WIDTH*channel_address);
                    operand_a_if.user <= alu_dest+(2**REG_ADDR_WIDTH*channel_address);
                    operand_a_if.valid <= 1;
                    operand_b_if.dest <= operand_b+(2**REG_ADDR_WIDTH*channel_address);
                    operand_b_if.user <= alu_dest+(2**REG_ADDR_WIDTH*channel_address);
                    operand_b_if.valid <= 1;
                    operation_if.data <= 'b010100;
                    operation_if.valid <= 1;
                end
                fcore_isa::BNE:begin
                    operand_a_if.dest <= operand_a+(2**REG_ADDR_WIDTH*channel_address);
                    operand_a_if.user <= alu_dest+(2**REG_ADDR_WIDTH*channel_address);
                    operand_a_if.valid <= 1; 
                    operand_b_if.dest <= operand_b+(2**REG_ADDR_WIDTH*channel_address);
                    operand_b_if.user <= alu_dest+(2**REG_ADDR_WIDTH*channel_address);
                    operand_b_if.valid <= 1;
                    operation_if.data <= 'b101100;
                    operation_if.valid <= 1;
                end
                fcore_isa::POPCNT:begin
                    operand_a_if.dest <= operand_a+(2**REG_ADDR_WIDTH*channel_address);
                    operand_a_if.user <= operand_b+(2**REG_ADDR_WIDTH*channel_address);
                    operand_a_if.valid <= 1;
                    operation_if.data <= 3;
                    operation_if.valid <= 1;
                end
                fcore_isa::ABS:begin
                    operand_a_if.dest <= operand_a+(2**REG_ADDR_WIDTH*channel_address);
                    operand_a_if.user <= operand_b+(2**REG_ADDR_WIDTH*channel_address);
                    operand_a_if.valid <= 1;
                    operation_if.data <= 4;
                    operation_if.valid <= 1;
                end
                fcore_isa::LAND:begin
                    operand_a_if.dest <= operand_a+(2**REG_ADDR_WIDTH*channel_address);
                    operand_a_if.user <= alu_dest+(2**REG_ADDR_WIDTH*channel_address);
                    operand_a_if.valid <= 1;
                    operand_b_if.dest <= operand_b+(2**REG_ADDR_WIDTH*channel_address);
                    operand_b_if.user <= alu_dest+(2**REG_ADDR_WIDTH*channel_address);
                    operand_b_if.valid <= 1;
                    operation_if.data <= 0;
                    operation_if.valid <= 1;
                end
                fcore_isa::LOR:begin
                    operand_a_if.dest <= operand_a+(2**REG_ADDR_WIDTH*channel_address);
                    operand_a_if.user <= alu_dest+(2**REG_ADDR_WIDTH*channel_address);
                    operand_a_if.valid <= 1;
                    operand_b_if.dest <= 5;
                    operand_b_if.dest <= operand_b+(2**REG_ADDR_WIDTH*channel_address);
                    operand_b_if.user <= alu_dest+(2**REG_ADDR_WIDTH*channel_address);
                    operand_b_if.valid <= 1;
                    operation_if.data <= 1;
                    operation_if.valid <= 1;
                end
                fcore_isa::LXOR:begin
                    operand_a_if.dest <= operand_a+(2**REG_ADDR_WIDTH*channel_address);
                    operand_a_if.user <= alu_dest+(2**REG_ADDR_WIDTH*channel_address);
                    operand_a_if.valid <= 1;
                    operand_b_if.dest <= 5;
                    operand_b_if.dest <= operand_b+(2**REG_ADDR_WIDTH*channel_address);
                    operand_b_if.user <= alu_dest+(2**REG_ADDR_WIDTH*channel_address);
                    operand_b_if.valid <= 1;
                    operation_if.data <= 6;
                    operation_if.valid <= 1;
                end
                fcore_isa::BSET:begin
                    operand_a_if.dest <= operand_a+(2**REG_ADDR_WIDTH*channel_address);
                    operand_a_if.user <= operand_a+(2**REG_ADDR_WIDTH*channel_address);
                    operand_a_if.valid <= 1;
                    operand_b_if.dest <= operand_b+(2**REG_ADDR_WIDTH*channel_address);
                    operand_b_if.user <= operand_a+(2**REG_ADDR_WIDTH*channel_address);
                    operand_b_if.valid <= 1;
                    operand_c_if.dest <= alu_dest+(2**REG_ADDR_WIDTH*channel_address);
                    operand_c_if.valid <= 1;
                    operation_if.data <=  7;
                    operation_if.valid <= 1;
                end
                fcore_isa::BSEL:begin
                    operand_a_if.dest <= operand_a+(2**REG_ADDR_WIDTH*channel_address);
                    operand_a_if.user <= alu_dest+(2**REG_ADDR_WIDTH*channel_address);
                    operand_a_if.valid <= 1;
                    operand_b_if.dest <= operand_b+(2**REG_ADDR_WIDTH*channel_address);
                    operand_b_if.dest <= operand_b+(2**REG_ADDR_WIDTH*channel_address);
                    operand_b_if.user <= alu_dest+(2**REG_ADDR_WIDTH*channel_address);
                    operand_b_if.valid <= 1;
                    operation_if.data <= 5;
                    operation_if.valid <= 1;
                end
                fcore_isa::LNOT:begin
                    operand_a_if.dest <= operand_a+(2**REG_ADDR_WIDTH*channel_address);
                    operand_a_if.user <= operand_b+(2**REG_ADDR_WIDTH*channel_address);
                    operand_a_if.valid <= 1;
                    operation_if.data <= 2;
                    operation_if.valid <= 1;
                end
                fcore_isa::SATP:begin
                    operand_a_if.dest <= operand_a+(2**REG_ADDR_WIDTH*channel_address);
                    operand_a_if.user <= alu_dest+(2**REG_ADDR_WIDTH*channel_address);
                    operand_a_if.valid <= 1;
                    operand_b_if.dest <= operand_b+(2**REG_ADDR_WIDTH*channel_address);
                    operand_b_if.user <= alu_dest+(2**REG_ADDR_WIDTH*channel_address);
                    operand_b_if.valid <= 1;
                    operation_if.data <= 1;
                    operation_if.user <= alu_dest+(2**REG_ADDR_WIDTH*channel_address);
                    operation_if.valid <= 1;
                end
                fcore_isa::SATN:begin
                    operand_a_if.dest <= operand_a+(2**REG_ADDR_WIDTH*channel_address);
                    operand_a_if.user <= alu_dest+(2**REG_ADDR_WIDTH*channel_address);
                    operand_a_if.valid <= 1;
                    operand_b_if.dest <= operand_b+(2**REG_ADDR_WIDTH*channel_address);
                    operand_b_if.user <= alu_dest+(2**REG_ADDR_WIDTH*channel_address);
                    operand_b_if.valid <= 1;
                    operation_if.data <= 0;
                    operation_if.user <= alu_dest+(2**REG_ADDR_WIDTH*channel_address);
                    operation_if.valid <= 1;
                end
                fcore_isa::EFI:begin
                    operand_a_if.dest <= operand_b;
                    operand_a_if.user <= operand_a;
                    operand_b_if.dest <= alu_dest;
                end
                fcore_isa::STOP:begin
                    core_stop <= 1;
                end         
                fcore_isa::NOP: begin
                    operand_a_if.dest <= 0;
                    operand_a_if.user <= 0;
                    operand_a_if.valid <= 0;

                    operand_b_if.dest <= 0;
                    operand_b_if.user <= 0;
                    operand_b_if.valid <= 0;
                    
                    operand_c_if.dest <= 0;
                    operand_c_if.user <= 0;
                    operand_c_if.valid <= 0;
                    
                    operation_if.data <= 0;
                    operation_if.dest <= 0;
                    operation_if.valid <= 0;
                    operation_if.user <= 0;
                end
            endcase                        
        end else begin
            operand_a_if.dest <= 0;
            operand_a_if.user <= 0;
            operand_a_if.valid <= 0;
            
            operand_b_if.dest <= 0;
            operand_b_if.user <= 0;
            operand_b_if.valid <= 0;

            operand_c_if.dest <= 0;
            operand_c_if.user <= 0;
            operand_c_if.valid <= 0;

            operation_if.data <= 0;
            operation_if.dest <= 0;            
            operation_if.valid <= 0;
            operation_if.user <= 0;
        end
        
    end

    
endmodule
