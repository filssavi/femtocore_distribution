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

module ad2s1210 #(parameter BASE_ADDRESS = 32'h43c00000)(
    input wire clock,
    input wire reset,
    input wire read_angle,
    input wire read_speed,
    output logic MOSI,
    input logic MISO,
    inout logic SS,
    inout logic SCLK,
    output reg R_RESET,
    output reg R_SAMPLE,
    output reg [1:0] R_A,
    output reg [1:0] R_RES,
    axi_stream.master data_out,
    axi_lite.slave axi_in
);
    

    localparam CONTROLLER_ADDRESS = BASE_ADDRESS;
    localparam SPI_ADDRESS = BASE_ADDRESS+'h40;


    axi_lite #(.INTERFACE_NAME("CONTROLLER")) controller_axi();
    axi_lite #(.INTERFACE_NAME("SPI")) spi_axi();

    axil_crossbar_interface #(
        .DATA_WIDTH(32),
        .ADDR_WIDTH(32),
        .NM(1),
        .NS(2),
        .SLAVE_ADDR('{CONTROLLER_ADDRESS, SPI_ADDRESS}),
        .SLAVE_MASK('{2{32'h040}})
    ) axi_xbar (
        .clock(clock),
        .reset(reset),
        .slaves('{axi_in}),
        .masters('{controller_axi, spi_axi})
    );


    wire [4:0] spi_transfer_length;

    axi_stream spi_transfer();

    ad2s1210_cu CU (
        .clock(clock),
        .reset(reset),
        .read_angle(read_angle),
        .read_speed(read_speed),
        .external_spi_transfer(spi_transfer),
        .SPI_data_in(unpacked_spi_data[0]),
        .spi_transfer_length(spi_transfer_length),
        .mode(R_A),
        .resolution(R_RES),
        .sample(R_SAMPLE),
        .rdc_reset(R_RESET),
        .data_out(data_out),
        .axi_in(controller_axi)
    );   
    
    wire data_valid;
    wire [31:0] unpacked_spi_data [0:0];
    
    SPI #(
        .SS_POLARITY_DEFAULT(1),
        .N_CHANNELS(1)
    ) ext_interface(
        .clock(clock),
        .reset(reset),
        .external_transfer_length(spi_transfer_length),
        .MISO(MISO),
        .SCLK(SCLK),
        .MOSI(MOSI),
        .SS(SS),
        .axi_in(spi_axi),
        .external_spi_transfer(spi_transfer),
        .data_valid(data_valid),
        .data_out(unpacked_spi_data)
    );

endmodule

    /**
        {
            "name": "ad2s1210",
            "type": "module_hierarchy",
            "children": [
                {
                    "type": "ad2s1210_cu",
                    "instance": "CU",
                    "offset": "0",
                    "children":[]
                },
                {
                    "type": "SPI",
                    "instance": "ext_interface",
                    "offset": "0x40",
                    "children":[]
                }
            ]    
        }
    **/
