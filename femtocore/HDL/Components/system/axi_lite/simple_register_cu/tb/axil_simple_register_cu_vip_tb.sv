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
import axi_vip_pkg::*;
import VIP_axi_vip_0_0_pkg::*;

module axil_simple_register_cu_vip_tb();
   
    axi_lite test_axi();

    reg clk, reset;

  
    axil_simple_register_vip VIP(
        .clock(clk),
        .reset(reset),
        .axil(test_axi)
    );

    VIP_axi_vip_0_0_mst_t master_agent;

    logic [31:0] input_registers [2:0] = {0,0,'hBEEF};
    logic [31:0] output_registers [2:0];

    axil_simple_register_cu #(
        .N_READ_REGISTERS(3),
        .N_WRITE_REGISTERS(3),
        .ADDRESS_MASK('h1f)
    ) UUT (
        .clock(clk),
        .reset(reset),
        .input_registers(input_registers),
        .output_registers(output_registers),
        .axil(test_axi)
    );
    
    always begin
        clk = 0'b1;
        #0.5 clk = 1'b0;
        #0.5;
    end
    
    reg [31:0] write_shadow_register [2:0] = {0,0,0};
    reg [31:0] write_address;
    reg [31:0] write_data;


    xil_axi_resp_t 	resp;
    reg[31:0]  addr, data, base_addr = 32'h4400_0000;
    
    initial begin  
        master_agent = new("master axi lite VIP agent", axil_simple_register_cu_vip_tb.VIP.VIP_i.axi_vip_0.inst.IF);
        master_agent.start_master();
        //Initial status
        reset <=1'h0;
        #16 reset <=1'h0;
        //TESTS
        #20.5 reset <=1'h1;



        #30;
        addr = 0;
        data = 32'hCAFE;
        // TEST WRITE
        master_agent.AXI4LITE_WRITE_BURST(base_addr+addr,0,data,resp);
        #10;
        // TEST READ
        master_agent.AXI4LITE_READ_BURST(base_addr+addr,0,data,resp);
    
    end

endmodule