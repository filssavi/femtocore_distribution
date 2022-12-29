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
							
module prioritised_fifo_tb();

    reg  clk, reset;


    axi_stream lp_stream();
    axi_stream hp_stream();
    axi_stream out_stream();

    //clock generation
    initial clk = 0; 
    always #0.5 clk = ~clk; 

    prioritised_fifo UUT(
        .clock(clk),
        .reset(reset),
        .in_lp(lp_stream),
        .in_hp(hp_stream),
        .out(out_stream)
    );


    axis_BFM lp_BFM;
    axis_BFM hp_BFM;

    initial begin
        lp_BFM = new(lp_stream,1);
        hp_BFM = new(hp_stream,1);
        reset <=1'h1;
        out_stream.ready <=0;
        #1 reset <=1'h0;
        //TESTS
        #5.5 reset <=1'h1;

        for(integer i = 0; i<16; i++)begin
            #10 hp_BFM.write($urandom);
            #10 lp_BFM.write($urandom);
        end 
        #10 out_stream.ready <=1;
        #150 out_stream.ready <=0;
        
        for(integer i = 0; i<16; i++)begin
            #10 hp_BFM.write($urandom);
            #10 lp_BFM.write($urandom);
        end
        
        out_stream.ready <=1;
        #150 out_stream.ready <=0;
        #1 reset <=1'h0;
        #5.5 reset <=1'h1;

        for(integer i = 0; i<5; i++)begin
            #10 lp_BFM.write($urandom);
        end 
        #10 hp_BFM.write($urandom);
        #10 out_stream.ready <=1;
        #10 hp_BFM.write($urandom);
        #10 hp_BFM.write($urandom);
        #150 out_stream.ready <=0;        
    end




endmodule