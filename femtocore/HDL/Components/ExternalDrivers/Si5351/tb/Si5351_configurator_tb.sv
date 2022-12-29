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
`include "interfaces.svh"

module si5351_config_tb();

    reg clk, rst, start;


    assign out.ready = 1;
    axi_stream #(
        .DATA_WIDTH(8),
        .DEST_WIDTH(8)
    ) out();
    
    si5351_config UUT(
        .clock(clk),
        .reset(rst),
        .start(start),
        .slave_address(2),
        .config_out(out)
    );
    
    
    //clock generation
    initial clk = 0; 
    always #0.5 clk = ~clk; 
    
    // reset generation
    initial begin
        rst <=1;
        start <= 0;
        #3.5 rst<=0;
        #5 rst <=1;
        #20 start <= 1;
        #1 start <= 0;
    end

    



endmodule