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

module TransformAccellerationUnit #(parameter BASE_ADDRESS = 'h43c00000)(
    input wire clock,
    input wire reset,
    axi_lite.slave   axi_in,
    input  wire [15:0] theta,
    input  wire [53:0] clarke_in,
    input  wire [35:0] park_in,
    output wire [35:0] clarke_out,
    output wire [35:0] park_out,
    input  wire [35:0] inverse_clarke_in,
    input  wire [35:0] inverse_park_in,
    output wire [53:0] inverse_clarke_out,
    output wire [35:0] inverse_park_out
);

    wire direct_chain_disable;
    wire inverse_chain_disable;
    wire soft_reset;
    wire [35:0] int_inv_park_in;
    wire [35:0] park_selected_in;
    wire [35:0] anticlarke_selected_in;

    assign park_selected_in = direct_chain_disable ? park_in : clarke_out;
    assign anticlarke_selected_in = inverse_chain_disable ? inverse_clarke_in : inverse_park_out;
    assign int_inv_park_in = inverse_park_in;


    TauControlUnit #(.BASE_ADDRESS(BASE_ADDRESS)) cu(
        .clock(clock),
        .reset(reset),
        .axi_in(axi_in),
        .disable_direct_chain_mode(direct_chain_disable),
        .disable_inverse_chain_mode(inverse_chain_disable),
        .soft_reset(soft_reset)
    );


    clarke c(
        .a(clarke_in[17:0]),
        .b(clarke_in[35:18]),
        .c(clarke_in[53:36]),
        .alpha(clarke_out[17:0]),
        .beta(clarke_out[35:18])
    );

    park p(
        .clock(clock),
        .reset(~soft_reset | reset),
        .alpha(park_selected_in[17:0]),
        .beta(park_selected_in[35:18]),
        .theta(theta),
        .d(park_out[17:0]),
        .q(park_out[35:18])
    );

    antiPark ap(
        .clock(clock),
        .reset(~soft_reset |reset),
        .d(int_inv_park_in[17:0]),
        .q(int_inv_park_in[35:18]),
        .theta(theta),
        .alpha(inverse_park_out[17:0]),
        .beta(inverse_park_out[35:18])
    );

    antiClarke  ac(
        .alpha(anticlarke_selected_in[17:0]),
        .beta(anticlarke_selected_in[35:18]),
        .a(inverse_clarke_out[17:0]),
        .b(inverse_clarke_out[35:18]),
        .c(inverse_clarke_out[53:36])
    );


endmodule



    /**
       {
        "name": "TauControlUnit",
        "type": "peripheral",
        "registers":[
            {
                "name": "ctrl",
                "offset": "0x0",
                "description": "Control register",
                "direction": "RW",
                "fields": [
                    {
                        "name":"direct_chain_disable",
                        "description": "Disable chaining of the transforms on the direct path",
                        "start_position": 0,
                        "length": 1
                    },
                    {
                        "name":"tb_en",
                        "description": "Disable chaining of the transforms on the inverse path",
                        "start_position": 1,
                        "length": 1
                    },
                    {
                        "name":"reset",
                        "description": "Soft reser register",
                        "start_position": 2,
                        "length": 1
                    }
                ]
            }
        ]
       }  
    **/
