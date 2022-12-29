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

module efi_sorter #(
    parameter DATA_WIDTH=32,
    parameter DEST_WIDTH=8,
    parameter USER_WIDTH=1,
    parameter MAX_SORT_LENGTH=256
)(
    input wire clock,
    input wire reset,
    axi_stream.slave efi_arguments,
    axi_stream.master efi_results
);

    reg order;

    axi_stream sorter_in();
    axi_stream sorter_out();

    reg [31:0] sorter_counter = 0;

    reg storter_start = 0;

    enum logic [2:0] { 
        fsm_idle = 0,
        fsm_start_sorter = 1,
        fsm_data_in = 2,
        fsm_wait_result = 3,
        fsm_data_out = 4
    } efi_fsm = fsm_idle;

    always_ff @(posedge clock) begin
        sorter_out.ready <= 1;
        case(efi_fsm)
            fsm_idle:begin
                sorter_in.data <= 0;
                sorter_in.dest <= 0;
                sorter_in.valid <= 0;
                sorter_in.tlast <= 0;
                efi_results.tlast <= 0;
                efi_results.valid <= 0;
                order <= 0;
                if(efi_arguments.valid)begin
                    efi_fsm <= fsm_start_sorter;
                    order <= efi_arguments.data == 'h0;
                    sorter_counter<= 0;
                end 
            end
            fsm_start_sorter:begin
                sorter_in.data <= efi_arguments.data;
                sorter_in.dest <= efi_arguments.dest-1;   
                sorter_in.valid <= efi_arguments.valid;
                storter_start <= 1;
                efi_fsm <= fsm_data_in;
            end
            fsm_data_in:begin
                storter_start <= 0;
                sorter_in.data <= efi_arguments.data;
                sorter_in.dest <= efi_arguments.dest-1;
                sorter_in.valid <= efi_arguments.valid;
                sorter_in.tlast <= efi_arguments.tlast;
                if(~sorter_in.valid)begin
                    efi_fsm <= fsm_wait_result;
                end
            end
            fsm_wait_result:begin
                if(sorter_out.valid)begin
                    if(order)begin
                        efi_results.dest <= 9 - sorter_counter;
                    end else begin
                        efi_results.dest <= 0;
                    end
                    sorter_counter <= sorter_counter+1;
                    efi_results.data <= sorter_out.dest-1;
                    efi_results.valid <= sorter_out.valid;
                    efi_fsm <= fsm_data_out;
                end
            end
            fsm_data_out:begin
                sorter_counter <= sorter_counter+1;
                efi_results.data <= sorter_out.dest-1;
                if(order)begin
                    efi_results.dest <= 9 - sorter_counter;
                end else begin
                    efi_results.dest <= sorter_counter;
                end
                efi_results.valid <= sorter_out.valid;
                if(sorter_counter == 9)begin
                    efi_results.tlast <= 1; 
                    efi_fsm <= fsm_idle;
                end
            end
        endcase

    end

    merge_sorter #(
        .DATA_WIDTH(DATA_WIDTH),
        .DEST_WIDTH(DEST_WIDTH),
        .USER_WIDTH(USER_WIDTH),
        .MAX_SORT_LENGTH(MAX_SORT_LENGTH)
    )sorter(
        .clock(clock),
        .reset(reset),
        .start(storter_start),
        .data_length(10),
        .input_data(sorter_in),
        .output_data(sorter_out)
    );



endmodule