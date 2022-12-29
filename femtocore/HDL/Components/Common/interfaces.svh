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
`ifndef INTERFACES_SV
`define INTERFACES_SV

interface axi_lite #(DATA_WIDTH = 32, ADDR_WIDTH = 32, INTERFACE_NAME = "IF");
    logic [ADDR_WIDTH-1:0] ARADDR;
    logic [2:0] ARPROT;
    logic ARREADY;
    logic ARVALID;
    logic [ADDR_WIDTH-1:0] AWADDR;
    logic [2:0] AWPROT;
    logic AWREADY;
    logic AWVALID;
    logic BREADY;
    logic [1:0] BRESP;
    logic BVALID;
    logic [DATA_WIDTH-1:0] RDATA;
    logic RREADY;
    logic [1:0] RRESP;
    logic RVALID;
    logic [DATA_WIDTH-1:0] WDATA;
    logic WREADY;
    logic WVALID;
    logic [DATA_WIDTH/8-1:0] WSTRB;

    modport master (input AWREADY, WREADY, BRESP, BVALID, ARREADY, RDATA, RRESP, RVALID, 
    output AWADDR, AWPROT, AWVALID, WDATA, WVALID, WSTRB, BREADY, ARADDR, ARPROT, ARVALID, RREADY);
    modport slave (output AWREADY, WREADY, BRESP, BVALID, ARREADY, RDATA, RRESP, RVALID,
    input AWADDR, AWPROT, AWVALID, WDATA, WVALID, WSTRB, BREADY, ARADDR, ARPROT, ARVALID, RREADY);

endinterface



interface axi_stream #(DATA_WIDTH = 32, USER_WIDTH = 32, DEST_WIDTH = 32);
    logic [DATA_WIDTH-1:0] data;
    logic [USER_WIDTH-1:0] user;
    logic [DEST_WIDTH-1:0] dest;
    logic valid;
    logic ready;
    logic tlast;

    modport master(input  ready, output data, valid, tlast, user, dest, import initialize);
    modport slave (output  ready, input data, valid, tlast, user, dest, import initialize);

    task initialize();
        valid <= 0;
        user <= 0;
        dest <= 0;
        data <= 0;
        tlast <= 0;
    endtask

    task write (input logic [31:0] wr_data, real clk_per);
        //WRITE ADDR
        if(ready) begin
            data <= wr_data;
            valid <= 1;
            #clk_per valid <= 0;    
        end;
    endtask

endinterface

interface APB;
    logic [31:0] PADDR;
    logic PPROT;
    logic PSEL;
    logic PENABLE;
    logic PWRITE;
    logic [31:0] PWDATA;
    logic [3:0] PSTRB;
    logic PREADY;
    logic [31:0] PRDATA;
    logic PSLVERR;
    modport master(input  PREADY, PRDATA, PSLVERR, output PADDR, PPROT, PSEL, PENABLE, PWRITE, PWDATA, PSTRB);
    modport slave (input  PADDR, PPROT, PSEL, PENABLE, PWRITE, PWDATA, PSTRB, output PREADY, PRDATA, PSLVERR);
endinterface


interface SPI_if;

    logic MISO;
    logic MOSI;
    logic SCLK;
    logic SS;
    modport master (input MISO, output MOSI, SCLK, SS);
    modport slave (input MOSI, SCLK, SS, output MISO);

endinterface

interface AXI #(parameter ID_WIDTH = 1, USER_WIDTH = 1, DATA_WIDTH = 32, ADDR_WIDTH = 12);

    logic [ID_WIDTH-1:0] AWID;
    logic [ADDR_WIDTH-1:0] AWADDR;
    logic [7:0] AWLEN;
    logic [2:0] AWSIZE;
    logic [1:0] AWBURST;
    logic       AWLOCK;
    logic [3:0] AWCACHE;
    logic [2:0] AWPROT;
    logic [3:0] AWQOS;
    logic [3:0] AWREGION;
    logic [USER_WIDTH-1:0] AWUSER;
    logic       AWVALID;
    logic       AWREADY;
    logic [DATA_WIDTH-1:0] WDATA;
    logic [(DATA_WIDTH/8)-1:0] WSTRB;
    logic       WLAST;
    logic [USER_WIDTH-1:0] WUSER;
    logic       WVALID;
    logic       WREADY;
    logic [ID_WIDTH:0] BID;
    logic [1:0] BRESP;
    logic [USER_WIDTH-1:0] BUSER;
    logic       BVALID;
    logic       BREADY;
    logic [ID_WIDTH-1:0] ARID;
    logic [ADDR_WIDTH-1:0] ARADDR;
    logic [7:0] ARLEN;
    logic [2:0] ARSIZE;
    logic [1:0] ARBURST;
    logic       ARLOCK;
    logic [3:0] ARCACHE;
    logic [2:0] ARPROT;
    logic [3:0] ARQOS;
    logic [3:0] ARREGION;
    logic [USER_WIDTH-1:0] ARUSER;
    logic       ARVALID;
    logic       ARREADY;
    logic [ID_WIDTH-1:0] RID;
    logic [DATA_WIDTH-1:0] RDATA;
    logic [1:0] RRESP;
    logic       RLAST;
    logic [USER_WIDTH-1:0] RUSER;
    logic       RVALID;
    logic       RREADY;

    modport master (input AWREADY, WREADY, BID, BRESP, BUSER, BVALID, ARREADY, RID, RDATA, RRESP, RLAST, RUSER, RVALID, output AWID, AWADDR, AWLEN, AWSIZE, AWBURST ,AWLOCK, AWCACHE, AWPROT, AWQOS, AWREGION, AWUSER, AWVALID, WSTRB, WDATA, WLAST, WUSER, WVALID, BREADY, ARID, ARADDR, ARLEN, ARSIZE, ARBURST, ARLOCK, ARCACHE, ARPROT, ARQOS, ARREGION, ARUSER, ARVALID, RREADY);
    modport slave (output AWREADY, WREADY, BID, BRESP, BUSER, BVALID, ARREADY, RID, RDATA, RRESP, RLAST, RUSER, RVALID, input AWID, AWADDR, AWLEN, AWSIZE, AWBURST ,AWLOCK, AWCACHE, AWPROT, AWQOS, AWREGION, AWUSER, AWVALID, WSTRB, WDATA, WLAST, WUSER, WVALID, BREADY, ARID, ARADDR, ARLEN, ARSIZE, ARBURST, ARLOCK, ARCACHE, ARPROT, ARQOS, ARREGION, ARUSER, ARVALID, RREADY);
    
endinterface

`endif