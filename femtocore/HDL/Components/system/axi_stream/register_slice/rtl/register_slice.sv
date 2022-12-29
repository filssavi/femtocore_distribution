
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

`timescale 10 ns / 1 ns
`include "interfaces.svh"


module register_slice #(parameter DATA_WIDTH = 32, DEST_WIDTH = 32, USER_WIDTH = 32, N_STAGES = 1, READY_REG = 0)(
    input wire        clock,
    input wire        reset,
    axi_stream.slave in,
    axi_stream.master out
);


    reg [31:0] data_reg [N_STAGES-1:0];
    reg [31:0] dest_reg [N_STAGES-1:0];
    reg [31:0] user_reg [N_STAGES-1:0];
    reg [N_STAGES-1:0] tlast_reg;
    reg [N_STAGES-1:0] valid_reg;

    assign out.valid = valid_reg[N_STAGES-1];
    assign out.dest = dest_reg[N_STAGES-1];
    assign out.data = data_reg[N_STAGES-1];
    assign out.user = user_reg[N_STAGES-1];
    assign out.tlast = tlast_reg[N_STAGES-1];


    generate
        if(READY_REG == 0)
            assign in.ready = out.ready;
        else begin
            always_ff@(posedge clock)begin
                in.ready <= out.ready;
            end       
        end
    endgenerate

    generate
        always_ff@(posedge clock)begin
            if(~reset)begin
                for(integer i = 0; i < N_STAGES; i++) begin
                    data_reg[i] <= 0;
                end
                for(integer i = 0; i < N_STAGES; i++) begin
                    dest_reg[i] <= 0;
                end
                for(integer i = 0; i < N_STAGES; i++) begin
                    user_reg[i] <= 0;
                end
                for(integer i = 0; i < N_STAGES; i++) begin
                    valid_reg[i] <= 0;
                end
                for(integer i = 0; i < N_STAGES; i++) begin
                    tlast_reg[i] <= 0;
                end    
            end else begin
                data_reg[0] <= in.data;
                for(integer i = 1; i < N_STAGES; i++) begin
                    data_reg[i] <= data_reg[i-1];
                end
                dest_reg[0] <= in.dest;
                for(integer i = 1; i < N_STAGES; i++) begin
                    dest_reg[i] <= dest_reg[i-1];
                end
                user_reg[0] <= in.user;
                for(integer i = 1; i < N_STAGES; i++) begin
                    user_reg[i] <= user_reg[i-1];
                end
                valid_reg[0] <= in.valid;
                for(integer i = 1; i < N_STAGES; i++) begin
                    valid_reg[i] <= valid_reg[i-1];
                end
                tlast_reg[0] <= in.tlast;
                for(integer i = 1; i < N_STAGES; i++) begin
                    tlast_reg[i] <= tlast_reg[i-1];
                end
            end
            
        end       
    endgenerate


endmodule