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

module clarke (
    input  wire signed [17:0] a,
    input  wire signed [17:0] b,
    input  wire signed [17:0] c,
    output wire signed [17:0] alpha,
    output wire signed [17:0] beta
);

    wire signed [35:0] int_alpha;
    wire signed [35:0] int_beta;


    wire signed [17:0] coefficients [5:0];
//   the following coefficients are calculated assuming a 18 bit fully fractional signed fixed point representation
//   current full scale is 220A maximum quantization error under 0.1%

    assign coefficients[0] = 397;
    assign coefficients[1] = -199;
    assign coefficients[2] = -199;
    assign coefficients[3] = 0;
    assign coefficients[4] = 344;
    assign coefficients[5] = -344;

//Static add/sub is supported
assign int_alpha = a*$signed(coefficients[0]) + b*$signed(coefficients[1]) + c*$signed(coefficients[2]);
assign int_beta  = a*$signed(coefficients[3]) + b*$signed(coefficients[4]) + c*$signed(coefficients[5]);

assign alpha = int_alpha >>> 18;
assign beta  = int_beta  >>> 18;


endmodule