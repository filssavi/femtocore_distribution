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

module axis_fifo #(parameter DATA_WIDTH = 32,USER_WIDTH = 32, DEST_WIDTH = 32, FIFO_DEPTH = 16)(
    input wire clock,
    input wire reset,
    axi_stream.slave in,
    axi_stream.master out
);


reg [$clog2(FIFO_DEPTH)-1:0] hp_mem_addr_w;
reg [$clog2(FIFO_DEPTH)-1:0] hp_mem_addr_r;

reg [$clog2(FIFO_DEPTH):0] fill_level;

reg [DATA_WIDTH-1:0] fifo_memory[FIFO_DEPTH-1:0];
reg [DEST_WIDTH-1:0] dest_memory[FIFO_DEPTH-1:0];
reg [USER_WIDTH-1:0] user_memory[FIFO_DEPTH-1:0];
integer i;

always@(posedge clock) begin
    if(~reset)begin
        for(i = 0; i< FIFO_DEPTH; i = i+1)begin
            fifo_memory[i] = 0;
        end
        for(i = 0; i< FIFO_DEPTH; i = i+1)begin
            dest_memory[i] = 0;
        end 
        for(i = 0; i< FIFO_DEPTH; i = i+1)begin
            user_memory[i] = 0;
        end 
        fill_level <=0;
        hp_mem_addr_w <=0;
        hp_mem_addr_r <=0;
        out.data <= 0;
        out.valid <= 0;
        out.tlast <= 0;
    end else begin
        out.valid <= 0;
        out.tlast <= 0;
        if(out.ready)begin
            if(fill_level != 0)begin
                if(hp_mem_addr_r == FIFO_DEPTH-1) hp_mem_addr_r <= 0;
                else hp_mem_addr_r <= hp_mem_addr_r+1;
                {out.tlast,out.data[DATA_WIDTH-1:0]} <= fifo_memory[hp_mem_addr_r];
                out.dest <= dest_memory[hp_mem_addr_r];
                out.user <= user_memory[hp_mem_addr_r];
                out.valid <=1;
                fill_level<= fill_level-1;
            end
        end
        if(in.valid)begin
            fifo_memory[hp_mem_addr_w] <= {in.tlast, in.data};
            dest_memory[hp_mem_addr_w] <= in.dest;
            user_memory[hp_mem_addr_w] <= in.user;
            fill_level<= fill_level+1;
            if(hp_mem_addr_w == FIFO_DEPTH-1) hp_mem_addr_w <= 0;
            else hp_mem_addr_w <= hp_mem_addr_w+1;
            
        end

    end
end

always_comb begin
    if(fill_level==FIFO_DEPTH) in.ready <=0;
    else in.ready <=1;
end

endmodule