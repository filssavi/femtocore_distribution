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
`include "SPI_BFM.svh"
`include "axis_BFM.svh"

module MC_spi_bfm_tb();
    
    logic clk, rst;

    event master_task_start;
    event slave_task_start;
    event transaction_check;

    parameter spi_width = 12;
    
    logic [2:0] mosi;
    logic [2:0] miso;
    wire  sclk, ss, out_val;
    logic [31:0] out[2:0];

    reg [31:0] SPI_write_data;
    reg SPI_write_valid;

    SPI_if spi_if_1();
    SPI_if spi_if_2();
    SPI_if spi_if_3();

    assign spi_if_1.SS = ss;
    assign spi_if_1.SCLK = sclk;
    assign spi_if_1.MOSI = mosi[0];
    assign miso[0] = spi_if_1.MISO;


    assign spi_if_2.SS = ss;
    assign spi_if_2.SCLK = sclk;
    assign spi_if_2.MOSI = mosi[1];
    assign miso[1] = spi_if_2.MISO;


    assign spi_if_3.SS = ss;
    assign spi_if_3.SCLK = sclk;
    assign spi_if_3.MOSI = mosi[2];
    assign miso[2] = spi_if_3.MISO;

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
    
    
    SPI #(
        .N_CHANNELS(3)
    )DUT(
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


    SPI_BFM spi_bfm_1;
    SPI_BFM spi_bfm_2;
    SPI_BFM spi_bfm_3;

    initial begin
        //INITIAL SETTINGS AND INSTANTIATIONS OF CLASSES
        write_BFM = new(write,1);
        read_req_BFM = new(read_req, 1);
        read_resp_BFM = new(read_resp, 1);
        spi_bfm_1 = new(spi_if_1,1);
        spi_bfm_2 = new(spi_if_2,1);
        spi_bfm_3 = new(spi_if_3,1);
        SPI_write_valid <= 0;
        SPI_write_data <= 0;

        //TEST MASTER MODE
        #10 -> slave_task_start;
        #2 -> master_task_start;
    end

    spi_checker #(
        .spi_width(spi_width)
    ) slave_1 (
        .clk(clk),
        .reset(rst),
        .SCLK(spi_if_1.SCLK),
        .SS(spi_if_1.SS),
        .MOSI(spi_if_1.MOSI),
        .MISO(spi_if_1.MISO)
    );

    spi_checker #(
        .spi_width(spi_width)
    ) slave_2 (
        .clk(clk),
        .reset(rst),
        .SCLK(spi_if_2.SCLK),
        .SS(spi_if_2.SS),
        .MOSI(spi_if_2.MOSI),
        .MISO(spi_if_2.MISO)
    );

    spi_checker #(
        .spi_width(spi_width)
    ) slave_3 (
        .clk(clk),
        .reset(rst),
        .SCLK(spi_if_3.SCLK),
        .SS(spi_if_3.SS),
        .MOSI(spi_if_3.MOSI),
        .MISO(spi_if_3.MISO)
    );

    logic [spi_width-1:0] master_data_s1;
    logic [spi_width-1:0] master_data_s2;
    logic [spi_width-1:0] master_data_s3;
    
    initial begin : master_1_axi
        @(master_task_start);
            #10 write_BFM.write_dest(32'h131c2, 'h0);
            #5 write_BFM.write_dest(32'h1b, 'h4);
            
        forever begin
            #5;
            master_data_s1 = $urandom();
            master_data_s2 = $urandom();
            master_data_s3 = $urandom();

            write_BFM.write_dest(master_data_s1, 32'h43C00010);
            write_BFM.write_dest(master_data_s2, 32'h43C00014);
            write_BFM.write_dest(master_data_s3, 32'h43C00018);
            #5 write_BFM.write_dest(31'h0, 32'h43C0000C);
            #120;
            #3;
        end
    end




    // initial begin: test_checker_1
    //     @(transaction_check);
    //     #1;
    //     //SLAVE 1
    //     assert (slave_data_e1[11:0] == slave_data_r1[11:0]) 
    //     else begin
    //         $display("MOSI 1 SIDE ERROR: expected value %h | recived value %h", slave_data_e1[11:0], slave_data_r1[11:0]);
    //         $stop();
    //     end
    //     assert (master_data_e1[11:0] == master_data_r1[11:0]) 
    //     else begin
    //         $display("MISO 1 SIDE ERROR: expected value %h | recived value %h", master_data_e1[11:0], master_data_r1[11:0]);
    //         $stop();
    //     end
    //     //SLAVE 2
    //     assert (slave_data_e2[11:0] == slave_data_r2[11:0]) 
    //     else begin
    //         $display("MOSI 2 SIDE ERROR: expected value %h | recived value %h", slave_data_e2[11:0], slave_data_r2[11:0]);
    //         $stop();
    //     end
    //     assert (master_data_e2[11:0] == master_data_r2[11:0]) 
    //     else begin
    //         $display("MISO 2 SIDE ERROR: expected value %h | recived value %h", master_data_e2[11:0], master_data_r2[11:0]);
    //         $stop();
    //     end
    //     //SLAVE 3
    //     assert (slave_data_e3[11:0] == slave_data_r3[11:0]) 
    //     else begin
    //         $display("MOSI 3 SIDE ERROR: expected value %h | recived value %h", slave_data_e3[11:0], slave_data_r3[11:0]);
    //         $stop();
    //     end
    //     assert (master_data_e3[11:0] == master_data_r3[11:0]) 
    //     else begin
    //         $display("MISO 3 SIDE ERROR: expected value %h | recived value %h", master_data_e3[11:0], master_data_r3[11:0]);
    //         $stop();
    //     end
    //     #1;
    // end

endmodule


module spi_checker #(
    parameter spi_width = 12
) (
    input wire clk,
    input wire reset,
    input wire SCLK,
    input wire SS,
    input wire MOSI,
    output reg MISO
);

    reg [11:0] slave_register = 0;

    always @(negedge SS) begin
        slave_register = $urandom;
    end

    always @(posedge SCLK) begin
        if(!reset)begin
            MISO <= 0;
        end else begin
            MISO <= slave_register[11]; 

        end
    end

    always @(negedge SCLK) begin
        slave_register[0] = MOSI;
        slave_register[11:0] = (slave_register[11:0] << 1);     
    end


    wire [11:0] output_reg;
    
    genvar i;
    for(i = 0; i<12; i = i+1)begin
        assign output_reg[i] = slave_register[11-i];
    end


    
endmodule