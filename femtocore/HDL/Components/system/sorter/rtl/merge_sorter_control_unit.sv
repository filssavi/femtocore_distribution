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

module merge_sorter_control_unit #(
    parameter DATA_WIDTH=16,
    parameter DEST_WIDTH=16,
    parameter USER_WIDTH=16,
    parameter MAX_SORT_LENGTH=256
)(
    input wire clock,
    input wire reset,
    input wire start,
    input wire input_valid,
    input wire [$clog2(MAX_SORT_LENGTH)-1:0] data_length,
    output reg [$clog2(MAX_SORT_LENGTH/8-1):0] n_complete_chunks,
    output wire [$clog2(MAX_SORT_LENGTH/8-1):0] selected_chunk_size,
    output wire [2:0] last_chunk_size
);

    reg [2:0] last_chunk_size_inner = 0;
    reg [$clog2(MAX_SORT_LENGTH/8-1):0] n_complete_chunks_inner = 0;

    assign last_chunk_size = last_chunk_size_inner;
    assign n_complete_chunks = n_complete_chunks_inner;

    reg [$clog2(MAX_SORT_LENGTH/8-1):0] chunk_counter = 0;
    reg enable_batcher_sort = 0;
        
    axi_stream #(.DATA_WIDTH(DATA_WIDTH), .DEST_WIDTH(DEST_WIDTH), .USER_WIDTH(USER_WIDTH)) batcher_out();


    assign selected_chunk_size = chunk_counter==n_complete_chunks_inner & last_chunk_size_inner != 0 ? last_chunk_size_inner : 8;


    reg [2:0] input_data_counter = 0;
    
    always_ff @(posedge clock) begin
        enable_batcher_sort <= 1;
        if(start)begin
            n_complete_chunks_inner <= data_length/8;
            chunk_counter <= 0;
            last_chunk_size_inner <= data_length%8;
        end

        if(input_valid)begin
            if(chunk_counter == n_complete_chunks_inner)begin
                if(input_data_counter == last_chunk_size_inner-1) begin
                    input_data_counter <= 0;
                    enable_batcher_sort<= 0;
                    chunk_counter <= chunk_counter + 1;
                end else begin
                    input_data_counter <= input_data_counter + 1;
                end
            end else begin 
                if(input_data_counter == 7) begin
                    input_data_counter <= 0;
                    chunk_counter <= chunk_counter + 1;
                end else begin
                    input_data_counter <= input_data_counter + 1;
                end
            end
        end
    end


    reg batches_counter_working = 0;
    reg [$clog2(MAX_SORT_LENGTH)-1:0] batches_counter  = 0;
    always_ff @(posedge clock) begin
        if(~batches_counter_working)begin
            batches_counter <= 0;
        end
        batcher_out.tlast <= 0;
        if(start) begin
            batches_counter_working <= 1;
            batches_counter <= 0;
        end
        if(batcher_out.valid & batches_counter_working) begin
            batches_counter <= batches_counter + 1;
            if(batches_counter == (n_complete_chunks_inner*8 + last_chunk_size_inner)-2) begin
                batcher_out.tlast <= 1;
                batches_counter_working <= 0;
            end

        end
    end



endmodule