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
`include "axis_BFM.svh"

module SPI_tb();
    
    logic clk, rst;

    logic mosi, sclk;
    logic spi_mode,ext_start,out_val;
    wire ss;
    logic miso;

    logic [31:0] read_result;
    logic [31:0] out [2:0];

    reg [31:0] SPI_write_data;
    reg SPI_write_valid;

    parameter spi_mode_master = 0, spi_mode_slave = 1;

    //clock generation
    initial clk = 1; 
    always #0.5 clk = ~clk; 
    

    
    // reset generation
    initial begin
        rst <=1;
        #3 rst<=0;
        #5 rst <=1;
    end

    axi_lite axil();
    
    axis_BFM write_BFM;
    axis_BFM read_req_BFM;
    axis_BFM read_resp_BFM;

    axi_stream read_req();
    axi_stream read_resp();
    axi_stream write();

    axis_to_axil WRITER(
        .clock(clk),
        .reset(rst), 
        .axis_write(write),
        .axis_read_request(read_req),
        .axis_read_response(read_resp),
        .axi_out(axil)
    );

    SPI DUT(
        .clock(clk),
        .reset(rst),
        .data_valid(out_val),
        .data_out(out),
        .MISO(miso),
        .SCLK(sclk),
        .MOSI(mosi),
        .SS(ss),
        .axi_in(axil),
        .SPI_write_data(SPI_write_data),
        .SPI_write_valid(SPI_write_valid)
    );


    initial begin
        
        //TEST MASTER MODE
        #10 write_BFM.write_dest(32'h101c4, 32'h43C00000);
        #5 write_BFM.write_dest(32'h1c, 32'h43C00004);
        #5 write_BFM.write_dest(32'h0, 32'h43C00008);
        #5 write_BFM.write_dest(32'hCAFE, 32'h43C0000C);
        #50 write_BFM.write_dest(32'h0, 32'h43C0000C);
        #10 write_BFM.write_dest(32'h111c4, 32'h43C00000);
        #50 write_BFM.write_dest(32'hff, 32'h43C00014);
    
    end
    
    initial begin
        //INITIAL SETTINGS AND INSTANTIATIONS OF CLASSES
        write_BFM = new(write,1);
        read_req_BFM = new(read_req, 1);
        read_resp_BFM = new(read_resp, 1);

        spi_mode <=spi_mode_master;
        miso <= 0;
        ext_start <=0;
        SPI_write_valid <= 0;
        SPI_write_data <= 0;

        //TEST MASTER MODE
        #10 write_BFM.write_dest(31'h101c4, 'h0);
        #5 write_BFM.write_dest(31'h1c, 'h4);
        #5 write_BFM.write_dest(31'hCAFE, 'h10);
        #5 write_BFM.write_dest(31'h0, 'hC);
        #50 write_BFM.write_dest(31'h0, 'hC);
        #5 read_req_BFM.write('h10);
        read_resp_BFM.read(read_result);
        #10 write_BFM.write_dest(31'h111c4, 'h0);
        #50 write_BFM.write_dest(31'hff, 'h14);
        
        #100 SPI_write_valid <= 1;
        SPI_write_data <= 'hFE;
        #1 SPI_write_valid <= 0;
        #500;
        
        //Text external conversion start

        #10 rst<=0;
        #10 rst <=1;
        
        #5 write_BFM.write_dest(31'hFF2,'h0);
        #5 write_BFM.write_dest(31'hF, 'h4);
        #5 spi_mode <=spi_mode_master;
        #5 write_BFM.write_dest(31'hFEDC, 'h10);
        #5 ext_start <=1;
        #1 ext_start <=0;


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