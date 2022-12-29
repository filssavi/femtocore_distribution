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

module calibration #(parameter DATA_PATH_WIDTH = 16)(
    input wire clock,
    input wire reset,
    input wire pipeline_flush,
    input wire signed [DATA_PATH_WIDTH-1:0] calibrator_coefficients [2:0],
    input wire gain_enable,
    axi_stream.slave data_in,
    axi_stream.master data_out
);

    wire signed [DATA_PATH_WIDTH-1:0] raw_data_out;
    reg signed [31:0] gain_corrected_data;
    reg signed [DATA_PATH_WIDTH-1:0] truncated_gain_corrected_data;

    
    assign data_in.ready = data_out.ready | ~reset ? 1 : 0;

    saturating_adder #(.DATA_WIDTH(DATA_PATH_WIDTH)) offset_adder(
        .a(data_in.data),
        .b(calibrator_coefficients[1]),
        .satp({1'b0,{DATA_PATH_WIDTH-1{1'b1}}}),
        .satn({1'b1,{DATA_PATH_WIDTH-1{1'b0}}}),
        .out(raw_data_out)
    );

    always @(posedge clock)begin
        if(~reset) begin
            gain_corrected_data <= 0;
            truncated_gain_corrected_data <= 0;
            data_out.data <= 0;
            data_out.valid <=0;
        end else begin
            if(data_in.valid & data_out.ready) begin
                if(gain_enable) begin
                    data_out.data <= raw_data_out << calibrator_coefficients[2];
                end else begin
                    data_out.data <= raw_data_out;
                end
                data_out.valid <=1;
            end else begin
                data_out.valid <=0;
            end
        end
    end


endmodule