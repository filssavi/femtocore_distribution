`timescale 1ns / 1ps
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
`include "axis_BFM.svh"
`include "interfaces.svh"


module pwm_tl_exp();

    reg  clk, reset;
    reg ext_tb=0;
    wire [11:0] pwm;
    
    parameter SB_TIMEBASE_ADDR = 'h43C00000;
    parameter SB_CHAIN_1_ADDR = 'h43C00004;
    parameter SB_CHAIN_2_ADDR = 'h43C00040;


    axi_lite axil();

    axis_BFM write_BFM;
    axis_BFM read_req_BFM;
    axis_BFM read_resp_BFM;

    axi_stream read_req();
    axi_stream read_resp();
    axi_stream write();

    axis_to_axil WRITER(
        .clock(clk),
        .reset(reset), 
        .axis_write(write),
        .axis_read_request(read_req),
        .axis_read_response(read_resp),
        .axi_out(axil)
    );
    
    PwmGenerator UUT (
        .clock(clk),
        .reset(reset),
        .ext_timebase(ext_tb),
        .pwm_out(pwm),
        .fault(0),
        .axi_in(axil)
    );

    localparam BASE_AXI = SB_TIMEBASE_ADDR;
    localparam CHAIN_1_AXI = BASE_AXI+'h100;
    localparam CHAIN_2_AXI = BASE_AXI+'h200;
    
    //clock generation
    initial clk = 0; 
    always #1.25 clk = ~clk; 

    initial begin

        write_BFM = new(write,2.5);
        read_req_BFM = new(read_req, 2.5);
        read_resp_BFM = new(read_resp, 2.5);

        //Initial status
        reset <=1'h1;
        #1 reset <=1'h0;
        //TESTS
        #5.5 reset <=1'h1;

        #3 write_BFM.write_dest('h1100 ,BASE_AXI);

        #3 write_BFM.write_dest('h0 ,CHAIN_1_AXI+'h34);
        #3 write_BFM.write_dest('h1 ,CHAIN_1_AXI+'h38);
        #3 write_BFM.write_dest('h3f ,CHAIN_1_AXI+'h30);
        #3 write_BFM.write_dest('h13f7 ,CHAIN_1_AXI+'h28);
        #3 write_BFM.write_dest('h4d8 ,CHAIN_1_AXI+'h4);
        #3 write_BFM.write_dest('h524 ,CHAIN_1_AXI+'h8);
        #3 write_BFM.write_dest('hf05 ,CHAIN_1_AXI+'h10);
        #3 write_BFM.write_dest('heeb ,CHAIN_1_AXI+'h14);

        #3 write_BFM.write_dest('h1128 ,BASE_AXI);
        #50000;

        #3 write_BFM.write_dest('h2d8 ,CHAIN_1_AXI+'h4);
        #3 write_BFM.write_dest('h724 ,CHAIN_1_AXI+'h8);
        
        #50000;
        
        #3 write_BFM.write_dest('h1168 ,BASE_AXI);
        #200 #3 write_BFM.write_dest('h1128 ,BASE_AXI);
        #2000 write_BFM.write_dest('h1100 ,BASE_AXI);
    end

endmodule
