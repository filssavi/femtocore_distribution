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

module enable_generator_3 #(
    COUNTER_WIDTH = 32
)(
    input wire        clock,
    input wire        reset,
    input wire        ext_timebase,
    input wire        gen_enable_in,
    output wire enable_out_1,
    output wire enable_out_2,
    output wire enable_out_3,
    axi_lite.slave axil
);

    reg [COUNTER_WIDTH-1:0] period;
    wire [COUNTER_WIDTH-1:0] count;

    reg bus_enable;
    
    reg [COUNTER_WIDTH-1:0] enable_threshold_1;
    reg [COUNTER_WIDTH-1:0] enable_threshold_2;
    reg [COUNTER_WIDTH-1:0] enable_threshold_3;



    reg [31:0] cu_write_registers [4:0];
    reg [31:0] cu_read_registers [4:0];

    localparam ADDITIONAL_BITS = 32 - COUNTER_WIDTH;

    axil_simple_register_cu #(
        .N_READ_REGISTERS(5),
        .N_WRITE_REGISTERS(5),
        .REGISTERS_WIDTH(32),
        .ADDRESS_MASK('hff)
    ) CU (
        .clock(clock),
        .reset(reset),
        .input_registers(cu_read_registers),
        .output_registers(cu_write_registers),
        .axil(axil)
    );



    assign bus_enable = cu_write_registers[0][0];
    assign period = cu_write_registers[1][COUNTER_WIDTH-1:0];
    assign enable_threshold_1 = cu_write_registers[2][COUNTER_WIDTH-1:0];
    assign enable_threshold_2 = cu_write_registers[3][COUNTER_WIDTH-1:0];
    assign enable_threshold_3 = cu_write_registers[4][COUNTER_WIDTH-1:0];

    assign cu_read_registers[0][31:0] = {31'b0, {bus_enable}};
    assign cu_read_registers[1][31:0] = {{ADDITIONAL_BITS{1'b0}},period};
    assign cu_read_registers[2][31:0] = {{ADDITIONAL_BITS{1'b0}},enable_threshold_1};
    assign cu_read_registers[3][31:0] = {{ADDITIONAL_BITS{1'b0}},enable_threshold_2};
    assign cu_read_registers[4][31:0] = {{ADDITIONAL_BITS{1'b0}},enable_threshold_3};

    enable_generator_counter counter(
        .clock(clock),
        .reset(reset),
        .external_timebase(ext_timebase),
        .gen_enable_in(bus_enable | gen_enable_in),
        .period(period),
        .counter_out(count)
    );
    
    enable_comparator #(
        .COUNTER_WIDTH(COUNTER_WIDTH)
    ) comparator_1(
        .clock(clock),
        .reset(reset),
        .enable_treshold(enable_threshold_1),
        .count(count),
        .enable_out(enable_out_1)
    );
    
    enable_comparator #(
        .COUNTER_WIDTH(COUNTER_WIDTH)
    ) comparator_2(
        .clock(clock),
        .reset(reset),
        .enable_treshold(enable_threshold_2),
        .count(count),
        .enable_out(enable_out_2)
    );
    
    enable_comparator #(
        .COUNTER_WIDTH(COUNTER_WIDTH)
    ) comparator_3(
        .clock(clock),
        .reset(reset),
        .enable_treshold(enable_threshold_3),
        .count(count),
        .enable_out(enable_out_3)
    );

endmodule

/**
       {
        "name": "enable_generator_3",
        "type": "peripheral",
        "registers":[
            {
                "name": "enable",
                "offset": "0x0",
                "description": "Writing 1 to this register enables the generator",
                "direction": "RW"
            },
            {
                "name": "period",
                "offset": "0x4",
                "description": "Period of the enable pulses in clock cycles",
                "direction": "RW"
            },
            {
                "name": "treshold_1",
                "offset": "0x8",
                "description": "Value of the counter at which the enable pulse for output 1 is produced",
                "direction": "RW"
            },
            {
                "name": "treshold_2",
                "offset": "0xC",
                "description": "Value of the counter at which the enable pulse for output 2 is produced",
                "direction": "RW"
            },
            {
                "name": "treshold_3",
                "offset": "0x10",
                "description": "Value of the counter at which the enable pulse for output 3 is produced",
                "direction": "RW"
            }
        ]
    }  
    **/