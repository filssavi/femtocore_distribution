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
							
module axi_stream_combiner_tb();

    reg  clk, reset;

    reg out_ready;
    wire dout_valid;
    wire [31:0] dout_data;

    axi_stream stream_1();
    axi_stream stream_2();


    axi_stream_combiner_6 UUT(
        .clock(clk),
        .reset(reset),
        .stream_1_data(stream_1.data),
        .stream_1_dest(0),
        .stream_1_valid(stream_1.valid),
        .stream_1_ready(stream_1.ready),
        .stream_2_data(stream_2.data),
        .stream_2_valid(stream_2.valid),
        .stream_2_ready(stream_2.ready),
        .stream_2_dest(1),
        .stream_out_ready(out_ready),
        .stream_out_valid(out_valid),
        .stream_out_data(out_data)
    );



    //clock generation
    initial clk = 0; 
    always #0.5 clk = ~clk; 

    axis_BFM BFM_1;
    axis_BFM BFM_2;

    integer i;

    initial begin
        BFM_1 = new(stream_1,1);
        BFM_2 = new(stream_2,1);
        reset <=1'h1;
        out_ready <=1;
        #1 reset <=1'h0;
        //TESTS
        #5.5 reset <=1'h1;
        #10 BFM_1.write($urandom);
        #10 BFM_2.write($urandom);
        #10 BFM_1.write($urandom);
        #10 BFM_2.write($urandom);
        #10 BFM_1.write($urandom);
        #10 BFM_2.write($urandom);
        #10 BFM_1.write($urandom);
        #10 BFM_2.write($urandom);
        out_ready <=0;
        #100 out_ready <=1;
        #10 BFM_1.write($urandom);
        #10 BFM_2.write($urandom);
        #10 BFM_1.write($urandom);
        #10 BFM_2.write($urandom);
        #10 BFM_1.write($urandom);
        #10 BFM_2.write($urandom);
        #10 BFM_1.write($urandom);
        #10 BFM_2.write($urandom);


        for(i = 0; i< 1050; i++)begin
            #10 BFM_1.write($urandom);
            #10 BFM_2.write($urandom);
        end
    end




endmodule