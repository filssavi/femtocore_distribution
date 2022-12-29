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
module ALU_tb();

    reg clk, rst;
    
    axi_stream op_a();
    axi_stream op_b();
    axi_stream op_res();

    ALU #(
        .BUFFERED_OUTPUT("TRUE")
    ) UUT(
        .clock(clk),
        .reset(rst),
        .operand_a(op_a),
        .operand_b(op_b),
        .result(op_res),
        .operation(0),
        .flags()
    );



    //clock generation
    initial clk = 0; 
    always #0.5 clk = ~clk; 
    
    // reset generation
    initial begin
        rst <=1;
        op_a.initialize();
        op_b.initialize();
        op_res.initialize();
        op_res.ready <= 1;

        #3 rst<=0;
        #10.5 rst <=1;
        
        // IMMEDIATE TEST
        #10 op_a.data = 5;
        op_b.data = 1;
        op_a.valid = 1;
        op_b.valid = 1;
        #1 op_a.valid = 0;
        op_b.valid = 0;
        
        // DELAYED OP TEST
        #30 op_a.data = 2;
         op_a.valid = 1;
        #1 op_a.valid = 0;

        #12 op_b.data = 1;
         op_b.valid = 1;
        #1 op_b.valid = 0;

        


    end

    
endmodule
