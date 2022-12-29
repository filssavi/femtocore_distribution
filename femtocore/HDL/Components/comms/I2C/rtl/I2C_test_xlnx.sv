// Copyright (C) : 3/16/2018, 11:06:33 AM Filippo Savi - All Rights Reserved
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

module i2c_test_tl (
	inout wire i2c_scl,
	inout wire i2c_sda
);
    wire sda_in, sda_out;
    wire scl_in, scl_out;

    assign i2c_sda = (sda_out == 1'b0) ? 1'b0 : 1'bz;
    assign sda_in = i2c_sda;

    assign i2c_scl = (scl_out == 1'b0) ? 1'b0 : 1'bz;
    assign scl_in = i2c_scl;

    wire internal_rst, fast_clock;

    axi_lite axi();

    Zynq_wrapper PS(
    .axi_out(axi),
    .Reset(internal_rst),
    .logic_clock(fast_clock)
    );

    
    I2c UUT(
        .clock(fast_clock),
        .reset(internal_rst),
        .axi_in(axi),
        .i2c_scl_in(scl_in),
        .i2c_scl_out(scl_out),
        .i2c_sda_in(sda_in),
        .i2c_sda_out(sda_out)
    );




endmodule