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

module efi_trig #(
    parameter DATA_WIDTH=32,
    parameter DEST_WIDTH=8,
    parameter USER_WIDTH=1
)(
    input wire clock,
    input wire reset,
    axi_stream.slave efi_arguments,
    axi_stream.master efi_results
);


    reg valid_pipeline = 0;
    reg tlast_pipeline = 0;
    reg [31:0] dest_pipeline = 0;
    reg opcode_latching = 0;

    reg opcode = 0;

    enum logic [1:0] { 
        fsm_idle = 0,
        fsm_calculate = 1,
        fsm_wait_data = 2
    } efi_trig_fsm = fsm_idle;


    always_ff @(posedge clock)begin
        case (efi_trig_fsm)
            fsm_idle:begin
                if(efi_arguments.valid)begin
                    efi_trig_fsm <= fsm_calculate;
                    opcode <= efi_arguments.data;
                end else begin
                    opcode <= 0;
                    theta.data <= 0;
                    theta.dest <= 0;
                    theta.valid <= 0;
                    efi_results.data <= 0;
                    efi_results.valid<=0;
                    efi_results.tlast<=0;
                end
            end
            fsm_calculate:begin
                theta.data <= efi_arguments.data;
                theta.dest <= efi_arguments.dest;
                theta.valid <= efi_arguments.valid;
                if(efi_arguments.tlast)begin
                    efi_trig_fsm <= fsm_wait_data;
                end
            end 
            fsm_wait_data:begin
                theta.valid <= 0;
                if(sin.valid)begin
                    efi_trig_fsm <= fsm_idle;
                    if(opcode) begin
                        efi_results.data <= cos.data;
                    end else begin
                        efi_results.data <= sin.data;
                    end
                    efi_results.dest <= sin.dest-2;
                    efi_results.valid<=1;
                    efi_results.tlast<=1;
                end
            end
        endcase
    end

    assign sin.ready = 1;
    assign cos.ready = 1;

    axi_stream  #(.DATA_WIDTH(DATA_WIDTH), .DEST_WIDTH(DEST_WIDTH), .USER_WIDTH(USER_WIDTH)) theta();
    axi_stream  #(.DATA_WIDTH(DATA_WIDTH), .DEST_WIDTH(DEST_WIDTH), .USER_WIDTH(USER_WIDTH)) sin();
    axi_stream  #(.DATA_WIDTH(DATA_WIDTH), .DEST_WIDTH(DEST_WIDTH), .USER_WIDTH(USER_WIDTH)) cos();

    efi_trig_lut trig(
        .clock(clock),
        .reset(reset),
        .theta(theta),
        .sin(sin),
        .cos(cos)
    );




endmodule