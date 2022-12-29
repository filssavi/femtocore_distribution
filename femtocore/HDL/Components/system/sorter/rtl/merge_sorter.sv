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

module merge_sorter #(
    parameter DATA_WIDTH=16,
    parameter DEST_WIDTH=16,
    parameter USER_WIDTH=16,
    parameter MAX_SORT_LENGTH=256
)(
    input wire clock,
    input wire reset,
    input wire start,
    input wire [$clog2(MAX_SORT_LENGTH)-1:0] data_length,
    axi_stream.slave input_data,
    axi_stream.master output_data
);


    reg [$clog2(MAX_SORT_LENGTH/8-1):0] chunk_counter = 0;
    reg enable_batcher_sort = 0;
        
    axi_stream #(.DATA_WIDTH(DATA_WIDTH), .DEST_WIDTH(DEST_WIDTH), .USER_WIDTH(USER_WIDTH)) batcher_out();

    wire [$clog2(MAX_SORT_LENGTH/8-1):0] selected_chunk_size;
    
    batcher_sorter_8_serial #(
       .DATA_WIDTH(DATA_WIDTH),
       .DEST_WIDTH(DEST_WIDTH),
       .USER_WIDTH(USER_WIDTH),
       .MAX_SORT_LENGTH(MAX_SORT_LENGTH)
    )in_sorter(
        .clock(clock),
        .chunk_size(selected_chunk_size),
        .data_in(input_data),
        .data_out(batcher_out)
    );

    wire [$clog2(MAX_SORT_LENGTH/8-1):0] n_complete_chunks;
    wire [2:0] last_chunk_size;

    merge_sorter_control_unit #(
        .DATA_WIDTH(DATA_WIDTH),
        .DEST_WIDTH(DEST_WIDTH),
        .USER_WIDTH(USER_WIDTH),
        .MAX_SORT_LENGTH(MAX_SORT_LENGTH)
    ) CU (
        .clock(clock),
        .reset(reset),
        .start(start),
        .input_valid(input_data.valid),
        .data_length(data_length),
        .n_complete_chunks(n_complete_chunks),
        .last_chunk_size(last_chunk_size),
        .selected_chunk_size(selected_chunk_size)
    );


    merging_unit #(
        .DATA_WIDTH(DATA_WIDTH),
        .DEST_WIDTH(DEST_WIDTH),
        .USER_WIDTH(USER_WIDTH),
        .MAX_SORT_LENGTH(MAX_SORT_LENGTH),
        .BASE_CHUNK_SIZE(8)
    )merger (
        .clock(clock),
        .reset(reset),
        .n_chunks_in(n_complete_chunks),
        .last_chunk_size(last_chunk_size),
        .data_in(batcher_out),
        .data_out(output_data)
    );



endmodule