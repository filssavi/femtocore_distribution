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

module enable_comparator #(parameter COUNTER_WIDTH = 32, parameter CLOCK_MODE = "FALSE")(
    input wire       clock,
    input wire       reset,
    input wire [COUNTER_WIDTH-1:0] enable_treshold,
    input wire [COUNTER_WIDTH-1:0] count,
    output reg       enable_out
);

    reg [COUNTER_WIDTH-1:0] shadow_enable_treshold;

    always@(posedge clock) begin : enable_treshold_shadow_load
        if(~reset)begin
            shadow_enable_treshold <= 0;
        end else begin
            if(count==0) begin
                shadow_enable_treshold <= enable_treshold;
            end
        end
    end

    generate
        if(CLOCK_MODE == "FALSE") begin
            always@(posedge clock)begin
                if(~reset)begin
                    enable_out <=0;
                end else begin
                    if(shadow_enable_treshold != 0) begin
                        if(count==shadow_enable_treshold-1) begin
                            enable_out <= 1;
                        end else if(count==shadow_enable_treshold) begin
                            enable_out <= 0;
                        end
                    end
                end
            end
        end else if(CLOCK_MODE == "TRUE") begin
            always@(posedge clock)begin
                if(~reset)begin
                    enable_out <=0;
                end else begin
                    if(shadow_enable_treshold != 0) begin
                        if(count==shadow_enable_treshold-1) begin
                            enable_out <= 1;
                        end else if(count==(shadow_enable_treshold-1)>>1) begin
                            enable_out <= 0;
                        end
                    end
                end
            end
        end
    endgenerate

endmodule