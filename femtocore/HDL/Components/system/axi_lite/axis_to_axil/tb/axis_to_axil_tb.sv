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
import axis_2_axil_vip_bd_axi_vip_0_0_pkg::*;


module axis_to_axil_tb();
   


    reg clk, reset;

    axi_lite axi_m();
    axi_stream write_in();
    axi_stream read_req();
    axi_stream read_resp();


    axis_2_axil_vip_bd_axi_vip_0_0_slv_mem_t slv_agent;

    axis_to_axil UUT(
        .clock(clk),
        .reset(reset), 
        .axis_write(write_in),
        .axis_read_request(read_req),
        .axis_read_response(read_resp),
        .axi_out(axi_m)
    );

    axis_2_axil_vip_bd_wrapper VIP(
        .clock(clk),
        .reset(reset),
        .axi(axi_m)
    );

    always begin
        clk = 1'b1;
        #0.5 clk = 1'b0;
        #0.5;
    end
    
    initial begin 
        reset <=1'h0;
        write_in.initialize();
        slv_agent = new("slave vip agent",axis_to_axil_tb.VIP.vip_bd_i.axi_vip_0.inst.IF);
        slv_agent.set_verbosity(400);
        slv_agent.start_slave();

        //TESTS
        #30.5 reset <=1'h1;


        #20;
        for (integer i = 0; i <101; i = i+1 ) begin
            write_in.data <= $urandom();
            write_in.dest <= 'h43c00000 + ($urandom()%10)*4;
            write_in.valid <= 1;
            #1;    
            @(write_in.ready);
        end
        write_in.valid <= 0;
    end

    initial begin 
        read_req.initialize();
        read_resp.ready = 1;
        #50.5;
        read_req.data <= 'h43c00004;
        read_req.valid <= 1;
        #1;    
        read_req.valid <= 0;
        @(write_in.ready);

    end

endmodule