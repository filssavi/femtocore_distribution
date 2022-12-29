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

module DeadTimeGenerator (
input wire         clock,
input wire         reset,
input wire         enable,
input wire  [15:0] deadTime,
input wire         in_a,
input wire         in_b,
output reg out_a,
output reg out_b
);


reg counter_enable;

wire [15:0] counter;

parameter COUNTER_WIDTH = 16;

reg load_counter;

reg [2:0] state;
parameter IDLE_STATE = 0, FIRST_DEADTIME_STATE = 1, FIRST_OUT = 2, SECOND_DEADTIME_STATE = 3;

timebase_shifter_core #(
    .COUNTER_WIDTH(COUNTER_WIDTH)
) deadTime_a(
    .clockIn(clock),
    .reset(reset),
    .enable(counter_enable),
    .load(load_counter),
    .count_in(deadTime-1),
    .count_out(counter)
);

always@(posedge clock)begin
    if(~reset)begin
        state <=0;
        counter_enable <=0;
    end else begin
        if(~enable) begin
            load_counter<=1;
        end else begin
            case (state)
                IDLE_STATE:begin
                    load_counter <=0;
                    if(in_a) begin
                        state<=FIRST_DEADTIME_STATE; 
                        counter_enable <=1;
                    end else
                        state <=IDLE_STATE;
                end
                FIRST_DEADTIME_STATE:begin
                    if(counter==0) begin
                        load_counter <= 1;
                        counter_enable <=0;
                        state <= FIRST_OUT;
                    end else
                        state <= FIRST_DEADTIME_STATE;
                end
                FIRST_OUT: begin
                    load_counter <= 0;
                    if(in_b) begin
                        state <= SECOND_DEADTIME_STATE;
                        counter_enable <=1;
                    end else
                        state <= FIRST_OUT;
                end
                SECOND_DEADTIME_STATE:begin
                    if(counter==0) begin
                        load_counter <= 1;
                        counter_enable <=0;
                        state <= IDLE_STATE;
                    end else
                        state <= SECOND_DEADTIME_STATE;
                end
                default: begin
                    state <= IDLE_STATE;
                end
            endcase
            end
    end
end



always@(*)begin
    if(~enable)begin
        out_a <= in_a;
        out_b <= in_b;
    end else begin
        case(state)
            IDLE_STATE:begin
                out_a <=0;
                out_b <=1;
            end
            FIRST_DEADTIME_STATE:begin
                out_a <=0;
                out_b <=0;
            end
            FIRST_OUT:begin
                out_a <=1;
                out_b <=0;
            end
            SECOND_DEADTIME_STATE:begin
                out_a <=0;
                out_b <=0;
            end
            default:begin
                out_a <=0;
                out_b <=1;
            end
        endcase
    end
end




endmodule