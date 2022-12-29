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

module Filter #(parameter DATA_PATH_WIDTH = 16)(
    input wire clock,
    input wire reset,
    input wire in_valid,
    output wire in_ready,
    input wire pipeline_flush,
    input wire [3:0] tap_address,
    input wire [15:0] tap_data,
    input wire tap_we,
    input wire signed [DATA_PATH_WIDTH-1:0] data_in,
    output reg signed [DATA_PATH_WIDTH-1:0] data_out,
    output reg out_valid,
    input wire out_ready
);

    reg [15:0] taps [8:0];
    reg signed [31:0] internal_registers [8:0];
    reg signed [31:0] pipeline_registers [8:0];
    wire signed [31:0] adder_outputs [7:0];
    reg [3:0] pipeline_fill_level;

    assign in_ready = out_ready | ~reset ? 1 : 0;

    saturating_adder add0(
        .a($signed(internal_registers[0])),
        .b($signed(pipeline_registers[0])),
        .satp(2147483647),
        .satn(-2147483647),
        .out(adder_outputs[0])
    );

    saturating_adder add1(
        .a($signed(internal_registers[1])),
        .b($signed(pipeline_registers[1])),
        .satp(2147483647),
        .satn(-2147483647),
        .out(adder_outputs[1])
    );

    saturating_adder add2(
        .a($signed(internal_registers[2])),
        .b($signed(pipeline_registers[2])),
        .satp(2147483647),
        .satn(-2147483647),
        .out(adder_outputs[2])
    );

    saturating_adder add3(
        .a($signed(internal_registers[3])),
        .b($signed(pipeline_registers[3])),
        .satp(2147483647),
        .satn(-2147483647),
        .out(adder_outputs[3])
    );

    saturating_adder add4(
        .a($signed(internal_registers[4])),
        .b($signed(pipeline_registers[4])),
        .satp(2147483647),
        .satn(-2147483647),
        .out(adder_outputs[4])
    );

    saturating_adder add5(
        .a($signed(internal_registers[5])),
        .b($signed(pipeline_registers[5])),
        .satp(2147483647),
        .satn(-2147483647),
        .out(adder_outputs[5])
    );

    saturating_adder add6(
        .a($signed(internal_registers[6])),
        .b($signed(pipeline_registers[6])),
        .satp(2147483647),
        .satn(-2147483647),
        .out(adder_outputs[6])
    );

    saturating_adder add7(
        .a($signed(internal_registers[7])),
        .b($signed(pipeline_registers[7])),
        .satp(2147483647),
        .satn(-2147483647),
        .out(adder_outputs[7])
    );

    

    always @(posedge clock or negedge reset or posedge pipeline_flush) begin
        if(~reset | pipeline_flush)begin
            pipeline_fill_level <=0;
            out_valid <=0;
            if(~reset) begin
                taps[0] <=0;
                taps[1] <=0;
                taps[2] <=0;
                taps[3] <=0;
                taps[4] <=0;
                taps[5] <=0;
                taps[6] <=0;
                taps[7] <=0;
                taps[8] <=0;
            end

            internal_registers[0] <=0;
            internal_registers[1] <=0;
            internal_registers[2] <=0;
            internal_registers[3] <=0;
            internal_registers[4] <=0;
            internal_registers[5] <=0;
            internal_registers[6] <=0;
            internal_registers[7] <=0;
            internal_registers[8] <=0;

            pipeline_registers[0] <= 0;
            pipeline_registers[1] <= 0;
            pipeline_registers[2] <= 0;
            pipeline_registers[3] <= 0;
            pipeline_registers[4] <= 0;
            pipeline_registers[5] <= 0;
            pipeline_registers[6] <= 0;
            pipeline_registers[7] <= 0;
            pipeline_registers[8] <= 0;
            data_out <= 0;
        end else begin
            if(tap_we) begin
                taps[tap_address] <= tap_data;
                data_out <= 0;
            end else begin
                if(in_valid & out_ready) begin
                    if(pipeline_fill_level==10) begin
                        out_valid <=1;
                        data_out <= adder_outputs[0] >> 15;
                    end else begin
                        data_out <= 0;
                        pipeline_fill_level <= pipeline_fill_level+1;
                    end
                    internal_registers[0] <= $signed(taps[0])*data_in;
                    internal_registers[1] <= $signed(taps[1])*data_in;
                    internal_registers[2] <= $signed(taps[2])*data_in;
                    internal_registers[3] <= $signed(taps[3])*data_in;
                    internal_registers[4] <= $signed(taps[4])*data_in;
                    internal_registers[5] <= $signed(taps[5])*data_in;
                    internal_registers[6] <= $signed(taps[6])*data_in;
                    internal_registers[7] <= $signed(taps[7])*data_in;
                    internal_registers[8] <= $signed(taps[8])*data_in;


                    
                    pipeline_registers[0] <= adder_outputs[1];
                    pipeline_registers[1] <= adder_outputs[2];
                    pipeline_registers[2] <= adder_outputs[3];
                    pipeline_registers[3] <= adder_outputs[4];
                    pipeline_registers[4] <= adder_outputs[5];
                    pipeline_registers[5] <= adder_outputs[6];
                    pipeline_registers[6] <= adder_outputs[7];
                    pipeline_registers[7] <= internal_registers[8];
                end else begin
                    out_valid <= 0;
                end
            end
        end
    end


endmodule