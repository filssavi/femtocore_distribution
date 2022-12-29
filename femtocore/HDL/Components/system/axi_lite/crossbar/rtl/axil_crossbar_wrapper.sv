// Copyright 2021 Filippo Savi
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

`include "interfaces.svh"

module axil_crossbar_interface #(
        parameter integer DATA_WIDTH = 32,
        parameter integer ADDR_WIDTH = 32,
        parameter NM = 4,
        parameter NS = 8,
        parameter [ADDR_WIDTH-1:0] SLAVE_ADDR [NS-1:0] = '{NS{0}},
        parameter [ADDR_WIDTH-1:0] SLAVE_MASK [NS-1:0] =  '{NS{0}},
        parameter [0:0] OPT_LOWPOWER = 1,
        parameter OPT_LINGER = 4,
        parameter LGMAXBURST = 5
    ) (
        input wire clock,
        input wire reset,
        axi_lite.slave slaves [NM-1:0],
        axi_lite.master masters [NS-1:0]
    );

    localparam STROBE_WIDTH = DATA_WIDTH/8;

    // SLAVE INTERFACES FLATTENING
    wire [NM-1:0] S_AXI_AWVALID;
    wire [NM*DATA_WIDTH-1:0] S_AXI_WDATA;
    wire [NM-1:0] S_AXI_WVALID;
    wire [NM-1:0] S_AXI_BREADY;
    wire [NM-1:0] S_AXI_ARVALID;
    wire [NM-1:0] S_AXI_RREADY;
    wire [NM-1:0] S_AXI_AWREADY;
    wire [NM-1:0] S_AXI_WREADY;
    wire [NM-1:0] S_AXI_BVALID;
    wire [NM-1:0] S_AXI_ARREADY;
    wire [NM-1:0] S_AXI_RVALID;
    wire [NM*DATA_WIDTH-1:0]  S_AXI_RDATA;
    wire [NM*STROBE_WIDTH-1:0] S_AXI_WSTRB;
    wire [NM*ADDR_WIDTH-1:0] S_AXI_AWADDR;
    wire [NM*ADDR_WIDTH-1:0] S_AXI_ARADDR;
    wire [NM*2-1:0] S_AXI_BRESP;
    wire [NM*2-1:0] S_AXI_RRESP;
    wire [NM*3-1:0] S_AXI_AWPROT;
    wire [NM*3-1:0] S_AXI_ARPROT;
    
    genvar i;
    generate
        for(i = 0; i< NM; i = i + 1) begin
            
            // WRITE ADDRESS CHANNEL FLATTENING
            assign S_AXI_AWVALID[i] =  slaves[i].AWVALID;
            assign slaves[i].AWREADY = S_AXI_AWREADY[i];
            assign S_AXI_AWADDR[i*ADDR_WIDTH +: ADDR_WIDTH] = slaves[i].AWADDR;
            assign S_AXI_AWPROT[i*3 +: 3] = 0;

            // READ ADDRESS CHANNEL FLATTENING
            assign S_AXI_ARADDR[i*ADDR_WIDTH +: ADDR_WIDTH] = slaves[i].ARADDR;
            assign S_AXI_ARVALID[i] = slaves[i].ARVALID;
            assign slaves[i].ARREADY = S_AXI_ARREADY[i];
            assign S_AXI_ARPROT[i*3 +: 3] = 0;

            // WRITE DATA CHANNEL FLATTENING
            assign S_AXI_WVALID[i] = slaves[i].WVALID;
            assign slaves[i].WREADY = S_AXI_WREADY[i];
            assign S_AXI_WDATA[i*DATA_WIDTH +: DATA_WIDTH] = slaves[i].WDATA;
            assign S_AXI_WSTRB[i*STROBE_WIDTH +: STROBE_WIDTH] = slaves[i].WSTRB;
            
            // READ DATA/RESPONSE CHANNEL FLATTENING
            assign slaves[i].RDATA = S_AXI_RDATA[i*DATA_WIDTH +: DATA_WIDTH];
            assign slaves[i].RVALID = S_AXI_RVALID[i];
            assign S_AXI_RREADY[i] = slaves[i].RREADY;
            assign slaves[i].RRESP = S_AXI_RRESP[i*2 +: 2];
            
            // WRITE RESPONSE CHANNEL
            assign slaves[i].BVALID = S_AXI_BVALID[i];
            assign S_AXI_BREADY[i] = slaves[i].BREADY;
            assign slaves[i].BRESP = S_AXI_BRESP[i*2 +: 2];
            
        end    
    endgenerate

    // MASTER INTERFACES FLATTENING
    wire [NS*ADDR_WIDTH-1:0] M_AXI_AWADDR;
    wire [NS-1:0] M_AXI_AWVALID;
    wire [NS-1:0] M_AXI_AWREADY;
    wire [NS*DATA_WIDTH-1:0] M_AXI_WDATA;
    wire [NS*DATA_WIDTH/8-1:0] M_AXI_WSTRB;
    wire [NS-1:0] M_AXI_WVALID;
    wire [NS-1:0] M_AXI_WREADY;
    wire [NS*2-1:0] M_AXI_BRESP;
    wire [NS-1:0] M_AXI_BVALID;
    wire [NS-1:0] M_AXI_BREADY;
    wire [NS*ADDR_WIDTH-1:0] M_AXI_ARADDR;
    wire [NS-1:0] M_AXI_ARVALID;
    wire [NS-1:0] M_AXI_ARREADY;
    wire [NS*DATA_WIDTH-1:0] M_AXI_RDATA;
    wire [NS*2-1:0] M_AXI_RRESP;
    wire [NS-1:0] M_AXI_RVALID;
    wire [NS-1:0] M_AXI_RREADY;
    wire [NS*3-1:0] M_AXI_AWPROT;
    wire [NS*3-1:0] M_AXI_ARPROT;

    generate
        for(i = 0; i< NS; i = i + 1) begin
            
            // WRITE ADDRESS CHANNEL FLATTENING
            assign masters[i].AWVALID = M_AXI_AWVALID[i];
            assign M_AXI_AWREADY[i] = masters[i].AWREADY;
            assign masters[i].AWADDR  = M_AXI_AWADDR[i*ADDR_WIDTH +: ADDR_WIDTH];

            // READ ADDRESS CHANNEL FLATTENING
            assign masters[i].ARADDR = M_AXI_ARADDR[i*ADDR_WIDTH +: ADDR_WIDTH];
            assign masters[i].ARVALID = M_AXI_ARVALID[i];
            assign M_AXI_ARREADY[i] = masters[i].ARREADY;

            // WRITE DATA CHANNEL FLATTENING
            assign masters[i].WVALID = M_AXI_WVALID[i];
            assign M_AXI_WREADY[i] = masters[i].WREADY;
            assign masters[i].WDATA = M_AXI_WDATA[i*DATA_WIDTH +: DATA_WIDTH];
            assign masters[i].WSTRB = M_AXI_WSTRB[i*STROBE_WIDTH +: STROBE_WIDTH];
            
            // READ DATA/RESPONSE CHANNEL FLATTENING
            assign M_AXI_RDATA[i*DATA_WIDTH +: DATA_WIDTH] = masters[i].RDATA;
            assign M_AXI_RVALID[i] = masters[i].RVALID;
            assign masters[i].RREADY = M_AXI_RREADY[i];
            assign M_AXI_RRESP[i*2 +: 2] = masters[i].RRESP;
            
            // WRITE RESPONSE CHANNEL
            assign M_AXI_BVALID[i] = masters[i].BVALID;
            assign masters[i].BREADY = M_AXI_BREADY[i];
            assign M_AXI_BRESP[i*2 +: 2] = masters[i].BRESP;
            
        end    
    endgenerate

    axilxbar #(
        .DATA_WIDTH(DATA_WIDTH),
        .ADDR_WIDTH(ADDR_WIDTH),
        .NM(NM),
        .NS(NS),
        .SLAVE_ADDR(SLAVE_ADDR),
        .SLAVE_MASK(SLAVE_MASK),
        .OPT_LOWPOWER(OPT_LOWPOWER),
        .OPT_LINGER(OPT_LINGER),
        .LGMAXBURST(LGMAXBURST)
    ) inner_crossbar(
        .clock(clock),
        .reset(reset),
        .S_AXI_AWADDR(S_AXI_AWADDR),
        .S_AXI_AWPROT(S_AXI_AWPROT),
        .S_AXI_AWVALID(S_AXI_AWVALID),
        .S_AXI_AWREADY(S_AXI_AWREADY),
        .S_AXI_WDATA(S_AXI_WDATA),
        .S_AXI_WSTRB(S_AXI_WSTRB),
        .S_AXI_WVALID(S_AXI_WVALID),
        .S_AXI_WREADY(S_AXI_WREADY),
        .S_AXI_BRESP(S_AXI_BRESP),
        .S_AXI_BVALID(S_AXI_BVALID),
        .S_AXI_BREADY(S_AXI_BREADY),
        .S_AXI_ARADDR(S_AXI_ARADDR),
        .S_AXI_ARPROT(S_AXI_ARPROT),
        .S_AXI_ARVALID(S_AXI_ARVALID),
        .S_AXI_ARREADY(S_AXI_ARREADY),
        .S_AXI_RDATA(S_AXI_RDATA),
        .S_AXI_RRESP(S_AXI_RRESP),
        .S_AXI_RVALID(S_AXI_RVALID),
        .S_AXI_RREADY(S_AXI_RREADY),

        .M_AXI_AWADDR(M_AXI_AWADDR),
        .M_AXI_AWPROT(M_AXI_AWPROT),
        .M_AXI_AWVALID(M_AXI_AWVALID),
        .M_AXI_AWREADY(M_AXI_AWREADY),
        .M_AXI_WDATA(M_AXI_WDATA),
        .M_AXI_WSTRB(M_AXI_WSTRB),
        .M_AXI_WVALID(M_AXI_WVALID),
        .M_AXI_WREADY(M_AXI_WREADY),
        .M_AXI_BRESP(M_AXI_BRESP),
        .M_AXI_BVALID(M_AXI_BVALID),
        .M_AXI_BREADY(M_AXI_BREADY),
        .M_AXI_ARADDR(M_AXI_ARADDR),
        .M_AXI_ARPROT(M_AXI_ARPROT),
        .M_AXI_ARVALID(M_AXI_ARVALID),
        .M_AXI_ARREADY(M_AXI_ARREADY),
        .M_AXI_RDATA(M_AXI_RDATA),
        .M_AXI_RRESP(M_AXI_RRESP),
        .M_AXI_RVALID(M_AXI_RVALID),
        .M_AXI_RREADY(M_AXI_RREADY)
    );



    

endmodule