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
`timescale 1 ps / 1 ps

module Decimator_wrapper #(parameter DATA_PATH_WIDTH = 16)(
    input wire clock,
    input wire signed [DATA_PATH_WIDTH-1:0] data_in_tdata,
    output wire data_in_tready,
    input wire data_in_tvalid,
    input wire data_out_tready,
    output wire signed [DATA_PATH_WIDTH-1:0] data_out_tdata,
    output wire data_out_tvalid
);
    
    wire signed [33:0] internal_data_out;
    assign data_out_tdata = internal_data_out;

    Decimator Decimator_i(
        .Clock(clock),
        .data_in_tdata(data_in_tdata),
        .data_in_tready(data_in_tready),
        .data_in_tvalid(data_in_tvalid),
        .data_out_tdata(internal_data_out),
        .data_out_tvalid(data_out_tvalid),
        .data_out_tready(data_out_tready)
    );
    
endmodule
