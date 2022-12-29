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


module trigger_hub #(parameter N_TRIGGERS = 16)(
    input wire        clock,
    input wire        reset,
    input wire [15:0] buffer_level,
    input wire trigger_in,
    input wire [31:0] selected_trigger,
    input wire capture_done,
    input wire capture_ack,
    input wire [15:0] trigger_position,
    output reg capture_inhibit,
    output reg [N_TRIGGERS-1:0] trigger_out
);

    reg [N_TRIGGERS-1:0] trigger_armed = 0;


    always_ff@(posedge clock) begin
        if(~reset)begin
            trigger_out <= 0;
        end else begin
            if (|trigger_out) begin
                trigger_out <= 0;
            end
            if(trigger_in)begin
                trigger_armed[selected_trigger] <= 1;
            end
            if(|trigger_armed)begin
                if(buffer_level == trigger_position) begin
                    trigger_out <= trigger_armed;
                    trigger_armed <= 0;
                end
            end
        end
    end

   
    
    enum reg [1:0] { 
        wait_trigger = 0,
        wait_capture_completion = 1,
        wait_capture_acknowledge = 2
    } state = wait_trigger;

    always_ff@(posedge clock) begin
        case (state)
            wait_trigger:begin
                capture_inhibit <= 0;
                if(|trigger_out)begin
                    state <= wait_capture_completion;
                end
            end
            
            wait_capture_completion: begin
                if(capture_done)begin
                    state <= wait_capture_acknowledge;
                    capture_inhibit <= 1;
                end
            end

            wait_capture_acknowledge: begin
                if(capture_ack)begin
                    state <= wait_trigger;
                    capture_inhibit <= 0;
                end
            end
            
        endcase
    end


endmodule