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

module SinCosLUT (
    input  wire clock,
    input  wire reset,
    axi_stream.slave theta,
    axi_stream.master sin,
    axi_stream.master cos
);

    reg [15:0] inner_sin_data = 0;
    reg [15:0] inner_cos_data = 0;
    reg [31:0] inner_dest = 0;

    // Declare the RAM variable
    reg [15:0] SinTable[511:0];

    reg [8:0] addr_a = 0;
    reg [8:0] addr_b = 0;
    
    reg [8:0] scaled_theta;
    reg [15:0] table_sin_out = 0;
    reg [15:0] table_cos_out = 0;
    reg [1:0] quadrant;
    
    initial begin : INIT
        $readmemh("sineTable_lut.dat", SinTable);
    end

    assign theta.ready = 1;

    assign cos.data = {{16{cos.valid & inner_cos_data[15]}}, inner_cos_data & {16{cos.valid}}};
    assign sin.data = {{16{sin.valid & inner_sin_data[15]}}, inner_sin_data & {16{sin.valid}}}; 
    assign sin.dest = inner_dest & {16{sin.valid}};
    assign cos.dest = inner_dest & {16{cos.valid}};

    // sin(x) =  LUT(x)       for [0 pi/2]
    //           LUT(pi-x)    for [pi/2 pi]
    //           -LUT(x-pi)   for [pi/2 3pi/2]
    //           -LUT(2pi-x)  for [3pi/2 2pi]
    // cos(x) =  LUT2(x)      for [0 pi/2]
    //           -LUT2(pi-x)  for [pi/2 pi]
    //           -LUT2(x-pi)  for [pi/2 3pi/2]
    //           LUT2(2pi-x)  for [3pi/2 2pi]

    always @ (posedge clock) begin

        inner_dest <= theta.dest;
        sin.valid <= theta.valid;
        cos.valid <= theta.valid;

        // look up sin and cos magnitudes
        table_sin_out <= SinTable[addr_b];
        table_cos_out <= SinTable[addr_a];

        case (quadrant)
            0:begin
                inner_sin_data <=  (table_sin_out >> 1);
                inner_cos_data <=  (table_cos_out >> 1);
            end 
            1:begin
                inner_sin_data <=  (table_sin_out >> 1);
                inner_cos_data <= -(table_cos_out >> 1);
            end
            2:begin
                inner_sin_data <= -(table_sin_out >> 1);
                inner_cos_data <= -(table_cos_out >> 1);
            end
            3:begin
                inner_sin_data <= -(table_sin_out >> 1);
                inner_cos_data <=  (table_cos_out >> 1);
            end
        endcase
    end



    always @(posedge clock) begin 
        if(~reset)begin
            quadrant <= 0;
            scaled_theta <= 0;
        end else begin
            // find first quadrant equivalent angle and scalefrom 16 bit angle to 9 bit adress 
            if(theta.data<=16'h3fff) begin
                quadrant <= 0;
                scaled_theta <= theta.data >> 5;
            end else if(theta.data=='h4000) begin
                quadrant <= 1;
                scaled_theta <= 'h1ff;
            end else if(theta.data<16'h8000) begin
                quadrant <= 1;
                scaled_theta <= (16'h8000-theta.data) >> 5;
            end else if(theta.data<16'hC000) begin
                quadrant <= 2;
                scaled_theta <= (theta.data-16'h8000) >> 5;
            end else begin
                quadrant <= 3;
                scaled_theta <= (16'hffff-theta.data) >> 5;
            end 

        // find separate sine and cosine angles
        addr_a <= scaled_theta;
        addr_b <= 10'h1FF - scaled_theta;
        end
        
    end 

endmodule