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
`include "axis_BFM.svh"
`include "interfaces.svh"

module I2C_tb();
    
    logic clk, rst;

    reg start;
    
    reg slave_disable;

    wire i2c_scl, sda_in, sda_out;
    wire i2c_sda, scl_in, scl_out;
    wire i2c_scl_en, i2c_sda_en; 

    assign i2c_sda = i2c_sda_en ? sda_out : 1'b1; // put z instead of 1 when a slave is connected
    assign sda_in = i2c_sda;

    assign i2c_scl = i2c_scl_en & ~scl_out ? 0 : 1'b1; // put z instead of 1 when a slave is connected

    assign scl_in = i2c_scl;

    axi_lite axi_master();

    axi_stream read_req();
    axi_stream read_resp();
    axi_stream write();

    axis_BFM write_BFM;
    axis_BFM read_req_BFM;
    axis_BFM read_resp_BFM;

    si5351_config configurator(
        .clock(clk),
        .reset(rst),
        .start(start),
        .slave_address(8'h62),
        .config_out(write)
    );

    axis_to_axil WRITER(
        .clock(clk),
        .reset(rst), 
        .axis_write(write),
        .axis_read_request(read_req),
        .axis_read_response(read_resp),
        .axi_out(axi_master)
    );
    
    I2c #(
        .FIXED_PERIOD("TRUE")
    ) UUT(
        .clock(clk),
        .reset(rst),
        .i2c_scl_in(scl_in),
        .i2c_scl_out(scl_out),
        .i2c_sda_out_en(i2c_sda_en),
        .i2c_sda_in(sda_in),
        .i2c_sda_out(sda_out),
        .i2c_scl_out_en(i2c_scl_en),
        .axi_in(axi_master)
    );



    logic [31:0] readdata;
    
    //clock generation
    initial clk = 0; 
    always #1.25 clk = ~clk; 
    
    // reset generation
    initial begin
        readdata = 0;
        write_BFM = new(write,1);
        read_req_BFM = new(read_req, 1);
        read_resp_BFM = new(read_resp, 1);
        read_resp.ready = 1;
        start = 0;
        rst =1;
        slave_disable =0;
        #3.5 rst = 0;
        #10.5 rst = 1;
        
        write_BFM.write_dest(32'h30, 8'h4);
        
        #20 read_req_BFM.write( 8'h4);
        #5 read_resp_BFM.read(readdata);
        

        #30 start <= 1;
        #1.5 start <= 0;
        #77950 slave_disable <= 1;
    end


    
endmodule