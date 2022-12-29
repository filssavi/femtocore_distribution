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

module axil_crossbar_tb();
   

    reg clk, reset;

    axi_lite axi_m1();
    axi_lite axi_m2();

    axi_lite axi_s1();
    axi_lite axi_s2();

    axi_lite_BFM axil_bfm_1;
    axi_lite_BFM axil_bfm_2;

    
    axil_crossbar_interface #(
        .NM(2),
        .NS(2),
        .SLAVE_ADDR('{'h20000000,'h00000000}),
        .SLAVE_MASK('{'hF0000000,'hF0000000})
    ) UUT (
        .clock(clk),
        .reset(reset),
        .masters('{axi_s2, axi_s1}),
        .slaves('{axi_m2, axi_m1})
    );

    logic [31:0] input_registers [2:0] = {0,0,0};
    logic [31:0] output_registers_1 [2:0];

    axil_simple_register_cu #(
        .N_READ_REGISTERS(3),
        .N_WRITE_REGISTERS(3),
        .ADDRESS_MASK('h1f)
    ) S1 (
        .clock(clk),
        .reset(reset),
        .input_registers(input_registers),
        .output_registers(output_registers_1),
        .axil(axi_s1)
    );


    logic [31:0] input_registers [2:0] = {0,0,0};
    logic [31:0] output_registers_2 [2:0];

    axil_simple_register_cu #(
        .N_READ_REGISTERS(3),
        .N_WRITE_REGISTERS(3),
        .ADDRESS_MASK('h1f)
    ) S2 (
        .clock(clk),
        .reset(reset),
        .input_registers(input_registers),
        .output_registers(output_registers_2),
        .axil(axi_s2)
    );

    always begin
        clk = 1'b1;
        #0.5 clk = 1'b0;
        #0.5;
    end
    
    initial begin  
        axil_bfm_1 = new(axi_m1, 1);
        axil_bfm_2 = new(axi_m2, 1);
        //Initial status
        reset <=1'h1;
        #10 reset <=1'h0;
        //TESTS
        #20.5 reset <=1'h1;

    end

    reg [31:0] write_shadow_register_1 [2:0] = {0,0,0};
    reg [31:0] write_address_1;
    reg [31:0] write_data_1;
    // test writes
    initial begin
        write_address_1 = 0;
        write_data_1 = 0;
        #30;
        forever begin
            #10;
            write_address_1 = $urandom_range('h0fffffff, 'h00000000);
            write_data_1 = $urandom();
            write_shadow_register_1[write_address_1] = write_data_1;
            axil_bfm_1.write(write_address_1, write_data_1);
            #3;
            if(write_shadow_register_1 != output_registers_1) begin
                $error("output registers 1 != write shadow registers 1");
            end
            #30;    
        end
    end 

    
    reg [31:0] write_shadow_register_2 [2:0] = {0,0,0};
    reg [31:0] write_address_2;
    reg [31:0] write_data_2;
    // test writes
    initial begin
        write_address_2 = 0;
        write_data_2 = 0;
        #40;
        forever begin
            #10;
            write_address_2 = $urandom_range('h2fffffff, 'h20000000);
            write_data_2 = $urandom();
            write_shadow_register_2[write_address_2] = write_data_2;
            axil_bfm_2.write(write_address_2, write_data_2);
            #3;
            if(write_shadow_register_2 != output_registers_2) begin
                $error("output registers 2 != write shadow registers 2");
            end
            #30;    
        end
    end 


endmodule