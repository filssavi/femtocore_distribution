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
`include "axis_BFM.svh"

module fCore_efi_tb();

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

    reg efi_done, efi_start;
    
    reg [7:0] efi_counter = 0;
    reg [31:0] efi_memory [9:0];

    axi_stream efi_arguments();
    axi_stream efi_results();

    reg efi_working = 0;

    always_ff @(posedge core_clk) begin
        efi_done <= 0;
        efi_results.tlast <= 0;
        efi_results.valid <= 0;
        if (efi_arguments.tlast) begin
            efi_working <=1;
        end
        if(efi_working)begin
            efi_results.data <= efi_memory[9-efi_counter];
            efi_results.dest <= efi_counter;
            efi_results.valid <= 1;
            efi_counter <= efi_counter + 1;
            if (efi_counter == 9) begin
                efi_done <= 1;
                efi_results.tlast <= 1;
                efi_counter <= 0;
                efi_working <= 0;
            end
        end
        if(efi_arguments.valid)begin
            efi_memory[efi_arguments.dest-1] <= efi_arguments.data;
        end
    end



    defparam uut.executor.RECIPROCAL_PRESENT = RECIPROCAL_PRESENT;
    fCore #(
        .FAST_DEBUG("TRUE"),
        .MAX_CHANNELS(9),
        .INIT_FILE("/home/fils/git/uscope_hdl/public/Components/system/fcore/tb/test_efi.mem")
    ) uut(
        .clock(core_clk),
        .reset(rst),
        .run(run),
        .done(done),
        .efi_done(efi_done),
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

    reg [31:0] expected_results [13:0];
    localparam CORE_DMA_BASE_ADDRESS = 32'h43c00004;
    reg [31:0] register_idx = 0;
    event run_test_done;
    event bus_read_test_done;
    initial begin
        expected_results[0] = 0;
        expected_results[1] = $shortrealtobits(30.0);
        expected_results[2] = $shortrealtobits(9.0);
        expected_results[3] = $shortrealtobits(8.0);
        expected_results[4] = $shortrealtobits(7.0);
        expected_results[5] = $shortrealtobits(6.0);
        expected_results[6] = $shortrealtobits(5.0);
        expected_results[7] = $shortrealtobits(4.0);
        expected_results[8] = $shortrealtobits(3.0);
        expected_results[9] = $shortrealtobits(2.0);
        expected_results[10] = $shortrealtobits(1.0);
        expected_results[11] = $shortrealtobits(11.0);
        expected_results[12] = $shortrealtobits(12.0);
        expected_results[13] = $shortrealtobits(13.0);
        @(posedge done) $display("femtoCore Processing Done");
        ->run_test_done;
        #100;
        for (integer i = 0; i<14; i++) begin
            read_req_BFM.write(CORE_DMA_BASE_ADDRESS+4*i);
            read_resp_BFM.read(reg_readback);
            if(reg_readback!=expected_results[i]) begin
                $display("BUS READ ERROR Channel 0 Register %d  Wrong Value detected. Expected %h Got %h",i,expected_results[i],reg_readback);
            end
            #100;
        end

        ->bus_read_test_done;
    end


    initial begin
        @(run_test_done) $display("TEST SUCCESSFUL 1/3: FEMTOCORE RUN");
        @(bus_read_test_done) $display("TEST SUCCESSFUL 2/3: BUS REGISTER_READ");
        $display("TEST SUITE COMPLEATED SUCESSFULLY");
        $finish();
    end


endmodule
