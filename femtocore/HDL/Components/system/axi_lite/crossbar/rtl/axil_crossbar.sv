////////////////////////////////////////////////////////////////////////////////
//
// Filename:  axilxbar.v
// {{{
// Project: WB2AXIPSP: bus bridges and other odds and ends
//
// Purpose: Create a full crossbar between NM AXI-lite sources (masters),
// and NS AXI-lite slaves.  Every master can talk to any slave,
// provided it isn't already busy.
//
// Performance: This core has been designed with the goal of being able to push
// one transaction through the interconnect, from any master to
// any slave, per clock cycle.  This may perhaps be its most unique
// feature.  While throughput is good, latency is something else.
//
// The arbiter requires a clock to switch, then another clock to send data
// downstream.  This creates a minimum two clock latency up front.  The
// return path suffers another clock of latency as well, placing the
// minimum latency at four clocks.  The minimum write latency is at
// least one clock longer, since the write data must wait for the write
// address before proceeeding.
//
// Usage: To use, you must first set NM and NS to the number of masters
// and the number of slaves you wish to connect to.  You then need to
// adjust the addresses of the slaves, found SLAVE_ADDR array.  Those
// bits that are relevant in SLAVE_ADDR to then also be set in SLAVE_MASK.
// Adjusting the data and address widths go without saying.
//
// Lower numbered masters are given priority in any "fight".
//
// Channel grants are given on the condition that 1) they are requested,
// 2) no other channel has a grant, 3) all of the responses have been
// received from the current channel, and 4) the internal counters are
// not overflowing.
//
// The core limits the number of outstanding transactions on any channel to
// 1<<LGMAXBURST-1.
//
// Channel grants are lost 1) after OPT_LINGER clocks of being idle, or
// 2) when another master requests an idle (but still lingering) channel
// assignment, or 3) once all the responses have been returned to the
// current channel, and the current master is requesting another channel.
//
// A special slave is allocated for the case of no valid address.
//
// Since the write channel has no address information, the write data
// channel always be delayed by at least one clock from the write address
// channel.
//
// If OPT_LOWPOWER is set, then unused values will be set to zero.
// This can also be used to help identify relevant values within any
// trace.
//
//
// Creator: Dan Gisselquist, Ph.D.
// Gisselquist Technology, LLC
//
////////////////////////////////////////////////////////////////////////////////
// }}}
// Copyright (C) 2019-2021, Gisselquist Technology, LLC
// {{{
// This file is part of the WB2AXIP project.
//
// The WB2AXIP project contains free software and gateware, licensed under the
// Apache License, Version 2.0 (the "License").  You may not use this project,
// or this file, except in compliance with the License.  You may obtain a copy
// of the License at
//
//  http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
// WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
// License for the specific language governing permissions and limitations
// under the License.
//
////////////////////////////////////////////////////////////////////////////////

