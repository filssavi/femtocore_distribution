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

module ChainControlUnit #(
    parameter BASE_ADDRESS = 0,
    N_CHANNELS = 3,
    COUNTER_WIDTH=16
)(
    input wire clock,
    input wire reset,
    input wire counter_running,
    output reg [15:0] timebase_shift,
    output reg [2:0] counter_mode,
    output reg [COUNTER_WIDTH-1:0] counter_start_data,
    output reg [COUNTER_WIDTH-1:0] counter_stop_data,
    output reg [COUNTER_WIDTH-1:0] comparator_tresholds [N_CHANNELS*2-1:0],
    output reg [1:0] output_enable [N_CHANNELS-1:0],
    output reg [15:0] deadtime [N_CHANNELS-1:0],
    output reg deadtime_enable [N_CHANNELS-1:0],
    axi_lite.slave axi_in
);

    reg [31:0] cu_write_registers [14:0];
    reg [31:0] cu_read_registers [14:0];
    
    localparam [31:0] THRESH_LOW_IV [N_CHANNELS-1:0] = '{N_CHANNELS{32'b0}};
    localparam [31:0] THRESH_HIGH_IV [N_CHANNELS-1:0] = '{N_CHANNELS{32'hffffffff}};
    localparam [31:0] OTHER_IV [8:0] = '{9{32'b0}};

    localparam [31:0] INITIAL_REGISTER_VALUES [14:0] = {OTHER_IV, THRESH_HIGH_IV, THRESH_LOW_IV};



    axil_simple_register_cu #(
        .N_READ_REGISTERS(15),
        .N_WRITE_REGISTERS(15),
        .REGISTERS_WIDTH(32),
        .ADDRESS_MASK('hff),
        .INITIAL_OUTPUT_VALUES(INITIAL_REGISTER_VALUES)
    ) CU (
        .clock(clock),
        .reset(reset),
        .input_registers(cu_read_registers),
        .output_registers(cu_write_registers),
        .axil(axi_in)
    );


    always_latch begin
        comparator_tresholds[0] <= cu_write_registers[0];
        comparator_tresholds[1] <= cu_write_registers[1];
        comparator_tresholds[2] <= cu_write_registers[2];
        comparator_tresholds[3] <= cu_write_registers[3];
        comparator_tresholds[4] <= cu_write_registers[4];
        comparator_tresholds[5] <= cu_write_registers[5];
        output_enable[0] <= cu_write_registers[12][1:0];
        output_enable[1] <= cu_write_registers[12][3:2];
        output_enable[2] <= cu_write_registers[12][5:4];
        deadtime_enable[0] <= cu_write_registers[13][0];
        deadtime_enable[1] <= cu_write_registers[13][1];
        deadtime_enable[2] <= cu_write_registers[13][2];
    end 

    always_ff @(posedge clock) begin
        if(!reset)begin
            for(integer i=0; i<N_CHANNELS; i=i+1) begin 
                deadtime[i] <= 0;
            end
            counter_mode <= 0;
            counter_start_data <= 0;
            counter_stop_data <= 0;
            timebase_shift <= 0;
        end else begin
            if(~counter_running) begin
                deadtime[0] <= cu_write_registers[6];
                deadtime[1] <= cu_write_registers[7];
                deadtime[2] <= cu_write_registers[8];
                counter_start_data <= cu_write_registers[9];
                counter_stop_data <= cu_write_registers[10];
                timebase_shift <= cu_write_registers[11];
                counter_mode <= cu_write_registers[14][2:0];
            end
    
        end
       
    end

    assign cu_read_registers = cu_write_registers;


endmodule


    /**
       {
        "name": "ChainControlUnit",
        "type": "peripheral",
        "registers":[
            {
                "name": "tresh_AL",
                "offset": "0x4",
                "description": "Comparator 0 treshold low",
                "direction": "RW"
            },
            {
                "name": "tresh_Bl",
                "offset": "0x8",
                "description": "Comparator B treshold low",
                "direction": "RW"
            },
            {
                "name": "tresh_CL",
                "offset": "0xC",
                "description": "Comparator C treshold low",
                "direction": "RW"
            },
            {
                "name": "tresh_AH",
                "offset": "0x10",
                "description": "Comparator A treshold high",
                "direction": "RW"
            },
            {
                "name": "tresh_BH",
                "offset": "0x14",
                "description": "Comparator B treshold high",
                "direction": "RW"
            },
            {
                "name": "tresh_CH",
                "offset": "0x18",
                "description": "Comparator C treshold high",
                "direction": "RW"
            },
            {
                "name": "deadtime_A",
                "offset": "0x1c",
                "description": "Length of deadtime automatically inserted in pair A (if enabled)",
                "direction": "RW"
            },
            {
                "name": "deadtime_B",
                "offset": "0x20",
                "description": "Length of deadtime automatically inserted in pair B (if enabled)",
                "direction": "RW"
            },
            {
                "name": "deadtime_C",
                "offset": "0x24",
                "description": "Length of deadtime automatically inserted in pair C (if enabled)",
                "direction": "RW"
            },
            {
                "name": "counter_start",
                "offset": "0x28",
                "description": "Start Value for the PWM generator",
                "direction": "RW"
            },
            {
                "name": "counter_stop",
                "offset": "0x2c",
                "description": "Stop Value for the PWM generator counter",
                "direction": "RW"
            },
            {
                "name": "tb_shift",
                "offset": "0x30",
                "description": "Delay to be applied to the counter enable signal (to apply shift between the counters)",
                "direction": "RW"
            },
            {
                "name": "out_en",
                "offset": "0x34",
                "description": "Output enable register",
                "direction": "RW",
                "fields":[
                    {
                        "name":"out_a",
                        "description": "enable output pair A of chain 0",
                        "start_position": 0,
                        "length": 2
                    },
                    {
                        "name":"out_b",
                        "description": "enable output pair B of chain 0",
                        "start_position": 2,
                        "length": 2
                    },
                    {
                        "name":"out_c",
                        "description": "enable output pair C of chain 0",
                        "start_position": 4,
                        "length": 2
                    }
                ]
            },
            {
                "name": "dt_en",
                "offset": "0x38",
                "description": "Deadtime insertion enable register",
                "direction": "RW",
                "fields":[
                    {
                        "name":"pair_a",
                        "description": "Enable deadtime insertion pair A of chain 0",
                        "start_position": 0,
                        "length": 1
                    },
                    {
                        "name":"pair_b",
                        "description": "Enable deadtime insertion pair B of chain 0",
                        "start_position": 1,
                        "length": 1
                    },
                    {
                        "name":"pair_c",
                        "description": "Enable deadtime insertion pair C of chain 0",
                        "start_position": 2,
                        "length": 1
                    }
                ]
            },
            {
                "name": "ctrl",
                "offset": "0x3C",
                "description": "Chain 0 control register",
                "direction": "RW",
                "fields":[
                    {
                        "name":"mode",
                        "description": "Chain 0 counter mode",
                        "start_position": 0,
                        "length": 3
                    }
                ]
            }
        ]
       }  
    **/
