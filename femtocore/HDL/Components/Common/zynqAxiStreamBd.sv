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
`timescale 10 ns / 100 ps
`include "interfaces.svh"

module Zynq_axis_wrapper #(
    parameter FCORE_PRESENT = 0
) (
    output wire IO_clock,
    output wire Logic_Clock,
    output wire [0:0]Reset,
    axi_lite.slave dma_axi,
    axi_lite.master axi_out,
    AXI.master fcore_axi,
    axi_stream.slave scope,
    output wire dma_done
  );

    // DUMMY CONNECTIONS
    wire [14:0]DDR_addr;
    wire [2:0]DDR_ba;
    wire DDR_cas_n;
    wire DDR_ck_n;
    wire DDR_ck_p;
    wire DDR_cke;
    wire DDR_cs_n;
    wire [3:0]DDR_dm;
    wire [31:0]DDR_dq;
    wire [3:0]DDR_dqs_n;
    wire [3:0]DDR_dqs_p;
    wire DDR_odt;
    wire DDR_ras_n;
    wire DDR_reset_n;
    wire DDR_we_n;
    wire FIXED_IO_ddr_vrn;
    wire FIXED_IO_ddr_vrp;
    wire [53:0]FIXED_IO_mio;
    wire FIXED_IO_ps_clk;
    wire FIXED_IO_ps_porb;
    wire FIXED_IO_ps_srstb;

    AXI term();

    generate
        
        if(FCORE_PRESENT == 0)begin
            axi_terminator terminator(
                .clock(Logic_Clock),
                .reset(Reset),
                .axi(term)
            );


            PS_AXI_stream PS (
                .axi_out_araddr(axi_out.ARADDR),
                .axi_out_arprot(axi_out.ARPROT),
                .axi_out_arready(axi_out.ARREADY),
                .axi_out_arvalid(axi_out.ARVALID),
                .axi_out_awaddr(axi_out.AWADDR),
                .axi_out_awprot(axi_out.AWPROT),
                .axi_out_awready(axi_out.AWREADY),
                .axi_out_awvalid(axi_out.AWVALID),
                .axi_out_bready(axi_out.BREADY),
                .axi_out_bresp(axi_out.BRESP),
                .axi_out_bvalid(axi_out.BVALID),
                .axi_out_rdata(axi_out.RDATA),
                .axi_out_rready(axi_out.RREADY),
                .axi_out_rresp(axi_out.RRESP),
                .axi_out_rvalid(axi_out.RVALID),
                .axi_out_wdata(axi_out.WDATA),
                .axi_out_wready(axi_out.WREADY),
                .axi_out_wstrb(axi_out.WSTRB),
                .axi_out_wvalid(axi_out.WVALID),
                .DDR_addr(DDR_addr),
                .DDR_ba(DDR_ba),
                .DDR_cas_n(DDR_cas_n),
                .DDR_ck_n(DDR_ck_n),
                .DDR_ck_p(DDR_ck_p),
                .DDR_cke(DDR_cke),
                .DDR_cs_n(DDR_cs_n),
                .DDR_dm(DDR_dm),
                .DDR_dq(DDR_dq),
                .DDR_dqs_n(DDR_dqs_n),
                .DDR_dqs_p(DDR_dqs_p),
                .DDR_odt(DDR_odt),
                .DDR_ras_n(DDR_ras_n),
                .DDR_reset_n(DDR_reset_n),
                .DDR_we_n(DDR_we_n),
                .FIXED_IO_ddr_vrn(FIXED_IO_ddr_vrn),
                .FIXED_IO_ddr_vrp(FIXED_IO_ddr_vrp),
                .FIXED_IO_mio(FIXED_IO_mio),
                .FIXED_IO_ps_clk(FIXED_IO_ps_clk),
                .FIXED_IO_ps_porb(FIXED_IO_ps_porb),
                .FIXED_IO_ps_srstb(FIXED_IO_ps_srstb),
                .IO_clock(IO_clock),
                .Logic_Clock(Logic_Clock),
                .Reset(Reset),
                .dma_control_araddr(dma_axi.ARADDR),
                .dma_control_arready(dma_axi.ARREADY),
                .dma_control_arvalid(dma_axi.ARVALID),
                .dma_control_awaddr(dma_axi.AWADDR),
                .dma_control_awready(dma_axi.AWREADY),
                .dma_control_awvalid(dma_axi.AWVALID),
                .dma_control_bready(dma_axi.BREADY),
                .dma_control_bresp(dma_axi.BRESP),
                .dma_control_bvalid(dma_axi.BVALID),
                .dma_control_rdata(dma_axi.RDATA),
                .dma_control_rready(dma_axi.RREADY),
                .dma_control_rresp(dma_axi.RRESP),
                .dma_control_rvalid(dma_axi.RVALID),
                .dma_control_wdata(dma_axi.WDATA),
                .dma_control_wready(dma_axi.WREADY),
                .dma_control_wvalid(dma_axi.WVALID),
                .fCore_araddr(term.ARADDR),
                .fCore_arburst(term.ARBURST),
                .fCore_arlen(term.ARLEN),
                .fCore_arready(term.ARREADY),
                .fCore_arsize(term.ARSIZE),
                .fCore_arvalid(term.ARVALID),
                .fCore_awaddr(term.AWADDR),
                .fCore_awburst(term.AWBURST),
                .fCore_awlen(term.AWLEN),
                .fCore_awready(term.AWREADY),
                .fCore_awsize(term.AWSIZE),
                .fCore_awvalid(term.AWVALID),
                .fCore_bready(term.BREADY),
                .fCore_bresp(term.BRESP),
                .fCore_bvalid(term.BVALID),
                .fCore_rdata(term.RDATA),
                .fCore_rlast(term.RLAST),
                .fCore_rready(term.RREADY),
                .fCore_rresp(term.RRESP),
                .fCore_rvalid(term.RVALID),
                .fCore_wdata(term.WDATA),
                .fCore_wlast(term.WLAST),
                .fCore_wready(term.WREADY),
                .fCore_wstrb(term.WSTRB),
                .fCore_wvalid(term.WVALID),
                .scope_data_tdata(scope.data),
                .scope_data_tkeep(4'b1111),
                .scope_data_tlast(scope.tlast),
                .scope_data_tready(scope.ready),
                .scope_data_tvalid(scope.valid),
                .dma_done(dma_done)
            );
        end else begin
            
        PS_AXI_stream PS (
            .axi_out_araddr(axi_out.ARADDR),
            .axi_out_arprot(axi_out.ARPROT),
            .axi_out_arready(axi_out.ARREADY),
            .axi_out_arvalid(axi_out.ARVALID),
            .axi_out_awaddr(axi_out.AWADDR),
            .axi_out_awprot(axi_out.AWPROT),
            .axi_out_awready(axi_out.AWREADY),
            .axi_out_awvalid(axi_out.AWVALID),
            .axi_out_bready(axi_out.BREADY),
            .axi_out_bresp(axi_out.BRESP),
            .axi_out_bvalid(axi_out.BVALID),
            .axi_out_rdata(axi_out.RDATA),
            .axi_out_rready(axi_out.RREADY),
            .axi_out_rresp(axi_out.RRESP),
            .axi_out_rvalid(axi_out.RVALID),
            .axi_out_wdata(axi_out.WDATA),
            .axi_out_wready(axi_out.WREADY),
            .axi_out_wstrb(axi_out.WSTRB),
            .axi_out_wvalid(axi_out.WVALID),
            .DDR_addr(DDR_addr),
            .DDR_ba(DDR_ba),
            .DDR_cas_n(DDR_cas_n),
            .DDR_ck_n(DDR_ck_n),
            .DDR_ck_p(DDR_ck_p),
            .DDR_cke(DDR_cke),
            .DDR_cs_n(DDR_cs_n),
            .DDR_dm(DDR_dm),
            .DDR_dq(DDR_dq),
            .DDR_dqs_n(DDR_dqs_n),
            .DDR_dqs_p(DDR_dqs_p),
            .DDR_odt(DDR_odt),
            .DDR_ras_n(DDR_ras_n),
            .DDR_reset_n(DDR_reset_n),
            .DDR_we_n(DDR_we_n),
            .FIXED_IO_ddr_vrn(FIXED_IO_ddr_vrn),
            .FIXED_IO_ddr_vrp(FIXED_IO_ddr_vrp),
            .FIXED_IO_mio(FIXED_IO_mio),
            .FIXED_IO_ps_clk(FIXED_IO_ps_clk),
            .FIXED_IO_ps_porb(FIXED_IO_ps_porb),
            .FIXED_IO_ps_srstb(FIXED_IO_ps_srstb),
            .IO_clock(IO_clock),
            .Logic_Clock(Logic_Clock),
            .Reset(Reset),
            .dma_control_araddr(dma_axi.ARADDR),
            .dma_control_arready(dma_axi.ARREADY),
            .dma_control_arvalid(dma_axi.ARVALID),
            .dma_control_awaddr(dma_axi.AWADDR),
            .dma_control_awready(dma_axi.AWREADY),
            .dma_control_awvalid(dma_axi.AWVALID),
            .dma_control_bready(dma_axi.BREADY),
            .dma_control_bresp(dma_axi.BRESP),
            .dma_control_bvalid(dma_axi.BVALID),
            .dma_control_rdata(dma_axi.RDATA),
            .dma_control_rready(dma_axi.RREADY),
            .dma_control_rresp(dma_axi.RRESP),
            .dma_control_rvalid(dma_axi.RVALID),
            .dma_control_wdata(dma_axi.WDATA),
            .dma_control_wready(dma_axi.WREADY),
            .dma_control_wvalid(dma_axi.WVALID),
            .fCore_araddr(fcore_axi.ARADDR),
            .fCore_arburst(fcore_axi.ARBURST),
            .fCore_arlen(fcore_axi.ARLEN),
            .fCore_arready(fcore_axi.ARREADY),
            .fCore_arsize(fcore_axi.ARSIZE),
            .fCore_arvalid(fcore_axi.ARVALID),
            .fCore_awaddr(fcore_axi.AWADDR),
            .fCore_awburst(fcore_axi.AWBURST),
            .fCore_awlen(fcore_axi.AWLEN),
            .fCore_awready(fcore_axi.AWREADY),
            .fCore_awsize(fcore_axi.AWSIZE),
            .fCore_awvalid(fcore_axi.AWVALID),
            .fCore_bready(fcore_axi.BREADY),
            .fCore_bresp(fcore_axi.BRESP),
            .fCore_bvalid(fcore_axi.BVALID),
            .fCore_rdata(fcore_axi.RDATA),
            .fCore_rlast(fcore_axi.RLAST),
            .fCore_rready(fcore_axi.RREADY),
            .fCore_rresp(fcore_axi.RRESP),
            .fCore_rvalid(fcore_axi.RVALID),
            .fCore_wdata(fcore_axi.WDATA),
            .fCore_wlast(fcore_axi.WLAST),
            .fCore_wready(fcore_axi.WREADY),
            .fCore_wstrb(fcore_axi.WSTRB),
            .fCore_wvalid(fcore_axi.WVALID),
            .scope_data_tdata(scope.data),
            .scope_data_tkeep(4'b1111),
            .scope_data_tlast(scope.tlast),
            .scope_data_tready(scope.ready),
            .scope_data_tvalid(scope.valid),
            .dma_done(dma_done)
        );
        end


    endgenerate

endmodule