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

module fCore_ALU #(OPCODE_WIDTH = 5, DATA_WIDTH = 32, REG_ADDR_WIDTH = 4) (
    input wire clock,
    input wire reset,
    input wire [DATA_WIDTH-1:0] op_a,
    input wire [DATA_WIDTH-1:0] op_b,
    input wire [REG_ADDR_WIDTH-1:0] dest_in,
    input wire [OPCODE_WIDTH-1:0] opcode,
    input wire alu_exec,
    output reg [2*DATA_WIDTH-1:0] result,
    output reg [REG_ADDR_WIDTH-1:0] dest_out,
    output reg result_valid,
    output reg core_stall
);
    
    typedef enum reg [OPCODE_WIDTH-1:0] { ADD = 1,
                                          SUB = 2,
                                          MUL = 3,
                                          MAC = 4,
                                          SHL = 5,
                                          SHR = 6,
                                          SAL = 7,
                                          SAR = 8,
                                          MULSR = 9,
                                          MACSR = 10,
                                          BGT = 12,
                                          BLE = 13,
                                          BEQ = 14,
                                          BNE = 15
                                          } operands;


    enum reg [1:0] { REGISTER_IN  = 0,
                     EXEC = 1,
                     REGISTER_OUT = 2
                    } state = REGISTER_IN;


    wire [2*DATA_WIDTH-1:0] result_test;
    assign result_test  = (op_a * op_b) >> 16;
    reg [DATA_WIDTH-1:0] op_a_reg;
    reg [DATA_WIDTH-1:0] op_b_reg;
    reg [DATA_WIDTH-1:0] opcode_reg;
    reg [2*DATA_WIDTH-1:0] out_reg; 
    reg [REG_ADDR_WIDTH-1:0] internal_dest;
    reg [REG_ADDR_WIDTH-1:0] registered_dest;
    always@(posedge clock)begin
        core_stall <= 0;
        result_valid <= 0;
        internal_dest <= dest_in;
        case(state)
            REGISTER_IN:begin
                if(alu_exec)begin
                    result_valid<=1;           
                    dest_out <= internal_dest;
                    case(opcode)
                        ADD:
                            result <= op_a + op_b;
                        SUB:
                            result <= op_a - op_b;
                        MUL:begin
                            result <= op_a * op_b;
                            /*
                            op_a_reg <= op_a;
                            op_b_reg <= op_b;
                            core_stall <= 1;
                            registered_dest <= internal_dest;
                            result_valid<=0;
                            state <= EXEC;
                            opcode_reg <= opcode;
                            */
                        end
                        MAC:begin
                            result <= op_a + (op_a * op_b);
                            /*
                            op_a_reg <= op_a;
                            op_b_reg <= op_b;
                            core_stall <= 1;
                            result_valid<=0;
                            registered_dest <= internal_dest;
                            state <= EXEC;
                            opcode_reg <= opcode;*/
                        end
                        SHL:
                            result <= op_a << op_b;
                        SHR:
                            result <= op_a >> op_b;
                        SAL:
                            result <= $signed(op_a) <<< op_b;
                        SAR:
                            result <= $signed(op_a) >>> op_b;
                        BGT:
                            result <= op_a > op_b;
                        BLE:    
                            result <= op_a <= op_b;
                        BEQ:
                            result <= op_a == op_b;
                        BNE:
                            result <= op_a != op_b;
                        MULSR:
                            result <= (op_a * op_b) >> 16;
                        MACSR:
                            result <= op_a + (op_a * op_b) >> 16;
                        default: begin
                            result <= 0;
                        end
                    endcase
                end else begin
                    dest_out <= dest_in;
                    result_valid<=0;
                    result <= 0;
                end
            end
            EXEC:begin
                if(opcode_reg == MAC)begin
                    out_reg <= op_a_reg + (op_a_reg * op_b_reg);
                end else if (opcode_reg == MUL) begin
                    out_reg <= op_a_reg * op_b_reg;
                end
                state <= REGISTER_OUT;
            end
            REGISTER_OUT:begin
                state <= REGISTER_IN;
                result <= out_reg;
                dest_out <= registered_dest;
                result_valid<=1;
                core_stall <= 0;
            end
        endcase

    end




    
endmodule
