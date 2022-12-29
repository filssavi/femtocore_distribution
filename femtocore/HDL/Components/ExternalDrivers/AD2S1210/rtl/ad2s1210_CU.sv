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

module ad2s1210_cu (
    input wire clock,
    input wire reset,
    input wire read_angle,
    input wire read_speed,
    axi_stream.master external_spi_transfer,
    input wire [31:0] SPI_data_in,
    output reg [1:0] mode,
    output reg [1:0] resolution,
    output wire sample,
    output reg rdc_reset,
    output reg [4:0] spi_transfer_length,
    axi_stream.master data_out,
    axi_lite.slave axi_in
);

    reg fc_mode;

    reg read_sample, fault_clear_sample;

 
    reg [1:0] internal_mode;

    reg [7:0] AD2S1210_addr[0:14] = '{'h80,'h81,'h82,'h83,'h88,'h89,'h8A,'h8B,'h8C,'h8D,'h8E,'h91,'h92,'hf0,'hff};
    reg [7:0] AD2S1210_values[0:14];

    reg [7:0] sample_read_delay;
    reg [7:0] sample_pulse_length;

    wire configuration_done, start_configuration;
    assign start_configuration = trigger_out & ~trigger_type;

    wire start_fault_clear, fault_clear_done;
    assign start_fault_clear = trigger_out & trigger_type;
    

    assign mode = state==configure_state | fc_mode ? 2'b11 : internal_mode;
    assign sample = read_sample & fault_clear_sample;



    enum logic [1:0] {
        run_state =             2'b00,
        configure_state =      2'b01,
        fault_clear_state =      2'b11
    } state = run_state;



    always_ff @(posedge clock) begin
        case (state)
            run_state: begin
                if(start_configuration)
                    state <= configure_state;
                else if(start_fault_clear)
                    state <= fault_clear_state;
            end
            configure_state:begin
                if(configuration_done)
                    state <= run_state;
            end
            fault_clear_state:begin
                if(fault_clear_done)
                    state <= run_state;
            end
            default: 
                state <= run_state;
        endcase
    end



    reg clear_fault;
    reg trigger_out;
    reg trigger_type;

    reg [7:0] slow_fault_threshold;

    reg [31:0] cu_write_registers [10:0];
    reg [31:0] cu_read_registers [10:0];

    axil_simple_register_cu #(
        .N_READ_REGISTERS(11),
        .N_WRITE_REGISTERS(11),
        .REGISTERS_WIDTH(32),
        .N_TRIGGER_REGISTERS(1),
        .TRIGGER_REGISTERS_IDX('{9}),
        .INITIAL_OUTPUT_VALUES({32'b0,32'b0,32'b0,32'b0,32'b0,32'b0,32'b0,32'b0,32'b0,32'b0,{3'b0,5'd22,20'b0,2'b10,2'b0}}),
        .ADDRESS_MASK('h3f)
    ) CU (
        .clock(clock),
        .reset(reset),
        .input_registers(cu_read_registers),
        .output_registers(cu_write_registers),
        .trigger_out(trigger_out),
        .axil(axi_in)
    );

    assign AD2S1210_values[0:3] = '{4{32'b0}};
    assign AD2S1210_values[4] = cu_write_registers[0];
    assign AD2S1210_values[5] = cu_write_registers[1];
    assign AD2S1210_values[6] = cu_write_registers[2];
    assign AD2S1210_values[7] = cu_write_registers[3];
    assign AD2S1210_values[8] = cu_write_registers[4];
    assign AD2S1210_values[9] = cu_write_registers[5];
    assign AD2S1210_values[10] = cu_write_registers[6];
    assign AD2S1210_values[11] = cu_write_registers[7];
    assign AD2S1210_values[12] = cu_write_registers[8];
    assign AD2S1210_values[13:14] = '{2{32'b0}};

    assign trigger_type = cu_write_registers[9];
    
    assign resolution = cu_write_registers[10][3:2];
    assign rdc_reset = cu_write_registers[10][4];
    assign sample_pulse_length = cu_write_registers[10][15:8];
    assign sample_read_delay = cu_write_registers[10][23:16];
    assign spi_transfer_length = cu_write_registers[10][28:24];

    assign cu_read_registers[0] = AD2S1210_values[4];
    assign cu_read_registers[1] = AD2S1210_values[5];
    assign cu_read_registers[2] = AD2S1210_values[6];
    assign cu_read_registers[3] = AD2S1210_values[7];
    assign cu_read_registers[4] = AD2S1210_values[8];
    assign cu_read_registers[5] = AD2S1210_values[9];
    assign cu_read_registers[6] = AD2S1210_values[10];
    assign cu_read_registers[7] = AD2S1210_values[11];
    assign cu_read_registers[8] = AD2S1210_values[12];
    assign cu_read_registers[9] = 0;
    assign cu_read_registers[10] = {
        3'b0,
        spi_transfer_length,
        sample_read_delay,
        sample_pulse_length,
        3'b0,
        rdc_reset,
        resolution,
        2'b0
    };

    axi_stream read_spi();
    axi_stream cfg_spi();
    axi_stream fc_spi();


    axi_stream_combiner_3 #(
        .INPUT_DATA_WIDTH(32),
        .OUTPUT_DATA_WIDTH(32),
        .MSB_DEST_SUPPORT("FALSE")
    ) spi_stream_combiner (
        .clock(clock),
        .reset(reset),
        .stream_in_1(read_spi),
        .stream_in_2(cfg_spi),
        .stream_in_3(fc_spi),
        .stream_out(external_spi_transfer)
    );



    ad2s1210_reader reader (
        .clock(clock),
        .reset(reset),
        .start(read_angle | read_speed),
        .transfer_type(read_speed),
        .sample_length(sample_pulse_length),
        .sample_delay(sample_read_delay),
        .spi_data_in(SPI_data_in),
        .spi_transfer(read_spi),
        .sample(read_sample),
        .mode(internal_mode),
        .data_out(data_out)
    );


    ad2s1210_configurator configurator (
        .clock(clock),
        .reset(reset),
        .start(start_configuration),
        .config_address(AD2S1210_addr),
        .config_data(AD2S1210_values),
        .spi_transfer(cfg_spi),
        .done(configuration_done)
    );


    ad2s1210_fault_handler fault_handler (
        .clock(clock),
        .reset(reset),
        .start(start_fault_clear),
        .sample_delay(sample_read_delay),
        .sample_length(sample_pulse_length),
        .spi_transfer(fc_spi),
        .mode(fc_mode),
        .sample(fault_clear_sample), 
        .done(fault_clear_done)
    );




