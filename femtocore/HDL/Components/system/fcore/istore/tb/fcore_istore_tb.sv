`timescale 10ns / 100ps
`include "interfaces.svh"
import axi_vip_pkg::*;
import vip_bd_axi_vip_0_0_pkg::*;


module fcore_istore_tb();
    reg clk= 0;
    reg rst= 0;
    reg [31:0] transaction_data[199:0];

    xil_axi_resp_t transaction_response;

    xil_axi_resp_t [255:0] resp;
    xil_axi_data_beat [255:0]  ruser;
    reg [200*32-1:0]read_data_serialized;
    
    reg [31:0] dma_read_addr;
    wire [31:0] dma_read_data;
    
    task automatic initialize_tr_data();
        integer i;
        for(i = 0; i < 200; i = i+1) begin
            transaction_data[i] <= i;
        end
    endtask //automatic

    task automatic randomize_tr_data();
        integer i;
        for(i = 0; i < 200; i = i+1) begin
            transaction_data[i] <= {$urandom};
        end
    endtask //automatic

    wire [200*32-1:0]transaction_data_serialized;
    genvar i;
    for (i=0; i<200; i=i+1) assign transaction_data_serialized[200*i+31:200*i] = transaction_data[i];

    initial begin
        rst <=0;
        #30 rst <=1;
    end

    //clock generation
    initial clk = 1; 
    always #0.5 clk = ~clk; 

    AXI axi_if();

    axi_transaction wr_transaction;
    vip_bd_axi_vip_0_0_mst_t master;

    vip_bd_wrapper VIP( 
        .clock(clk),
        .reset(rst),
        .axi(axi_if)
    );

    fCore_Istore DUT(
        .clock(clk),
        .reset(rst),
        .axi(axi_if),
        .dma_read_addr(dma_read_addr),
        .dma_read_data(dma_read_data)
    );



    initial begin
        dma_read_addr <= 0;
        master = new("master", VIP.vip_bd_i.axi_vip_0.inst.IF);
        master.start_master();
        
        #50 randomize_tr_data();

        master.AXI4_WRITE_BURST(0,
                                0,
                                199,
                                XIL_AXI_SIZE_4BYTE,
                                XIL_AXI_BURST_TYPE_INCR,
                                XIL_AXI_ALOCK_NOLOCK,
                                0,
                                0,
                                0,
                                0,
                                0,
                                transaction_data_serialized,
                                0,
                                transaction_response
        ); 


        #50 
        master.AXI4_READ_BURST(0,
                                0,
                                199,
                                XIL_AXI_SIZE_4BYTE,
                                XIL_AXI_BURST_TYPE_INCR,
                                XIL_AXI_ALOCK_NOLOCK,
                                0,
                                0,
                                0,
                                0,
                                0,
                                read_data_serialized,
                                resp,
                                ruser
        ); 




        forever begin
            wr_transaction = master.wr_driver.create_transaction("write transaction");
            WR_TRANSACTION_FAIL_1b: assert(wr_transaction.randomize());
            master.wr_driver.send(wr_transaction);
            #100;
            dma_read_addr = $urandom()%200;
            #100;
        end
        
        
    end


endmodule
