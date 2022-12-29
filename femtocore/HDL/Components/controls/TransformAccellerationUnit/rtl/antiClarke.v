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

module antiClarke (
    input  wire signed [17:0] alpha,
    input  wire signed [17:0] beta,
    output wire signed [17:0] a,
    output wire signed [17:0] b,
    output wire signed [17:0] c
);

    wire signed [35:0] int_a;
    wire signed [35:0] int_b;
    wire signed [35:0] int_c;

    wire signed [17:0] coefficients [5:0];
//   the following coefficients are calculated assuming a 18 bit fully fractional signed fixed point representation
//   current full scale is 220A maximum quantization error under 0.1%


    assign coefficients[0] = 595;
    assign coefficients[1] = 0;
    assign coefficients[2] = -298;
    assign coefficients[3] = 516;
    assign coefficients[4] = -298;
    assign coefficients[5] = -516;


assign int_a = alpha*$signed(coefficients[0]) + beta*$signed(coefficients[1]);
assign int_b = alpha*$signed(coefficients[2]) + beta*$signed(coefficients[3]);
assign int_c = alpha*$signed(coefficients[4]) + beta*$signed(coefficients[5]);

assign a = int_a >>> 18;
assign b = int_b >>> 18;
assign c = int_c >>> 18;


endmodule