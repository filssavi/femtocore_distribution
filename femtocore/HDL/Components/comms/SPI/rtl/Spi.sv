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

module SPI #(
    SS_POLARITY_DEFAULT=0,
    N_CHANNELS=3,
    OUTPUT_WIDTH=32
)(
    input logic clock,
    input logic reset,
    input logic [4:0] external_transfer_length,
    output logic data_valid,
    output logic [OUTPUT_WIDTH-1:0] data_out [N_CHANNELS-1:0],
    input logic [N_CHANNELS-1:0] MISO,
    output logic SCLK,
    output logic [N_CHANNELS-1:0] MOSI,
    output logic SS,
    axi_lite.slave axi_in,
    axi_stream.slave external_spi_transfer
);


    logic clockgen_out, spi_mode,register_enable,enable_clockgen, ss_polarity, ss_deassert_delay_enable, transfer_length_choice;
    logic generated_sclk;
    logic register_load,int_transfer_start,spi_direction,transfer_start, latching_edge;
    logic internal_start;
    logic [2:0] divider_setting;
    logic [4:0] chosen_spi_transfer_length;
    logic [3:0] bus_transfer_length;
    logic [31:0] parallel_reg_in [N_CHANNELS-1:0];
    logic [OUTPUT_WIDTH-1:0] parallel_reg_out [N_CHANNELS-1:0];
    logic [OUTPUT_WIDTH-1:0] cu_in [N_CHANNELS-1:0];
    logic [31:0] cu_out [N_CHANNELS-1:0];
    logic [N_CHANNELS-1:0] parallel_reg_valid;
    logic [31:0] spi_delay;
    logic [31:0] start_generator_period;
    wire master_ss, sync, clock_cont;
    wire clock_polarity, transfer_done, ss_blanking,start_generator_enable;

    assign chosen_spi_transfer_length = transfer_length_choice ? external_transfer_length : bus_transfer_length;

    assign SCLK = generated_sclk; 

    assign master_ss = register_enable & ~ss_blanking;
    assign transfer_start = int_transfer_start | internal_start;


    assign data_out = cu_in;
    assign data_valid = transfer_done;
    
    enable_generator_core ENG(
        .clock(clock),
        .reset(reset),
        .gen_enable_in(start_generator_enable),
        .period(start_generator_period),
        .enable_out(internal_start)
    );

    ClockGen CKG (
        .clockIn(clock),
        .reset(reset),
        .sync(sync),
        .polarity(clock_polarity),
        .enable(enable_clockgen),
        .dividerSetting(divider_setting),
        .timebaseOut(clock_cont)
    );
    
    
    assign clockgen_out = clock_cont & enable_clockgen;

    always@(posedge clock)begin
        if(~reset) begin
            generated_sclk <= 0;
        end else begin
            generated_sclk <= clockgen_out;
            if(ss_polarity) begin
                SS <= ~master_ss;
            end else begin
                SS <= master_ss;
            end
        end
    end
    
    generate
        genvar i;
        for (i = 0; i < N_CHANNELS; i=i+1) begin
            SpiRegister #(
                .N_CHANNELS(N_CHANNELS)
            ) SHR(
                .clock(clock),
                .shift_clock(generated_sclk),
                .reset(reset),
                .enable(register_enable),
                .latching_edge(latching_edge),
                .spi_transfer_length(chosen_spi_transfer_length),
                .serial_in(MISO[i]),
                .parallel_in(parallel_reg_in[i]),
                .register_direction(spi_direction),
                .register_load(register_load),
                .parallel_out(parallel_reg_out[i]),
                .parallel_out_valid(parallel_reg_valid[i]),
                .serial_out(MOSI[i])
            );
        end
    endgenerate
    

    TransferEngine #(
        .N_CHANNELS(N_CHANNELS),
        .OUTPUT_WIDTH(OUTPUT_WIDTH)
    ) STE(
        .clock(clock),
        .reset(reset),
        .spi_delay(spi_delay),
        .sync(sync),
        .divider_setting(divider_setting),
        .spi_transfer_length(chosen_spi_transfer_length),
        .spi_start_transfer(transfer_start),
        .ss_deassert_delay_enable(ss_deassert_delay_enable),
        .cu_data_out(cu_out),
        .reg_data_out(parallel_reg_out),
        .reg_data_out_valid(parallel_reg_valid[0]),
        .cu_data_in(cu_in),
        .reg_data_in(parallel_reg_in),
        .register_load(register_load),
        .enable_clockgen(enable_clockgen),
        .register_enable(register_enable),
        .transfer_done(transfer_done),
        .ss_blanking(ss_blanking)
    );

    SpiControlUnit #(
        .N_CHANNELS(N_CHANNELS),
        .SS_POLARITY_DEFAULT(SS_POLARITY_DEFAULT),
        .OUTPUT_WIDTH(OUTPUT_WIDTH)
    ) SCU(
        .clock(clock),
        .reset(reset),
        .spi_data_in(cu_in),
        .transfer_done(transfer_done),
        .spi_delay(spi_delay),
        .spi_transfer_length(bus_transfer_length),
        .spi_data_out(cu_out),
        .divider_setting(divider_setting),
        .spi_mode(spi_mode),
        .spi_start_transfer(int_transfer_start),
        .spi_direction(spi_direction),
        .ss_polarity(ss_polarity),
        .clock_polarity(clock_polarity),
        .ss_deassert_delay_enable(ss_deassert_delay_enable),
        .latching_edge(latching_edge),
        .period(start_generator_period),
        .start_generator_enable(start_generator_enable),
        .transfer_length_choice(transfer_length_choice),
        .axi_in(axi_in),
        .external_spi_transfer(external_spi_transfer)
    );


