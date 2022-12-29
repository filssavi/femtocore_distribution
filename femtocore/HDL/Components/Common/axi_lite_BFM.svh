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
`timescale 10 ns / 1 ns
`include "interfaces.svh"

`ifndef AXI_LITE_BFM_SV
`define AXI_LITE_BFM_SV


class axi_lite_BFM;

    virtual axi_lite.master bus;
    integer clock_period;


    function new (virtual axi_lite.master test_bus, integer period);
        begin
            this.bus = test_bus;

            this.bus.ARADDR <= 0;
            this.bus.ARVALID <= 0;

            this.bus.AWPROT <= 0;
            this.bus.ARPROT <= 0;

            this.bus.AWADDR <= 0;
            this.bus.AWVALID <= 0;

            this.bus.BREADY <= 0;
            this.bus.RREADY <= 0;

            this.bus.WDATA <= 0;
            this.bus.WVALID <= 0;
            this.bus.WSTRB <= 0;

            this.clock_period = period;
        end
    endfunction

    task write(input logic [31:0] address, input logic [31:0] data);
        // WRITE ADDRESS CHANNEL
        this.bus.AWADDR <= address;
        this.bus.AWVALID <= 1;
        // WRITE DATA CHANNEL
        this.bus.WDATA <= data;
        this.bus.WVALID <= 1;
        this.bus.WSTRB <= 'hF;

        this.bus.BREADY <= 1;
        // WAIT FOR THE WRITE DATA HANDSHAKE
        wait(this.bus.AWREADY);
        wait(!this.bus.AWREADY);
        this.bus.AWVALID <= 0;
        this.bus.WVALID <= 0;
        #1;

        // CHECK THAT THE DATA HANDSHAKE WAS PERFORMED CORRECTLY

        this.bus.AWADDR <= 0;
        this.bus.WDATA <= 0;
        this.bus.WSTRB <= 0;
    endtask

    task  read(input logic [31:0] address, output logic [31:0] data);
        this.bus.ARADDR <= address;
        this.bus.ARVALID <= 1;
        this.bus.RREADY <= 1;
        wait(this.bus.ARREADY);
        #1;
        this.bus.ARVALID <= 0;
        wait(this.bus.RVALID);
        #1;
        data = this.bus.RDATA;
        
        this.bus.RREADY <= 0;
    endtask

endclass

`endif