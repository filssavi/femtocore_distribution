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

module fCore_bitmanip_unit #(
    PIPELINE_DEPTH=5
)(
    input wire clock,
    input wire reset,
    axi_stream.slave operand_a,
    axi_stream.slave operand_b,
    axi_stream.slave operand_c,
    axi_stream.slave operation,
    axi_stream.master result 
);

    axi_stream bitmanip_result();
    axi_stream popcount_result();

    assign result.data = bitmanip_result.data | popcount_result.data;
    assign result.dest = bitmanip_result.dest | popcount_result.dest;
    assign result.user = bitmanip_result.user | popcount_result.user;
    assign result.valid = bitmanip_result.valid | popcount_result.valid;
    assign result.tlast = bitmanip_result.tlast | popcount_result.tlast;
    assign bitmanip_result.ready = result.ready;
    assign popcount_result.ready = result.ready;

    axi_stream early_bitmanip_result();
    register_slice #(
        .DATA_WIDTH(32),
        .DEST_WIDTH(32),
        .USER_WIDTH(32),
        .N_STAGES(PIPELINE_DEPTH-1),
        .READY_REG(0)
    ) bitmanip_pipeline_adapter (
        .clock(clock),
        .reset(reset),
        .in(early_bitmanip_result),
        .out(bitmanip_result)
    );

    axi_stream early_popcount_result();
    register_slice #(
        .DATA_WIDTH(32),
        .DEST_WIDTH(32),
        .USER_WIDTH(32),
        .N_STAGES(PIPELINE_DEPTH-2),
        .READY_REG(0)
    ) popcount_pipeline_adapter (
        .clock(clock),
        .reset(reset),
        .in(early_popcount_result),
        .out(popcount_result)
    );
    
    wire [15:0] popcount_in_partition_0;
    wire [15:0] popcount_in_partition_1;
    assign popcount_in_partition_0 = operand_a.data[15:0];
    assign popcount_in_partition_1 = operand_a.data[31:16];

    reg [5:0] popcount_partials [1:0];

    reg [31:0] popcount_user;

    always_ff @(posedge clock) begin
        early_bitmanip_result.valid <= 0;
        early_bitmanip_result.user <= 0;
        early_bitmanip_result.data <= 0;
        early_popcount_result.valid <= 0;
        early_popcount_result.user <= 0;
        early_popcount_result.data <= 0;
        if(operand_a.valid)begin
            case(operation.data)
                3:begin
                    popcount_partials[0] <= popcount_in_partition_0[0] + popcount_in_partition_0[1] + popcount_in_partition_0[2] + popcount_in_partition_0[3] + popcount_in_partition_0[4] + popcount_in_partition_0[4] + popcount_in_partition_0[5] + popcount_in_partition_0[6] + popcount_in_partition_0[7] + popcount_in_partition_0[8] + popcount_in_partition_0[9] + popcount_in_partition_0[10] + popcount_in_partition_0[11] + popcount_in_partition_0[12] + popcount_in_partition_0[13] + popcount_in_partition_0[14] + popcount_in_partition_0[15];
                    popcount_partials[1] <= popcount_in_partition_1[0] + popcount_in_partition_1[1] + popcount_in_partition_1[2] + popcount_in_partition_1[3] + popcount_in_partition_1[4] + popcount_in_partition_1[4] + popcount_in_partition_1[5] + popcount_in_partition_1[6] + popcount_in_partition_1[7] + popcount_in_partition_1[8] + popcount_in_partition_1[9] + popcount_in_partition_1[10] + popcount_in_partition_1[11] + popcount_in_partition_1[12] + popcount_in_partition_1[13] + popcount_in_partition_1[14] + popcount_in_partition_1[15];
                    popcount_user <= operand_a.user;
                    early_popcount_result.data <= popcount_partials[0] + popcount_partials[1];
                    early_popcount_result.valid <= 1;
                    early_popcount_result.user <= popcount_user;
                end
                5:begin
                    early_bitmanip_result.valid <= 1;
                    early_bitmanip_result.user <= operand_a.user;
                    early_bitmanip_result.data <= operand_a.data[31:0];
                    early_bitmanip_result.data <= operand_a.data[operand_b.data];  
                end
                7:begin
                    early_bitmanip_result.valid <= 1;
                    early_bitmanip_result.user <= operand_a.user;
                    early_bitmanip_result.data <= operand_a.data[31:0];
                    early_bitmanip_result.data[operand_b.data] <= operand_c.data;
                end
            endcase
        end
    end

endmodule