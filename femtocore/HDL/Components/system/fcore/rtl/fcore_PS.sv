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

module fCore_PS(
    APB.master APB,
    AXI.master fCore_axi,
    output wire IO_clock,
    output wire Logic_Clock,
    output wire Reset
    );

  fCore_PS_bd fCore_PS_i
       (.APB_M_0_paddr(APB.PADDR),
        .APB_M_0_penable(APB.PENABLE),
        .APB_M_0_pprot(APB.PPROT),
        .APB_M_0_prdata(APB.PRDATA),
        .APB_M_0_pready(APB.PREADY),
        .APB_M_0_psel(APB.PSEL),
        .APB_M_0_pslverr(APB.PSLVERR),
        .APB_M_0_pstrb(APB.PSTRB),
        .APB_M_0_pwdata(APB.PWDATA),
        .APB_M_0_pwrite(APB.PWRITE),
        .IO_clock(IO_clock),
        .Logic_Clock(Logic_Clock),
        .Reset(Reset),
        .fCore_araddr(fCore_axi.ARADDR),
        .fCore_arburst(fCore_axi.ARBURST),
        .fCore_arcache(fCore_axi.ARCACHE),
        .fCore_arlen(fCore_axi.ARLEN),
        .fCore_arlock(fCore_axi.ARLOCK),
        .fCore_arprot(fCore_axi.ARPROT),
        .fCore_arqos(fCore_axi.ARQOS),
        .fCore_arready(fCore_axi.ARREADY),
        .fCore_arsize(fCore_axi.ARSIZE),
        .fCore_arvalid(fCore_axi.ARVALID),
        .fCore_awaddr(fCore_axi.AWADDR),
        .fCore_awburst(fCore_axi.AWBURST),
        .fCore_awcache(fCore_axi.AWCACHE),
        .fCore_awlen(fCore_axi.AWLEN),
        .fCore_awlock(fCore_axi.AWLOCK),
        .fCore_awprot(fCore_axi.AWPROT),
        .fCore_awqos(fCore_axi.AWQOS),
        .fCore_awready(fCore_axi.AWREADY),
        .fCore_awsize(fCore_axi.AWSIZE),
        .fCore_awvalid(fCore_axi.AWVALID),
        .fCore_bready(fCore_axi.BREADY),
        .fCore_bresp(fCore_axi.BRESP),
        .fCore_bvalid(fCore_axi.BVALID),
        .fCore_rdata(fCore_axi.RDATA),
        .fCore_rlast(fCore_axi.RLAST),
        .fCore_rready(fCore_axi.RREADY),
        .fCore_rresp(fCore_axi.RRESP),
        .fCore_rvalid(fCore_axi.RVALID),
        .fCore_wdata(fCore_axi.WDATA),
        .fCore_wlast(fCore_axi.WLAST),
        .fCore_wready(fCore_axi.WREADY),
        .fCore_wstrb(fCore_axi.WSTRB),
        .fCore_wvalid(fCore_axi.WVALID)
        );

endmodule
