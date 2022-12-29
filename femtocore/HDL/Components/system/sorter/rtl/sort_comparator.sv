// Copyright 2021 Filippo Savi
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

`timescale 10ns / 1ns
`include "interfaces.svh"

module sort_comparator #(
    parameter DATA_WIDTH = 32,
    parameter USER_WIDTH = 32,
    parameter DEST_WIDTH = 32
)(
    input wire clock,
    input wire [(DATA_WIDTH+USER_WIDTH+DEST_WIDTH)-1:0] data_in [1:0],
    output reg [(DATA_WIDTH+USER_WIDTH+DEST_WIDTH)-1:0] data_out [1:0]
);

always_ff @(posedge clock) begin
    if(data_in[0][DATA_WIDTH-1:0] > data_in[1][DATA_WIDTH-1:0]) begin
        data_out[0] <= data_in[1];
        data_out[1] <= data_in[0];
    end else begin
        data_out[0] <= data_in[0];
        data_out[1] <= data_in[1];
    end
end

endmodule