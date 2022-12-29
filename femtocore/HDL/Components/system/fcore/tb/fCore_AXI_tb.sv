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

`timescale 10ns / 1ns
`include "interfaces.svh"
`include "axi_lite_BFM.svh"

import axi_vip_pkg::*;
import vip_bd_axi_vip_0_0_pkg::*;

module fCore_AXI_tb();

    `define DEBUG

    reg core_clk, io_clk, rst, run,programming_start;
    
    axi_stream op_a();
    axi_stream dummy();
    axi_stream op_res();
    axi_lite axi_in();
    AXI axi_programmer();

    axi_stream dma_read_request();
    axi_stream dma_read_response();

    axi_lite_BFM axil_bfm;
     
    vip_bd_wrapper Programmer(
        .clock(core_clk),
        .reset(rst),
        .axi(axi_programmer)
    );

    fCore UUT(
        .clock(core_clk),
        .reset(rst),
        .run(run),
        .control_axi_in(axi_in),
        .axis_dma(dummy),
        .axi(axi_programmer),
        .axis_dma_read_request(dma_read_request),
        .axis_dma_read_response(dma_read_response)
    );

    axi_transaction wr_transaction;
    vip_bd_axi_vip_0_0_mst_t master;
    xil_axi_resp_t transaction_response;
    reg [31:0] test_program [4095:0];
    reg [31:0] test_data = 0;
    
    int File = $fopen("test_result.txt","w");
    wire [4096*32-1:0]transaction_data_serialized;
    genvar i;
    for (i=0; i<4096; i=i+1) assign transaction_data_serialized[32*i+31:32*i] = test_program[i][31:0];


    //clock generation
    initial core_clk = 0; 
    always #0.5 core_clk = ~core_clk;

    //clock generation
    initial begin
        io_clk = 0; 
    
        forever begin
            #1 io_clk = ~io_clk; 
        end 
    end

    reg [31:0] reg_readback;
    // reset generation
    initial begin
        axil_bfm = new(axi_in,1);
        
        $readmemh("/home/fils/git/uscope_hdl/public/Components/system/fcore/tb/test_program.mem", test_program);
        //$readmemh("/home/fils/git/sicdrive-hdl/Applications/SicDriveMaster/tb/sogi.mem", test_program);


        
        master = new("master", Programmer.vip_bd_i.axi_vip_0.inst.IF);
        master.start_master();
        programming_start = 0;
        reg_readback <= 0;
        rst <=0;

        op_a.initialize();
        op_res.initialize();
        op_res.ready <= 1;
        run <= 0;
        #10.5;
        #20.5 rst <=1;
        

        #40 program_fcore();
        #4; run <= 1;
        #5 run <=  0;
        #4150;
        for(int i = 0; i<15; i = i+1)begin
            axil_bfm.read(32'h43c00008+i*4,reg_readback);
            $fwrite(File, "%d\n", reg_readback);
        end
        $fclose(File);
        $finish("simulation end");
    end


    initial begin
        #300 axil_bfm.write(32'h43c00000,3);
        #5 axil_bfm.write(32'h43c0000C,69);
    end



    task automatic program_fcore;
        wr_transaction = master.wr_driver.create_transaction("tr1");

            for(int i = 0; i<2048; i = i+1)begin
                wr_transaction.set_write_cmd(2*i,XIL_AXI_BURST_TYPE_INCR,0,1,XIL_AXI_SIZE_4BYTE);
                wr_transaction.set_data_block(transaction_data_serialized[i*64 +:64]);
                master.wr_driver.send(wr_transaction);
                #25;
            end
    endtask //automatic

    
endmodule
