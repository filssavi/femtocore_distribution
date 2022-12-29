//Copyright 1986-2019 Xilinx, Inc. All Rights Reserved.
//--------------------------------------------------------------------------------
//Tool Version: Vivado v.2019.1 (lin64) Build 2552052 Fri May 24 14:47:09 MDT 2019
//Date        : Fri Mar 20 16:48:49 2020
//Host        : fils-desktop running 64-bit Ubuntu 19.04
//Command     : generate_target vip_bd_wrapper.bd
//Design      : vip_bd_wrapper
//Purpose     : IP block netlist
//--------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

module vip_bd_wrapper
   (S_AXI_0_araddr,
    S_AXI_0_arburst,
    S_AXI_0_arcache,
    S_AXI_0_arlen,
    S_AXI_0_arlock,
    S_AXI_0_arprot,
    S_AXI_0_arqos,
    S_AXI_0_arready,
    S_AXI_0_arregion,
    S_AXI_0_arsize,
    S_AXI_0_arvalid,
    S_AXI_0_awaddr,
    S_AXI_0_awburst,
    S_AXI_0_awcache,
    S_AXI_0_awlen,
    S_AXI_0_awlock,
    S_AXI_0_awprot,
    S_AXI_0_awqos,
    S_AXI_0_awready,
    S_AXI_0_awregion,
    S_AXI_0_awsize,
    S_AXI_0_awvalid,
    S_AXI_0_bready,
    S_AXI_0_bresp,
    S_AXI_0_bvalid,
    S_AXI_0_rdata,
    S_AXI_0_rlast,
    S_AXI_0_rready,
    S_AXI_0_rresp,
    S_AXI_0_rvalid,
    S_AXI_0_wdata,
    S_AXI_0_wlast,
    S_AXI_0_wready,
    S_AXI_0_wstrb,
    S_AXI_0_wvalid,
    aclk_0,
    aresetn_0);
  input [31:0]S_AXI_0_araddr;
  input [1:0]S_AXI_0_arburst;
  input [3:0]S_AXI_0_arcache;
  input [7:0]S_AXI_0_arlen;
  input [0:0]S_AXI_0_arlock;
  input [2:0]S_AXI_0_arprot;
  input [3:0]S_AXI_0_arqos;
  output S_AXI_0_arready;
  input [3:0]S_AXI_0_arregion;
  input [2:0]S_AXI_0_arsize;
  input S_AXI_0_arvalid;
  input [31:0]S_AXI_0_awaddr;
  input [1:0]S_AXI_0_awburst;
  input [3:0]S_AXI_0_awcache;
  input [7:0]S_AXI_0_awlen;
  input [0:0]S_AXI_0_awlock;
  input [2:0]S_AXI_0_awprot;
  input [3:0]S_AXI_0_awqos;
  output S_AXI_0_awready;
  input [3:0]S_AXI_0_awregion;
  input [2:0]S_AXI_0_awsize;
  input S_AXI_0_awvalid;
  input S_AXI_0_bready;
  output [1:0]S_AXI_0_bresp;
  output S_AXI_0_bvalid;
  output [31:0]S_AXI_0_rdata;
  output S_AXI_0_rlast;
  input S_AXI_0_rready;
  output [1:0]S_AXI_0_rresp;
  output S_AXI_0_rvalid;
  input [31:0]S_AXI_0_wdata;
  input S_AXI_0_wlast;
  output S_AXI_0_wready;
  input [3:0]S_AXI_0_wstrb;
  input S_AXI_0_wvalid;
  input aclk_0;
  input aresetn_0;

  wire [31:0]S_AXI_0_araddr;
  wire [1:0]S_AXI_0_arburst;
  wire [3:0]S_AXI_0_arcache;
  wire [7:0]S_AXI_0_arlen;
  wire [0:0]S_AXI_0_arlock;
  wire [2:0]S_AXI_0_arprot;
  wire [3:0]S_AXI_0_arqos;
  wire S_AXI_0_arready;
  wire [3:0]S_AXI_0_arregion;
  wire [2:0]S_AXI_0_arsize;
  wire S_AXI_0_arvalid;
  wire [31:0]S_AXI_0_awaddr;
  wire [1:0]S_AXI_0_awburst;
  wire [3:0]S_AXI_0_awcache;
  wire [7:0]S_AXI_0_awlen;
  wire [0:0]S_AXI_0_awlock;
  wire [2:0]S_AXI_0_awprot;
  wire [3:0]S_AXI_0_awqos;
  wire S_AXI_0_awready;
  wire [3:0]S_AXI_0_awregion;
  wire [2:0]S_AXI_0_awsize;
  wire S_AXI_0_awvalid;
  wire S_AXI_0_bready;
  wire [1:0]S_AXI_0_bresp;
  wire S_AXI_0_bvalid;
  wire [31:0]S_AXI_0_rdata;
  wire S_AXI_0_rlast;
  wire S_AXI_0_rready;
  wire [1:0]S_AXI_0_rresp;
  wire S_AXI_0_rvalid;
  wire [31:0]S_AXI_0_wdata;
  wire S_AXI_0_wlast;
  wire S_AXI_0_wready;
  wire [3:0]S_AXI_0_wstrb;
  wire S_AXI_0_wvalid;
  wire aclk_0;
  wire aresetn_0;

  vip_bd vip_bd_i
       (.S_AXI_0_araddr(S_AXI_0_araddr),
        .S_AXI_0_arburst(S_AXI_0_arburst),
        .S_AXI_0_arcache(S_AXI_0_arcache),
        .S_AXI_0_arlen(S_AXI_0_arlen),
        .S_AXI_0_arlock(S_AXI_0_arlock),
        .S_AXI_0_arprot(S_AXI_0_arprot),
        .S_AXI_0_arqos(S_AXI_0_arqos),
        .S_AXI_0_arready(S_AXI_0_arready),
        .S_AXI_0_arregion(S_AXI_0_arregion),
        .S_AXI_0_arsize(S_AXI_0_arsize),
        .S_AXI_0_arvalid(S_AXI_0_arvalid),
        .S_AXI_0_awaddr(S_AXI_0_awaddr),
        .S_AXI_0_awburst(S_AXI_0_awburst),
        .S_AXI_0_awcache(S_AXI_0_awcache),
        .S_AXI_0_awlen(S_AXI_0_awlen),
        .S_AXI_0_awlock(S_AXI_0_awlock),
        .S_AXI_0_awprot(S_AXI_0_awprot),
        .S_AXI_0_awqos(S_AXI_0_awqos),
        .S_AXI_0_awready(S_AXI_0_awready),
        .S_AXI_0_awregion(S_AXI_0_awregion),
        .S_AXI_0_awsize(S_AXI_0_awsize),
        .S_AXI_0_awvalid(S_AXI_0_awvalid),
        .S_AXI_0_bready(S_AXI_0_bready),
        .S_AXI_0_bresp(S_AXI_0_bresp),
        .S_AXI_0_bvalid(S_AXI_0_bvalid),
        .S_AXI_0_rdata(S_AXI_0_rdata),
        .S_AXI_0_rlast(S_AXI_0_rlast),
        .S_AXI_0_rready(S_AXI_0_rready),
        .S_AXI_0_rresp(S_AXI_0_rresp),
        .S_AXI_0_rvalid(S_AXI_0_rvalid),
        .S_AXI_0_wdata(S_AXI_0_wdata),
        .S_AXI_0_wlast(S_AXI_0_wlast),
        .S_AXI_0_wready(S_AXI_0_wready),
        .S_AXI_0_wstrb(S_AXI_0_wstrb),
        .S_AXI_0_wvalid(S_AXI_0_wvalid),
        .aclk_0(aclk_0),
        .aresetn_0(aresetn_0));
endmodule
