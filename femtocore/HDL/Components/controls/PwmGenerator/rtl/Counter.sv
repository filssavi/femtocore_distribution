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

/* Module: Counter

    Selectable UP/DOWN/UP-DOWN counter with asynchronous reset.
    
    Modes of operation:
        1) continuous up counter
        0) continuous down counter
        2) continuous up-down counter

    the counter will automatically reload the appropriate value and restart until stopped

    Inputs: 
        timebase:       Counter clock
        reset:          Counter asynchronous reset
        start:          counter run
        mode [2:0]:     mode selection
        adress [4:0]    register adress
        dataIn [31:0]:  register data write input
*/

module Counter #(parameter COUNTER_WIDTH = 16)(
    input wire         clock,
    input wire         timebase,
    input wire         reset,
    input wire         run,   
    input wire  [1:0]  mode,
    input wire         sync,
    input wire [COUNTER_WIDTH-1:0] counter_start_data,
    input wire [COUNTER_WIDTH-1:0] counter_stop_data,
    output reg  [COUNTER_WIDTH-1:0] countOut,
    output reg         reload_compare
);

    wire [COUNTER_WIDTH-1:0] counter; 
    reg counter_enable;     //0: counter stopped 1: counter running
    reg direction;         //0: up counting 1: down counting
    reg [COUNTER_WIDTH-1:0] cnt_stopValue;


    always@(posedge clock)begin
        if(~reset) begin
            reload_compare<=1;
        end else begin 
            if(counter==0) begin
                reload_compare<=1;
            end else 
                reload_compare <=0;
        end
    end

    always@(posedge clock) begin : output_logic
        if(~reset) begin
            countOut <= 0;
        end else begin
            if(counter_enable)begin
                if(timebase) begin
                    if(mode != 0) countOut <= counter + counter_start_data;
                    else countOut <= counter_stop_data - counter;
                end else begin
                    countOut <= countOut;
                end
            end else begin
                countOut <= countOut;
            end
        end
    end

    counter_core #(
        .COUNTER_WIDTH(COUNTER_WIDTH)
    ) core (
        .clockIn(clock),
        .timebase(timebase),
        .reset(reset & ~sync ),
        .enable(counter_enable),
        .direction(direction),
        .reload_value(cnt_stopValue),
        .inhibit_load(~mode[1]),
        .count_in(0),
        .count_out(counter)
    );

    always@(posedge clock)begin :direction_logic
        if(~reset)begin
            direction <= 0;
        end else begin
            if(~counter_enable)begin
                direction <=0;
            end else begin
                if(mode==2)begin
                    if(counter==cnt_stopValue) direction<=1;
                    if(counter==counter_start_data) direction<=0;
                end else begin
                    direction <=0;
                end
            end
        end
    end

    //Asyncronous start stop signal processing
    always @(posedge clock)begin : start_stop_logic
        if(~reset)begin
            counter_enable <=0;
            cnt_stopValue <= 32'h0;
        end else begin
            if(~run & counter_enable) begin
                counter_enable <= 0;  //stop counter
            end else if(run & ~counter_enable) begin
                counter_enable <=1;  //start counter
                if(mode!=0)
                    cnt_stopValue <= counter_stop_data - counter_start_data;
                else
                    cnt_stopValue <= counter_stop_data - counter_start_data+1;
            end
        end
    end


endmodule