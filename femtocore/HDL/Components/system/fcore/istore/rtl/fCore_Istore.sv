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

`timescale 10ns / 1ns
`include "interfaces.svh"
module fCore_Istore # (
        parameter integer ID_WIDTH = 1,
        parameter integer DATA_WIDTH = 32,
        parameter integer USER_WIDTH = 10,
        parameter integer MEM_DEPTH = 4096,
        parameter READBACK = "DISABLED",
        parameter REGISTERED = "FALSE",
        parameter FAST_DEBUG = "TRUE",
        parameter INIT_FILE = "init.mem"
    )(
        input wire clock_in,
        input wire clock_out,
        input wire reset_in,
        input wire reset_out,
        input wire enable_bus_read,
        input wire [$clog2(MEM_DEPTH)-1:0] dma_read_addr,
        output reg [2*DATA_WIDTH-1:0] dma_read_data_w,
        AXI.slave axi
    );
    
    localparam ADDR_WIDTH = $clog2(MEM_DEPTH);
    // AXI SPECIFIC SIGNALS

    reg [ADDR_WIDTH-1 : 0] axi_awaddr;
    reg [ADDR_WIDTH-1 : 0] axi_word_address_w;
    reg [ADDR_WIDTH-1 : 0] axi_word_address_r;
    reg [ADDR_WIDTH-1 : 0] 	axi_araddr;

    wire aw_wrap_en;
    wire ar_wrap_en;
    wire [31:0]  aw_wrap_size ; 
    wire [31:0]  ar_wrap_size ; 
    reg axi_awv_awr_flag;
    reg axi_arv_arr_flag; 
    reg [ADDR_WIDTH-1:0] axi_awlen_cntr;
    reg [ADDR_WIDTH-1:0] axi_arlen_cntr;
    reg [1:0] axi_arburst;
    reg [1:0] axi_awburst;
    reg [ADDR_WIDTH:0] axi_arlen;
    reg [ADDR_WIDTH:0] axi_awlen;

    localparam integer ADDR_LSB = (DATA_WIDTH/32)+ 1;
    localparam integer OPT_MEM_ADDR_BITS = 7;
    localparam integer USER_NUM_MEM = 100;



    assign axi.BID = axi.AWID;
    assign axi.RID = axi.ARID;
    assign  aw_wrap_size = (DATA_WIDTH/8 * (axi_awlen)); 
    assign  ar_wrap_size = (DATA_WIDTH/8 * (axi_arlen)); 
    assign  aw_wrap_en = ((axi_awaddr & aw_wrap_size) == aw_wrap_size)? 1'b1: 1'b0;
    assign  ar_wrap_en = ((axi_araddr & ar_wrap_size) == ar_wrap_size)? 1'b1: 1'b0;

    always @( posedge clock_in ) begin : axi_awready_generation
        if ( reset_in == 1'b0 ) begin
            axi.AWREADY <= 1'b0;
            axi_awv_awr_flag <= 1'b0;
        end else begin    
            if (~axi.AWREADY && axi.AWVALID && ~axi_awv_awr_flag && ~axi_arv_arr_flag) begin
                axi.AWREADY <= 1'b1;
                axi_awv_awr_flag  <= 1'b1; 
            end else if (axi.WLAST && axi.WREADY) begin
                axi_awv_awr_flag  <= 1'b0;
            end else begin
                axi.AWREADY <= 1'b0;
            end
        end 
    end     

    
    assign axi_word_address_w = axi.AWADDR >>2;

    always @( posedge clock_in ) begin : write_address_latching
        if ( reset_in == 1'b0 ) begin
            axi_awaddr <= 0;
            axi_awlen_cntr <= 0;
            axi_awburst <= 0;
            axi_awlen <= 0;
        end else begin    
            if (~axi.AWREADY && axi.AWVALID && ~axi_awv_awr_flag) begin
                axi_awaddr <= axi_word_address_w[ADDR_WIDTH - 1:0];  
                axi_awburst <= axi.AWBURST; 
                axi_awlen <= axi.AWLEN;     
                axi_awlen_cntr <= 0;
            end else if((axi_awlen_cntr <= axi_awlen) && axi.WREADY && axi.WVALID) begin
                axi_awlen_cntr <= axi_awlen_cntr + 1;
                case (axi_awburst)
                    2'b00: begin // fixed burst
                        axi_awaddr <= axi_awaddr;          
                    end   
                    2'b01: begin //incremental burst
                        axi_awaddr<= axi_awaddr+ 1;

                    end   
                    2'b10: //Wrapping burst
                        if (aw_wrap_en) begin
                            axi_awaddr <= (axi_awaddr - aw_wrap_size); 
                        end else begin
                            axi_awaddr[ADDR_WIDTH - 1:ADDR_LSB] <= axi_awaddr[ADDR_WIDTH - 1:ADDR_LSB] + 1;
                            axi_awaddr[ADDR_LSB-1:0]  <= {ADDR_LSB{1'b0}}; 
                        end                      
                    default: begin //reserved (incremental burst for example)
                        axi_awaddr <= axi_awaddr[ADDR_WIDTH - 1:ADDR_LSB] + 1;
                    end
                endcase              
            end
        end 
    end       

    always @( posedge clock_in ) begin : wready_generation
        if ( reset_in == 1'b0 ) begin
            axi.WREADY <= 1'b0;
        end else begin    
            if ( ~axi.WREADY && axi.WVALID && axi_awv_awr_flag) begin
                axi.WREADY <= 1'b1;
            end else if (axi.WLAST && axi.WREADY) begin
                axi.WREADY <= 1'b0;
            end
        end 
    end       
    
    always @( posedge clock_in ) begin : write_response_generation
        if ( reset_in == 1'b0 ) begin
            axi.BVALID <= 0;
            axi.BRESP <= 2'b0;
            axi.BUSER <= 0;
        end else begin    
            if (axi_awv_awr_flag && axi.WREADY && axi.WVALID && ~axi.BVALID && axi.WLAST ) begin
                axi.BVALID <= 1'b1;
                axi.BRESP  <= 2'b0; 
            end else begin
                if (axi.BREADY && axi.BVALID) begin
                    axi.BVALID <= 1'b0; 
                end  
            end
        end
    end   


    always @( posedge clock_in ) begin : read_address_ready_generation
        if ( reset_in == 1'b0 ) begin
            axi.ARREADY <= 1'b0;
            axi_arv_arr_flag <= 1'b0;
        end else begin    
            if (~axi.ARREADY && axi.ARVALID && ~axi_awv_awr_flag && ~axi_arv_arr_flag) begin
                axi.ARREADY <= 1'b1;
                axi_arv_arr_flag <= 1'b1;
            end else if (axi.RVALID && axi.RREADY && axi_arlen_cntr == axi_arlen) begin
                axi_arv_arr_flag  <= 1'b0;
            end else begin
                axi.ARREADY <= 1'b0;
            end
        end 
    end     

    assign axi_word_address_r = axi.ARADDR>>2;

    always @( posedge clock_in ) begin: read_address_latching
        if ( reset_in == 1'b0 ) begin
            axi_araddr <= 0;
            axi_arlen_cntr <= 0;
            axi_arburst <= 0;
            axi_arlen <= 0;
            axi.RLAST <= 1'b0;
            axi.RUSER <= 0;
        end else begin    
            if (~axi.ARREADY && axi.ARVALID && ~axi_arv_arr_flag) begin
                axi_araddr <= axi_word_address_r[ADDR_WIDTH - 1:0]; 
                axi_arburst <= axi.ARBURST; 
                axi_arlen <= axi.ARLEN;     
                axi_arlen_cntr <= 0;
                axi.RLAST <= 1'b0;
            end else if((axi_arlen_cntr <= axi_arlen) && axi.RVALID && axi.RREADY) begin
                axi_arlen_cntr <= axi_arlen_cntr + 1;
                axi.RLAST <= 1'b0;
                case (axi_arburst)
                    2'b00: begin // fixed burst
                        axi_araddr <= axi_araddr;        
                    end   
                    2'b01: begin //incremental burst
                        axi_araddr[ADDR_WIDTH - 1:ADDR_LSB] <= axi_araddr[ADDR_WIDTH - 1:ADDR_LSB] + 1; 
                        axi_araddr[ADDR_LSB-1:0]  <= {ADDR_LSB{1'b0}};
                    end   
                    2'b10: //Wrapping burst
                    if (ar_wrap_en) begin
                        axi_araddr <= (axi_araddr - ar_wrap_size); 
                    end else begin
                        axi_araddr[ADDR_WIDTH - 1:ADDR_LSB] <= axi_araddr[ADDR_WIDTH - 1:ADDR_LSB] + 1; 
                        axi_araddr[ADDR_LSB-1:0]  <= {ADDR_LSB{1'b0}};   
                    end                      
                    default: begin //reserved
                        axi_araddr <= axi_araddr[ADDR_WIDTH - 1:ADDR_LSB]+1;
                    end
                endcase              
            end else if((axi_arlen_cntr == axi_arlen) && ~axi.RLAST && axi_arv_arr_flag ) begin
                axi.RLAST <= 1'b1;
            end else if (axi.RREADY) begin
                axi.RLAST <= 1'b0;
            end          
        end 
    end
           
    always @( posedge clock_in ) begin : read_address_valid_gen
        if ( reset_in == 1'b0 ) begin
          axi.RVALID <= 0;
          axi.RRESP  <= 0;
        end else begin    
            if (axi_arv_arr_flag && ~axi.RVALID) begin
              axi.RVALID <= 1'b1;
              axi.RRESP  <= 2'b0; 
            end else if (axi.RVALID && axi.RREADY) begin
              axi.RVALID <= 1'b0;
            end            
        end
    end    

    // ------------------------------------------
    // -- Example code to access user logic memory region
    // ------------------------------------------
    
    wire [31:0]  memory_read_addr; 
    assign axi.RDATA = dma_read_data_w[31:0];

    
    assign memory_read_addr = enable_bus_read ? axi_araddr : dma_read_addr;

    istore_memory #(
        .ADDR_WIDTH($clog2(MEM_DEPTH)),
        .INIT_FILE(INIT_FILE),
        .FAST_DEBUG(FAST_DEBUG)
    ) memory_block(
        .clock_in(clock_in),
        .clock_out(clock_out),
        .reset(reset_in),
        .data_a(axi.WDATA),
        .data_b(dma_read_data_w),
        .addr_a(axi_awaddr),
        .addr_b(memory_read_addr),
        .we_a(axi.WREADY && axi.WVALID)
    );



    endmodule
