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

module I2CControlUnit #(parameter BASE_ADDRESS = 0)(
    input wire clock,
    input wire reset,
    input wire done,
    output reg        direction,
    output reg [31:0] prescale,
    output reg [7:0]  slave_adress,
    output reg [7:0]  register_adress,
    output reg [7:0]  data,
    output reg        start,
    output reg        timebase_enable,
    axi_lite.slave axi_in
);

    logic [31:0] cu_write_registers [2:0];
    logic [31:0] cu_read_registers [2:0];

    logic start_transfer;

    axil_simple_register_cu #(
        .N_READ_REGISTERS(3),
        .N_WRITE_REGISTERS(3),
        .N_TRIGGER_REGISTERS(1),
        .TRIGGER_REGISTERS_IDX('{2}),
        .INITIAL_OUTPUT_VALUES('{0, 1, 0}),
        .REGISTERS_WIDTH(32),
        .ADDRESS_MASK('hf)
    ) CU (
        .clock(clock),
        .reset(reset),
        .input_registers(cu_read_registers),
        .output_registers(cu_write_registers),
        .trigger_out('{start_transfer}),
        .axil(axi_in)
    );

    
    assign direction = cu_write_registers[0][0];
    assign timebase_enable = cu_write_registers[0][1];
    assign prescale = cu_write_registers[1];

    assign register_adress = cu_write_registers[2][7:0];
    assign slave_adress = cu_write_registers[2][15:8];
    assign data = cu_write_registers[2][23:16];
    

    assign cu_read_registers[0][31:0] = {timebase_enable, direction};
    assign cu_read_registers[1][31:0] = prescale;
    assign cu_read_registers[2][31:0] = {data, slave_adress, register_adress};


    //FSM STATE CONTROL REGISTERS
    enum logic [2:0]{
        idle_state = 0,
        comm_start_state = 1,
        comm_in_progress_state = 2
    } state = idle_state;

    // Determine the next state
    always @ (posedge clock) begin : control_state_machine
        if (~reset) begin
            start <= 0;
        end else begin
            case (state)
                idle_state: 
                    if(start_transfer) begin
                        state <= comm_start_state;
                        start <= 1;
                    end else
                        state <=idle_state;
                comm_start_state: begin
                    start <= 0;
                    state <= comm_in_progress_state;
                end
                comm_in_progress_state: begin
                    if(done) begin
                        state <= idle_state;
                    end else begin
                        state <= comm_in_progress_state;
                    end 
                end
            endcase
        end
    end
endmodule