

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
`include "axi_lite_BFM.svh"
`include "interfaces.svh"

module PID_tb();
    reg  clk, reset;

    axi_lite axil();
    axi_lite_BFM axil_bfm;

    axi_stream reference();
    axi_stream feedback();
    axi_stream out();
    axi_stream error_mon();


    //clock generation
    initial clk = 0; 
    always #0.5 clk = ~clk; 

    
    PID #(
        .INPUT_DATA_WIDTH(16)
    )uut (
        .clock(clk),
        .reset(reset),
        .axil(axil),
        .reference(reference),
        .feedback(feedback),
        .out(out),
        .error_mon(error_mon)
    );

    initial begin
        axil_bfm = new(axil, 1);
        reference.initialize();
        feedback.initialize();
        //Initial status
        reset <=1'h1;
        #1 reset <=1'h0;
        //TESTS
        #5.5 reset <=1'h1;


        //Compare low 1
        #8;
        axil_bfm.write(32'h00, 32'h1);
        axil_bfm.write(32'h04, 32'h154);
        axil_bfm.write(32'h08, 32'h2645);
        axil_bfm.write(32'h0C, 32'h64);
        axil_bfm.write(32'h10, 32'h333);
        axil_bfm.write(32'h14, 32'h222);
        axil_bfm.write(32'h18, 32'h555);
        axil_bfm.write(32'h1C, 32'h666);
        axil_bfm.write(32'h20, 32'h777);

    end

endmodule