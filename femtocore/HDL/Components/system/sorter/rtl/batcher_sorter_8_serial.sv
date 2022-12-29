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

module batcher_sorter_8_serial #(
    parameter DATA_WIDTH = 32,
    parameter USER_WIDTH = 32,
    parameter DEST_WIDTH = 32,
    parameter MAX_SORT_LENGTH=32
)(
    input wire clock,
    input wire [$clog2(MAX_SORT_LENGTH/8-1):0] chunk_size,
    axi_stream.slave data_in,
    axi_stream.master data_out
);


    assign data_in.ready = data_out.ready;
    
    reg [2:0] input_buffer_index = 0;
    reg [(DATA_WIDTH+USER_WIDTH+DEST_WIDTH)-1:0] input_buffer [7:0];         
    reg sorter_start = 0;

    reg [$clog2(MAX_SORT_LENGTH)-1:0] working_size;

    always_ff @(posedge clock)begin
        sorter_start <= 0;

        if(data_in.valid)begin
            input_buffer[input_buffer_index] <= {data_in.user, data_in.dest, data_in.data};
            if(input_buffer_index== 0)begin   
                for(int i = 1; i<8; i=i+1) begin
                    input_buffer[i] <= 0;
                end
            end
            if(input_buffer_index == chunk_size-1)begin
                input_buffer_index <= 0;
                sorter_start <= 1;
                working_size <= chunk_size;
            end else begin
                input_buffer_index <= input_buffer_index + 1;
            end
        end
    end
    
    wire data_out_valid;
    wire [(DATA_WIDTH+USER_WIDTH+DEST_WIDTH)-1:0] parallel_data_out [7:0];

    reg [3:0] transfer_chunk_size;

    batcher_sorter_8 #(
        .DATA_WIDTH(DATA_WIDTH),
        .USER_WIDTH(USER_WIDTH),
        .DEST_WIDTH(DEST_WIDTH)
    ) parallel_sorter (
        .clock(clock),
        .data_in(input_buffer),
        .chunk_size_in(working_size),
        .data_in_valid(sorter_start),
        .data_out(parallel_data_out),
        .chunk_size_out(transfer_chunk_size),
        .data_out_valid(data_out_valid)
    );

    enum logic [1:0] { 
        fsm_idle = 0,
        fsm_in_transfer = 1,
        fsm_wait_final_chunk = 2,
        fsm_transfer_final_chunk = 3
    } transfer_state = fsm_idle;

    reg [(DATA_WIDTH+USER_WIDTH+DEST_WIDTH)-1:0] transfer_buffer [7:0];
    reg [(DATA_WIDTH+USER_WIDTH+DEST_WIDTH)-1:0] final_chunk_buffer [7:0];
    reg [2:0] transfer_index = 0;

    always_ff @(posedge clock)begin
        case (transfer_state) 
            fsm_idle:begin
                data_out.valid <= 0;
                if(data_out_valid) begin
                    transfer_state <= fsm_in_transfer;
                    transfer_buffer <= parallel_data_out;

                    data_out.data <= parallel_data_out[0][DATA_WIDTH-1:0];
                    data_out.dest <= parallel_data_out[0][(DEST_WIDTH+DATA_WIDTH)-1:DATA_WIDTH];
                    data_out.user <= parallel_data_out[0][(DEST_WIDTH+DATA_WIDTH+USER_WIDTH)-1:(DEST_WIDTH+DATA_WIDTH)];

                    transfer_index <= 1;
                    data_out.valid <= 1;
                end
            end
            fsm_in_transfer:begin
                transfer_index <= transfer_index + 1;

                data_out.data <= transfer_buffer[transfer_index][DATA_WIDTH-1:0];
                data_out.dest <= transfer_buffer[transfer_index][(DEST_WIDTH+DATA_WIDTH)-1:DATA_WIDTH];
                data_out.user <= transfer_buffer[transfer_index][(DEST_WIDTH+DATA_WIDTH+USER_WIDTH)-1:(DEST_WIDTH+DATA_WIDTH)];
                
                if(data_out_valid & transfer_chunk_size != 8) begin
                    if(transfer_chunk_size == 7) begin
                        transfer_state <= fsm_transfer_final_chunk;
                        transfer_index <= 8-transfer_chunk_size;
                    end else begin
                        transfer_state <= fsm_wait_final_chunk;
                    end
                    final_chunk_buffer <= parallel_data_out;
                end else if(transfer_index == 7)begin
                    transfer_index <= 1;
                    transfer_state <= fsm_idle;
                end
            end 
            fsm_wait_final_chunk:begin
                transfer_index <= transfer_index + 1;
                if(transfer_index == 7) begin
                    transfer_index <= 8-transfer_chunk_size;
                    transfer_state <= fsm_transfer_final_chunk;
                end

                data_out.data <= transfer_buffer[transfer_index][DATA_WIDTH-1:0];
                data_out.dest <= transfer_buffer[transfer_index][(DEST_WIDTH+DATA_WIDTH)-1:DATA_WIDTH];
                data_out.user <= transfer_buffer[transfer_index][(DEST_WIDTH+DATA_WIDTH+USER_WIDTH)-1:(DEST_WIDTH+DATA_WIDTH)];
                
            end
            fsm_transfer_final_chunk:begin
                if(transfer_index == 7) begin
                    transfer_state <= fsm_idle;
                end
                transfer_index <= transfer_index + 1;
                data_out.data <= final_chunk_buffer[transfer_index][DATA_WIDTH-1:0];
                data_out.dest <= final_chunk_buffer[transfer_index][(DEST_WIDTH+DATA_WIDTH)-1:DATA_WIDTH];
                data_out.user <= final_chunk_buffer[transfer_index][(DEST_WIDTH+DATA_WIDTH+USER_WIDTH)-1:(DEST_WIDTH+DATA_WIDTH)];
            end
        endcase
    end

endmodule