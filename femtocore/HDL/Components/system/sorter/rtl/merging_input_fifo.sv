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

module merger_input_fifo #(
    parameter DATA_WIDTH=32,
    parameter MAX_SORT_LENGTH=32
)(
    input wire clock,
    input wire reset,
    input wire start,
    input wire [15:0] chunk_size,
    input wire [15:0] chunk_base_address,
    input wire [15:0] read_data,
    axi_stream.master output_data,
    output reg [15:0] read_addr,
    output reg done
);

    axi_stream #(.DATA_WIDTH(DATA_WIDTH)) fifo_input();

    axis_fifo_xpm #(
        .DATA_WIDTH(DATA_WIDTH), 
        .FIFO_DEPTH(MAX_SORT_LENGTH)
    ) buffer_fifo (
        .clock(clock),
        .reset(reset),
        .in(fifo_input),
        .out(output_data)
    );


    enum logic [1:0] { 
        fsm_idle = 0,
        fsm_wait_latency = 1,
        fsm_read_data = 2,
        fsm_read_last = 3
    } state = fsm_idle;

    reg [15:0] working_size = 0;

    always_ff @(posedge clock)begin
        case(state)
        fsm_idle:begin
            fifo_input.valid <= 0;
            read_addr <= 0;
            done <= 0;
            if(start) begin
                state <= fsm_wait_latency;
                read_addr <= chunk_base_address;
                working_size <= chunk_size;
            end
        end
        fsm_wait_latency:begin
            state <= fsm_read_data;
            read_addr <= read_addr + 1;
        end
        fsm_read_data:begin
            if(working_size == 1)begin
                state <= fsm_idle;
            end
            fifo_input.data <= read_data;
            fifo_input.valid <= 1;
            if(read_addr == (chunk_base_address + working_size-1)) begin
                state <= fsm_read_last;
            end
            read_addr <= read_addr + 1;
        end
        fsm_read_last: begin
            fifo_input.data <= read_data;
            done <= 1;
            state <= fsm_idle;
        end
        endcase
    end



endmodule