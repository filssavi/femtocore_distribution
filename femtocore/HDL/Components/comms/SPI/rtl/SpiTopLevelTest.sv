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
`include "axis_BFM.svh"

module SpiTopLevelTest (
    input logic MISO,
    inout logic SCLK,
    output logic MOSI,
    output logic SS
);

    wire clk, rst;
    axi_lite axi();

    SPI IFACE(
        .clock(clk),
        .reset(rst),
        .MISO(MISO),
        .SCLK(SCLK),
        .MOSI(MOSI),
        .SS(SS),
        .axi_in(axi)
    );

    Zynq_wrapper Zynq(
        .axi_out(axi),
        .logic_clock(clk),
        .Reset(rst)
    );
        


endmodule