`timescale 10ns / 100ps
`include "interfaces.svh"
import axi_vip_pkg::*;
import design_1_axi_vip_0_0_pkg::*;

module dma_manager_tb();

    reg clk, rst;


    initial begin
        rst <=0;
        #10 rst <=1;
    end


    //clock generation
    initial clk = 1; 
    always #0.5 clk = ~clk; 
    
    reg fifo_full;

    wire [31 : 0] m00_axi_awaddr;
    wire [2 : 0] m00_axi_awprot;
    wire  m00_axi_awvalid;
    wire  m00_axi_awready;
    wire [31 : 0] m00_axi_wdata;
    wire [31 : 0] m00_axi_wstrb;
    wire  m00_axi_wvalid;
    wire  m00_axi_wready;
    wire [1 : 0] m00_axi_bresp;
    wire  m00_axi_bvalid;
    wire  m00_axi_bready;
    wire [31 : 0] m00_axi_araddr;
    wire [2 : 0] m00_axi_arprot;
    wire  m00_axi_arvalid;
    wire  m00_axi_arready;
    wire [31 : 0] m00_axi_rdata;
    wire [1 : 0] m00_axi_rresp;
    wire  m00_axi_rvalid;
    wire  m00_axi_rready;


    vip_bd_wrapper VIP( 
        .S_AXI_0_araddr(axi.ARADDR),
        .S_AXI_0_arprot(3'b001),
        .S_AXI_0_awprot(3'b000),
        .S_AXI_0_wstrb( 4'b1111),
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
        .S_AXI_0_wvalid(axi.WVALID),
        .aclk_0(clk),
        .aresetn_0(rst)
    );

    design_1_axi_vip_0_0_slv_mem_t slave;
    axi_lite axi();
    initial begin
        slave = new("slave", VIP.design_1_i.axi_vip_0.inst.IF);
        slave.start_slave();
        fifo_full <= 0;
        #55 fifo_full <= 1;
        #4 fifo_full <= 0;
    end

    DMA_manager DUT(
		// Users to add ports here
        .fifo_full(fifo_full),
        .axi_lite(axi),
		.clock(clk),
		.reset(rst)
	);

endmodule
