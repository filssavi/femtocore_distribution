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

module gpio #(
    parameter BASE_ADDRESS = 0,
    INPUT_WIDTH = 8,
    OUTPUT_WIDTH = 8
)(
    input wire clock,
    input wire reset,
    input wire [INPUT_WIDTH-1:0] gpio_i,
    output reg [OUTPUT_WIDTH-1:0] gpio_o,
    axi_lite.slave axil
);

    localparam ADDITIONAL_INPUT_BITS = 32 - INPUT_WIDTH;
    localparam ADDITIONAL_OUTPUT_BITS = 32 - OUTPUT_WIDTH;
    axil_simple_register_cu #(
        .N_READ_REGISTERS(2),
        .N_WRITE_REGISTERS(1),
        .REGISTERS_WIDTH(32),
        .ADDRESS_MASK('hf)
    ) CU (
        .clock(clock),
        .reset(reset),
        .input_registers('{{{ADDITIONAL_INPUT_BITS{1'b0}},{gpio_i}}, {{ADDITIONAL_OUTPUT_BITS{1'b0}},{gpio_o}}}),
        .output_registers('{gpio_o}),
        .axil(axil)
    );


endmodule
   
    /**
       {
        "name": "gpio",
        "type": "peripheral",
        "registers":[
            {
                "name": "out",
                "offset": "0x0",
                "description": "Output Register",
                "direction": "RW"        
            },
            {
                "name": "in",
                "offset": "0x4",
                "description": "Input Register",
                "direction": "R"
            }
        ]
       }  
    **/