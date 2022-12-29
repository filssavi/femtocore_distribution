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

module merging_core #(
    parameter DATA_WIDTH=32,
    parameter DEST_WIDTH=32,
    parameter USER_WIDTH=32,
    parameter MAX_SORT_LENGTH=32
)(
    input wire clock,
    input wire [$clog2(MAX_SORT_LENGTH)-1:0] chunk_a_size,
    input wire [$clog2(MAX_SORT_LENGTH)-1:0] chunk_b_size,
    input wire start,
    axi_stream.slave stream_in_a,
    axi_stream.slave stream_in_b,
    axi_stream.master merged_stream,
    output reg merge_done
);

    reg merge_in_progress = 0;

    reg [$clog2(MAX_SORT_LENGTH)-1:0] chunk_a_counter = 0;
    reg [$clog2(MAX_SORT_LENGTH)-1:0] chunk_b_counter = 0;

    enum logic [2:0] {
        fsm_idle = 0,
        //fsm_start_merge = 1,
        fsm_merging_ab = 2,
        fsm_merging_a = 3,
        fsm_merging_b = 4
    } core_fsm = fsm_idle;


    always_ff @(posedge clock) begin
        case(core_fsm)
        fsm_idle:begin
            merge_done <= 0;
            merged_stream.tlast <= 0;
            chunk_a_counter <= 0;
            chunk_b_counter <= 0;
            if(start) begin
                if(chunk_a_size == 0)begin
                    core_fsm <= fsm_merging_b;
                end else if(chunk_b_size == 0)begin
                    core_fsm <= fsm_merging_a;
                end else begin
                    core_fsm <= fsm_merging_ab;
                end
                
            end
        end
        fsm_merging_ab:begin
            
            if(stream_in_a.data > stream_in_b.data) begin
                chunk_b_counter += 1;
            end else begin
                chunk_a_counter += 1;
            end 

            if(chunk_a_counter == chunk_a_size)begin
                core_fsm <= fsm_merging_b;
            end
            if(chunk_b_counter ==  chunk_b_size)begin
                core_fsm <= fsm_merging_a;
            end
        end
        fsm_merging_a:begin
                chunk_a_counter += 1;
            if(chunk_a_counter ==  chunk_a_size-1) begin
                merged_stream.tlast <=1;
            end else if(chunk_a_counter ==  chunk_a_size)begin
                core_fsm <= fsm_idle;
                merged_stream.tlast <=0;
                merge_done <= 1;
            end
        end
        fsm_merging_b:begin
            chunk_b_counter += 1;
            if(chunk_b_counter ==  chunk_b_size-1) begin
                merged_stream.tlast <=1;
            end else if(chunk_b_counter ==  chunk_b_size)begin
                core_fsm <= fsm_idle;
                merged_stream.tlast <=0;
                merge_done <= 1;
            end
        end
        endcase
    end


    always_comb begin
        case(core_fsm)
        fsm_idle:begin
            stream_in_a.ready <= 0;
            stream_in_b.ready <= 0;
            merged_stream.valid <= 0; 
            merged_stream.data <= 0;
            merged_stream.dest <= 0;
            merged_stream.user <= 0;
        end
        fsm_merging_ab:begin
            if(stream_in_a.valid & stream_in_b.valid)begin
                if(stream_in_a.data > stream_in_b.data) begin
                    merged_stream.data <= stream_in_b.data;
                    merged_stream.dest <= stream_in_b.dest;
                    merged_stream.user <= stream_in_b.user;
                end else begin
                    merged_stream.data <= stream_in_a.data;
                    merged_stream.dest <= stream_in_a.dest;
                    merged_stream.user <= stream_in_a.user;
                end 
                stream_in_a.ready <= stream_in_a.data <= stream_in_b.data;
                stream_in_b.ready <= stream_in_a.data > stream_in_b.data;
                merged_stream.valid <= 1;
            end
        end
        fsm_merging_a:begin
            if(stream_in_a.valid)begin
                merged_stream.data <= stream_in_a.data;
                merged_stream.dest <= stream_in_a.dest;
                merged_stream.user <= stream_in_a.user;
                stream_in_a.ready <= 1;
                stream_in_b.ready <= 0;
                merged_stream.valid <= 1; 
            end
        end
        fsm_merging_b:begin
            if(stream_in_b.valid)begin
                merged_stream.data <= stream_in_b.data;
                merged_stream.dest <= stream_in_b.dest;
                merged_stream.user <= stream_in_b.user;
                stream_in_b.ready <= 1;
                stream_in_a.ready <= 0;
                merged_stream.valid <= 1;   
            end
        end
        default: begin
            stream_in_b.ready <= 1;
            stream_in_a.ready <= 1;
            merged_stream.data <= 0;
            merged_stream.dest <= 0;
            merged_stream.user <= 0;
            merged_stream.valid <= 0;   
        end
        endcase
    end


endmodule