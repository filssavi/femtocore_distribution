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

module TransferEngine #(parameter N_CHANNELS=3, OUTPUT_WIDTH=32) (
    input logic clock,
    input logic reset,
    input logic [4:0] spi_transfer_length,
    input logic [31:0] spi_delay,
    input logic [2:0] divider_setting,
    input logic spi_start_transfer,
    input logic ss_deassert_delay_enable,
    input logic [31:0] cu_data_out [N_CHANNELS-1:0],
    input logic [OUTPUT_WIDTH-1:0] reg_data_out [N_CHANNELS-1:0],
    input logic reg_data_out_valid,
    input wire sync,
    output logic enable_clockgen,
    output logic [OUTPUT_WIDTH-1:0] cu_data_in [N_CHANNELS-1:0],
    output logic [31:0] reg_data_in [N_CHANNELS-1:0],
    output logic register_load,
    output logic register_enable,
    output logic transfer_done,
    output logic ss_blanking
);

    //FSM STATE CONTROL REGISTERS
    enum logic [2:0]{
        idle_state = 0,
        start_transfer_state = 1,
        transfer_in_progress_state = 2,
        wait_sync = 3,
        ss_wait_outputs = 4,
        ss_deassert_delay = 5,
        ss_output_results = 6
    } state = idle_state;

    //TRANSFER AND SS DELAY TIMERS
    logic [31:0] ss_delay_timer = 0;
    logic [4:0] internal_transfer_length =0; // Added register to reduce delay

    // REGISTER USED TO LATCH DATA TO OUTPUT AT TRANSFER START
    logic [31:0] latched_output_data [N_CHANNELS-1:0] = '{N_CHANNELS{0}};


    logic [OUTPUT_WIDTH-1:0] int_cu_data_in [N_CHANNELS-1:0];

    assign cu_data_in = int_cu_data_in;

    function [N_CHANNELS-1:0][OUTPUT_WIDTH-1:0] PurgeReadValue (
        input [OUTPUT_WIDTH-1:0] data [N_CHANNELS-1:0],
        input [4:0] length
    );
        integer i, j;
        integer k;
        begin
            for (j=0; j < N_CHANNELS; j=j+1) begin
                for (i=0; i < OUTPUT_WIDTH; i=i+1) begin : purge
                    k = data[j][i];
                    if(i>length) PurgeReadValue[j][i] = 0;
                    else PurgeReadValue[j][i] = data[j][i];
                end
            end
        end
    endfunction


    always @(posedge clock)begin
        if(!reset)begin
            int_cu_data_in <= '{N_CHANNELS{0}};
        end else begin
            if(reg_data_out_valid) begin
                {>>{int_cu_data_in}} <=  PurgeReadValue(reg_data_out,spi_transfer_length);
            end
        end
    end
    reg [5:0] output_delay_counter;
    reg [31:0] progress_counter;
    reg [31:0] stop_condition; 
    always @(posedge clock) begin
        if (~reset) begin
            state <= idle_state;
            ss_delay_timer <= 0;
            reg_data_in <= '{N_CHANNELS{0}};
            register_load <=0;
            progress_counter <= 0;
            register_enable <= 0;
            enable_clockgen <=0;
            stop_condition <= 0;
            ss_blanking <=1;
        end else begin
            case (state)

                idle_state: begin
                    if(spi_start_transfer) begin
                        ss_blanking <=1;
                        latched_output_data <= cu_data_out;
                        state <= start_transfer_state;
                    end else begin
                        state <= idle_state;
                    end
                end

                start_transfer_state: begin
                    if(ss_delay_timer==spi_delay-1) begin
                        if(sync)begin
                            state <= transfer_in_progress_state;
                            ss_blanking <=0;
                            enable_clockgen <= 1;
                            progress_counter <= 0;
                            case (divider_setting)
                                0: stop_condition <= internal_transfer_length;
                                1: stop_condition <= 2*internal_transfer_length+2;
                                2: stop_condition <= 4*internal_transfer_length+2;
                                3: stop_condition <= 8*internal_transfer_length+4;
                                4: stop_condition <= 16*internal_transfer_length+6;
                                5: stop_condition <= 32*internal_transfer_length+8; 
                            endcase
                        end else begin
                            state <= wait_sync;
                        end
                        
                    end else begin
                        ss_delay_timer <= ss_delay_timer+1;
                        state <= start_transfer_state;
                    end
                end
                wait_sync: begin
                    if(sync)begin
                        state <= transfer_in_progress_state;
                        ss_blanking <=0;
                            enable_clockgen <= 1;
                            progress_counter <= 0;
                            case (divider_setting)
                                0: stop_condition <= internal_transfer_length;
                                1: stop_condition <= 2*internal_transfer_length+2;
                                2: stop_condition <= 4*internal_transfer_length+2;
                                3: stop_condition <= 8*internal_transfer_length+4;
                                4: stop_condition <= 16*internal_transfer_length+6;
                                5: stop_condition <= 32*internal_transfer_length+8; 
                            endcase
                    end
                end
                transfer_in_progress_state: begin
                    progress_counter <= progress_counter +1;
                    if(progress_counter == stop_condition) begin
                        state <= ss_wait_outputs;
                        output_delay_counter <= 0;
                        enable_clockgen <=0;
                        ss_delay_timer <= 0;
                    end else begin
                        state <= transfer_in_progress_state;
                    end
                end
                ss_wait_outputs:begin
                    register_enable <=0;
                    output_delay_counter <= output_delay_counter +1;
                    if(output_delay_counter ==1)begin
                        if(ss_deassert_delay_enable)begin
                            state <= ss_deassert_delay;
                        end else begin
                            state <= ss_output_results;
                        end
                    end
                end
                ss_deassert_delay:begin
                    if(ss_delay_timer==spi_delay-1)begin
                        state <= idle_state;
                        transfer_done <=1;
                    end else begin
                        ss_delay_timer <= ss_delay_timer+1;
                        state <= ss_deassert_delay;
                    end
                end
                ss_output_results:begin
                    transfer_done <=1;
                    state <= idle_state;
                end
                default: begin
                    state <= idle_state;
                end
            endcase

            case (state)
                idle_state: begin
                    internal_transfer_length <= spi_transfer_length;
                    transfer_done <=0;
                    ss_delay_timer <=0;
                end
                start_transfer_state: begin
                    register_enable <= 1;
                    register_load <= 1;
                    reg_data_in <= latched_output_data;
                end
                transfer_in_progress_state: begin
                    register_load <= 0;
                end
                ss_deassert_delay:begin
                    enable_clockgen <= 0;
                end
                default:begin
                    register_load <= 0;
                end
            endcase

        end
    end



endmodule