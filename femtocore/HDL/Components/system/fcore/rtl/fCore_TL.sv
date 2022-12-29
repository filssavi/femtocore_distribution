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

module fCore_TL();
    
    parameter INSTRUCTION_STORE_SIZE = 4096;
    parameter INSTRUCTION_WIDTH = 20;
    parameter ALU_OPCODE_WIDTH = 4;
    parameter REGISTER_FILE_DEPTH = 12;

    wire logic_clock, core_clock, reset, run;
    
    APB apb();
    AXI fcore_axi(); 
    axi_lite dma_axi();

    
    axi_stream dummy_scope();
    axi_lite ctrl_axi();

    Zynq_axis_wrapper PS(
        .Logic_Clock(logic_clock),
        .Reset(reset),
        .dma_axi(dma_axi),
        .axi_out(ctrl_axi),
        .fcore_axi(fcore_axi),
        .scope(dummy_scope)
    );

    axi_lite #(.INTERFACE_NAME("GPIO")) gpio_axi();
    axi_lite #(.INTERFACE_NAME("FCORE")) fcore_axi();

    localparam GPIO_GEN = 32'h43c00000;
    localparam FCORE_BASE = 32'h43c01000;

    localparam [31:0] AXI_ADDRESSES [2:0] = '{GPIO_GEN, FCORE_BASE};

    axil_crossbar_interface #(
        .DATA_WIDTH(32),
        .ADDR_WIDTH(32),
        .NM(1),
        .NS(2),
        .SLAVE_ADDR(AXI_ADDRESSES),
        .SLAVE_MASK('{2{32'hf000}})
    ) axi_xbar (
        .clock(clock),
        .reset(reset),
        .slaves('{axi_master}),
        .masters('{gpio_axi, fcore_axi})
    );

    gpio gpio (
        .clock(logic_clock),
        .reset(reset),
        .gpio_o(run),
        .axi_in(gpio_axi)
    );

    fCore core(
        .clock(logic_clock),
        .reset(reset),
        .run(run),
        .sb(s2),
        .control_axi_in(fcore_axi),
        .axi(fcore_axi)
    );
    

endmodule
