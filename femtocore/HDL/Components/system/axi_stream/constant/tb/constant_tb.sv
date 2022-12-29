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
`include "axi_lite_BFM.svh"						

module axis_constant_tb();

    reg  clk, reset;

    axi_lite axil();
    axi_lite_BFM axil_bfm;
    
    axi_stream out();
    
    //clock generation
    initial clk = 0; 
    always #0.5 clk = ~clk; 

    axis_constant UUT(
        .clock(clk),
        .reset(reset),
        .sync(1),
        .const_out(out),
        .axil(axil)
    );


    initial begin
        out.ready = 1;
        axil_bfm = new(axil, 1);
        reset <=1'h1;
        #1 reset <=1'h0;
        //TESTS
        #5.5 reset <=1'h1;

        # 10 axil_bfm.write('h43c00004, 'h333);
        #1 axil_bfm.write('h43c00008, 'h44);
        #1 axil_bfm.write('h43c00000, 'h999);


    end

endmodule