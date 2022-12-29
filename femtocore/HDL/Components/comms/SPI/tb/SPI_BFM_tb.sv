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
`include "SPI_BFM.svh"

module SPI_bfm_tb();
    
    logic clk, rst;

    event master_task_start;
    event slave_task_start;
    event transaction_check;

    parameter spi_width = 12;

    logic mosi, sclk;
    logic out_val;
    wire ss;
    logic sclk_slave;
    wire miso;
    logic [31:0] out[0:0];

    reg [31:0] SPI_write_data;
    reg SPI_write_valid;

    parameter spi_mode_master = 0, spi_mode_slave = 1;

    assign spi_if.SS = ss;
    assign spi_if.SCLK = sclk;
    assign spi_if.MOSI = mosi;
    assign miso = spi_if.MISO;

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

    SPI_if spi_if();

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
    
    SPI #(
        .N_CHANNELS(1)
    ) DUT(
        .clock(clk),
        .reset(rst),
        .data_valid(out_val),
        .data_out(out),
        .MISO(miso),
        .SCLK(sclk),
        .MOSI(mosi),
        .SS(ss),
        .axi_in(axi_master),
        .SPI_write_data(SPI_write_data),
        .SPI_write_valid(SPI_write_valid)
    );


    SPI_BFM spi_bfm;

    initial begin
        //INITIAL SETTINGS AND INSTANTIATIONS OF CLASSES
        write_BFM = new(write,1);
        read_req_BFM = new(read_req, 1);
        read_resp_BFM = new(read_resp, 1);
        read_resp.ready = 1;
        spi_bfm = new(spi_if,1);
        SPI_write_valid <= 0;
        SPI_write_data <= 0;

        //TEST MASTER MODE
        #10 -> slave_task_start;
        #2 -> master_task_start;
    end
    


    logic [spi_width-1:0] slave_data_s = 0;
    logic [spi_width-1:0] slave_data_e = 0;
    logic [spi_width-1:0] slave_data_r = 0;
    logic [spi_width-1:0] master_data_s =0;
    logic [spi_width-1:0] master_data_e =0;
    logic [spi_width-1:0] master_data_r =0;
    
    initial begin : slave
        @(slave_task_start);
        forever begin
            slave_data_s = $urandom;
            spi_bfm.transfer(slave_data_s, spi_width,master_data_r);
            slave_data_e = slave_data_s;
        end
    end


    initial begin : master
        @(master_task_start);
            #10 write_BFM.write_dest(32'h131c2, 'h0);
            #10 write_BFM.write_dest(32'h1b, 'h4);
            
        forever begin
            #10 master_data_s = $urandom;
            write_BFM.write_dest(master_data_s, 'h10);
            #10 write_BFM.write_dest(31'h0, 'hC);
            #10 read_req_BFM.write('h10);
             read_resp_BFM.read(slave_data_r);
            master_data_e <= master_data_s;
            #2->transaction_check;
        end
    end
    
    logic trans_check = 0;
    initial begin: test_checker
        @(transaction_check);
        trans_check <= 1;
        assert (slave_data_e[11:0] == slave_data_r[11:0]) 
        else begin
            $display("MISO SIDE ERROR: expected value %h | recived value %h", slave_data_e[11:0], slave_data_r[11:0]);
            $stop();
        end
        assert (master_data_e[11:0] == master_data_r[11:0]) 
        else begin
            $display("MISO SIDE ERROR: expected value %h | recived value %h", master_data_e[11:0], master_data_r[11:0]);
            $stop();
        end
        #1 trans_check <= 0;
    end

endmodule