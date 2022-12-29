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

`timescale 10ns / 1ns
`include "interfaces.svh"
`include "axis_BFM.svh"
							
module axi_stream_mux_tb();

    reg  clk, reset;

    reg [1:0] addr;

    axi_stream stream_1();
    axi_stream stream_2();
    axi_stream stream_3();
    axi_stream stream_4();
    axi_stream stream_out();

    axi_stream_mux_4 UUT(
        .clock(clk),
        .reset(reset),
        .address(addr),
        .stream_in_1(stream_1),
        .stream_in_2(stream_2),
        .stream_in_3(stream_3),
        .stream_in_4(stream_4),
        .stream_out(stream_out)
    );

    //clock generation
    initial clk = 0; 
    always #0.5 clk = ~clk; 

    integer i;

    initial begin

        addr <= 0;
        reset <=1'h1;
        stream_out.ready <=1;
        stream_1.initialize();
        stream_2.initialize();
        stream_3.initialize();
        stream_4.initialize();
        #1 reset <=1'h0;
        //TESTS
        #5.5 reset <=1'h1;
        #10 addr <= 0;
        #2 stream_1.data <= $urandom;
        stream_2.data <= $urandom;
        stream_3.data <= $urandom;
        stream_4.data <= $urandom;
        stream_1.dest <= $urandom % 10;
        stream_1.user <= $urandom;
        stream_1.valid <=1;
        #1 stream_1.valid <=0;

        #10 addr <= 1;
        #2 stream_1.data <= $urandom;
        stream_2.data <= $urandom;
        stream_3.data <= $urandom;
        stream_4.data <= $urandom;
        stream_2.dest <= $urandom % 10;
        stream_2.user <= $urandom;
        stream_2.valid <=1;
        #1 stream_2.valid <=0;

        #10 addr <= 2;
        #2 stream_1.data <= $urandom;
        stream_2.data <= $urandom;
        stream_3.data <= $urandom;
        stream_4.data <= $urandom;
        stream_3.dest <= $urandom % 10;
        stream_3.user <= $urandom;
        stream_3.valid <=1;
        #1 stream_3.valid <=0;

        #10 addr <= 3;
        #2 stream_1.data <= $urandom;
        stream_2.data <= $urandom;
        stream_3.data <= $urandom;
        stream_4.data <= $urandom;
        stream_4.dest <= $urandom % 10;
        stream_4.user <= $urandom;
        stream_4.valid <=1;
        #1 stream_4.valid <=0;

    end




endmodule