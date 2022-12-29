// Copyright 2021 Filippo Savi
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
`include "axis_BFM.svh"

module efi_sorter_tb();


    `define DEBUG

    reg core_clk, io_clk, rst, run;
    wire done;
    
    axi_stream op_a();
    axi_stream op_res();
    AXI axi_programmer();
    axi_stream axis_dma_write();

    axi_stream dma_read_request();
    axi_stream dma_read_response();
    axi_stream data_out();

    axis_BFM read_dma_BFM;

    localparam RECIPROCAL_PRESENT = 0;
    
    axis_BFM axis_dma_write_BFM;
    axis_BFM write_BFM;
    axis_BFM read_req_BFM;
    axis_BFM read_resp_BFM;

    axi_stream read_req();
    axi_stream read_resp();
    axi_stream write();
    axi_lite axi_master();

    axis_to_axil WRITER(
        .clock(core_clk),
        .reset(rst), 
        .axis_write(write),
        .axis_read_request(read_req),
        .axis_read_response(read_resp),
        .axi_out(axi_master)
    );

    reg efi_start;
    
    axi_stream efi_arguments();
    axi_stream efi_results();


    efi_sorter #(
        .DATA_WIDTH(32),
        .DEST_WIDTH(8),
        .USER_WIDTH(1),
        .MAX_SORT_LENGTH(256)
    )efi_1(
        .clock(core_clk),
        .reset(rst),
        .efi_arguments(efi_arguments),
        .efi_results(efi_results)
    );

    defparam core.executor.RECIPROCAL_PRESENT = RECIPROCAL_PRESENT;
    fCore #(
        .FAST_DEBUG("TRUE"),
        .MAX_CHANNELS(9),
        .EFI_IMPLEMENTED(1),
        .INIT_FILE("/home/fils/git/uscope_hdl/public/Components/system/fcore/efi/sorter/tb/test_efi.mem")
    ) core(
        .clock(core_clk),
        .axi_clock(core_clk),
        .reset(rst),
        .reset_axi(rst),
        .run(run),
        .done(done),
        .efi_start(efi_start),
        .control_axi_in(axi_master),
        .axi(axi_programmer),
        .axis_dma_write(axis_dma_write),
        .axis_dma_read_request(dma_read_request),
        .axis_dma_read_response(dma_read_response),
        .efi_arguments(efi_arguments),
        .efi_results(efi_results)
    );

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
        write_BFM = new(write,1);
        axis_dma_write_BFM = new(axis_dma_write,1);
        read_req_BFM = new(read_req, 1);
        read_resp_BFM = new(read_resp, 1);
        read_resp.ready = 1;
        rst <=0;
        axis_dma_write.initialize();
        op_a.initialize();
        op_res.initialize();
        op_res.ready <= 1;
        run <= 0;
        #10.5;
        #20.5 rst <=1;
        #35 write_BFM.write_dest(8,32'h43c00000);
        #4; run <= 1;
        #5 run <=  0;
    end



endmodule
