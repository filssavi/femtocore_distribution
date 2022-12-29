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

import axi_vip_pkg::*;
import vip_bd_axi_vip_0_0_pkg::*;
							
module axi_terminator_tb();

    reg  clk, reset;

    //clock generation
    initial clk = 0; 
    always #0.5 clk = ~clk; 




    axi_transaction wr_transaction;
    vip_bd_axi_vip_0_0_mst_t master;
    
    AXI test();

    vip_bd_wrapper vip(
        .clock(clk),
        .reset(reset),
        .axi(test)
    );

    axi_terminator UUT(
        .clock(clk),
        .reset(reset),
        .axi(test)
    );

    initial begin
        master = new("master", vip.vip_bd_i.axi_vip_0.inst.IF);
        master.start_master();
            
        reset <=1'h1;
        #1 reset <=1'h0;
        //TESTS
        #50 reset <=1'h1;
        forever begin
            #300
        
            wr_transaction = master.wr_driver.create_transaction("write transaction");
            WR_TRANSACTION_FAIL_1b: assert(wr_transaction.randomize());
            master.wr_driver.send(wr_transaction);
        end
    end

endmodule