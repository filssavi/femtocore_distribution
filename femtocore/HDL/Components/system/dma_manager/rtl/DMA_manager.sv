
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
`timescale 1 ns / 100 ps
`include "interfaces.svh"

module DMA_manager # (
    parameter DMA_BASE_ADDRESS = 32'h40400000,
    parameter integer C_M00_AXI_ADDR_WIDTH	= 32,
    parameter integer C_M00_AXI_DATA_WIDTH	= 32
)(
    input wire  clock,
    input wire  reset,
    input wire enable,
    input wire start_dma,
    input wire dma_done,
    input wire [31:0] transfer_size,
    input wire [31:0] buffer_base_address,
    axi_lite axi,
    output wire  m00_axi_error,
    output wire  m00_axi_txn_done
);


    reg prev_start_dma, axi_start_tx, dma_init_done;
    reg [31:0]axi_data, axi_address;
    reg [1:0] dma_init_counter;
    reg [31:0] dma_init_data [3:0];
    reg [31:0] dma_init_offsets [3:0];

    DMA_manager_inst # ( 
        .C_M_AXI_ADDR_WIDTH(C_M00_AXI_ADDR_WIDTH),
        .C_M_AXI_DATA_WIDTH(C_M00_AXI_DATA_WIDTH)
    ) internals (
        .address(axi_address),
        .data(axi_data),
        .INIT_AXI_TXN(axi_start_tx),
        .ERROR(m00_axi_error),
        .TXN_DONE(m00_axi_txn_done),
        .M_AXI_ACLK(clock),
        .M_AXI_ARESETN(reset),
        .M_AXI_AWADDR(axi.AWADDR),
        .M_AXI_AWVALID(axi.AWVALID),
        .M_AXI_AWREADY(axi.AWREADY),
        .M_AXI_WDATA(axi.WDATA),
        .M_AXI_WVALID(axi.WVALID),
        .M_AXI_WREADY(axi.WREADY),
        .M_AXI_BRESP(axi.BRESP),
        .M_AXI_BVALID(axi.BVALID),
        .M_AXI_BREADY(axi.BREADY),
        .M_AXI_ARADDR(axi.ARADDR),
        .M_AXI_ARVALID(axi.ARVALID),
        .M_AXI_ARREADY(axi.ARREADY),
        .M_AXI_RDATA(axi.RDATA),
        .M_AXI_RRESP(axi.RRESP),
        .M_AXI_RVALID(axi.RVALID),
        .M_AXI_RREADY(axi.RREADY)
    );

    always@(posedge clock)begin
        dma_init_data[1] <= buffer_base_address;
        dma_init_data[2] <= transfer_size;
        if(~reset)begin
            dma_init_done <= 0;
            axi_start_tx <= 0;
            dma_init_counter <= 0;
            prev_start_dma <= 0;	
            dma_init_data[0] <= 32'h1001;

            dma_init_data[3] <= 32'h1000;
            dma_init_offsets[0] <= 32'h30;
            dma_init_offsets[1] <= 32'h48;
            dma_init_offsets[2] <= 32'h58;
            dma_init_offsets[3] <= 32'h34;
        end else begin
            if(enable)begin
                if(~dma_init_done)begin
                    if(dma_init_counter==2)begin
                        dma_init_done <= 1;
                    end else begin
                        if(axi_start_tx & m00_axi_txn_done)begin
                            axi_start_tx <= 0;
                            dma_init_counter <= dma_init_counter+1;
                        end else begin
                            axi_start_tx <= 1;
                            axi_address <= DMA_BASE_ADDRESS + dma_init_offsets[dma_init_counter];
                            axi_data <= dma_init_data[dma_init_counter];
                        end
                    end
                end else begin
                    if(start_dma & ~prev_start_dma)begin
                        axi_start_tx <= 1;
                        axi_address <= DMA_BASE_ADDRESS + dma_init_offsets[2];
                        axi_data <= dma_init_data[2];
                    end
                    if(dma_done)begin
                        axi_start_tx <= 1;
                        axi_address <= DMA_BASE_ADDRESS + dma_init_offsets[3];
                        axi_data <= dma_init_data[3];
                    end 
                    if(axi_start_tx) begin
                        axi_start_tx <= 0;
                    end
                    prev_start_dma <= start_dma;
                end
            end else begin
                dma_init_done <= 0;
            end
        end
    end

endmodule
