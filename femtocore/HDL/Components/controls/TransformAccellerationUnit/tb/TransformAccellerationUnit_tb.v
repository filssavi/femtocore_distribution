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

module TAU_tb();

    reg  clk, reset, read, write;
    reg [7:0] address;
    wire [31:0] readdata;
    reg [31:0] writedata;
    wire tau_ready;

    reg [15:0] theta;
    reg [53:0] clarke_in;
    reg [35:0] park_in;
    wire [35:0] clarke_out;
    wire [35:0] park_out;
    reg [35:0] inverse_clarke_in;
    reg [35:0] inverse_park_in1;
    wire [53:0] inverse_clarke_out;
    wire [35:0] inverse_park_out;

    // TransformAccellerationUnit tb(
    //     .clock(clk),
    //     .reset(reset),
    //     .tau_address(address),
    //     .tau_read(read),
    //     .tau_readdata(readdata),
    //     .tau_write(write),
    //     .tau_writedata(writedata),
    //     .tau_ready(tau_ready),
    //     .theta(theta),
    //     .clarke_in(clarke_in),
    //     .park_in(park_in),
    //     .clarke_out(clarke_out),
    //     .park_out(park_out),
    //     .inverse_clarke_in(inverse_clarke_in),
    //     .inverse_park_in(inverse_park_in1),
    //     .inverse_clarke_out(inverse_clarke_out),
    //     .inverse_park_out(inverse_park_out)
    // );

    wire [35:0] single_park_out;
    reg [35:0] single_park_in;
     park tb2(
        .clock(clk),
        .reset(reset),
        .alpha(single_park_in[17:0]),
        .beta(single_park_in[35:18]),
        .theta(theta),
        .d(single_park_out[17:0]),
        .q(single_park_out[35:18])
    );



    wire [35:0] single_antipark_out;
    reg [35:0] single_antipark_in;

    antiPark tb3(
        .clock(clk),
        .reset(reset),
        .theta(theta),
        .d(single_antipark_in[17:0]),
        .q(single_antipark_in[35:18]),
        .alpha(single_antipark_out[17:0]),
        .beta(single_antipark_out[35:18])
    );

    //clock generation
    initial clk = 0; 
    always #0.5 clk = ~clk; 

    initial begin

        theta <= 0;
        clarke_in <= 54'sh30000C0003;
        inverse_park_in1 <= 36'shC0003;
        inverse_clarke_in <= 0;
        park_in <= 0;
        single_park_in[17:0] <= 18'hA000;
        single_park_in[35:18] <= 18'h5000;

        single_antipark_in[17:0] <= 18'hA000;
        single_antipark_in[35:18] <= 18'h5000;

        //Initial status
        reset <=1'h1;
        address <=1'h0;
        read <=1'b0;
        write <=1'h0;
        writedata <= 32'h0;
        #2 reset <=1'h0;

        //TESTS
        #5.5 reset <=1'h1;

        #10 clarke_in <= 54'sh100A040A480;
        inverse_park_in1 <= 36'sh80002;
        #10 theta <= 16'h1f60; // 45 deg
        #10 theta <= 16'h5f8e; // 135 deg
        #10 theta <= 16'h9fbc; // 225 deg
        #10 theta <= 16'hdfe9; // 315 deg
        #10 theta <= 16'h14ae; // 30 deg
        #10 theta <= 16'h54dc; // 120 deg
        #10 theta <= 16'h9509; // 210 deg
        #10 theta <= 16'hd537; // 300 deg


    end
endmodule