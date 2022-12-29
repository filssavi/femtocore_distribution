

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
`include "axis_BFM.svh"

module uScope_tb();
    reg  clk, reset;

    reg start_test;

    axi_lite axil();
    axi_lite dma_axi();
    axi_lite_BFM axil_bfm;

    axi_stream in_1();
    axis_BFM axis_BFM_1;
    axi_stream in_2();
    axis_BFM axis_BFM_2;
    axi_stream in_3();
    axis_BFM axis_BFM_3;
    axi_stream in_4();
    axis_BFM axis_BFM_4;
    axi_stream in_5();
    axis_BFM axis_BFM_5;
    axi_stream in_6();
    axis_BFM axis_BFM_6;
    axi_stream in_7();
    axi_stream in_8();
    
    initial begin
        axis_BFM_1 = new(in_1,1);
        axis_BFM_2 = new(in_2,1);
        axis_BFM_3 = new(in_3,1);
        axis_BFM_4 = new(in_4,1);
        axis_BFM_5 = new(in_5,1);
        axis_BFM_6 = new(in_6,1);
    end

    
    axi_stream out();
    axi_stream error_mon();

    reg dma_done;
    wire [15:0] triggers;

    localparam BASE_ADDRESS = 'h43C00000;

    uScope UUT (
        .clock(clk),
        .reset(reset),
        .dma_done(dma_done),
        .trigger_out(triggers),
        .in_1(in_1),
        .in_2(in_2),
        .in_3(in_3),
        .in_4(in_4),
        .in_5(in_5),
        .in_6(in_6),
        .in_7(in_7),
        .in_8(in_8),
        .axi_in(axil),
        .dma_axi(dma_axi),
        .out(out)
    );
    
    uscope_tb_axis_emulator axis_emu(
        .clock(clk),
        .reset(reset),
        .data(out),
        .dma_done(dma_done)
    );
        

    //clock generation
    initial clk = 0; 
    always #0.5 clk = ~clk; 


    initial begin
        axil_bfm = new(axil, 1);
        in_1.initialize();
        in_2.initialize();
        in_3.initialize();
        in_4.initialize();
        in_5.initialize();
        in_6.initialize();
        //Initial status
        reset <=1'h1;
        #1 reset <=1'h0;
        //TESTS
        #5.5 reset <=1'h1;


        #8;
        // number of samples
        axil_bfm.write(BASE_ADDRESS, 32'h40);
        //dma buffer base
        #10 axil_bfm.write(BASE_ADDRESS+4, 32'h3f000000);
        
        #10 axil_bfm.write(BASE_ADDRESS+8, 32'h1);

        start_test <= 1;
        #50 axil_bfm.write(BASE_ADDRESS+'hC, 32'h0);
        #50 axil_bfm.write(BASE_ADDRESS+14, 32'h5);
    end

    always @(posedge clk) begin
        if(start_test)begin
            axis_BFM_1.write_dest($urandom, 1);
            axis_BFM_2.write_dest($urandom, 2);
            axis_BFM_3.write_dest($urandom, 3);
            axis_BFM_4.write_dest($urandom, 4);
            axis_BFM_5.write_dest($urandom, 5);
            axis_BFM_6.write_dest($urandom, 6);
        end  
    end



    initial begin
        dma_axi.ARREADY <= 0;
        dma_axi.AWREADY <= 0;
        dma_axi.BRESP <= 0;
        dma_axi.BVALID <= 0;
        dma_axi.RDATA <= 0;
        dma_axi.RRESP <= 0;
        dma_axi.RVALID <= 0;
        dma_axi.WREADY <= 0;
        forever begin
            @(posedge dma_axi.AWVALID);
            dma_axi.AWREADY <= 1;
            dma_axi.WREADY <= 1;
            #1 dma_axi.AWREADY <= 0;
            dma_axi.WREADY <= 0;
            dma_axi.BRESP <= 0;
            dma_axi.BVALID <= 1;
            @(dma_axi.BREADY)
            #1 dma_axi.BVALID <= 0;
        end
    end


endmodule

module uscope_tb_axis_emulator (
    input wire clock,
    input wire reset,
    axi_stream.slave data,
    output reg dma_done
);

assign data.ready = 1;

always_ff @(posedge clock) begin
    if(data.tlast)begin
        dma_done <= 1;
    end else
        dma_done <= 0;

end
    
endmodule