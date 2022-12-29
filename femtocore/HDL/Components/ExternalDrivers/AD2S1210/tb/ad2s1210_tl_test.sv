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


module ad2s1210_tl_test (
    input wire clock,
    input wire reset,
    input wire R_SDO_RES,
    output wire R_SDI_RES,
    output wire R_WR,
    output wire R_SCK_RES,
    output wire R_A0,
    output wire R_A1,
    output wire R_RE0,
    output wire R_RE1,
    output wire R_SAMPLE,
    output wire R_RESET,
    axi_stream.master resolver_out,
    axi_lite.slave axi_in
);
    
    
    assign R_RESET = 1;
    
    wire SS;

    assign R_WR = SS;
    wire start_read;

    parameter UUT_BASE_ADDRESS = 'h43c00000;
    parameter ENGEN_BASE_ADDRESS = 'h43c00100;

    axi_lite #(.INTERFACE_NAME("UUT A")) uut_axi();
    axi_lite #(.INTERFACE_NAME("ENABLE GEN")) en_gen_axi();

    axil_crossbar_interface #(
        .DATA_WIDTH(32),
        .ADDR_WIDTH(32),
        .NM(1),
        .NS(2),
        .SLAVE_ADDR('{UUT_BASE_ADDRESS, ENGEN_BASE_ADDRESS}),
        .SLAVE_MASK('{2{32'hf00}})
    ) axi_xbar (
        .clock(clock),
        .reset(reset),
        .slaves('{axi_in}),
        .masters('{uut_axi, en_gen_axi})
    );


    ad2s1210 #(
        .BASE_ADDRESS(UUT_BASE_ADDRESS)
    ) test(
        .clock(clock),
        .reset(reset),
        .read_angle(read_angle),
        .read_speed(read_speed),
        .MOSI(R_SDI_RES),
        .MISO(R_SDO_RES),
        .SS(SS),
        .SCLK(R_SCK_RES),
        .R_A({R_A1, R_A0}),
        .R_RES({R_RE1, R_RE0}),
        .R_SAMPLE(R_SAMPLE),
        .data_out(resolver_out),
        .axi_in(uut_axi)
    );

    enable_generator_2 #(
        .BASE_ADDRESS(ENGEN_BASE_ADDRESS)
    ) tb_gen(
        .clock(clock),
        .reset(reset),
        .gen_enable_in(0),
        .enable_out_1(read_angle),
        .enable_out_2(read_speed),
        .axil(en_gen_axi)
    );

endmodule