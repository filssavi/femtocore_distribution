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

module internal_enable_generator (
    input wire       clock,
    input wire       reset,
    input wire       enable,
    input wire [31:0] period,
    output reg       start
);

    reg [31:0] conv_start_counter;

    always@(posedge clock)begin
        if(~reset)begin
            conv_start_counter <=0;
            start <=0;
        end else begin
            if(enable) begin
                if(conv_start_counter==period) begin
                    conv_start_counter <= 0;
                end else begin
                    conv_start_counter <= conv_start_counter+1;
                end
                if(conv_start_counter==period) begin
                    start <= 1;
                end else if(conv_start_counter==14'h0) begin
                    start <= 0;
                end
            end
        end
    end

endmodule