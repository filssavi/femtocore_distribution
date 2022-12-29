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

module enable_generator #(
    COUNTER_WIDTH = 32,
    EXTERNAL_TIMEBASE_ENABLE = 0
)(
    input wire        clock,
    input wire        ext_timebase,
    input wire        reset,
    input wire        gen_enable_in,
    output wire        enable_out,
    axi_lite.slave axil
);

    reg [COUNTER_WIDTH-1:0] period;
    wire [COUNTER_WIDTH-1:0] count;
    reg bus_enable;
    reg [COUNTER_WIDTH-1:0] enable_threshold_1;



    logic [31:0] cu_write_registers [2:0];
    logic [31:0] cu_read_registers [2:0];

    localparam ADDITIONAL_BITS = 32 - COUNTER_WIDTH;

    axil_simple_register_cu #(
        .N_READ_REGISTERS(3),
        .N_WRITE_REGISTERS(3),
        .REGISTERS_WIDTH(32),
        .ADDRESS_MASK('hf)
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

    assign cu_read_registers[0][31:0] = {31'b0, {bus_enable}};
    assign cu_read_registers[1][31:0] = {{ADDITIONAL_BITS{1'b0}},period};
    assign cu_read_registers[2][31:0] = {{ADDITIONAL_BITS{1'b0}},enable_threshold_1};
    
    wire comparator_out;
    reg synchronized_tb,prev_comp_out;
    
    generate
        if(EXTERNAL_TIMEBASE_ENABLE==1)begin
            assign enable_out = synchronized_tb;
        end else begin
            assign enable_out = comparator_out;
        end
    endgenerate


    always_ff@(posedge clock) begin
        if(period == 0 || period == 1) begin
            synchronized_tb <= ext_timebase;
        end else begin
            prev_comp_out <= comparator_out;
            if(comparator_out & ~prev_comp_out)begin
                synchronized_tb<= 1;
            end else begin
                synchronized_tb<= 0;
            end
        end
    end
    
    enable_generator_counter #(
        .COUNTER_WIDTH(COUNTER_WIDTH),
        .EXTERNAL_TIMEBASE_ENABLE(EXTERNAL_TIMEBASE_ENABLE)
    ) counter(
        .clock(clock),
        .reset(reset),
        .external_timebase(ext_timebase),
        .gen_enable_in(bus_enable | gen_enable_in),
        .period(period),
        .counter_out(count)
    );

    enable_comparator #(
        .COUNTER_WIDTH(COUNTER_WIDTH),
        .CLOCK_MODE("FALSE")
    ) comparator_1(
        .clock(clock),
        .reset(reset),
        .enable_treshold(enable_threshold_1),
        .count(count),
        .enable_out(comparator_out)
    );

endmodule
 
    /**
       {
        "name": "enable_generator",
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
                "name": "treshold",
                "offset": "0x8",
                "description": "value of the counter at which the enable pulse is produced",
                "direction": "RW"
                
            }
        ]
    }  
    **/