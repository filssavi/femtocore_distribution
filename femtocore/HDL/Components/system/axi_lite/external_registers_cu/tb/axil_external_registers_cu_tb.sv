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
`timescale 10 ns / 1 ns
`include "interfaces.svh"
`include "axi_lite_BFM.svh"

module axil_external_registers_cu_tb();
   
    axi_lite test_axi();

    reg clk, reset;

  
    axi_lite_BFM axil_bfm;

    axi_stream read_addr();
    axi_stream read_data_stream();
    axi_stream write_data_stream();
    
    axil_external_registers_cu UUT (
        .clock(clk),
        .reset(reset),
        .read_address(read_addr),
        .read_data(read_data_stream),
        .write_data(write_data_stream),
        .axi_in(test_axi)
    );

    always begin
        clk = 1'b1;
        #0.5 clk = 1'b0;
        #0.5;
    end
    
    reg [31:0] write_shadow_register [2:0] = {0,0,0};
    reg [31:0] CU_write_register [2:0] = {0,0,0};
    reg [31:0] write_address;
    reg [31:0] write_data;

    initial begin  
        read_addr.ready = 1;
        write_data_stream.ready = 1;
        read_data_stream.initialize();
        axil_bfm = new(test_axi,1);
        //Initial status
        reset <=1'h1;
        #10 reset <=1'h0;
        //TESTS
        #20.5 reset <=1'h1;
    end

    // test writes
    initial begin
        write_address = 0;
        write_data = 0;
        #30;
        forever begin
            #10;
            write_address = $urandom()%3;
            write_data = $urandom();
            write_shadow_register[write_address] = write_data;
            axil_bfm.write(write_address<<2, write_data);
            #3;
            if(write_shadow_register != CU_write_register) begin
                $error("output registers != write shadow registers");
            end
            #30;    
        end
    end 

    always @(posedge clk) begin
        if(write_data_stream.valid)begin
            CU_write_register[write_data_stream.dest] = write_data_stream.data;    
        end
    end


    always @(posedge clk) begin
        if(read_addr.valid)begin
            read_data_stream.data = CU_read_register[read_addr.data];    
        end
        read_data_stream.valid <= read_addr.valid;
    end


    reg [31:0] read_shadow_register [2:0] = {0,0,0};
    reg [31:0] CU_read_register [2:0] = {0,0,0};
    reg [31:0] read_address;
    reg [31:0] read_data;

    reg [31:0] readback;
    reg read_func = 0;
     // test reads
    initial begin
        read_address = 0;
        read_data = 0;
        read_func <= 0;
        #30;
        #5;
        forever begin
            #10
            read_address = $urandom()%3;
            read_data = $urandom();
            CU_read_register[read_address] = read_data;
            #3;
            read_func = 1;
            axil_bfm.read(read_address<<2, readback);
            read_func = 0;
            read_shadow_register[read_address] = readback;
            if(read_shadow_register != CU_read_register ) begin
                $error("input registers != read shadow registers");
            end
            #20;   
        end
    end 

endmodule