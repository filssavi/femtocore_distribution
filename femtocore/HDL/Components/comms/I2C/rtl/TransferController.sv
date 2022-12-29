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

module TransferController #(parameter START_STOP_DELAY = 350, ACK_DELAY = 1600, BUS_FREE_DELAY = 300)(
    input wire clock,
    input wire reset,
    input wire start_transfert,
    input wire timebase,
    input wire transfer_step_done,
    input wire ack,
    output reg send_slave_address,
    output reg timebase_enable,
    output reg send_register_address,
    output reg send_data,
    output reg i2c_sda_control,
    output reg i2c_scl_control,
    output reg transfert_done
);

    
    reg [2:0] state;
    reg wait_for_ack, wait_timer_enabled;
    reg [2:0] next_phase;
    
    reg [15:0] wait_timer;
    localparam idle_state = 0, start_state = 1, slave_address = 2, register_address = 3, data_state = 4, wait_ack_state = 5, stop_state = 6, bus_free_state = 7;

    always@(posedge clock)begin
        if(~reset)begin
            wait_timer <= 0;
        end else begin
            if(wait_timer_enabled)begin
                wait_timer <= wait_timer+1;
            end else begin
                wait_timer <= 0;
            end
        end
    end

    // Determine the next state
    always @ (posedge clock) begin : control_state_machine
        if (~reset) begin
            state <=idle_state;
            send_register_address <= 0;
            send_slave_address <= 0;
            send_data <= 0;
            wait_for_ack <= 0;
            i2c_sda_control <= 1;
            timebase_enable <= 0;
            i2c_scl_control <= 1;
            next_phase <= 0;
            transfert_done <= 0;
            wait_timer_enabled <=0;
        end else begin
            case (state)
                idle_state: begin
                    if(start_transfert)begin
                        state <= start_state;
                        i2c_sda_control <=0;
                    end else begin
                        state <= idle_state;
                    end
                    wait_for_ack <= 0;
                end
                start_state: begin
                    if(wait_timer == START_STOP_DELAY)begin
                        state <= slave_address;
                        i2c_scl_control <= 0;
                        timebase_enable <= 1;
                    end else begin
                        state <= start_state;
                    end
                end
                slave_address: begin
                    wait_for_ack <= 0;
                    i2c_sda_control <= 0;
                    wait_timer_enabled <=0;
                    if(transfer_step_done)begin
                        send_slave_address <= 0;
                        wait_for_ack <= 1;
                        wait_timer_enabled <=1;
                        state <= wait_ack_state;
                        next_phase <= register_address;
                    end else begin
                        state <= slave_address;
                    end
                end
                register_address: begin
                    wait_for_ack <= 0;
                    i2c_sda_control <= 0;
                    wait_timer_enabled <=0;
                    if(transfer_step_done)begin
                        send_register_address <= 0;
                        wait_for_ack <= 1;
                        wait_timer_enabled <=1;
                        state <= wait_ack_state;
                        next_phase <= data_state;
                    end else begin
                        state <= register_address;
                    end
                end
                data_state: begin
                    wait_for_ack <= 0;
                    i2c_sda_control <= 0;
                    if(transfer_step_done)begin
                        send_data <= 0;
                        wait_for_ack <= 1;
                        wait_timer_enabled <=1;
                        state <= wait_ack_state;
                        next_phase <= stop_state;
                    end else begin
                        state <= data_state;
                    end
                end
                wait_ack_state: begin
                    if(wait_timer > 540) begin
                        i2c_sda_control <= 1;
                    end
                    if(wait_timer==ACK_DELAY) begin
                        wait_timer_enabled <=0;
                        if(ack)
                            state <= next_phase;
                        else
                            state <= next_phase;
                    end else begin
                        state <= wait_ack_state;
                    end
                end
                stop_state: begin
                    wait_timer_enabled <=1;
                    i2c_sda_control <= 0;
                    if(wait_timer == START_STOP_DELAY)begin
                        state <= bus_free_state;
                        timebase_enable <= 0;
                        wait_timer_enabled <= 0;
                        i2c_sda_control <= 1;
                    end else begin
                        state <= stop_state;
                    end
                end
                bus_free_state: begin
                    wait_timer_enabled <= 1;
                    if(wait_timer == BUS_FREE_DELAY)begin
                        state <= idle_state;
                        transfert_done <= 1;
                    end else begin
                        state <= bus_free_state;
                    end
                end
            endcase
            
            case (state)
                idle_state:  begin
                    transfert_done <= 0;
                    wait_timer_enabled <=0;
                end
                start_state: begin
                    wait_timer_enabled <=1;
                end
                slave_address: begin
                    if(~transfer_step_done) send_slave_address <= 1;
                end
                register_address: begin
                    if(~transfer_step_done) send_register_address <= 1;
                end
                data_state: begin
                    if(~transfer_step_done) send_data <= 1;
                end
                wait_ack_state: begin
                end
                stop_state: begin
                    if(wait_timer == 157) i2c_scl_control <= 1;
                end
                bus_free_state:begin
  
                end
            endcase
        end
    end


endmodule