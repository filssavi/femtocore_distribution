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

module AD2S1210_tb();
    reg clk, rst, start;

    axi_lite test_axi();
    axi_stream resolver_out();

    wire ss;
    wire mosi;
    reg miso = 0;
    reg spi_mode =0;

    wire sclk;

    wire [1:0] RES_A;
    wire [1:0] RES_RE;
    wire RES_SAMPLE, RES_RESET;

    ad2s1210_tl_test UUT(
        .clock(clk),
        .reset(rst),
        .R_SDO_RES(miso),
        .R_SDI_RES(mosi),
        .R_WR(ss),
        .R_SCK_RES(sclk),
        .R_A0(RES_A[0]),
        .R_A1(RES_A[1]),
        .R_RE0(RES_RE[0]),
        .R_RE1(RES_RE[1]),
        .R_SAMPLE(RES_SAMPLE),
        .R_RESET(RES_RESET),
        .axi_in(test_axi),
        .resolver_out(resolver_out)
    );

    axi_lite_BFM axil_bfm;

    localparam CONTROLLER_ADDRESS = 32'h43c00000;
    localparam SPI_ADDRESS = CONTROLLER_ADDRESS+'h40;
    localparam TB_ADDRESS = CONTROLLER_ADDRESS+'h100;

    //clock generation
    initial clk = 0; 
    always #0.5 clk = ~clk; 

    reg config_done = 0;
    // reset generation
    initial begin
        BFM = new(s,1);
        axil_bfm = new(test_axi, 1);
        rst <=1;
        start <= 0;
        #3.5 rst<=0;
        #5 rst <=1;
        #8;

        axil_bfm.write(CONTROLLER_ADDRESS + 'h28, 'h16501c14);
        #3 axil_bfm.write(SPI_ADDRESS + 'h04 ,31'h1c);
        #5 axil_bfm.write(SPI_ADDRESS + 'h00 ,31'h3e184);
        axil_bfm.write(CONTROLLER_ADDRESS + 'h24, 'h0);
        #60 axil_bfm.write(CONTROLLER_ADDRESS + 'h24, 'h1); 
        #8800 
        #10 axil_bfm.write(TB_ADDRESS + 'h4, 8000);
        
        #10 axil_bfm.write(TB_ADDRESS + 'h8, 300);
        #10 axil_bfm.write(TB_ADDRESS + 'hC, 3500);
        #10 axil_bfm.write(TB_ADDRESS, 'h1);
        #1900 config_done = 1;

    end

    reg test_read = 0;
    reg [31:0] prev_data = 0;

    always@(negedge RES_SAMPLE)begin
        if(config_done)begin
            test_read = 1;
            prev_data = resolver_out.data; 
            #264.5;
            assert(resolver_out.valid == 1)
            else begin
                $display("RESOLVER OUT VALID ERROR: Resolver out valid did not raise when expected");
                $stop();
            end
            test_read = 0;
            assert(resolver_out.data != prev_data)
            else begin
                $display("RESOLVER OUT DATA ERROR: Resolver out data is stuck and did not change as expected");
                $stop();
            end
            #1;
            assert(resolver_out.valid == 0)
            else begin
                $display("RESOLVER OUT VALID ERROR: Resolver out valid remained high more than necessary");
                $stop();
            end
        end
    end


    always@(posedge sclk)begin
        miso = $urandom;
    end

endmodule