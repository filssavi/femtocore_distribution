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

module CounterEnableDelay (
    input wire clock,
    input wire reset,
    input wire enable,
    input wire [15:0] delay,
    output reg delayedEnable
);

parameter COUNTER_WIDTH = 16;

reg startCounter;
reg resetCounter;
reg countInProgress;
reg internalEnable;
wire [15:0] counter;

reg  [15:0] latched_delay;

timebase_shifter_core #(
    .COUNTER_WIDTH(COUNTER_WIDTH)
) phase_shifter (
    .clockIn(clock),
    .reset(reset),
    .enable(countInProgress),
    .load(startCounter),
    .count_in(delay),
    .count_out(counter)
);

always@(posedge clock) begin : output_register
    if(~reset) begin
        delayedEnable <=0;
    end else begin
        if(latched_delay==0) begin
            delayedEnable <= enable;
        end else
            delayedEnable <= internalEnable;
    end
end

always @(posedge clock) begin : enable_counter_starting
    if(~reset) begin
        startCounter <= 0;
        latched_delay <=0;
    end else begin
        if(enable) begin
            if(~countInProgress & delay!=0) begin
                startCounter <= 1;
            end else begin
                startCounter <= 0;
            end
        end else begin
            startCounter <= 0;
            latched_delay <= delay;
        end
    end
end

always @(posedge clock) begin : enable_counter_reset
    if (~reset) begin
        internalEnable <= 0;
        countInProgress <=0;
        resetCounter <= 0;
    end else begin
        if(enable) begin 
            if(startCounter & ~resetCounter) begin
                resetCounter <= 1'b1;
                countInProgress <= 1'b1;
                internalEnable <= 1'b0;
            end 
            if(countInProgress & counter == 1) begin
                    internalEnable <= 1'b1;
                    countInProgress <= 1'b0;
            end
        end else begin
            internalEnable <= 1'b0;
            resetCounter <= 1'b0;
        end
    end
end


endmodule