endmodule


 /**
       {
        "name": "SPI",
        "type": "peripheral",
        "registers":[
            {
                "name": "control",
                "offset": "0x0",
                "description": "SPI peripheral control register",
                "direction": "RW",
                "fields":[
                    {
                        "name":"spi_mode",
                        "description": "Deprecated",
                        "start_position": 0,
                        "length": 1
                    },
                    {
                        "name":"divider_setting",
                        "description": "SCLK generator division setting",
                        "start_position": 1,
                        "length": 3
                    },
                    {
                        "name":"spi_transfer_length",
                        "description": "length of the SPI transfer",
                        "start_position": 4,
                        "length": 4
                    },
                    {
                        "name":"spi_direction",
                        "description": "Direction of travel fo the data (MSB or LSB first)",
                        "start_position": 9,
                        "length": 1
                    },
                    {
                        "name":"start_generator_enable",
                        "description": "Enable the internal trigger generator for periodic transfers",
                        "start_position": 12,
                        "length": 1
                    },
                    {
                        "name":"ss_polarity",
                        "description": "Polarity of the Chip Select signal",
                        "start_position": 13,
                        "length": 1
                    },
                    {
                        "name":"ss_deassert_delay_enable",
                        "description": "Enable the addition of delay between CS deassertion and SPI transfer",
                        "start_position": 14,
                        "length": 1
                    },
                    {
                        "name":"transfer_length_choice",
                        "description": "Toggle between internal and external transfer length input",
                        "start_position": 15,
                        "length": 1
                    },
                    {
                        "name":"latching_edge",
                        "description": "Select edge with which the data is transfered",
                        "start_position": 16,
                        "length": 1
                    },
                    {
                        "name":"clock_polarity",
                        "description": "Polarity of the SCLK signal (active high or active low)",
                        "start_position": 17,
                        "length": 1
                    }
                ]
            },
            {
                "name": "ss_delay",
                "offset": "0x4",
                "description": "Delay between the Chip Select signal and the spi transfer",
                "direction": "RW"
            },
            {
                "name": "period",
                "offset": "0x8",
                "description": "Period of the periodic transfer enable generator",
                "direction": "RW"
            },
            {
                "name": "trigger",
                "offset": "0xC",
                "description": "Writing 1 to this register triggers a transfer",
                "direction": "RW"
            },
            {
                "name": "data_1",
                "offset": "0x10",
                "description": "SPI register for the first channel",
                "direction": "RW"
            }
        ]
    }  
    **/
