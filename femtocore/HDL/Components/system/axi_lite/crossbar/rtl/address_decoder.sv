////////////////////////////////////////////////////////////////////////////////
//
// Filename: addrdecode.v
// {{{
// Project: WB2AXIPSP: bus bridges and other odds and ends
//
// Purpose: 
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
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
// WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
// License for the specific language governing permissions and limitations
// under the License.
//
////////////////////////////////////////////////////////////////////////////////
//
//
`default_nettype none
// }}}
module address_decoder #(

        parameter NS=8,
        parameter AW = 32, DW=32+32/8+1+1,
    
        // Verilator lint_on WIDTH
        //
        // SLAVE_ADDR contains address assignments for each of the
        // various slaves we are adjudicating between.
        parameter [AW-1:0] SLAVE_ADDR [NS-1:0] = '{NS{0}},    
        //
        // SLAVE_MASK contains a mask of those address bits in
        // SLAVE_ADDR which are relevant.  It shall be true that if
        // !SLAVE_MASK[k] then !SLAVE_ADDR[k], for any bits of k
        parameter [AW-1:0] SLAVE_MASK [NS-1:0] =  '{NS{0}},
        //
        // ACCESS_ALLOWED is a bit-wise mask indicating which slaves
        // may get access to the bus.  If ACCESS_ALLOWED[slave] is true,
        // then a master can connect to the slave via this method.  This
        // parameter is primarily here to support AXI (or other similar
        // buses) which may have separate accesses for both read and
        // write.  By using this, a read-only slave can be connected,
        // which would also naturally create an error on any attempt to
        // write to it.
        parameter [NS-1:0] ACCESS_ALLOWED = -1,
        //
        // If OPT_REGISTERED is set, address decoding will take an extra
        // clock, and will register the results of the decoding
        // operation.
        parameter [0:0] OPT_REGISTERED = 0,
        //
        // If OPT_LOWPOWER is set, then whenever the output is not
        // valid, any respective data linse will also be forced to zero
        // in an effort to minimize power.
        parameter [0:0] OPT_LOWPOWER = 0

    ) (
        input wire clock,
        input wire reset,
        input wire i_valid,
        output reg o_stall,
        input wire [AW-1:0] i_addr,
        input wire [DW-1:0] i_data,
        output reg o_valid,
        input wire i_stall,
        output wire [NS:0] o_decode,
        output reg [AW-1:0] o_addr,
        output reg [DW-1:0] o_data

    );

    // Local declarations

    // OPT_NONESEL controls whether or not the address lines are fully
    // proscribed, or whether or not a "no-slave identified" slave should
    // be created.  To avoid a "no-slave selected" output, slave zero must
    // have no mask bits set (and therefore no address bits set), and it
    // must also allow access.
    localparam [0:0] OPT_NONESEL = (!ACCESS_ALLOWED[0]) || (SLAVE_MASK[0] != 0);


    reg [NS:0] int_o_decode;
    assign o_decode = int_o_decode;
    
    reg [AW-1:0] int_o_addr;
    assign o_addr = int_o_addr;

    reg [DW-1:0] int_o_data;
    assign o_data = int_o_data;

    reg int_o_valid;
    assign o_valid = int_o_valid;


    wire [NS:0] request;
    reg [NS-1:0] prerequest;

    // prerequest
    always_comb begin
        for(integer int_m=0; int_m<NS; int_m=int_m+1) begin
            prerequest[int_m] = (((i_addr ^ SLAVE_ADDR[int_m]) &SLAVE_MASK[int_m])==0) &&(ACCESS_ALLOWED[int_m]);
        end    
    end

    // request
    generate
        if (OPT_NONESEL) begin : NO_DEFAULT_REQUEST

            reg [NS-1:0] r_request;

            // Need to create a slave to describe when nothing is selected
            always_comb begin
                for(integer int_m=0; int_m<NS; int_m=int_m+1) begin
                    r_request[int_m] = i_valid && prerequest[int_m];
                end
                   
                if (!OPT_NONESEL && (NS > 1 && |prerequest[NS-1:1])) begin
                    r_request[0] = 1'b0;
                end
            end

            assign request[NS-1:0] = r_request;

        end else if (NS == 1) begin : SINGLE_SLAVE

            assign request[0] = i_valid;

        end else begin

            reg [NS-1:0] r_request;

            always_comb begin
                for(integer int_m=0; int_m<NS; int_m=int_m+1) begin
                    r_request[int_m] = i_valid && prerequest[int_m];
                end
                if (!OPT_NONESEL && (NS > 1 && |prerequest[NS-1:1])) begin
                    r_request[0] = 1'b0;
                end
            end

            assign request[NS-1:0] = r_request;

        end 
    endgenerate


    // request[NS]
    generate 
        if (OPT_NONESEL) begin
            reg r_request_NS, r_none_sel;

            always_comb begin
                // Let's assume nothing's been selected, and then check
                // to prove ourselves wrong.
                //
                // Note that none_sel will be considered an error
                // condition in the follow-on processing.  Therefore
                // it's important to clear it if no request is pending.
                r_none_sel = i_valid && (prerequest == 0);
                //
                // request[NS] indicates a request for a non-existent
                // slave.  A request that should (eventually) return a
                // bus error
                //
                r_request_NS = r_none_sel;
            end

            assign request[NS] = r_request_NS;
        end else begin
            assign request[NS] = 1'b0;
        end
    endgenerate


    // int_o_valid, int_o_addr, int_o_data, int_o_decode, o_stall
    generate
        if (OPT_REGISTERED) begin

            // int_o_valid
            always_ff @(posedge clock) begin
                if (reset) begin
                    int_o_valid <= 0;
                end else if (!o_stall) begin
                    int_o_valid <= i_valid;
                end
            end


            // int_o_addr, int_o_data
            always_ff @(posedge clock) begin
                if (reset && OPT_LOWPOWER) begin
                    int_o_addr   <= 0;
                    int_o_data   <= 0;
                end else if ((!int_o_valid || !i_stall) && (i_valid || !OPT_LOWPOWER)) begin
                    int_o_addr   <= i_addr;
                    int_o_data   <= i_data;
                end else if (OPT_LOWPOWER && !i_stall) begin
                    int_o_addr   <= 0;
                    int_o_data   <= 0;
                end 
            end


            // int_o_decode
            always_ff @(posedge clock) begin
                if (reset) begin
                    int_o_decode <= 0;
                end else if ((!int_o_valid || !i_stall) && (i_valid || !OPT_LOWPOWER)) begin
                    int_o_decode <= request;
                end else if (OPT_LOWPOWER && !i_stall) begin
                    int_o_decode <= 0;
                end
            end


            // o_stall
            always_comb begin
                o_stall = (int_o_valid & i_stall);
            end

        end else begin

            always_comb begin
                int_o_valid = i_valid;
                o_stall = i_stall;
                int_o_addr  = i_addr;
                int_o_data  = i_data;

                int_o_decode = request; 
            end

        end
    endgenerate
endmodule
