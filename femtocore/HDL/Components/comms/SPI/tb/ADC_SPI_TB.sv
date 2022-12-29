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
`include "axis_BFM.svh"
module ADC_SPI_tb();
    
    logic clk, rst;

    logic mosi, sclk,sclk_en;
    logic spi_mode,ext_start,out_val;
    wire sclk_in;
    wire ss;
    wire ss_in;
    logic sclk_slave;
    logic ss_slave;
    logic miso;

    logic [31:0] read_result;
    logic [15:0] out;


    parameter spi_mode_master = 0, spi_mode_slave = 1;

    assign sclk_in = spi_mode ? sclk_slave & sclk_en : 1'bz;
    assign sclk = !spi_mode ? sclk_in : 1'b0;
    assign ss_in = spi_mode ? ss_slave : 1'bz;
    assign ss = !spi_mode ? ss_in : 1'b0;

    //clock generation
    initial clk = 1; 
    always #0.5 clk = ~clk; 
    

    initial #0.5 sclk_slave = 1;
    always #1 sclk_slave = ~sclk_slave; 

    
    // reset generation
    initial begin
        rst <=1;
        #3 rst<=0;
        #5 rst <=1;
    end


    axis_BFM write_BFM;
    axis_BFM read_req_BFM;
    axis_BFM read_resp_BFM;

    axi_stream read_req();
    axi_stream read_resp();
    axi_stream write();

    axi_lite axi_master();

    axis_to_axil WRITER(
        .clock(clk),
        .reset(rst), 
        .axis_write(write),
        .axis_read_request(read_req),
        .axis_read_response(read_resp),
        .axi_out(axi_master)
    );


    wire cnv_start;

    enable_generator_core eng(
        .clock(clk),
        .reset(rst),
        .gen_enable_in(1),
        .period(100),
        .enable_out(cnv_start)
    );

    SPI DUT(
        .clock(clk),
        .reset(rst),
        .SPI_write_valid(cnv_start),
        .MISO(miso),
        .SCLK(sclk_in),
        .MOSI(mosi),
        .SS(ss_in),
        .axi_in(axi_master)
    );

    
    initial begin
        //INITIAL SETTINGS AND INSTANTIATIONS OF CLASSES
        write_BFM = new(write,1);
        read_req_BFM = new(read_req, 1);
        read_resp_BFM = new(read_resp, 1);

        spi_mode <=spi_mode_master;
        miso <= 0;
        sclk_en <= 0;
        ss_slave <=0;
        ext_start <=0;

        //Text external conversion start
        
        #50 write_BFM.write_dest(32'h1DC2, 'h0);
        #5 write_BFM.write_dest(32'h1B, 'h4);

        #5 spi_mode <=spi_mode_master;

        forever begin
            #5 ext_start <=1;
            #1 ext_start <=0;
             miso = $random();
            #4 miso = $random();
            #4 miso = $random();
            #4 miso = $random();
            #4 miso = $random();
            #4 miso = $random();
            #4 miso = $random();
            #4 miso = $random();
            #4 miso = $random();
            #4 miso = $random();
            #4 miso = $random();
            #4 miso = $random();
        end

    end
    
endmodule