`default_nettype none
module axilxbar #(
        parameter integer DATA_WIDTH = 32,
        parameter integer ADDR_WIDTH = 32,
        //
        // NM is the number of master interfaces this core supports
        parameter NM = 4,
        //
        // NS is the number of slave interfaces
        parameter NS = 8,
        // SLAVE_ADDR is a bit vector containing ADDR_WIDTH bits for each of the
        // slaves indicating the base address of the slave.  This
        // goes with SLAVE_MASK below.
        parameter [ADDR_WIDTH-1:0] SLAVE_ADDR [NS-1:0] = '{NS{0}},    
        //
        // SLAVE_MASK indicates which bits in the SLAVE_ADDR bit vector
        // need to be checked to determine if a given address request
        // maps to the given slave or not .
        // slave selection is done through simple address pattern matching,
        // if a bit in the mask is 1 the corresponding bit in the SLAVE_ADDR
        // field is checked against the incoming transaction, those bits are ignored
        // Verilator lint_off WIDTH
        parameter [ADDR_WIDTH-1:0] SLAVE_MASK [NS-1:0] =  '{NS{0}},
        // Verilator lint_on WIDTH
        //
        // If set, OPT_LOWPOWER will set all unused registers, both
        // internal and external, to zero anytime their corresponding
        // *VALID bit is clear
        parameter [0:0] OPT_LOWPOWER = 1,
        //
        // OPT_LINGER is the number of cycles to wait, following a
        // transaction, before tearing down the bus grant.
        parameter OPT_LINGER = 4,
        //
        // LGMAXBURST is the log (base two) of the maximum number of
        // requests that can be outstanding on any given channel at any
        // given time.  It is used within this core to control the
        // counters that are used to determine if a particular channel
        // grant must stay open, or if it may be closed.
        parameter LGMAXBURST = 5
    ) (
        input wire clock,
        input wire reset,
        // Incoming AXI4-lite slave port(s)
        input wire [NM*ADDR_WIDTH-1:0] S_AXI_AWADDR,
        input wire [NM*3-1:0] S_AXI_AWPROT,
        input wire [NM-1:0] S_AXI_AWVALID,
        output wire [NM-1:0] S_AXI_AWREADY,
        input wire [NM*DATA_WIDTH-1:0] S_AXI_WDATA,
        input wire [NM*DATA_WIDTH/8-1:0] S_AXI_WSTRB,
        input wire [NM-1:0] S_AXI_WVALID,
        output wire [NM-1:0] S_AXI_WREADY,
        output wire [NM*2-1:0] S_AXI_BRESP,
        output wire [NM-1:0] S_AXI_BVALID,
        input wire [NM-1:0] S_AXI_BREADY,
        input wire [NM*ADDR_WIDTH-1:0] S_AXI_ARADDR,
        input wire [NM*3-1:0] S_AXI_ARPROT,
        input wire [NM-1:0] S_AXI_ARVALID,
        output wire [NM-1:0] S_AXI_ARREADY,
        output wire [NM*DATA_WIDTH-1:0]  S_AXI_RDATA,
        output wire [NM*2-1:0] S_AXI_RRESP,
        output wire [NM-1:0] S_AXI_RVALID,
        input wire [NM-1:0] S_AXI_RREADY,
        // Outgoing AXI4-lite master port(s)
        output wire [NS*ADDR_WIDTH-1:0] M_AXI_AWADDR,
        output wire [NS*3-1:0] M_AXI_AWPROT,
        output wire [NS-1:0] M_AXI_AWVALID,
        input wire [NS-1:0] M_AXI_AWREADY,
        output wire [NS*DATA_WIDTH-1:0] M_AXI_WDATA,
        output wire [NS*DATA_WIDTH/8-1:0] M_AXI_WSTRB,
        output wire [NS-1:0] M_AXI_WVALID,
        input wire [NS-1:0] M_AXI_WREADY,
        input wire [NS*2-1:0] M_AXI_BRESP,
        input wire [NS-1:0] M_AXI_BVALID,
        output wire [NS-1:0] M_AXI_BREADY,
        output wire [NS*ADDR_WIDTH-1:0] M_AXI_ARADDR,
        output wire [NS*3-1:0] M_AXI_ARPROT,
        output wire [NS-1:0] M_AXI_ARVALID,
        input wire [NS-1:0] M_AXI_ARREADY,
        input wire [NS*DATA_WIDTH-1:0] M_AXI_RDATA,
        input wire [NS*2-1:0] M_AXI_RRESP,
        input wire [NS-1:0] M_AXI_RVALID,
        output wire [NS-1:0] M_AXI_RREADY
    );

    // Local parameters, derived from those above
    localparam LGLINGER = (OPT_LINGER>1) ? $clog2(OPT_LINGER+1) : 1;
    localparam LGNM = (NM>1) ? $clog2(NM) : 1;
    localparam LGNS = (NS>1) ? $clog2(NS+1) : 1;

    // In order to use indexes, and hence fully balanced mux trees, it helps
    // to make certain that we have a power of two based lookup.  NMFULL
    // is the number of masters in this lookup, with potentially some
    // unused extra ones.  NSFULL is defined similarly.
    localparam NMFULL = (NM>1) ? (1<<LGNM) : 1;
    localparam NSFULL = (NS>1) ? (1<<LGNS) : 2;
    localparam [1:0] INTERCONNECT_ERROR = 2'b11;
    localparam [0:0] OPT_SKID_INPUT = 0;
    localparam [0:0] OPT_BUFFER_DECODER = 1;

    genvar N,M;

    reg [NSFULL-1:0] wrequest [0:NM-1];
    reg [NSFULL-1:0] rrequest [0:NM-1];
    reg [NSFULL-1:0] wrequested [0:NM];
    reg [NSFULL-1:0] rrequested [0:NM];
    reg [NS:0] wgrant [0:NM-1] = '{NM{0}};
    reg [NS:0] rgrant [0:NM-1];
    reg [NM-1:0] swgrant = 0;
    reg [NM-1:0] srgrant = 0;
    reg [NS-1:0] mwgrant = 0;
    reg [NS-1:0] mrgrant;


    wire [LGMAXBURST-1:0] w_sawpending [0:NM-1];
    wire [LGMAXBURST-1:0] w_swpending [0:NM-1];
    wire [LGMAXBURST-1:0] w_srpending [0:NM-1];

    reg [NM-1:0] swfull = {NM{1'b0}};
    reg [NM-1:0] srfull = {NM{1'b0}};
    reg [NM-1:0] swempty = {NM{1'b1}};
    reg [NM-1:0] srempty = {NM{1'b1}};
    wire [LGNS-1:0] swindex [0:NMFULL-1];
    wire [LGNS-1:0] srindex [0:NMFULL-1];
    wire [LGNM-1:0] mwindex [0:NSFULL-1];
    wire [LGNM-1:0] mrindex [0:NSFULL-1];

    wire [NM-1:0] wdata_expected;

    // The shadow buffers
    wire [NMFULL-1:0] m_awvalid, m_wvalid, m_arvalid;
    wire [NM-1:0] dcd_awvalid, dcd_arvalid;

    wire [ADDR_WIDTH-1:0] m_awaddr [0:NMFULL-1];
    wire [2:0] m_awprot [0:NMFULL-1];
    wire [DATA_WIDTH-1:0] m_wdata [0:NMFULL-1];
    wire [DATA_WIDTH/8-1:0] m_wstrb [0:NMFULL-1];

    wire [ADDR_WIDTH-1:0] m_araddr [0:NMFULL-1];
    wire [2:0] m_arprot [0:NMFULL-1];

    wire [NM-1:0] skd_awvalid, skd_awstall, skd_wvalid;
    wire [NM-1:0] skd_arvalid, skd_arstall;
    wire [ADDR_WIDTH-1:0] skd_awaddr [0:NM-1];
    wire [3-1:0] skd_awprot [0:NM-1];
    wire [ADDR_WIDTH-1:0] skd_araddr [0:NM-1];
    wire [3-1:0] skd_arprot [0:NM-1];

    reg r_bvalid [0:NM-1] = '{NM{0}};
    reg [1:0] r_bresp [0:NM-1] = '{NM{0}};

    reg [NSFULL-1:0] m_axi_awvalid;
    reg [NSFULL-1:0] m_axi_awready;
    reg [NSFULL-1:0] m_axi_wvalid;
    reg [NSFULL-1:0] m_axi_wready;
    reg [NSFULL-1:0] m_axi_bvalid;
    reg [1:0] m_axi_bresp [0:NSFULL-1];

    reg [NSFULL-1:0] m_axi_arvalid;
    reg [NSFULL-1:0] m_axi_arready;
    reg [NSFULL-1:0] m_axi_rvalid;
    reg [NSFULL-1:0] m_axi_rready;

    reg r_rvalid [0:NM-1] = '{NM{0}};
    reg [1:0] r_rresp [0:NM-1] = '{NM{0}};
    reg [DATA_WIDTH-1:0] r_rdata [0:NM-1] = '{NM{0}};

    reg [DATA_WIDTH-1:0] m_axi_rdata [0:NSFULL-1];
    reg [1:0]  m_axi_rresp [0:NSFULL-1];

    reg [NM-1:0] slave_awaccepts;
    reg [NM-1:0] slave_waccepts;
    reg [NM-1:0] slave_raccepts;


    // m_axi_[aw|w|b]*

    always_comb begin
        m_axi_awvalid = -1;
        m_axi_awready = -1;
        m_axi_wvalid = -1;
        m_axi_wready = -1;
        m_axi_bvalid = 0;

        m_axi_awvalid[NS-1:0] = M_AXI_AWVALID;
        m_axi_awready[NS-1:0] = M_AXI_AWREADY;
        m_axi_wvalid[NS-1:0]  = M_AXI_WVALID;
        m_axi_wready[NS-1:0]  = M_AXI_WREADY;
        m_axi_bvalid[NS-1:0]  = M_AXI_BVALID;
        
        for(integer int_m1=0; int_m1<NS; int_m1=int_m1+1) begin
            m_axi_bresp[int_m1] = M_AXI_BRESP[int_m1* 2 +:  2];

            m_axi_rdata[int_m1] = M_AXI_RDATA[int_m1*DATA_WIDTH +: DATA_WIDTH];
            m_axi_rresp[int_m1] = M_AXI_RRESP[int_m1* 2 +:  2];
        end

        for(integer int_m2=NS; int_m2<NSFULL; int_m2=int_m2+1) begin
            m_axi_bresp[int_m2] = INTERCONNECT_ERROR;

            m_axi_rdata[int_m2] = 0;
            m_axi_rresp[int_m2] = INTERCONNECT_ERROR;
        end
    end

    generate
        for(N=0; N<NM; N=N+1) begin : DECODE_WRITE_REQUEST
            wire [NS:0] wdecode;
            reg r_mawvalid, r_mwvalid;


            // awskid
            axil_skid_buffer #(
                .REGISTER_OUTPUT(OPT_SKID_INPUT),
                .DATA_WIDTH(ADDR_WIDTH+3)
            ) awskid (
                .clock(clock),
                .reset(reset),
                .in_valid(S_AXI_AWVALID[N]),
                .in_ready(S_AXI_AWREADY[N]),
                .in_data({ S_AXI_AWADDR[N*ADDR_WIDTH +: ADDR_WIDTH], S_AXI_AWPROT[N*3 +: 3] }),
                .out_valid(skd_awvalid[N]),
                .out_ready(!skd_awstall[N]),
                .out_data({ skd_awaddr[N], skd_awprot[N] })
            );


         

            // write address decoding
            address_decoder #(
                .AW(ADDR_WIDTH),
                .DW(3),
                .NS(NS),
                .SLAVE_ADDR(SLAVE_ADDR),
                .SLAVE_MASK(SLAVE_MASK),
                .OPT_REGISTERED(OPT_BUFFER_DECODER)
            ) wraddr(
                .clock(clock),
                .reset(!reset),
                .i_valid(skd_awvalid[N]),
                .o_stall(skd_awstall[N]),
                .i_addr(skd_awaddr[N]),
                .i_data(skd_awprot[N]),
                .o_valid(dcd_awvalid[N]),
                .i_stall(!dcd_awvalid[N]||!slave_awaccepts[N]),
                .o_decode(wdecode),
                .o_addr(m_awaddr[N]),
                .o_data(m_awprot[N])
            );

            // wskid
            
            // awskid
            axil_skid_buffer #(
                .REGISTER_OUTPUT(OPT_SKID_INPUT),
                .DATA_WIDTH(DATA_WIDTH+DATA_WIDTH/8)
            ) wskid (
                .clock(clock),
                .reset(reset),
                .in_valid(S_AXI_WVALID[N]),
                .in_ready(S_AXI_WREADY[N]),
                .in_data({ S_AXI_WDATA[N*DATA_WIDTH +: DATA_WIDTH], S_AXI_WSTRB[N*DATA_WIDTH/8 +: DATA_WIDTH/8]}),
                .out_valid(skd_wvalid[N]),
                .out_ready((m_wvalid[N] && slave_waccepts[N])),
                .out_data({ m_wdata[N], m_wstrb[N] })
            );


            // slave_awaccepts
            always_comb begin
                slave_awaccepts[N] = 1'b1;
                if (!swgrant[N]) begin
                    slave_awaccepts[N] = 1'b0;
                end
                if (swfull[N]) begin
                    slave_awaccepts[N] = 1'b0;
                end
                if (!wrequest[N][swindex[N]]) begin
                    slave_awaccepts[N] = 1'b0;
                end
                if (!wgrant[N][NS]&&(m_axi_awvalid[swindex[N]] && !m_axi_awready[swindex[N]])) begin
                    slave_awaccepts[N] = 1'b0;
                end
                // ERRORs are always accepted
                // back pressure is handled in the write side
            end

            // slave_waccepts
            always_comb begin
                slave_waccepts[N] = 1'b1;
                if (!swgrant[N]) begin
                    slave_waccepts[N] = 1'b0;
                end
                if (!wdata_expected[N]) begin
                    slave_waccepts[N] = 1'b0;
                end
                if (!wgrant[N][NS] &&(m_axi_wvalid[swindex[N]] && !m_axi_wready[swindex[N]])) begin
                    slave_waccepts[N] = 1'b0;
                end
                if (wgrant[N][NS]&&(S_AXI_BVALID[N]&& !S_AXI_BREADY[N])) begin
                    slave_waccepts[N] = 1'b0;
                end
            end

            always_comb begin
                r_mawvalid= dcd_awvalid[N] && !swfull[N];
                r_mwvalid = skd_wvalid[N];
                wrequest[N]= 0;
                if (!swfull[N]) begin
                    wrequest[N][NS:0] = wdecode;
                end
            end

            assign m_awvalid[N] = r_mawvalid;
            assign m_wvalid[N] = r_mwvalid;

        end 

        for (N=NM; N<NMFULL; N=N+1) begin : UNUSED_WSKID_BUFFERS
            assign m_awvalid[N] = 0;
            assign m_awaddr[N] = 0;
            assign m_awprot[N] = 0;
            assign m_wdata[N] = 0;
            assign m_wstrb[N] = 0;
        end
    endgenerate

    generate 
        for(N=0; N<NM; N=N+1) begin : DECODE_READ_REQUEST
            wire [NS:0] rdecode;
            reg r_marvalid;

            // arskid

                     // awskid
            axil_skid_buffer #(
                .REGISTER_OUTPUT(OPT_SKID_INPUT),
                .DATA_WIDTH(ADDR_WIDTH+3)
            ) awskid (
                .clock(clock),
                .reset(reset),
                .in_valid(S_AXI_ARVALID[N]),
                .in_ready(S_AXI_ARREADY[N]),
                .in_data({ S_AXI_ARADDR[N*ADDR_WIDTH +: ADDR_WIDTH], S_AXI_ARPROT[N*3 +: 3] }),
                .out_valid(skd_arvalid[N]),
                .out_ready(!skd_arstall[N]),
                .out_data({ skd_araddr[N], skd_arprot[N] })
            );

            // Read address decoding
            address_decoder #(
                .AW(ADDR_WIDTH),
                .DW(3),
                .NS(NS),
                .SLAVE_ADDR(SLAVE_ADDR),
                .SLAVE_MASK(SLAVE_MASK),
                .OPT_REGISTERED(OPT_BUFFER_DECODER)
            ) rdaddr(
                .clock(clock),
                .reset(!reset),
                .i_valid(skd_arvalid[N]),
                .o_stall(skd_arstall[N]),
                .i_addr(skd_araddr[N]),
                .i_data(skd_arprot[N]),
                .o_valid(dcd_arvalid[N]),
                .i_stall(!m_arvalid[N] || !slave_raccepts[N]),
                .o_decode(rdecode),
                .o_addr(m_araddr[N]),
                .o_data(m_arprot[N])
            );

            // m_arvalid[N]
            always_comb begin
                r_marvalid = dcd_arvalid[N] && !srfull[N];
                rrequest[N] = 0;
                if (!srfull[N]) begin
                    rrequest[N][NS:0] = rdecode;
                end
            end

            assign m_arvalid[N] = r_marvalid;

            // slave_raccepts
            always_comb begin
                slave_raccepts[N] = 1'b1;
                if (!srgrant[N]) begin
                    slave_raccepts[N] = 1'b0;
                end
                if (srfull[N]) begin
                    slave_raccepts[N] = 1'b0;
                end

                if (!rrequest[N][srindex[N]]) begin
                    slave_raccepts[N] = 1'b0;
                end

                if (!rgrant[N][NS]) begin
                    if (m_axi_arvalid[srindex[N]] && !m_axi_arready[srindex[N]]) begin
                        slave_raccepts[N] = 1'b0;
                    end
                end else if (S_AXI_RVALID[N] && !S_AXI_RREADY[N]) begin
                    slave_raccepts[N] = 1'b0;
                end
                    
            end
        end 
        
        for (N=NM; N<NMFULL; N=N+1) begin : UNUSED_RSKID_BUFFERS
            assign m_arvalid[N] = 0;
            assign m_araddr[N] = 0;
            assign m_arprot[N] = 0;
        end
    endgenerate

    // wrequested
    always_comb begin : DECONFLICT_WRITE_REQUESTS

        for(integer int_n =1; int_n<NM ; int_n=int_n+1) begin
            wrequested[int_n] = 0;
        end
            

        // Vivado may complain about too many bits for wrequested.
        // This is (currrently) expected.  swindex is used to index
        // into wrequested, and swindex has LGNS bits, where LGNS
        // is $clog2(NS+1) rather than $clog2(NS).  The extra bits
        // are defined to be zeros, but the point is there are defined.
        // Therefore, no matter what swindex is, it will always
        // reference something valid.
        wrequested[NM] = 0;

        for(integer int_m=0; int_m<NS; int_m=int_m+1) begin
            wrequested[0][int_m] = 1'b0;
            for(integer int_n =1; int_n<NM ; int_n=int_n+1)  begin
                // Continue to request any channel with
                // a grant and pending operations
                if (wrequest[int_n-1][int_m] && wgrant[int_n-1][int_m])
                    wrequested[int_n][int_m] = 1;
                if (wrequest[int_n-1][int_m] && (!swgrant[int_n-1]||swempty[int_n-1]))
                    wrequested[int_n][int_m] = 1;
                // Otherwise, if it's already claimed, then
                // it can't be claimed again
                if (wrequested[int_n-1][int_m])
                    wrequested[int_n][int_m] = 1;
            end
            wrequested[NM][int_m] = wrequest[NM-1][int_m] || wrequested[NM-1][int_m];
        end
    end

    // rrequested
    always_comb begin : DECONFLICT_READ_REQUESTS
        for(integer int_n=0; int_n<NM ; int_n=int_n+1)begin
            rrequested[int_n] = 0;
        end

        // See the note above for wrequested.  This applies to
        // rrequested as well.
        rrequested[NM] = 0;

        for(integer int_m=0; int_m<NS; int_m=int_m+1) begin
            rrequested[0][int_m] = 0;
            for(integer int_n=1; int_n<NM ; int_n=int_n+1) begin
                // Continue to request any channel with
                // a grant and pending operations
                if (rrequest[int_n-1][int_m] && rgrant[int_n-1][int_m])
                    rrequested[int_n][int_m] = 1;
                if (rrequest[int_n-1][int_m] && (!srgrant[int_n-1] || srempty[int_n-1]))
                    rrequested[int_n][int_m] = 1;
                // Otherwise, if it's already claimed, then
                // it can't be claimed again
                if (rrequested[int_n-1][int_m])
                    rrequested[int_n][int_m] = 1;
            end
            rrequested[NM][int_m] = rrequest[NM-1][int_m] || rrequested[NM-1][int_m];
        end
    end

    // mwgrant, mrgrant
    generate 
        for(M=0; M<NS; M=M+1) begin
            always_comb begin
                mwgrant[M] = 0;
                for(integer int_n=0; int_n<NM; int_n=int_n+1) begin
                    if (wgrant[int_n][M]) begin
                        mwgrant[M] = 1;
                    end
                end
            end

            always_comb begin
                mrgrant[M] = 0;
                for(integer int_n=0; int_n<NM; int_n=int_n+1) begin
                    if (rgrant[int_n][M]) begin
                        mrgrant[M] = 1;    
                    end
                end
            end
        end
    endgenerate

    generate 
        for(N=0; N<NM; N=N+1)begin : ARBITRATE_WRITE_REQUESTS
            // Declarations
            reg stay_on_channel;
            reg requested_channel_is_available;
            reg leave_channel;
            reg [LGNS-1:0] requested_index;


            // stay_on_channel
            always_comb begin
                stay_on_channel = |(wrequest[N][NS:0] & wgrant[N]);

                if (swgrant[N] && !swempty[N])begin
                    stay_on_channel = 1;
                end
            end

            // requested_channel_is_available
            always_comb begin
                requested_channel_is_available = |(wrequest[N][NS-1:0] & ~mwgrant & ~wrequested[N][NS-1:0]);
                if (wrequest[N][NS])begin
                    requested_channel_is_available = 1;
                end
                    

                if (NM < 2) begin
                    requested_channel_is_available = m_awvalid[N];
                end
                    
            end


            wire linger;
            if (OPT_LINGER == 0) begin
                assign linger = 0;
            end else begin : WRITE_LINGER
                reg [LGLINGER-1:0] linger_counter = 0;
                reg r_linger = 0;

                always_ff @(posedge clock) begin
                    if (!reset || wgrant[N][NS]) begin
                        r_linger <= 0;
                        linger_counter <= 0;
                    end else if (!swempty[N] || S_AXI_BVALID[N]) begin
                        linger_counter <= OPT_LINGER;
                        r_linger <= 1;
                    end else if (linger_counter > 0) begin
                        r_linger <= (linger_counter > 1);
                        linger_counter <= linger_counter - 1;
                    end else begin
                        r_linger <= 0;
                    end
                end

                assign linger = r_linger;
            end

            // leave_channel
            always_comb begin
                leave_channel = 0;
                if (!m_awvalid[N] && (!linger || wrequested[NM][swindex[N]])) begin
                    // Leave the channel after OPT_LINGER counts
                    // of the channel being idle, or when someone
                    // else asks for the channel
                    leave_channel = 1;
                end
                if (m_awvalid[N] && !wrequest[N][swindex[N]]) begin
                    // Need to leave this channel to connect
                    // to any other channel
                    leave_channel = 1;
                end
            end

            // wgrant, swgrant
            always_ff @(posedge clock) begin
                if (!reset) begin
                    wgrant[N]  <= 0;
                    swgrant[N] <= 0;
                end else if (!stay_on_channel) begin
                    if (requested_channel_is_available) begin
                        // Switching channels
                        swgrant[N] <= 1'b1;
                        wgrant[N]  <= wrequest[N][NS:0];
                    end else if (leave_channel) begin
                        swgrant[N] <= 1'b0;
                        wgrant[N]  <= 0;
                    end
                end    
            end

            // requested_index

            always @(wrequest[N]) begin
                requested_index = 0;
                for(integer int_m=0; int_m<=NS; int_m=int_m+1) begin
                    if (wrequest[N][int_m]) begin
                        requested_index= requested_index | int_m[LGNS-1:0];
                    end
                end
            end

            // Now for swindex
            reg [LGNS-1:0] r_swindex = 0;
            always_ff @(posedge clock) begin
                if (!stay_on_channel && requested_channel_is_available) begin
                    r_swindex <= requested_index;
                end    
            end

            assign swindex[N] = r_swindex;
        end 

        for (N=NM; N<NMFULL; N=N+1) begin
            assign swindex[N] = 0;
        end 
    endgenerate

    generate 
        for(N=0; N<NM; N=N+1) begin : ARBITRATE_READ_REQUESTS
            // Declarations

            reg stay_on_channel;
            reg requested_channel_is_available;
            reg leave_channel;
            reg [LGNS-1:0] requested_index;

            // stay_on_channel
            always_comb begin
                stay_on_channel = |(rrequest[N][NS:0] & rgrant[N]);

                if (srgrant[N] && !srempty[N]) begin
                    stay_on_channel = 1;
                end
                    
            end

            // requested_channel_is_available
            always_comb begin
                requested_channel_is_available = |(rrequest[N][NS-1:0] & ~mrgrant & ~rrequested[N][NS-1:0]);
                if (rrequest[N][NS]) begin
                    requested_channel_is_available = 1;
                end
                    
                if (NM < 2) begin
                    requested_channel_is_available = m_arvalid[N];
                end
            end

            wire linger;
            if (OPT_LINGER == 0) begin
                assign linger = 0;
            end else begin : READ_LINGER
                reg [LGLINGER-1:0] linger_counter = 0;
                reg r_linger = 0;

                always_ff @(posedge clock) begin
                    if (!reset || rgrant[N][NS]) begin
                        r_linger <= 0;
                        linger_counter <= 0;
                    end else if (!srempty[N] || S_AXI_RVALID[N]) begin
                        linger_counter <= OPT_LINGER;
                        r_linger <= 1;
                    end else if (linger_counter > 0) begin
                        r_linger <= (linger_counter > 1);
                        linger_counter <= linger_counter - 1;
                    end else begin
                        r_linger <= 0;
                    end
                end
                
                assign linger = r_linger;
            end

            // leave_channel
            always_comb begin
                leave_channel = 0;
                if (!m_arvalid[N] && (!linger || rrequested[NM][srindex[N]])) begin
                    // Leave the channel after OPT_LINGER counts
                    // of the channel being idle, or when someone
                    // else asks for the channel
                    leave_channel = 1;
                end
                    
                if (m_arvalid[N] && !rrequest[N][srindex[N]]) begin
                    // Need to leave this channel to connect
                    // to any other channel
                    leave_channel = 1;
                end
            end

            // rgrant, srgrant
            initial rgrant[N]  = 0;
            always @(posedge clock) begin
                if (!reset) begin
                    rgrant[N]  <= 0;
                    srgrant[N] <= 0;
                end else if (!stay_on_channel) begin
                    if (requested_channel_is_available) begin
                        // Switching channels
                        srgrant[N] <= 1'b1;
                        rgrant[N] <= rrequest[N][NS:0];
                    end else if (leave_channel) begin
                        srgrant[N] <= 1'b0;
                        rgrant[N]  <= 0;
                    end
                end    
            end
            

            // requested_index
            always_ff @(rrequest[N]) begin
                requested_index = 0;
                for(integer int_im=0; int_im<=NS; int_im=int_im+1) begin
                    if (rrequest[N][int_im]) begin
                        requested_index = requested_index|int_im[LGNS-1:0];        
                    end
                end
            end

            // Now for srindex
            reg [LGNS-1:0] r_srindex = 0;
            always_ff @(posedge clock) begin
                if (!stay_on_channel && requested_channel_is_available) begin
                    r_srindex <= requested_index;
                end
            end

            assign srindex[N] = r_srindex;
        end 
        for (N=NM; N<NMFULL; N=N+1) begin
            assign srindex[N] = 0;
        end 
    endgenerate

    // Calculate mwindex
    generate 
        for (M=0; M<NS; M=M+1) begin : SLAVE_WRITE_INDEX
            int in_var;
            if (NM <= 1) begin
                assign mwindex[M] = 0;
            end else begin : MULTIPLE_MASTERS

                reg [LGNM-1:0] reswindex;
                reg [LGNM-1:0] r_mwindex;

                always_comb begin
                    reswindex = 0;
                    for(in_var=0; in_var<NM; in_var=in_var+1) begin
                        if ((!swgrant[in_var] || swempty[in_var]) &&(wrequest[in_var][M] && !wrequested[in_var][M])) begin
                            reswindex = reswindex | in_var[LGNM-1:0];
                        end
                    end 
                end

                always_ff @(posedge clock) begin
                    if (!mwgrant[M]) begin
                        r_mwindex <= reswindex;
                    end
                end
          
                assign mwindex[M] = r_mwindex;
            end
        end 

        for (M=NS; M<NSFULL; M=M+1) begin
            assign mwindex[M] = 0;
        end 
    endgenerate


    // Calculate mrindex
    generate 
        for (M=0; M<NS; M=M+1) begin : SLAVE_READ_INDEX
            int in_var;
            if (NM <= 1) begin
                assign mrindex[M] = 0;
            end else begin : MULTIPLE_MASTERS
                reg [LGNM-1:0] resrindex;
                reg [LGNM-1:0] r_mrindex;

                always_comb begin
                    resrindex = 0;
                    for(in_var=0; in_var<NM; in_var=in_var+1) begin
                        if ((!srgrant[in_var] || srempty[in_var]) &&(rrequest[in_var][M] && !rrequested[in_var][M])) begin
                            resrindex = resrindex | in_var[LGNM-1:0];
                        end
                    end
                end

                always_ff @(posedge clock) begin
                    if (!mrgrant[M]) begin
                        r_mrindex <= resrindex;
                    end
                end
   
                assign mrindex[M] = r_mrindex;
            end
        end 
        for (M=NS; M<NSFULL; M=M+1) begin
            assign mrindex[M] = 0;
        end 
    endgenerate

    // Assign outputs to the various slaves
    generate 
        for(M=0; M<NS; M=M+1) begin : WRITE_SLAVE_OUTPUTS
            // Declarations
            reg axi_awvalid = 0;
            reg [ADDR_WIDTH-1:0] axi_awaddr = 0;
            reg [2:0] axi_awprot = 0;

            reg axi_wvalid = 0;
            reg [DATA_WIDTH-1:0] axi_wdata = 0;
            reg [DATA_WIDTH/8-1:0] axi_wstrb = 0;
            reg axi_bready = 1;

            wire sawstall, swstall, mbstall;

            assign sawstall = (M_AXI_AWVALID[M]&& !M_AXI_AWREADY[M]);
            assign swstall = (M_AXI_WVALID[M] && !M_AXI_WREADY[M]);
            assign mbstall = (S_AXI_BVALID[mwindex[M]] && !S_AXI_BREADY[mwindex[M]]);

            // axi_awvalid
            always_ff @(posedge clock) begin
                if (!reset || !mwgrant[M]) begin
                    axi_awvalid <= 0;
                end else if (!sawstall) begin
                    axi_awvalid <= m_awvalid[mwindex[M]] &&(slave_awaccepts[mwindex[M]]);
                end
            end 
            

            // axi_awaddr, axi_awprot
            always_ff @(posedge clock) begin
                if (OPT_LOWPOWER && !reset) begin
                    axi_awaddr  <= 0;
                    axi_awprot  <= 0;
                end else if (OPT_LOWPOWER && !mwgrant[M]) begin
                    axi_awaddr  <= 0;
                    axi_awprot  <= 0;
                end else if (!sawstall) begin
                    if (!OPT_LOWPOWER||(m_awvalid[mwindex[M]]&&slave_awaccepts[mwindex[M]])) begin
                        axi_awaddr  <= m_awaddr[mwindex[M]];
                        axi_awprot  <= m_awprot[mwindex[M]];
                    end else begin
                        axi_awaddr  <= 0;
                        axi_awprot  <= 0;
                    end
                end        
            end

            // axi_wvalid
            always_ff @(posedge clock) begin
                if (!reset || !mwgrant[M]) begin
                    axi_wvalid <= 0;
                end else if (!swstall) begin
                    axi_wvalid <= (m_wvalid[mwindex[M]]) && (slave_waccepts[mwindex[M]]);
                end    
            end


            // axi_wdata, axi_wstrb
            always_ff @(posedge clock) begin
                if (OPT_LOWPOWER && !reset) begin
                    axi_wdata  <= 0;
                    axi_wstrb  <= 0;
                end else if (OPT_LOWPOWER && !mwgrant[M]) begin
                    axi_wdata  <= 0;
                    axi_wstrb  <= 0;
                end else if (!swstall) begin
                    if (!OPT_LOWPOWER || (m_wvalid[mwindex[M]]&&slave_waccepts[mwindex[M]])) begin
                        axi_wdata  <= m_wdata[mwindex[M]];
                        axi_wstrb  <= m_wstrb[mwindex[M]];
                    end else begin
                        axi_wdata  <= 0;
                        axi_wstrb  <= 0;
                    end
                end    
            end


            // axi_bready
            always_ff @(posedge clock) begin
                if (!reset || !mwgrant[M]) begin
                    axi_bready <= 1;
                end else if (!mbstall) begin
                    axi_bready <= 1;
                end else if (M_AXI_BVALID[M]) begin
                    axi_bready <= 0; 
                end
            end

            assign M_AXI_AWVALID[M] = axi_awvalid;
            assign M_AXI_AWADDR[M*ADDR_WIDTH +: ADDR_WIDTH] = axi_awaddr;
            assign M_AXI_AWPROT[M*3 +: 3] = axi_awprot;

            assign M_AXI_WVALID[M] = axi_wvalid;
            assign M_AXI_WDATA[M*DATA_WIDTH +: DATA_WIDTH] = axi_wdata;
            assign M_AXI_WSTRB[M*DATA_WIDTH/8 +: DATA_WIDTH/8] = axi_wstrb;

            assign M_AXI_BREADY[M] = axi_bready;

        end
    endgenerate


    generate 
        for(M=0; M<NS; M=M+1) begin : READ_SLAVE_OUTPUTS

            // Declarations
            reg axi_arvalid = 0;
            reg [ADDR_WIDTH-1:0] axi_araddr = 0;
            reg [2:0] axi_arprot = 0;
            reg axi_rready = 1;

            wire arstall, srstall;

            assign arstall = (M_AXI_ARVALID[M]&& !M_AXI_ARREADY[M]);
            assign srstall = (S_AXI_RVALID[mrindex[M]] && !S_AXI_RREADY[mrindex[M]]);

            // axi_arvalid
            always_ff @(posedge clock) begin
                if (!reset || !mrgrant[M]) begin
                    axi_arvalid <= 0;
                end else if (!arstall) begin
                    axi_arvalid <= m_arvalid[mrindex[M]] && slave_raccepts[mrindex[M]];
                end
            end

            // axi_araddr, axi_arprot
            always_ff @(posedge clock) begin
                if (OPT_LOWPOWER && !reset) begin
                    axi_araddr  <= 0;
                    axi_arprot  <= 0;
                end else if (OPT_LOWPOWER && !mrgrant[M]) begin
                    axi_araddr  <= 0;
                    axi_arprot  <= 0;
                end else if (!arstall) begin
                    if (!OPT_LOWPOWER || (m_arvalid[mrindex[M]] && slave_raccepts[mrindex[M]])) begin
                        if (NM == 1) begin
                            axi_araddr  <= m_araddr[0];
                            axi_arprot  <= m_arprot[0];
                        end else begin
                            axi_araddr  <= m_araddr[mrindex[M]];
                            axi_arprot  <= m_arprot[mrindex[M]];
                        end
                    end else begin
                        axi_araddr  <= 0;
                        axi_arprot  <= 0;
                    end
                end
            end
            

            // axi_rready
            always_ff @(posedge clock) begin
                if (!reset || !mrgrant[M]) begin
                    axi_rready <= 1;
                end else if (!srstall) begin
                    axi_rready <= 1;
                end else if (M_AXI_RVALID[M] && M_AXI_RREADY[M]) begin
                    axi_rready <= 0;
                end
            end



            assign M_AXI_ARVALID[M] = axi_arvalid;
            assign M_AXI_ARADDR[M*ADDR_WIDTH +: ADDR_WIDTH] = axi_araddr;
            assign M_AXI_ARPROT[M*3 +: 3] = axi_arprot;

            assign M_AXI_RREADY[M] = axi_rready;
        end
    endgenerate

    // Return values
    generate 
        for (N=0; N<NM; N=N+1) begin : WRITE_RETURN_CHANNEL
            reg axi_bvalid = 1'b0;
            reg [1:0] axi_bresp = 0;
            reg i_axi_bvalid = 1'b0;
            wire [1:0] i_axi_bresp;
            wire mbstall;

            always_comb begin
                if (wgrant[N][NS]) begin
                    i_axi_bvalid = m_wvalid[N] && slave_waccepts[N];
                end else begin
                    i_axi_bvalid = m_axi_bvalid[swindex[N]];
                end
            end
            
            assign i_axi_bresp = m_axi_bresp[swindex[N]];
            assign mbstall = S_AXI_BVALID[N] && !S_AXI_BREADY[N];

            // r_bvalid
            always_ff @(posedge clock) begin
                if (!reset) begin
                    r_bvalid[N] <= 0;
                end else if (mbstall && !r_bvalid[N] && !wgrant[N][NS]) begin
                    r_bvalid[N] <= swgrant[N] && i_axi_bvalid;
                end else if (!mbstall) begin
                    r_bvalid[N] <= 1'b0;
                end
            end
            

            // r_bresp
            always_ff @(posedge clock) begin
                if (OPT_LOWPOWER && !reset) begin
                    r_bresp[N] <= 0;
                end else if (OPT_LOWPOWER && (!swgrant[N] || S_AXI_BREADY[N])) begin
                    r_bresp[N] <= 0;
                end else if (!r_bvalid[N]) begin
                    if (!OPT_LOWPOWER ||(i_axi_bvalid && !wgrant[N][NS] && mbstall)) begin
                        r_bresp[N] <= i_axi_bresp;
                    end else begin
                        r_bresp[N] <= 0;
                    end
                end    
            end
            

            // axi_bvalid
            always_ff @(posedge clock) begin
                if (!reset)begin
                    axi_bvalid <= 0;
                end else if (!mbstall) begin
                    axi_bvalid <= swgrant[N] && (r_bvalid[N] || i_axi_bvalid);    
                end
            end

            // axi_bresp
            always_ff @(posedge clock) begin
                if (OPT_LOWPOWER && !reset) begin
                    axi_bresp <= 0;
                end else if (OPT_LOWPOWER && !swgrant[N]) begin
                    axi_bresp <= 0;
                end else if (!mbstall) begin
                    if (r_bvalid[N]) begin
                        axi_bresp <= r_bresp[N];
                    end else if (!OPT_LOWPOWER || i_axi_bvalid) begin
                        axi_bresp <= i_axi_bresp;
                    end else begin
                        axi_bresp <= 0;
                    end
                        
                    if (wgrant[N][NS] && (!OPT_LOWPOWER || i_axi_bvalid)) begin
                        axi_bresp <= INTERCONNECT_ERROR;
                    end
                end
            end

            assign S_AXI_BVALID[N]       = axi_bvalid;
            assign S_AXI_BRESP[N*2 +: 2] = axi_bresp;
        end
    endgenerate

    // m_axi_?r* values
    always_comb begin
        m_axi_arvalid = 0;
        m_axi_arready = 0;
        m_axi_rvalid = 0;
        m_axi_rready = 0;

        m_axi_arvalid[NS-1:0] = M_AXI_ARVALID;
        m_axi_arready[NS-1:0] = M_AXI_ARREADY;
        m_axi_rvalid[NS-1:0]  = M_AXI_RVALID;
        m_axi_rready[NS-1:0]  = M_AXI_RREADY;
    end 

    // Return values
    generate 
        for (N=0; N<NM; N=N+1) begin : READ_RETURN_CHANNEL
            reg axi_rvalid = 0;
            reg [1:0] axi_rresp = 0;
            reg [DATA_WIDTH-1:0] axi_rdata = 0;
            wire srstall;
            reg i_axi_rvalid = 1'b0;

            always_comb begin
                if (rgrant[N][NS])begin
                    i_axi_rvalid = m_arvalid[N] && slave_raccepts[N];
                end else begin
                    i_axi_rvalid = m_axi_rvalid[srindex[N]];    
                end
            end 

            assign srstall = S_AXI_RVALID[N] && !S_AXI_RREADY[N];

            always_ff @(posedge clock) begin
                if (!reset) begin
                    r_rvalid[N] <= 0;
                end else if (srstall && !r_rvalid[N]) begin
                    r_rvalid[N] <= srgrant[N] && !rgrant[N][NS]&&i_axi_rvalid;
                end else if (!srstall) begin
                    r_rvalid[N] <= 0;
                end
            end


            always_ff @(posedge clock) begin
                if (OPT_LOWPOWER && !reset) begin
                    r_rresp[N] <= 0;
                    r_rdata[N] <= 0;
                end else if (OPT_LOWPOWER && (!srgrant[N] || S_AXI_RREADY[N])) begin
                    r_rresp[N] <= 0;
                    r_rdata[N] <= 0;
                end else if (!r_rvalid[N]) begin
                    if (!OPT_LOWPOWER || (i_axi_rvalid && !rgrant[N][NS] && srstall)) begin
                        if (NS == 1) begin
                            r_rresp[N] <= m_axi_rresp[0];
                            r_rdata[N] <= m_axi_rdata[0];
                        end else begin
                            r_rresp[N] <= m_axi_rresp[srindex[N]];
                            r_rdata[N] <= m_axi_rdata[srindex[N]];
                        end
                    end else begin
                        r_rresp[N] <= 0;
                        r_rdata[N] <= 0;
                    end
                end
            end

            always_ff @(posedge clock)begin
                if (!reset) begin
                    axi_rvalid <= 0;
                end else if (!srstall) begin
                    axi_rvalid <= srgrant[N] && (r_rvalid[N] || i_axi_rvalid);    
                end
            end

            always_ff @(posedge clock) begin
                if (OPT_LOWPOWER && !reset) begin
                    axi_rresp <= 0;
                    axi_rdata <= 0;
                end else if (OPT_LOWPOWER && !srgrant[N]) begin
                    axi_rresp <= 0;
                    axi_rdata <= 0;
                end else if (!srstall) begin
                    if (r_rvalid[N]) begin
                        axi_rresp <= r_rresp[N];
                        axi_rdata <= r_rdata[N];
                    end else if (!OPT_LOWPOWER || i_axi_rvalid) begin
                        if (NS == 1) begin
                            axi_rresp <= m_axi_rresp[0];
                            axi_rdata <= m_axi_rdata[0];
                        end else begin
                            axi_rresp <= m_axi_rresp[srindex[N]];
                            axi_rdata <= m_axi_rdata[srindex[N]];
                        end
    
                        if (rgrant[N][NS]) begin
                            axi_rresp <= INTERCONNECT_ERROR;
                        end
                    end else begin
                        axi_rresp <= 0;
                        axi_rdata <= 0;
                    end
                end
            end
            

            assign S_AXI_RVALID[N] = axi_rvalid;
            assign S_AXI_RRESP[N*2 +: 2] = axi_rresp;
            assign S_AXI_RDATA[N*DATA_WIDTH +: DATA_WIDTH]= axi_rdata;
        end 
    endgenerate


    // Count pending transactions
    generate for (N=0; N<NM; N=N+1) begin : COUNT_PENDING
        reg [LGMAXBURST-1:0] rpending = 0;
        reg [LGMAXBURST-1:0] missing_wdata = 0;
        reg [LGMAXBURST-1:0] awpending = 0;
        reg [LGMAXBURST-1:0] wpending = 0;
        reg r_wdata_expected = 0;


        always_ff @(posedge clock) begin
            if (!reset) begin
                awpending <= 0;
                swempty[N] <= 1;
                swfull[N] <= 0;
            end else begin
                case ({(m_awvalid[N] && slave_awaccepts[N]),(S_AXI_BVALID[N] && S_AXI_BREADY[N])})
                    2'b01: begin
                        awpending <= awpending - 1;
                        swempty[N] <= (awpending <= 1);
                        swfull[N] <= 0;
                    end
                    2'b10: begin
                        awpending <= awpending + 1;
                        swempty[N] <= 0;
                        swfull[N] <= &awpending[LGMAXBURST-1:1];
                    end
                    default: begin 
                    end
                endcase
            end
        end

        always_ff @(posedge clock) begin
            if (!reset) begin
                wpending <= 0;
            end else begin
                case ({(m_wvalid[N] && slave_waccepts[N]),(S_AXI_BVALID[N] && S_AXI_BREADY[N])})
                    2'b01: wpending <= wpending - 1;
                    2'b10: wpending <= wpending + 1;
                    default: begin 
                    end
                endcase
            end 
        end

        always_ff @(posedge clock) begin
            if (!reset) begin
                missing_wdata <= 0;
            end else begin
                missing_wdata <= missing_wdata
                    +((m_awvalid[N] && slave_awaccepts[N])? 1:0)
                    -((m_wvalid[N] && slave_waccepts[N])? 1:0);
            end    
        end

        always_ff @(posedge clock) begin
            if (!reset)begin
                r_wdata_expected <= 0;
            end else begin
                case({ m_awvalid[N] && slave_awaccepts[N],m_wvalid[N] && slave_waccepts[N] })            
                    2'b10: r_wdata_expected <= 1;
                    2'b01: r_wdata_expected <= (missing_wdata > 1);
                    default: begin
                    end
                endcase
            end
        end

        always_ff @(posedge clock)begin
            if (!reset) begin
                rpending <= 0;
                srempty[N]<= 1;
                srfull[N] <= 0;
            end else begin
                case ({(m_arvalid[N] && slave_raccepts[N]),(S_AXI_RVALID[N] && S_AXI_RREADY[N])})
                    2'b01: begin
                        rpending <= rpending - 1;
                        srempty[N] <= (rpending == 1);
                        srfull[N] <= 0;
                    end
                    2'b10: begin
                        rpending <= rpending + 1;
                        srfull[N] <= &rpending[LGMAXBURST-1:1];
                        srempty[N] <= 0;
                    end
                    default: begin
                    end
                endcase
            end
        end

        assign w_sawpending[N] = awpending;
        assign w_swpending[N] = wpending;
        assign w_srpending[N] = rpending;

        assign wdata_expected[N] = r_wdata_expected;

    end
    endgenerate
endmodule