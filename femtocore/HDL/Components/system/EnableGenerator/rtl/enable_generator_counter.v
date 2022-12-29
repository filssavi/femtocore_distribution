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

module enable_generator_counter #(parameter COUNTER_WIDTH = 32, EXTERNAL_TIMEBASE_ENABLE = 0)(
    input wire       clock,
    input wire       reset,
    input wire       external_timebase,
    input wire       gen_enable_in,
    input wire [COUNTER_WIDTH-1:0] period,
    output wire [COUNTER_WIDTH-1:0] counter_out
);

    reg [COUNTER_WIDTH-1:0] enable_counter;
    reg [COUNTER_WIDTH-1:0] internal_period;
    
    assign counter_out = enable_counter;

   

    always@(posedge clock) begin : period_shadow_load
        if(~reset)begin
            internal_period <= 0;
        end else begin
            if(gen_enable_in) begin
                if(enable_counter==0) begin
                    internal_period <= period;
                end
            end else begin
                internal_period <= period;
            end
        end
    end

    wire chosen_sync;
    generate
        if(EXTERNAL_TIMEBASE_ENABLE==1)begin
            assign chosen_sync = external_timebase;
        end else begin
            assign chosen_sync = 1;
        end
    endgenerate

    

    always@(posedge clock)begin : enable_counter_logic
        if(~reset)begin
            enable_counter <=0;
        end else begin
            if(chosen_sync)begin
                if(gen_enable_in & internal_period != 0) begin
                    if(enable_counter==internal_period-1) begin
                        enable_counter <= 0;
                    end else begin
                        enable_counter <= enable_counter+1;
                    end
                end else begin
                    enable_counter <= 0;
                end
            end
            
        end
    end

endmodule