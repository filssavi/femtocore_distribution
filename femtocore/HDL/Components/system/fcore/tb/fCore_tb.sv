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

module fCore_tb();

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
        .INIT_FILE("/home/filssavi/git/uplatform-hdl/public/Components/system/fcore/tb/test_sat.mem"),
        .BITMANIP_IMPLEMENTED(1),
        .INSTRUCTION_STORE_SIZE(512)
    ) uut(
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

    reg data_mover_start;
    
    axis_data_mover #(
        .DATA_WIDTH(32),
        .CHANNEL_NUMBER(3),
        .SOURCE_ADDR('{1,2,3}),
        .TARGET_ADDR('{1,2,3})
    ) mover (
        .clock(core_clk),
        .reset(rst),
        .start(data_mover_start),
        .data_request(dma_read_request),
        .data_response(dma_read_response),
        .data_out(data_out)
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
        #35 write_BFM.write_dest('h8,32'h43c00000); // CHANNELS
        // IO TRANSLATION TABLE ROW 1
        #35 write_BFM.write_dest(1,32'h43c00004); // TRANSL ADDR
        #35 write_BFM.write_dest(3,32'h43c00008); // TRANSL DATA
        // IO TRANSLATION TABLE ROW 2
        #35 write_BFM.write_dest(2,32'h43c00004); // TRANSL ADDR
        #35 write_BFM.write_dest(2,32'h43c00008); // TRANSL DATA
        // IO TRANSLATION TABLE ROW 3
        #35 write_BFM.write_dest(3,32'h43c00004); // TRANSL ADDR
        #35 write_BFM.write_dest(1,32'h43c00008); // TRANSL DATA
        // IO TRANSLATION TABLE ROW 3
        #35 write_BFM.write_dest(63,32'h43c00004); // TRANSL ADDR
        #35 write_BFM.write_dest('h1b,32'h43c00008); // TRANSL DATA

        #4; run <= 1;
        #5 run <=  0;

        #8000  write_BFM.write_dest('hCAFE0008,32'h43c00000);
        read_req_BFM.write(32'h43c00000);
    end

    reg dbg = 0;
    reg [7:0] read_idx = 0;
    reg [31:0] expected_results [13:0];
    localparam CORE_DMA_BASE_ADDRESS = 32'h43c00004;
    
    event run_test_done;
    event bus_read_test_done;
    initial begin
        if(RECIPROCAL_PRESENT==1) begin
            expected_results <= {'h40e00001, 'h428C0000,'h0000000c,'h40a00000,'h3c6d7304,'h40800000,'h40400000,'hc0800000,'h428c0000,'h40400000,'h40800000,'hc0800000,'h00000005,'h0};
        end else begin
            expected_results <= {'h40e00001, 'h428C0000,'h0000000c,'h40a00000,'h0,'h40800000,'h40400000,'hc0800000,'h428c0000,'h40400000,'h40800000,'hc0800000,'h00000005,'h0};
        end
        @(posedge done) $display("femtoCore Processing Done");
        ->run_test_done;
        #100;
        for (integer i = 1; i<14; i++) begin      
            read_req_BFM.write(CORE_DMA_BASE_ADDRESS+4*(read_idx+2));
            read_resp_BFM.read(reg_readback);
            if(reg_readback!=expected_results[read_idx]) begin
                $display("BUS READ ERROR Register %d  Wrong Value detected. Expected %f (%h) Got %f (%h)",read_idx,$bitstoshortreal(expected_results[read_idx]),expected_results[read_idx],$bitstoshortreal(reg_readback),reg_readback);
            end
            read_idx++;
            #100;
        end
        ->bus_read_test_done;
    end



    event axis_dma_test_done;

    initial begin

        data_mover_start <= 0;
        @(bus_read_test_done);

        axis_dma_write_BFM.write_dest('hCAFE, 'h2);
        expected_results[2] = 'hCAFE;
        #20 data_mover_start <=1;
        #1 data_mover_start <= 0;
        
        for(integer  i = 0; i<3; i = i+1) begin
            @(data_out.valid)
            assert (data_out.data == expected_results[data_out.dest]) 
            else begin
                $display("AXI STREAM DMA ERROR Wrong Value detected on register %d . Expected %f (%h) Got %f (%h)",data_out.dest,expected_results[data_out.dest],expected_results[data_out.dest],data_out.data,data_out.data);
                $finish();
            end
            #1;
        end
        ->axis_dma_test_done;
    end

    initial begin
        @(run_test_done) $display("TEST SUCCESSFUL 1/3: FEMTOCORE RUN");
        @(bus_read_test_done) $display("TEST SUCCESSFUL 2/3: BUS REGISTER_READ");
        @(axis_dma_test_done) $display("TEST SUCCESSFUL 3/3: AXI STREAM DMA");
        $display("TEST SUITE COMPLEATED SUCESSFULLY");
        $finish();
    end


endmodule
