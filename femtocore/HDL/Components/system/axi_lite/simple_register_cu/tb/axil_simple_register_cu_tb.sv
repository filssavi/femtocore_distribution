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

module axil_simple_register_cu_tb();
   
    axi_lite test_axi();

    reg clk, reset;

    wire trigger_out;
  
    axi_lite_BFM axil_bfm;

    logic [31:0] input_registers [2:0] = {0,0,0};
    logic [31:0] output_registers [2:0];
    
    axil_simple_register_cu #(
        .N_READ_REGISTERS(3),
        .N_WRITE_REGISTERS(3),
        .N_TRIGGER_REGISTERS(1),
        .TRIGGER_REGISTERS_IDX({2}),
        .ADDRESS_MASK('hf)
    ) UUT (
        .clock(clk),
        .reset(reset),
        .input_registers(input_registers),
        .output_registers(output_registers),
        .trigger_out({trigger_out}),
        .axil(test_axi)
    );
    
    always begin
        clk = 1'b1;
        #0.5 clk = 1'b0;
        #0.5;
    end
    
    reg [31:0] write_shadow_register [2:0] = {0,0,0};
    reg [31:0] write_address;
    reg [31:0] write_data;

    initial begin  
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
            if(write_shadow_register != output_registers) begin
                $error("output registers != write shadow registers");
            end
            #30;    
        end
    end 

    reg test = 0;

 // test trigger_out
    initial begin
        #31.5;
        forever begin
            #11;
            if(write_address == 2)begin
                if(!trigger_out) begin
                    $error("trigger register did not fire trigger out");
                end
            end
            #3
            
            #30;    
        end
    end 


    always@(posedge trigger_out) begin
        if(write_address != 2)begin
            $error("spurious trigger register firing");
        end
    end


    reg [31:0] read_shadow_register [2:0] = {0,0,0};
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
            input_registers[read_address] = read_data;
            #3;
            read_func = 1;
            axil_bfm.read(read_address<<2, readback);
            read_func = 0;
            read_shadow_register[read_address] = readback;
            if(read_shadow_register != input_registers) begin
                $error("input registers != read shadow registers");
            end
            #20;   
        end
    end 

endmodule