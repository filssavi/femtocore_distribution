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

module trigonometricUnit (
    input  wire clk,
    input  wire [15:0] theta,
    output reg signed [15:0] sin_theta,
    output reg signed [15:0] cos_theta,
    output reg output_valid
);

    reg [15:0] latched_theta = 0;

    // Declare the RAM variable
    reg [15:0] SinTable[511:0];

    reg [9:0] addr_a = 0;
    reg [9:0] addr_b = 0;
    
    reg [9:0] scaled_theta;
    reg [15:0] table_sin_out = 0;
    reg [15:0] table_cos_out = 0;

    initial begin : INIT
        $readmemh("tau_sineTable.dat", SinTable);
    end

    // sin(x) =  LUT(x)       for [0 pi/2]
    //           LUT(pi-x)    for [pi/2 pi]
    //           -LUT(x-pi)   for [pi/2 3pi/2]
    //           -LUT(2pi-x)  for [3pi/2 2pi]
    // cos(x) =  LUT2(x)      for [0 pi/2]
    //           -LUT2(pi-x)  for [pi/2 pi]
    //           -LUT2(x-pi)  for [pi/2 3pi/2]
    //           LUT2(2pi-x)  for [3pi/2 2pi]

    always @ (posedge clk) begin
        if(theta != latched_theta & output_valid) begin
            output_valid <= 0;
        end else begin
            output_valid <= 1;
        end
        
        latched_theta <= theta;
        // look up sin and cos magnitudes
        table_sin_out <= SinTable[addr_b];
        table_cos_out <= SinTable[addr_a];

        // Add right sign to sin and cos magnitudes
        if(theta<16'h4000) begin
            sin_theta <=  (table_sin_out >> 1);
            cos_theta <=  (table_cos_out >> 1);
        end else if(theta<16'h8000) begin
            sin_theta <=  (table_sin_out >> 1);
            cos_theta <= -(table_cos_out >> 1);
        end else if(theta<16'hC000) begin
            sin_theta <= -(table_sin_out >> 1);
            cos_theta <= -(table_cos_out >> 1);
        end else begin
            sin_theta <= -(table_sin_out >> 1);
            cos_theta <=  (table_cos_out >> 1);
        end 
    end

    always @(*) begin 

        // find first quadrant equivalent angle and scalefrom 16 bit angle to 9 bit adress 
        if(theta<16'h4000) begin
            scaled_theta <= theta >> 5;
        end else if(theta<16'h8000) begin
            scaled_theta <= (16'h8000-theta) >> 5;
        end else if(theta<16'hC000) begin
            scaled_theta <= (theta-16'h8000) >> 5;
        end else begin
            scaled_theta <= (16'hffff-theta) >> 5;
        end 

        // find separate sine and cosine angles
        addr_a <= scaled_theta;
        addr_b <= 10'h1FF - scaled_theta;
    end 

endmodule