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
`timescale 10 ns / 1 ns
`include "interfaces.svh"

module axil_simple_register_vip(
    input wire clock,
    input wire reset,
    axi_lite.master axil
);

    VIP VIP_i(
        .AXI_araddr(axil.ARADDR),
        .AXI_arready(axil.ARREADY),
        .AXI_arvalid(axil.ARVALID),
        .AXI_awaddr(axil.AWADDR),
        .AXI_awready(axil.AWREADY),
        .AXI_awvalid(axil.AWVALID),
        .AXI_bready(axil.BREADY),
        .AXI_bresp(axil.BRESP),
        .AXI_bvalid(axil.BVALID),
        .AXI_rdata(axil.RDATA),
        .AXI_rready(axil.RREADY),
        .AXI_rresp(axil.RRESP),
        .AXI_rvalid(axil.RVALID),
        .AXI_wdata(axil.WDATA),
        .AXI_wready(axil.WREADY),
        .AXI_wstrb(axil.WSTRB),
        .AXI_wvalid(axil.WVALID),
        .clock(clock),
        .reset(reset)
    );

endmodule