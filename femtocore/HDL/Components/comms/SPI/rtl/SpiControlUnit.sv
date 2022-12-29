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

module SpiControlUnit #(
    SS_POLARITY_DEFAULT = 0,
    N_CHANNELS=3,
    OUTPUT_WIDTH=32
) (
    input logic clock,
    input logic reset,
    input logic [OUTPUT_WIDTH-1:0] spi_data_in[N_CHANNELS-1:0],
    input logic transfer_done,
    output logic [3:0] spi_transfer_length,
    output logic [31:0] spi_delay,
    output logic [31:0] spi_data_out [N_CHANNELS-1:0],
    output logic [2:0] divider_setting,
    output logic spi_mode,
    output logic spi_start_transfer,
    output logic spi_direction,
    output logic [31:0] period,
    output logic start_generator_enable,
    output logic ss_polarity,
    output logic clock_polarity,
    output logic ss_deassert_delay_enable,
    output logic latching_edge,
    output logic transfer_length_choice,
    axi_lite.slave axi_in,
    axi_stream.slave external_spi_transfer
);

    localparam  N_REGISTERS = 4 + N_CHANNELS;

    localparam [31:0] TRIGGER_REGISTERS_IDX [0:0] = '{3};

    localparam [31:0] FIXED_REGISTER_VALUES [3:0]= '{
        0,
        0,
        1,
        {SS_POLARITY_DEFAULT,3'b0,SS_POLARITY_DEFAULT,5'b0,4'hE,4'b0}
    };

    localparam [31:0] VARIABLE_INITIAL_VALUES [N_CHANNELS-1:0] = '{N_CHANNELS{1'b0}};
 
    parameter [31:0] INITIAL_REGISTER_VALUES [N_REGISTERS-1:0] = {VARIABLE_INITIAL_VALUES, FIXED_REGISTER_VALUES};

    assign spi_start_transfer = bus_start_transfer | axis_start_transfer;

    reg [31:0] cu_write_registers [N_REGISTERS-1:0];
    reg [31:0] cu_read_registers [N_REGISTERS-1:0];
    reg trigger_transfer;

    reg bus_start_transfer, axis_start_transfer;

    
    reg [31:0] axis_spi_data;
    axil_simple_register_cu #(
        .N_READ_REGISTERS(N_REGISTERS),
        .N_WRITE_REGISTERS(N_REGISTERS),
        .REGISTERS_WIDTH(32),
        .N_TRIGGER_REGISTERS(1),
        .INITIAL_OUTPUT_VALUES(INITIAL_REGISTER_VALUES),
        .TRIGGER_REGISTERS_IDX(TRIGGER_REGISTERS_IDX),
        .ADDRESS_MASK('h3f)
    ) axi_if(
        .clock(clock),
        .reset(reset),
        .input_registers(cu_read_registers),
        .output_registers(cu_write_registers),
        .trigger_out(trigger_transfer),
        .axil(axi_in)
    );

    assign spi_mode = cu_write_registers[0][0];
    assign divider_setting = cu_write_registers[0][3:1];
    assign spi_transfer_length = cu_write_registers[0][7:4];
    assign spi_direction = cu_write_registers[0][9];
    assign start_generator_enable = cu_write_registers[0][12];
    assign ss_polarity = cu_write_registers[0][13];
    assign ss_deassert_delay_enable = cu_write_registers[0][14];
    assign transfer_length_choice = cu_write_registers[0][15];
    assign latching_edge = cu_write_registers[0][16];
    assign clock_polarity = cu_write_registers[0][17];

    assign spi_delay = cu_write_registers[1];
    assign period = cu_write_registers[2];
    // a write to cu_write_registers[3] is used to trigger a spi transfer

    assign spi_data_out[0] = axis_start_transfer ? axis_spi_data : cu_write_registers[4];

    generate
        for(genvar i = 1; i < N_CHANNELS;  i = i+1)begin
            assign spi_data_out[i] = cu_write_registers[i+4];   
        end
    endgenerate

    assign cu_read_registers[0]  = {
        14'b0, clock_polarity, latching_edge,
        transfer_length_choice, ss_deassert_delay_enable, ss_polarity,
        start_generator_enable, 2'b0, spi_direction, 1'b0,
        spi_transfer_length, divider_setting, spi_mode
    };

    assign cu_read_registers[1] = spi_delay;
    assign cu_read_registers[2] = period;
    assign cu_read_registers[3] = unit_busy;

    generate
        for(genvar i = 0; i < N_CHANNELS;  i = i+1)begin
            assign cu_read_registers[i+4] = spi_data_in[i];   
        end
    endgenerate

    assign bus_start_transfer = trigger_transfer;

    reg unit_busy = 0;

    
    always_ff @(posedge clock) begin
        if(!reset)begin
            unit_busy <= 0;
            external_spi_transfer.ready <= 1;
        end else begin
            axis_start_transfer <= 0;
            if(external_spi_transfer.valid) begin
                axis_spi_data  <= external_spi_transfer.data[31:0];
                axis_start_transfer <=1;
                unit_busy <= 1;
                external_spi_transfer.ready <= 0;
            end

            if(spi_start_transfer) begin
                unit_busy <= 1;
                external_spi_transfer.ready <= 0;
            end else if(transfer_done) begin
                unit_busy <= 0;
                external_spi_transfer.ready <= 1;
            end
        end
        
    end


endmodule