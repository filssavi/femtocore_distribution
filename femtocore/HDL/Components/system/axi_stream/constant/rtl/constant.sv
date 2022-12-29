
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


module axis_constant #(
    parameter CONSTANT_WIDTH = 32
)(
    input wire        clock,
    input wire        reset,
    input wire        sync,
    axi_stream.master const_out,
    axi_lite axil
);


    localparam ADDITIONAL_BITS = 32 - CONSTANT_WIDTH;

    wire trigger_axis_write;
    reg [31:0] cu_write_registers [2:0];
    reg [31:0] cu_read_registers [2:0];


    axil_simple_register_cu #(
        .N_READ_REGISTERS(3),
        .N_WRITE_REGISTERS(3),
        .REGISTERS_WIDTH(32),
        .ADDRESS_MASK('hf),
        .N_TRIGGER_REGISTERS(1),
        .TRIGGER_REGISTERS_IDX({0})
    ) CU (
        .clock(clock),
        .reset(reset),
        .input_registers(cu_read_registers),
        .output_registers(cu_write_registers),
        .trigger_out(trigger_axis_write),
        .axil(axil)
    );

    reg wait_sync;

    reg [31:0] constant_low_bytes;
    reg [31:0] constant_high_bytes;
    reg [31:0] constant_dest;

    assign constant_low_bytes = cu_write_registers[0];
    assign constant_high_bytes = cu_write_registers[1];
    assign constant_dest = cu_write_registers[2];

    assign cu_read_registers[0] = {{ADDITIONAL_BITS{1'b0}}, constant_low_bytes};
    assign cu_read_registers[1] = {{ADDITIONAL_BITS{1'b0}}, constant_high_bytes};
    assign cu_read_registers[2] = {{ADDITIONAL_BITS{1'b0}}, constant_dest};


    always_ff @(posedge clock) begin
        if (~reset) begin
            const_out.valid <= 0;
            const_out.data <= 0;
            const_out.dest <= 0;
            wait_sync <= 0;
        end else begin
            const_out.valid <= 0;
            if(trigger_axis_write)begin
                if(const_out.ready & sync) begin
                    const_out.data <= {constant_high_bytes, constant_low_bytes};
                    const_out.dest <= constant_dest;
                    const_out.valid <= 1;
                end else begin
                    wait_sync = 1;
                end   
            end else if(wait_sync) begin
                if(const_out.ready & sync) begin
                    const_out.data <= {constant_high_bytes, constant_low_bytes};
                    const_out.dest <= constant_dest;
                    const_out.valid <= 1;
                    wait_sync <= 0;
                end              
            end
        end
    end



endmodule


    /**
       {
        "name": "axis_constant",
        "type": "peripheral",
        "registers":[
            {
                "name": "low",
                "offset": "0x0",
                "description": "Least significant bytes of the constant",
                "direction": "RW"
            },
            {
                "name": "high",
                "offset": "0x4",
                "description": "Most significant bytes of the constant",
                "direction": "RW"
            },
            {
                "name": "dest",
                "offset": "0x8",
                "description": "Value of the AXI stream dest signal associated with the constant",
                "direction": "RW"
                
            }
        ]
    }  
    **/
