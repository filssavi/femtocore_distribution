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

module FP_saturator #(
    DATA_WIDTH = 32,
    REG_ADDR_WIDTH = 4,
    SELCTION_DEST = 6,
    PIPELINE_DEPTH = 5
    ) (
    input wire clock,
    input wire reset,
    input wire [DATA_WIDTH-1:0] operand_a,
    input wire [DATA_WIDTH-1:0] operand_b,
    axi_stream.slave operation,
    axi_stream.master result
);

    axi_stream #(
        .USER_WIDTH(REG_ADDR_WIDTH)
    ) early_saturation_result();

    register_slice #(
        .DATA_WIDTH(32),
        .DEST_WIDTH(32),
        .USER_WIDTH(32),
        .N_STAGES(PIPELINE_DEPTH-2),
        .READY_REG(0)
    ) sat_pipeline_adapter (
        .clock(clock),
        .reset(reset),
        .in(early_saturation_result),
        .out(result)
    );

    reg [REG_ADDR_WIDTH-1:0] destination;
    reg compare_result, saturation_mode, saturation_in_progress, negative_compare;

    reg [DATA_WIDTH-1:0] op_a_pipeline;
    reg [DATA_WIDTH-1:0] op_b_pipeline; 
    always_ff@(posedge clock)begin
        if(~reset)begin
            destination <= 0;
            early_saturation_result.dest <= 0;
            early_saturation_result.valid <= 0;
            early_saturation_result.data <= 0;
            early_saturation_result.user <= 0;
            saturation_mode <= 0;
            compare_result <= 0;
            op_a_pipeline <= 0;
            op_b_pipeline <= 0;
            negative_compare <= 0;
        end else begin
            early_saturation_result.valid <= 0;
            saturation_in_progress <= 0;
            if(operation.valid & operation.dest == SELCTION_DEST) begin
                destination <= operation.user;
                saturation_in_progress <= 1;
                saturation_mode <= operation.data;
                op_a_pipeline <= operand_a;
                op_b_pipeline <= operand_b;
                compare_result <= $signed(operand_a) > $signed(operand_b);
                negative_compare <= operand_a[DATA_WIDTH-1] & operand_b[DATA_WIDTH-1];
            end
            if(saturation_in_progress)begin
                if(saturation_mode)begin
                    if(negative_compare)begin
                        if(compare_result)begin
                            early_saturation_result.data <= op_a_pipeline; 
                        end else begin
                            early_saturation_result.data <= op_b_pipeline; 
                        end                    
                    end else begin
                        if(compare_result)begin
                            early_saturation_result.data <= op_b_pipeline; 
                        end else begin
                            early_saturation_result.data <= op_a_pipeline; 
                        end  
                    end
                    early_saturation_result.user <= destination;
                    early_saturation_result.valid <= 1;
                end else begin
                    if(negative_compare)begin
                        if(compare_result)begin
                            early_saturation_result.data <= op_b_pipeline;
                        end else begin
                            early_saturation_result.data <= op_a_pipeline;
                        end    
                    end else begin
                        if(compare_result)begin
                            early_saturation_result.data <= op_a_pipeline;
                        end else begin
                            early_saturation_result.data <= op_b_pipeline;
                        end
                    end
                    early_saturation_result.user <= destination;
                    early_saturation_result.valid <= 1;
                end
            end else begin
                early_saturation_result.valid <= 0;
            end
        end   
    end
        
endmodule
