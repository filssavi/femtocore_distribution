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

module merger_output_fifo #(
    parameter DATA_WIDTH=32,
    parameter MAX_SORT_LENGTH=32
)(
    input wire clock,
    input wire reset,
    input wire start,
    input wire [15:0] chunk_size,
    output reg [15:0] write_data,
    axi_stream.slave input_data,
    output reg [15:0] write_addr,
    output reg write_enable,
    output reg writeback_done
);

    axi_stream #(.DATA_WIDTH(DATA_WIDTH)) fifo_output();

    axis_fifo_xpm #(
        .DATA_WIDTH(DATA_WIDTH), 
        .FIFO_DEPTH(MAX_SORT_LENGTH)
    ) buffer_fifo (
        .clock(clock),
        .reset(reset),
        .in(input_data),
        .out(fifo_output)
    );


    enum logic [1:0] { 
        fsm_idle = 0,
        fsm_start_writing = 1,
        fsm_writing = 2
    } state = fsm_idle;

    always_ff @(posedge clock)begin
        case(state)
        fsm_idle:begin
            write_enable <= 0;
            write_addr <= 0;
            write_data <= 0;
            writeback_done <= 0;
            fifo_output.ready <= 0;
            if(start) begin
                fifo_output.ready <= 1;
                state <= fsm_start_writing;
            end
        end
        fsm_start_writing:begin
            write_enable <= 1;
            write_data <= fifo_output.data;
            state <= fsm_writing;
        end
        fsm_writing:begin
            if(write_addr == chunk_size-1)begin
                write_enable <= 0;
                state <= fsm_idle;
                writeback_done <= 1;
            end
            write_data <= fifo_output.data;
            write_addr <= write_addr + 1;
        end
        endcase
    end



endmodule