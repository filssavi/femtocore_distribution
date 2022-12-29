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

module AdcProcessingControlUnit #(
    STICKY_FAULT = 0,
    DATA_PATH_WIDTH = 16
)(
    input wire clock,
    input wire reset,
    input wire data_in_valid,
    axi_lite.slave axi_in,
    // COMPARATORS
    output reg signed [DATA_PATH_WIDTH-1:0] comparator_thresholds [0:7],
    output reg [1:0]  latch_mode,
    output reg [1:0]  clear_latch,
    input wire [1:0]  trip_high,
    input wire [1:0]  trip_low,
    // CALIBRATION
    output reg signed [DATA_PATH_WIDTH-1:0] calibrator_coefficients [2:0],
    output reg        gain_enable,
    output reg        fault,
    output reg [7:0]  decimation_ratio
);

    reg clear_fault, disable_fault;
    reg [7:0] slow_fault_threshold;

    reg [31:0] cu_write_registers [5:0];
    reg [31:0] cu_read_registers [5:0];

    axil_simple_register_cu #(
        .N_READ_REGISTERS(6),
        .N_WRITE_REGISTERS(6),
        .REGISTERS_WIDTH(32),
        .ADDRESS_MASK('h1f)
    ) CU (
        .clock(clock),
        .reset(reset),
        .input_registers(cu_read_registers),
        .output_registers(cu_write_registers),
        .axil(axi_in)
    );

    assign comparator_thresholds[0] =  cu_write_registers[0][15:0];
    assign comparator_thresholds[4] =  cu_write_registers[0][31:16];
    assign comparator_thresholds[1] =  cu_write_registers[1][15:0];
    assign comparator_thresholds[5] =  cu_write_registers[1][31:16];
    assign comparator_thresholds[2] =  cu_write_registers[2][15:0];
    assign comparator_thresholds[6] =  cu_write_registers[2][31:16];
    assign comparator_thresholds[3] =  cu_write_registers[3][15:0];
    assign comparator_thresholds[7] =  cu_write_registers[3][31:16];
    assign calibrator_coefficients[1] =  cu_write_registers[4][15:0];
    assign calibrator_coefficients[0] =  cu_write_registers[4][31:16];

    assign latch_mode = cu_write_registers[5][2:1];
    assign clear_latch = cu_write_registers[5][4:3];
    assign calibrator_coefficients[2] = cu_write_registers[5][7:5];
    assign slow_fault_threshold = cu_write_registers[5][15:8];
    assign clear_fault = cu_write_registers[5][16];
    assign disable_fault =cu_write_registers[5][17];
    assign decimation_ratio = cu_write_registers[5][31:24];


    assign cu_read_registers = cu_write_registers;
    
    reg arm_fault;

    reg [7:0] slow_fault_counter;
    

    always_ff@(posedge clock)begin
        if(~reset | disable_fault)begin
            arm_fault <= 0; 
        end else begin
            if(data_in_valid)begin
                arm_fault <= 1;
            end    
        end
        
    end

    generate
        if(STICKY_FAULT==0) begin
            always_comb begin
                fault <= trip_high[0] | trip_low[0] | trip_high[1] | trip_low[1];
            end       
        end else begin
            always @(posedge clock) begin : fault_trip
                if(~reset | ~arm_fault) begin
                    fault <= 0;
                    slow_fault_counter <= 0;
                end else begin
                    if(trip_high[0] | trip_low[0])begin
                        fault <= 1;
                    end else if (trip_high[1] | trip_low[1]) begin
                        if(slow_fault_counter == slow_fault_threshold-1)begin
                            fault <= 1;
                        end else begin
                            slow_fault_counter <= slow_fault_counter +1;    
                        end                
                    end else if(clear_fault)begin
                        fault <= 0;
                    end
                end
            end        
        end
    endgenerate

endmodule