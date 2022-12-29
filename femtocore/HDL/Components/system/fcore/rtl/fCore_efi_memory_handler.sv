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


module fCore_efi_memory_handler #(
    parameter DATAPATH_WIDTH = 20,
    parameter REG_ADDR_WIDTH = 8,
    parameter BASE_REG_ADDR_WIDTH = 4,
    parameter CH_ADDRESS_WIDTH = 8
)(
    input wire clock,
    input wire reset,
    input wire send_arguments,
    input wire [REG_ADDR_WIDTH-1:0] arguments_base_address,
    input wire [REG_ADDR_WIDTH-1:0] return_base_address,
    input wire [CH_ADDRESS_WIDTH-1:0] channel_address, 
    input wire [7:0] length,
    output reg [1:0] mem_efi_enable,
    output reg [REG_ADDR_WIDTH-1:0] mem_address,
    input wire [DATAPATH_WIDTH-1:0] mem_read_data,
    axi_stream.master efi_arguments,
    axi_stream.slave efi_results, 
    axi_stream.master result_writeback
);

    reg send_args_del;
    reg [7:0] working_length = 0;
    reg [CH_ADDRESS_WIDTH-1:0] working_channel_address;
    reg [REG_ADDR_WIDTH-1:0] working_register = 0;
    reg [REG_ADDR_WIDTH-1:0] return_address = 0; 

    enum logic [2:0] {
        fsm_idle = 0,
        fsm_send_args = 1,
        fsm_wait_execution = 2
    } handler_fsm = fsm_idle;
    
    reg [7:0] arguments_counter = 0;

    assign efi_arguments.data = handler_fsm==fsm_idle ? 0 : mem_read_data; 
    
    always_ff @(posedge clock) begin
        send_args_del <= send_arguments;
        case (handler_fsm)
            fsm_idle: begin
                if(send_arguments)begin
                    working_channel_address <= channel_address;
                end
                arguments_counter <= 1;
                mem_efi_enable <= 0;
                result_writeback.valid <= 0;
                efi_arguments.tlast <= 0;
                efi_arguments.valid <= 0;
                if(send_args_del) begin
                    mem_efi_enable <= 1;
                    working_length <= length;
                    working_register <= arguments_base_address;
                    return_address <= return_base_address;
                    handler_fsm <= fsm_send_args;
                    mem_address <= arguments_base_address + (2**BASE_REG_ADDR_WIDTH*channel_address);
                end
            end
            fsm_send_args: begin
                mem_address <= working_register + arguments_counter + (2**BASE_REG_ADDR_WIDTH*working_channel_address);
                efi_arguments.dest <= arguments_counter;
                efi_arguments.valid <= 1;
                if(arguments_counter == working_length)begin
                    handler_fsm <= fsm_wait_execution;
                    efi_arguments.tlast <= 1;
                    
                end else begin
                    arguments_counter <= arguments_counter + 1;
                end
            end
            fsm_wait_execution:begin
                mem_efi_enable <= 0;
                efi_arguments.valid <= 0;
                efi_arguments.tlast <= 0;
                if(efi_results.valid)begin
                    result_writeback.dest <= return_address + efi_results.dest + (2**BASE_REG_ADDR_WIDTH*working_channel_address);
                    result_writeback.valid <= 1;
                    mem_efi_enable <= 3;
                    result_writeback.data <= efi_results.data;
                    if(efi_results.tlast)begin
                        handler_fsm <= fsm_idle;
                    end
                end
            end
        endcase
    end



endmodule