endmodule


/**
       {
        "name": "ad2s1210_cu",
        "type": "peripheral",
        "registers":[
            {
                "name": "rdc_los_thres",
                "offset": "0x0",
                "description": "Value of AD2S1210 Loss of signal threshold register",
                "direction": "RW"        
            },
            {
                "name": "rdc_dos_or_thres",
                "offset": "0x4",
                "description": "Value of AD2S1210 Degradation of signal overrange threshold register",
                "direction": "RW"
            },
            {
                "name": "rdc_dos_mism_thres",
                "offset": "0x8",
                "description": "Value of AD2S1210 Degradation of signal mismatch threshold register",
                "direction": "RW"
            },
            {
                "name": "rdc_dos_reset_minmax",
                "offset": "0xc",
                "description": "Value of AD2S1210 Degradation of signal minimum and maximum reset threshold register",
                "direction": "RW"
            },
            {
                "name": "rdc_lot_high",
                "offset": "0x10",
                "description": "Value of AD2S1210 Loss of tracking high threshold register",
                "direction": "RW"
            },
            {
                "name": "rdc_lot_low",
                "offset": "0x14",
                "description": "Value of AD2S1210 Loss of tracking low threshold register",
                "direction": "RW"
            },
            {
                "name": "rdc_exc_freq",
                "offset": "0x18",
                "description": "Value of AD2S1210 excitation frequency register",
                "direction": "RW"
            },
            {
                "name": "rdc_control",
                "offset": "0x1c",
                "description": "Value of AD2S1210 control register",
                "direction": "RW"
            },
            {
                "name": "rdc_reset",
                "offset": "0x20",
                "description": "Value of AD2S1210 soft reset register",
                "direction": "RW"
            },
            {
                "name": "trigger",
                "offset": "0x24",
                "description": "Writing 0 to this register will configure the RDC while writing 1 will clear pending",
                "direction": "W"
            },
            {
                "name": "control",
                "offset": "0x28",
                "description": "AD2S1210 Driver control register",
                "direction": "RW",
                "fields":[
                    {
                        "name":"resolution",
                        "description": "Resolver to digital resolution setting",
                        "start_position": 2,
                        "length": 2
                    },
                    {
                        "name":"rdc_reset",
                        "description": "Value of the AD2S1210 RESET pin",
                        "start_position": 4,
                        "length": 1
                    },
                    {
                        "name":"sample_pulse_length",
                        "description": "length of the sample pulse",
                        "start_position": 8,
                        "length": 8
                    },
                    {
                        "name":"sample_read_delay",
                        "description": "delay between the sample pulse and the data readback phase",
                        "start_position": 16,
                        "length": 8
                    },
                    {
                        "name":"spi_transfer_length",
                        "description": "lenght of the SPI transfer",
                        "start_position": 24,
                        "length": 5
                    }
                ]     
            }
        ]
    }  
    **/