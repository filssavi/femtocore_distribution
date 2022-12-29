// Copyright (C) : 3/17/2019, 6:09:40 PM Filippo Savi - All Rights Reserved
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

module gpio_tb();
    
    logic clk, rst;
    
    axi_lite axil();
    axi_lite_BFM axil_bfm;

    //clock generation
    initial clk = 0; 
    always #0.5 clk = ~clk;
    
    reg [7:0] gpio_i;
    wire [7:0] gpio_o;
    reg [31:0] sb_read_data_test;

    gpio #(
        .INPUT_WIDTH(8),
        .OUTPUT_WIDTH(8)
    ) DUT(
        .clock(clk),
        .reset(rst),
        .gpio_i(gpio_i),
        .gpio_o(gpio_o),
        .axil(axil)
    );


    // reset generation
    initial begin
        axil_bfm = new(axil,1);

        gpio_i = 8'hfe;
        rst <=1;
        #3.5 rst<=0;
        #5 rst <=1;

        #8 axil_bfm.write(32'h0,32'hCA);
        #8 axil_bfm.read(32'h4,sb_read_data_test);
    end


    
endmodule