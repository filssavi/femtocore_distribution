`timescale 1 ps / 1 ps

module vip_bd_wrapper (
    input wire clock,
    input wire reset,
    AXI.master axi
);

    vip_bd vip_bd_i (
        .M_AXI_0_araddr(axi.ARADDR),
        .M_AXI_0_arburst(axi.ARBURST),
        .M_AXI_0_arcache(axi.ARCACHE),
        .M_AXI_0_arlen(axi.ARLEN),
        .M_AXI_0_arlock(axi.ARLOCK),
        .M_AXI_0_arprot(axi.ARPROT),
        .M_AXI_0_arqos(axi.ARQOS),
        .M_AXI_0_arready(axi.ARREADY),
        .M_AXI_0_arregion(axi.ARREGION),
        .M_AXI_0_arsize(axi.ARSIZE),
        .M_AXI_0_arvalid(axi.ARVALID),
        .M_AXI_0_awaddr(axi.AWADDR),
        .M_AXI_0_awburst(axi.AWBURST),
        .M_AXI_0_awcache(axi.AWCACHE),
        .M_AXI_0_awlen(axi.AWLEN),
        .M_AXI_0_awlock(axi.AWLOCK),
        .M_AXI_0_awprot(axi.AWPROT),
        .M_AXI_0_awqos(axi.AWQOS),
        .M_AXI_0_awready(axi.AWREADY),
        .M_AXI_0_awregion(axi.AWREGION),
        .M_AXI_0_awsize(axi.AWSIZE),
        .M_AXI_0_awvalid(axi.AWVALID),
        .M_AXI_0_bready(axi.BREADY),
        .M_AXI_0_bresp(axi.BRESP),
        .M_AXI_0_bvalid(axi.BVALID),
        .M_AXI_0_rdata(axi.RDATA),
        .M_AXI_0_rlast(axi.RLAST),
        .M_AXI_0_rready(axi.RREADY),
        .M_AXI_0_rresp(axi.RRESP),
        .M_AXI_0_rvalid(axi.RVALID),
        .M_AXI_0_wdata(axi.WDATA),
        .M_AXI_0_wlast(axi.WLAST),
        .M_AXI_0_wready(axi.WREADY),
        .M_AXI_0_wstrb(axi.WSTRB),
        .M_AXI_0_wvalid(axi.WVALID),
        .aclk_0(clock),
        .aresetn_0(reset)
    );
endmodule
