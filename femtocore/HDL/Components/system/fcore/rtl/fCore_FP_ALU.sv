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

module fCore_FP_ALU #(
    parameter DATAPATH_WIDTH =32,
    PIPELINE_DEPTH=5,
    OPCODE_WIDTH=8, 
    REGISTER_ADDR_WIDTH = 8,
    RECIPROCAL_PRESENT=0,
    BITMANIP_IMPLEMENTED = 0,
    LOGIC_IMPLEMENTED = 0,
    FULL_COMPARE = 1
)(
    input wire clock,
    input wire reset,
    input wire [OPCODE_WIDTH-1:0] opcode,
    axi_stream.slave operand_a,
    axi_stream.slave operand_b,
    axi_stream.slave operand_c,
    axi_stream.slave operation,
    axi_stream.master result 
);

    localparam  PIPELINE_LENGTH = 5+3*RECIPROCAL_PRESENT;

    reg [OPCODE_WIDTH-1:0] result_select_dly[PIPELINE_LENGTH:0];

    wire [OPCODE_WIDTH-1:0] result_select;
    assign result_select = result_select_dly[PIPELINE_LENGTH];
    

    always@(posedge clock)begin

        result_select_dly[0][OPCODE_WIDTH-1:0] <= opcode;
        for(integer i =0 ; i<PIPELINE_LENGTH; i= i+1) begin
            result_select_dly[i+1][OPCODE_WIDTH-1:0] <= result_select_dly[i][OPCODE_WIDTH-1:0];
        end
    end

    
    axi_stream #(
        .USER_WIDTH(REGISTER_ADDR_WIDTH)
    ) add_result();
    
    axi_stream #(
        .USER_WIDTH(REGISTER_ADDR_WIDTH)
    ) reciprocal_result();

    axi_stream #(
        .USER_WIDTH(REGISTER_ADDR_WIDTH)
    ) mul_result();

    axi_stream #(
        .USER_WIDTH(REGISTER_ADDR_WIDTH)
    ) fti_result();

    axi_stream #(
        .USER_WIDTH(REGISTER_ADDR_WIDTH)
    ) itf_result();

    axi_stream #(
        .USER_WIDTH(REGISTER_ADDR_WIDTH)
    ) logic_result();
 
    axi_stream #(
        .USER_WIDTH(REGISTER_ADDR_WIDTH)
    ) comparison_result();

    axi_stream #(
        .USER_WIDTH(REGISTER_ADDR_WIDTH)
    ) early_logic_result();

    axi_stream #(
        .USER_WIDTH(REGISTER_ADDR_WIDTH)
    ) saturation_result();


    axi_stream #(
        .USER_WIDTH(REGISTER_ADDR_WIDTH)
    ) ldr_operand_a();

    axi_stream #(
        .USER_WIDTH(REGISTER_ADDR_WIDTH)
    ) ldc_adj_a();

    axi_stream #(
        .USER_WIDTH(REGISTER_ADDR_WIDTH)
    ) ldc_operand_a();

    axi_stream #(
        .USER_WIDTH(REGISTER_ADDR_WIDTH)
    ) early_bitmanip_result();

    axi_stream #(
        .USER_WIDTH(REGISTER_ADDR_WIDTH)
    ) bitmanip_result();

    axi_stream #(
        .USER_WIDTH(REGISTER_ADDR_WIDTH)
    ) abs_result();
 
    axi_stream #(
        .USER_WIDTH(REGISTER_ADDR_WIDTH)
    ) early_abs_result();

    generate 
        if(RECIPROCAL_PRESENT==1)begin

        div_alu_wrapper div_alu (
            .clock(clock),
            .reset(reset),
            .operand_a(operand_a),
            .operand_b(operand_b),
            .operation(operation),
            .add_result(add_result),
            .fti_result(fti_result),
            .itf_result(itf_result),
            .mul_result(mul_result),
            .reciprocal_result(reciprocal_result)
        );


        end else begin

            simple_alu_wrapper #(
                .REGISTER_ADDR_WIDTH(REGISTER_ADDR_WIDTH)
            ) simple_alu (
                .clock(clock),
                .reset(reset),
                .operand_a(operand_a),
                .operand_b(operand_b),
                .operation(operation),
                .add_result(add_result),
                .fti_result(fti_result),
                .itf_result(itf_result),
                .mul_result(mul_result)
            );    
        end
        
    endgenerate  

    always_comb begin

        case (result_select)
            fcore_isa::ADD,
            fcore_isa::SUB: begin
                result.data <= add_result.data;
                result.dest <= add_result.user;
                result.valid <= 1;
            end
            fcore_isa::MUL:begin
                result.data <= mul_result.data;
                result.dest <= mul_result.user;
                result.valid <= 1;          
            end
            fcore_isa::REC:begin
                result.data <= reciprocal_result.data;
                result.dest <= reciprocal_result.user;
                result.valid <= 1;       
            end
            fcore_isa::LDR:begin
                result.data <= ldr_operand_a.dest;
                result.dest <= ldr_operand_a.user;
                result.valid <= 1;     
            end
            fcore_isa::LDC:begin
                result.data <= ldc_operand_a.dest;
                result.dest <= ldc_operand_a.user;
                result.valid <= 1;
            end
            fcore_isa::BGT,
            fcore_isa::BLE,
            fcore_isa::BEQ,
            fcore_isa::BNE: begin
                result.data <= comparison_result.data;
                result.dest <= comparison_result.user;
                result.valid <= 1;
            end
            fcore_isa::FTI:begin
                result.data <= fti_result.data;
                result.dest <= fti_result.user;
                result.valid <= 1;
            end
            fcore_isa::ITF: begin
                result.data <= itf_result.data;
                result.dest <= itf_result.user;
                result.valid <= 1;
            end
            fcore_isa::ABS:begin
                result.data <= abs_result.data;
                result.dest <= abs_result.user;
                result.valid <= 1;
            end                
            fcore_isa::LAND,
            fcore_isa::LOR,
            fcore_isa::LXOR,
            fcore_isa::LNOT:begin
                result.data <= logic_result.data;
                result.dest <= logic_result.user;
                result.valid <= 1;
            end
            fcore_isa::POPCNT,
            fcore_isa::BSET,
            fcore_isa::BSEL:begin
                result.data <= bitmanip_result.data;
                result.dest <= bitmanip_result.user;
                result.valid <= 1;
            end
            fcore_isa::SATN,
            fcore_isa::SATP:begin
                result.data <= saturation_result.data;
                result.dest <= saturation_result.user;
                result.valid <= 1;
            end
            default: begin
                result.data <= 0;
                result.dest <= 0;
                result.valid <= 0;
            end
        endcase
    end


    ////////////////////////////////////////////////
    //                    LOGIC                   //
    ////////////////////////////////////////////////
    
    always@(posedge clock) begin
        early_abs_result.valid <= 0;
        early_abs_result.user <= 0;
        early_abs_result.data <= 0;
        if(operand_a.valid)begin
            case(operation.data)
                4:begin
                    early_abs_result.valid <= 1;
                    early_abs_result.user <= operand_a.user;
                    early_abs_result.data <= {0, operand_a.data[30:0]};  
                end
            endcase
        end
    end

   register_slice #(
        .DATA_WIDTH(32),
        .DEST_WIDTH(32),
        .USER_WIDTH(32),
        .N_STAGES(PIPELINE_DEPTH-1),
        .READY_REG(0)
   ) abs_pipeline_adapter (
        .clock(clock),
        .reset(reset),
        .in(early_abs_result),
        .out(abs_result)
    );

    ////////////////////////////////////////////////
    //                   LOGIC                    //
    ////////////////////////////////////////////////
    generate
        if(LOGIC_IMPLEMENTED==1)begin
            fCore_logic_unit logic_engine (
                .clock(clock),
                .reset(reset),
                .operand_a(operand_a),
                .operand_b(operand_b),
                .operand_c(operand_c),
                .operation(operation),
                .result(early_logic_result) 
            );


            register_slice #(
                .DATA_WIDTH(32),
                .DEST_WIDTH(32),
                .USER_WIDTH(32),
                .N_STAGES(PIPELINE_DEPTH-1),
                .READY_REG(0)
            ) logic_pipeline_adapter (
                .clock(clock),
                .reset(reset),
                .in(early_logic_result),
                .out(logic_result)
            );
        end
    endgenerate
    ////////////////////////////////////////////////
    //                  BITMANIP                  //
    ////////////////////////////////////////////////
    
    generate
        if(BITMANIP_IMPLEMENTED==1)begin
            fCore_bitmanip_unit #(
                .PIPELINE_DEPTH(PIPELINE_DEPTH)
            ) bitmanip_engine (
                .clock(clock),
                .reset(reset),
                .operand_a(operand_a),
                .operand_b(operand_b),
                .operand_c(operand_c),
                .operation(operation),
                .result(bitmanip_result) 
            );
        end
    endgenerate


    ////////////////////////////////////////////////
    //                  SATURATION                //
    ////////////////////////////////////////////////

    FP_saturator #(
        .DATA_WIDTH(32),
        .REG_ADDR_WIDTH(REGISTER_ADDR_WIDTH),
        .PIPELINE_DEPTH(PIPELINE_DEPTH),
        .SELCTION_DEST(0)
    ) saturator(
        .clock(clock),
        .reset(reset),
        .operand_a(operand_a.data),
        .operand_b(operand_b.data),
        .operation(operation),
        .result(saturation_result)
    );

    ////////////////////////////////////////////////
    //                  COMPARISON                //
    ////////////////////////////////////////////////

    fCore_compare_unit #(
        .FULL_COMPARE(FULL_COMPARE),
        .PIPELINE_DEPTH(PIPELINE_DEPTH)
    )compare_unit(
        .clock(clock),
        .reset(reset),
        .operand_a(operand_a),
        .operand_b(operand_b),
        .operand_c(operand_c),
        .operation(operation),
        .result(comparison_result)
    );

    ////////////////////////////////////////////////
    //                    LDC/LDR                 //
    ////////////////////////////////////////////////


    register_slice #(
        .DATA_WIDTH(32),
        .DEST_WIDTH(32),
        .USER_WIDTH(32),
        .N_STAGES(PIPELINE_DEPTH),
        .READY_REG(0)
    ) load_register_pipeline (
        .clock(clock),
        .reset(reset),
        .in(operand_a),
        .out(ldr_operand_a)
    );




    assign ldc_adj_a.valid = operand_a.valid;
    assign ldc_adj_a.dest = operand_a.dest;
    always_ff@(posedge clock)begin
        ldc_adj_a.user <= operand_a.user;
    end

    register_slice #(
        .DATA_WIDTH(32),
        .DEST_WIDTH(32),
        .USER_WIDTH(32),
        .N_STAGES(PIPELINE_DEPTH-2),
        .READY_REG(0)
    ) load_constant_pipeline (
        .clock(clock),
        .reset(reset),
        .in(ldc_adj_a),
        .out(ldc_operand_a)
    );

endmodule