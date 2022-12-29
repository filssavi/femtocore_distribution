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


module merging_unit #(
    parameter DATA_WIDTH=32,
    parameter DEST_WIDTH=32,
    parameter USER_WIDTH=32,
    parameter MAX_SORT_LENGTH=32,
    parameter BASE_CHUNK_SIZE=8
)(
    input wire clock,
    input wire reset,
    axi_stream.slave data_in,
    input wire [$clog2(MAX_SORT_LENGTH/8-1):0] n_chunks_in,
    input wire [$clog2(BASE_CHUNK_SIZE)-1:0] last_chunk_size,
    axi_stream.master data_out
);

    axi_stream #(.DATA_WIDTH(DATA_WIDTH), .DEST_WIDTH(DEST_WIDTH), .USER_WIDTH(USER_WIDTH)) registered_input();
    axi_stream #(.DATA_WIDTH(DATA_WIDTH), .DEST_WIDTH(DEST_WIDTH), .USER_WIDTH(USER_WIDTH)) bypass_load();
    axi_stream #(.DATA_WIDTH(DATA_WIDTH), .DEST_WIDTH(DEST_WIDTH), .USER_WIDTH(USER_WIDTH)) stream_to_merge();
    axi_stream #(.DATA_WIDTH(DATA_WIDTH), .DEST_WIDTH(DEST_WIDTH), .USER_WIDTH(USER_WIDTH)) merge_result();
    axi_stream #(.DATA_WIDTH(DATA_WIDTH), .DEST_WIDTH(DEST_WIDTH), .USER_WIDTH(USER_WIDTH)) result_fifo_in();
    axi_stream #(.DATA_WIDTH(DATA_WIDTH), .DEST_WIDTH(DEST_WIDTH), .USER_WIDTH(USER_WIDTH)) post_out_result();
    axi_stream #(.DATA_WIDTH(DATA_WIDTH), .DEST_WIDTH(DEST_WIDTH), .USER_WIDTH(USER_WIDTH)) merger_feedback();

    wire select_merge_bypass, output_selector, core_start;
    wire merge_done;
    wire [15:0] input_chunk_size;
    wire [15:0] result_size;


    axis_fifo_xpm #(
        .DATA_WIDTH(DATA_WIDTH),
        .DEST_WIDTH(DEST_WIDTH),
        .USER_WIDTH(USER_WIDTH),
        .FIFO_DEPTH(MAX_SORT_LENGTH)
    ) input_fifo (
        .clock(clock),
        .reset(reset),
        .in(data_in),
        .out(registered_input)
    );


    axi_stream_selector_2 #(
        .REGISTERED(0)
    ) bypass_selector(
        .clock(clock),
        .address(select_merge_bypass),
        .stream_in(registered_input),
        .stream_out_1(stream_to_merge), 
        .stream_out_2(bypass_load)
    );


    merging_core #(
        .DATA_WIDTH(DATA_WIDTH),
        .DEST_WIDTH(DEST_WIDTH),
        .USER_WIDTH(USER_WIDTH),
        .MAX_SORT_LENGTH(MAX_SORT_LENGTH)
     ) merge_core (
        .clock(clock),
        .start(core_start),
        .chunk_a_size(result_size),
        .chunk_b_size(input_chunk_size),
        .stream_in_a(merger_feedback),
        .stream_in_b(stream_to_merge),
        .merged_stream(merge_result),
        .merge_done(merge_done)
    );


    axi_stream_selector_2 #(
        .REGISTERED(0)
    ) result_selector(
        .clock(clock),
        .address(output_selector),
        .stream_in(merge_result),
        .stream_out_1(post_out_result), 
        .stream_out_2(data_out)
    );
    


    axi_stream_mux_2 #(
        .DATA_WIDTH(DATA_WIDTH)
    )result_mux(
        .clock(clock),
        .reset(reset),
        .address(select_merge_bypass),
        .stream_in_1(post_out_result),
        .stream_in_2(bypass_load),
        .stream_out(result_fifo_in)
    );


    axis_fifo_xpm #(
        .DATA_WIDTH(DATA_WIDTH),
        .DEST_WIDTH(DEST_WIDTH),
        .USER_WIDTH(USER_WIDTH),
        .FIFO_DEPTH(MAX_SORT_LENGTH)
    ) result_fifo (
        .clock(clock),
        .reset(reset),
        .in(result_fifo_in),
        .out(merger_feedback)
    );

 
    merger_control_unit #(
        .MAX_SORT_LENGTH(MAX_SORT_LENGTH),
        .BASE_CHUNK_SIZE(BASE_CHUNK_SIZE)
    ) CU (
        .clock(clock),
        .last_chunk_size(last_chunk_size),
        .n_chunks_in(n_chunks_in),
        .output_selector(output_selector),
        .data_in_valid(data_in.valid),
        .registered_in_valid(registered_input.valid),
        .select_merge_bypass(select_merge_bypass),
        .core_start(core_start),
        .input_chunk_size(input_chunk_size),
        .result_size(result_size),
        .merge_done(merge_done)
    );

        
endmodule