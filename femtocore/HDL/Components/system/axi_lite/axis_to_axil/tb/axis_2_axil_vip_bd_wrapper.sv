`timescale 1 ps / 1 ps

module axis_2_axil_vip_bd_wrapper (
    input wire clock,
    input wire reset,
    axi_lite.slave axi
);

    axis_2_axil_vip_bd vip_bd_i (
        .S_AXI_0_araddr(axi.ARADDR),
        .S_AXI_0_arready(axi.ARREADY),
        .S_AXI_0_arvalid(axi.ARVALID),
        .S_AXI_0_awaddr(axi.AWADDR),
        .S_AXI_0_awready(axi.AWREADY),
        .S_AXI_0_awvalid(axi.AWVALID),
        .S_AXI_0_bready(axi.BREADY),
        .S_AXI_0_bresp(axi.BRESP),
        .S_AXI_0_bvalid(axi.BVALID),
        .S_AXI_0_rdata(axi.RDATA),
        .S_AXI_0_rready(axi.RREADY),
        .S_AXI_0_rresp(axi.RRESP),
        .S_AXI_0_rvalid(axi.RVALID),
        .S_AXI_0_wdata(axi.WDATA),
        .S_AXI_0_wready(axi.WREADY),
        .S_AXI_0_wstrb(axi.WSTRB),
        .S_AXI_0_wvalid(axi.WVALID),
        .aclk_0(clock),
        .aresetn_0(reset)
    );
endmodule
