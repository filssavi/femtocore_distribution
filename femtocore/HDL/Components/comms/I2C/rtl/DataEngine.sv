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

module DataEngine #(parameter SETUP_DELAY = 35)(
    input wire clock,
    input wire reset,
    input wire timebase,
    input wire direction,
    input wire [6:0] slave_address,
    input wire [7:0] register_address,
    input wire [7:0] data,
    input wire send_slave_address,
    input wire send_register,
    input wire send_data,
    output reg transfer_done,
    output reg i2c_sda
);


    reg send_in_progress;
    reg [7:0] latched_data;
    reg [3:0] transfer_counter;
    reg previous_timebase;

    always@(posedge clock) begin
        if(~reset) begin
            i2c_sda <= 0;
            transfer_counter <= 0;
            transfer_done <=0;
        end else begin
            if(send_in_progress)begin
                if(timebase & ~previous_timebase)begin
                    if(transfer_counter==7)begin
                        transfer_done <=1;
                    end
                    transfer_counter <= transfer_counter +1;
                    i2c_sda <= latched_data[7-transfer_counter];

                end           
            end else begin
                if(timebase& ~previous_timebase) transfer_counter <= 0;
                transfer_done <=0;
                if(transfer_counter == 0) i2c_sda <= 0;
            end
        end
    end


    always @(posedge clock ) begin
        if (~reset) begin
            previous_timebase <= 0;
        end else begin
            previous_timebase <= timebase;
        end
    end



    always@(posedge clock) begin
        if(~reset)begin
            send_in_progress <= 0;
            latched_data <= 0;
        end else begin
            if(~send_in_progress)begin
                if(send_slave_address)begin
                    latched_data <= {slave_address, direction};
                    send_in_progress <= 1;
                end else if(send_register) begin
                    latched_data <= register_address;
                    send_in_progress <= 1;
                end else if(send_data) begin
                    latched_data <= data;
                    send_in_progress <= 1;
                end
            end else begin
                if(transfer_done) begin
                    send_in_progress <= 0;
                end
            end
        end
    end



endmodule