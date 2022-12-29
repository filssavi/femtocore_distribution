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

module EnableGen_core_tb();
    
    logic clk, rst;
    logic gen_en;
    wire en_out;

    enable_generator_core #(
        .CLOCK_MODE("TRUE")
    ) uut(
        .clock(clk),
        .reset(rst),
        .gen_enable_in(gen_en),
        .period(33),
        .enable_out(en_out)
    );

    //clock generation
    initial clk = 1; 
    always #0.5 clk = ~clk; 
    
    // reset generation
    initial begin
        rst <=1;
        #3 rst<=0;
        #5 rst <=1;
        #10 gen_en <= 1;
    end


    
endmodule