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

`timescale 10ns / 1ns
`include "interfaces.svh"
import fcore_isa::*;

module fCore_compare_unit #(
    FULL_COMPARE = 0,
    PIPELINE_DEPTH = 5
)(
    input wire clock,
    input wire reset,
    axi_stream.slave operand_a,
    axi_stream.slave operand_b,
    axi_stream.slave operand_c,
    axi_stream.slave operation,
    axi_stream.master result 
);



    axi_stream early_compare_result();

    register_slice #(
        .DATA_WIDTH(32),
        .DEST_WIDTH(32),
        .USER_WIDTH(32),
        .N_STAGES(PIPELINE_DEPTH-1),
        .READY_REG(0)
    ) compare_pipeline_adapter (
        .clock(clock),
        .reset(reset),
        .in(early_compare_result),
        .out(result)
    );

    wire [31:0] comparison_result;
    generate 
        if(FULL_COMPARE)begin
            assign comparison_result = {32{1'b1}};
        end else begin
            assign comparison_result = 1;
        end
    endgenerate

    

    always@(posedge clock) begin
        early_compare_result.valid <= 0;
        early_compare_result.user <= 0;
        early_compare_result.data <= 0;
        if(operand_a.valid)begin
            case(operation.data)
                'b100100:begin
                    if($signed(operand_a.data) > $signed(operand_b.data)) begin
                        early_compare_result.data <= comparison_result;
                    end else begin
                        early_compare_result.data <= 0;
                    end
                    early_compare_result.user <= operand_a.user;
                    early_compare_result.valid <= 1;                 
                end
                'b011100:begin
                    if($signed(operand_a.data) <= $signed(operand_b.data)) begin
                        early_compare_result.data <= comparison_result;
                    end else begin
                        early_compare_result.data <= 0;
                    end
                    early_compare_result.user <= operand_a.user;
                    early_compare_result.valid <= 1;
                end
            endcase
        end
    end


endmodule