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

module PinControl (
    input wire clock,
    input wire reset,
    input wire [1:0] enableOutputs,
    input wire counter_stopped,
    input wire matchHigh,
    input wire matchLow,
    output reg outA,
    output reg outB
);
    reg internalOutStatus;

    always@(posedge clock) begin
        if(~counter_stopped) begin
            case(enableOutputs)
                2'b00: begin
                    outA <= 0;
                    outB <= 0;
                end
                2'b01: begin
                    outA <= internalOutStatus;
                    outB <= 0;
                end
                2'b10: begin
                    outA <= 0;
                    outB <= ~internalOutStatus;
                end
                2'b11: begin
                    outA <= internalOutStatus;
                    outB <= ~internalOutStatus;
                end
                default: begin
                    outA <= 0;
                    outB <= 0;
                end
            endcase
        end else begin
            outA <= 0;
            outB <= 0;
        end
    end

    always@(*) begin
        if(~reset) begin
            internalOutStatus <=0;
        end else begin
            if(~matchHigh&~matchLow) internalOutStatus <=1;
            else internalOutStatus <=0;
        end
    end

endmodule