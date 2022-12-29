

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

module PID #(
    parameter INPUT_DATA_WIDTH = 12, 
    parameter OUTPUT_DATA_WIDTH = 16
    )(
    input wire clock,
    input wire reset,

    // PID
    axi_stream.slave reference,
    axi_stream.slave feedback,
    axi_stream.master out,
    axi_stream.master error_mon,
    axi_lite.slave axil
);


    assign reference.ready = 1;
    assign feedback.ready = 1;
    
    // Top level parameters
    reg signed [OUTPUT_DATA_WIDTH-1:0] error;
    reg signed [OUTPUT_DATA_WIDTH-1:0] integrator_in;

    reg signed [OUTPUT_DATA_WIDTH-1:0] propotional_out;
    wire signed [OUTPUT_DATA_WIDTH-1:0] integral_out;
    wire signed [OUTPUT_DATA_WIDTH-1:0] diff_out;

    reg signed [OUTPUT_DATA_WIDTH-1:0] differential_out;
    reg signed [OUTPUT_DATA_WIDTH-1:0] int_pid_out;

    wire inputs_valid;
    assign inputs_valid = reference.valid && feedback.valid;

    reg error_valid, integrator_in_valid, integrator_out_valid;

    assign diff_out = 0;

    reg [31:0] cu_write_registers [8:0];
    reg [31:0] cu_read_registers [8:0];

    localparam ADDITIONAL_BITS = 32 - OUTPUT_DATA_WIDTH;
    localparam [31:0] INITIAL_OUTPUT_VALUES [8:0]= '{
            'h010101,
            -16'sd32767,
            16'sd32767,
            -16'sd32767,
            16'sd32767,
            0,
            0,
            0,
            0
        };


    axil_simple_register_cu #(
        .N_READ_REGISTERS(9),
        .N_WRITE_REGISTERS(9),
        .REGISTERS_WIDTH(32),
        .ADDRESS_MASK('h3f),
        .INITIAL_OUTPUT_VALUES(INITIAL_OUTPUT_VALUES)
    ) CU (
        .clock(clock),
        .reset(reset),
        .input_registers(cu_read_registers),
        .output_registers(cu_write_registers),
        .axil(axil)
    );

    reg nonblocking_output;
    reg [OUTPUT_DATA_WIDTH-1:0] kP;
    reg [OUTPUT_DATA_WIDTH-1:0] kI;
    reg [OUTPUT_DATA_WIDTH-1:0] kD;
    reg signed [OUTPUT_DATA_WIDTH-1:0] limit_out_up;
    reg signed [OUTPUT_DATA_WIDTH-1:0] limit_out_down;
    reg signed [OUTPUT_DATA_WIDTH-1:0] limit_int_up;
    reg signed [OUTPUT_DATA_WIDTH-1:0] limit_int_down;
    reg [7:0] kP_den;
    reg [7:0] kI_den;
    reg [7:0] kD_den;

    assign nonblocking_output = cu_write_registers[0];
    assign kP = cu_write_registers[1];
    assign kI = cu_write_registers[2];
    assign kD = cu_write_registers[3];
    assign limit_out_up = cu_write_registers[4];
    assign limit_out_down = cu_write_registers[5];
    assign limit_int_up = cu_write_registers[6];
    assign limit_int_down = cu_write_registers[7];
    assign {kD_den, kI_den, kP_den} = cu_write_registers[8];

    assign cu_read_registers[0] = nonblocking_output;
    assign cu_read_registers[1] = kP;
    assign cu_read_registers[2] = kI;
    assign cu_read_registers[3] = kD;
    assign cu_read_registers[4] = limit_out_up;
    assign cu_read_registers[5] = limit_out_down;
    assign cu_read_registers[6] = limit_int_up;
    assign cu_read_registers[7] = limit_int_down;
    assign cu_read_registers[8] = {kD_den, kI_den, kP_den};


    
    Integrator #(
        .DATA_WIDTH(OUTPUT_DATA_WIDTH)
    ) pid_int(
        .clock(clock),
        .reset(reset),
        // PID
        .input_valid(integrator_in_valid),
        .limit_int_up(limit_int_up),
        .limit_int_down(limit_int_down),
        .error_in(integrator_in),
        .out(integral_out)
    );

   always@(posedge clock)begin
       if(~reset) begin
            error <= 0;
            error_valid <= 0;
        end else begin
            if(inputs_valid & (out.ready | nonblocking_output)) begin
                error <= reference.data - feedback.data;
                error_valid <=1;
            end else begin
                error_valid <= 0;
            end
        end
   end

    assign error_mon.data = error;
    assign error_mon.valid = error_valid;

    always@(posedge clock)begin
        if(~reset) begin
            propotional_out <= 0;
            differential_out <= 0;
            integrator_in <= 0;
            integrator_in_valid <=0;
            integrator_out_valid <= 0;
        end else begin
            integrator_out_valid <= integrator_in_valid;
            if(error_valid & (out.ready | nonblocking_output)) begin
                propotional_out <= ($signed(kP) * error) >>> kP_den;
                integrator_in <= ($signed(kI) * error) >>> kI_den;
                differential_out <= ($signed(kD) * diff_out) >>> kD_den;
                integrator_in_valid <=1;    
            end else begin
                integrator_in_valid <=0;
            end
        end
    end
    

    always@(posedge clock)begin
        if(~reset) begin
            int_pid_out <= 0;
            out.valid <= 0;
        end else begin
            if(integrator_out_valid && out.ready) begin
                int_pid_out <= propotional_out + integral_out;  
                out.valid <= 1;
            end else begin
                out.valid <= 0;
            end
        end
    end
   
    always@(*)begin
        if(~reset) begin
            out.data <= 0;
        end else begin
            if (int_pid_out > limit_out_up) begin 
                out.data <= limit_out_up;
            end else if (int_pid_out < limit_out_down) begin 
                out.data <= limit_out_down;    
            end else begin 
                out.data <= int_pid_out;
            end
        end

    end


