//Copyright 1986-2018 Xilinx, Inc. All Rights Reserved.
//--------------------------------------------------------------------------------
//Tool Version: Vivado v.2018.2.2 (win64) Build 2348494 Mon Oct  1 18:25:44 MDT 2018
//Date        : Fri Oct 12 10:58:47 2018
//Host        : PMB119-7050-GB running 64-bit major release  (build 9200)
//Command     : generate_target zynq_apb_bd.bd
//Design      : zynq_apb_bd
//Purpose     : IP block netlist
//--------------------------------------------------------------------------------
`timescale 10 ns / 1 ps
`include "interfaces.svh"

module Zynq_wrapper(
    axi_lite.master axi_out,
    inout wire DDR_addr,
    inout wire DDR_ba,
    inout wire DDR_cas_n,
    inout wire DDR_ck_n,
    inout wire DDR_ck_p,
    inout wire DDR_cke,
    inout wire DDR_cs_n,
    inout wire DDR_dm,
    inout wire DDR_dq,
    inout wire DDR_dqs_n,
    inout wire DDR_dqs_p,
    inout wire DDR_odt,
    inout wire DDR_ras_n,
    inout wire DDR_reset_n,
    inout wire DDR_we_n,
    inout wire FIXED_IO_ddr_vrn,
    inout wire FIXED_IO_ddr_vrp,
    inout wire FIXED_IO_mio,
    inout wire FIXED_IO_ps_clk,
    inout wire FIXED_IO_ps_porb,
    inout wire FIXED_IO_ps_srstb,
    output wire Reset,
    output wire logic_clock,
    output wire IO_clock
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
    

    zynq_axi_lite_bd zynq_axi_lite_bd_i (
        .M00_AXI_0_araddr(axi_out.ARADDR),
        .M00_AXI_0_arprot(axi_out.ARPROT),
        .M00_AXI_0_arready(axi_out.ARREADY),
        .M00_AXI_0_arvalid(axi_out.ARVALID),
        .M00_AXI_0_awaddr(axi_out.AWADDR),
        .M00_AXI_0_awprot(axi_out.AWPROT),
        .M00_AXI_0_awready(axi_out.AWREADY),
        .M00_AXI_0_awvalid(axi_out.AWVALID),
        .M00_AXI_0_bready(axi_out.BREADY),
        .M00_AXI_0_bresp(axi_out.BRESP),
        .M00_AXI_0_bvalid(axi_out.BVALID),
        .M00_AXI_0_rdata(axi_out.RDATA),
        .M00_AXI_0_rready(axi_out.RREADY),
        .M00_AXI_0_rresp(axi_out.RRESP),
        .M00_AXI_0_rvalid(axi_out.RVALID),
        .M00_AXI_0_wdata(axi_out.WDATA),
        .M00_AXI_0_wready(axi_out.WREADY),
        .M00_AXI_0_wstrb(axi_out.WSTRB),
        .M00_AXI_0_wvalid(axi_out.WVALID),
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
        .Logic_Clock(logic_clock),
        .IO_clock(IO_clock),
        .Reset(Reset)
    );
endmodule
