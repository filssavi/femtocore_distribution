
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


module axis_limiter #(parameter BASE_ADDRESS = 'h43c00000)(
    input wire        clock,
    input wire        reset,
    axi_stream.master in,
    axi_stream.master out,
    axi_lite.slave axi_in
);

    reg [31:0] limit_up;
    reg [31:0] limit_down;

    reg [31:0] cu_write_registers [1:0];
    reg [31:0] cu_read_registers [1:0];

    axil_simple_register_cu #(
        .N_READ_REGISTERS(2),
        .N_WRITE_REGISTERS(2),
        .REGISTERS_WIDTH(32),
        .ADDRESS_MASK('hf),
        .INITIAL_OUTPUT_VALUES('{32'h0, 32'hffffffff})
    ) CU (
        .clock(clock),
        .reset(reset),
        .input_registers(cu_read_registers),
        .output_registers(cu_write_registers),
        .axil(axi_in)
    );

    assign limit_up = cu_write_registers[0];
    assign limit_down = cu_write_registers[1];

    assign cu_read_registers = cu_write_registers;


    assign in.ready = out.ready; 

    always_ff@(posedge clock)begin
        if(~reset)begin
            out.valid <= 0;
            out.data <= 0;
            out.dest <= 0;
        end else begin
            if(out.ready & in.valid) begin
                if(in.data > limit_up)
                    out.data <= limit_up;
                else if(in.data < limit_down)
                    out.data <= limit_down;
                else
                    out.data <= in.data;
                out.dest <= in.dest;
                out.valid <= 1;
                out.user <= in.user;
                out.tlast <= in.tlast;
            end else
                out.valid <= 0;
            
        end
    end

endmodule

    /**
       {
        "name": "axis_constant",
        "type": "peripheral",
        "registers":[
            {
                "name": "lim_up",
                "offset": "0x0",
                "description": "Highest allowable value on the stream",
                "direction": "RW"
            },
            {
                "name": "high",
                "offset": "0x4",
                "description": "Lowest allowable value on the stream",
                "direction": "RW"
            }
        ]
    }  
    **/