endmodule

    /**
       {
        "name": "PID",
        "type": "peripheral",
        "registers":[
            {
                "name": "control",
                "offset": "0x0",
                "description": "Control register",
                "direction": "RW"        
            },
            {
                "name": "kp",
                "offset": "0x4",
                "description": "Proportional action gain",
                "direction": "RW"
            },
            {
                "name": "ki",
                "offset": "0x8",
                "description": "Integral action gain",
                "direction": "RW"
            },
            {
                "name": "kd",
                "offset": "0xc",
                "description": "Derivative action gain",
                "direction": "RW"
            },
            {
                "name": "limit_out_p",
                "offset": "0x10",
                "description": "Upper output saturation limit",
                "direction": "RW"
            },
            {
                "name": "limit_out_n",
                "offset": "0x14",
                "description": "Lower output saturation limit",
                "direction": "RW"
            },
            {
                "name": "limit_int_p",
                "offset": "0x18",
                "description": "Upper integrator saturation limit",
                "direction": "RW"
            },
            {
                "name": "limit_int_n",
                "offset": "0x1c",
                "description": "Lower integrator saturation limit",
                "direction": "RW"
            },
            {
                "name": "gain_scaling",
                "offset": "0x20",
                "description": "Gain scaling factor",
                "direction": "RW",
                "fields": [
                    {
                        "name":"kp_den",
                        "description": "Proportional action scaling factor",
                        "start_position": 0,
                        "length": 8
                    },
                    {
                        "name":"ki_den",
                        "description": "Integral action scaling factor",
                        "start_position": 8,
                        "length": 8
                    },
                    {
                        "name":"kd_den",
                        "description": "derivative action scaling factor",
                        "start_position": 16,
                        "length": 8
                    }
                ]
            }
        ]
       }  
    **/