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


module merger_control_unit #(
    parameter MAX_SORT_LENGTH=32,
    parameter BASE_CHUNK_SIZE=8
)(
    input wire clock,
    input wire [$clog2(BASE_CHUNK_SIZE)-1:0] last_chunk_size,
    input wire [$clog2(MAX_SORT_LENGTH/8-1):0] n_chunks_in,
    input wire merge_done,
    input wire data_in_valid,
    input wire registered_in_valid,
    output reg output_selector,
    output reg select_merge_bypass,
    output reg core_start,
    output reg [15:0] input_chunk_size,
    output reg [15:0] result_size
);
    

    reg [2:0] start_merging_pipe;


    reg[15:0] chunks_to_merge  = 0;

    enum logic [2:0] {
        fsm_idle = 0,
        fsm_bypass = 1,
        fsm_merging = 2,
        fsm_update_sizes = 3,
        fsm_done = 4
    } fsm_merger = fsm_idle;

    reg [2:0] bypass_load_ctr;

    always_ff @(posedge clock)begin
        case(fsm_merger)
        fsm_idle:begin
            bypass_load_ctr <=1;
            output_selector <= 0;
            select_merge_bypass <= 1;
            start_merging_pipe[0] <= data_in_valid;
            start_merging_pipe[1] <= start_merging_pipe[0];
            start_merging_pipe[2] <= start_merging_pipe[1];
            core_start <= 0;
            if(registered_in_valid & start_merging_pipe[2])begin
                input_chunk_size <= 8;
                result_size <= 8;
                fsm_merger <= fsm_bypass;
                if(last_chunk_size != 0)begin
                        if(n_chunks_in == 1) begin
                            input_chunk_size <= last_chunk_size;
                        end else if (n_chunks_in == 0) begin
                            input_chunk_size <= last_chunk_size;
                            result_size <= last_chunk_size;
                        end
                    chunks_to_merge <= n_chunks_in;
                end else begin
                    chunks_to_merge <= n_chunks_in-1;
                end
            end
        end
        fsm_bypass:begin
            if(bypass_load_ctr == 7)begin 
                select_merge_bypass <= 0;
                core_start <= 1;
                fsm_merger <= fsm_merging;
            end else begin
                bypass_load_ctr <= bypass_load_ctr + 1;
            end
        end
        fsm_merging:begin
            core_start <= 0;
            if(chunks_to_merge == 1)begin
                output_selector <= 1;
            end
            if(merge_done) begin
                fsm_merger <= fsm_update_sizes;
                chunks_to_merge <= chunks_to_merge-1;
            end  
        end
        fsm_update_sizes:begin
            if(chunks_to_merge == 1) begin
                if(last_chunk_size != 0)begin
                    input_chunk_size <= last_chunk_size;
                end
            end
            result_size <= result_size + BASE_CHUNK_SIZE;
            

            if(chunks_to_merge == 0)begin
                fsm_merger <= fsm_idle;
            end else begin
                core_start <= 1;
                fsm_merger <= fsm_merging;
            end
        end
        endcase
    end


endmodule