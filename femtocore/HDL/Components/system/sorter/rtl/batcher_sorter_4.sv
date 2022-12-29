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

module batcher_sorter_4 #(
    parameter DATA_WIDTH = 32,
    parameter USER_WIDTH = 32,
    parameter DEST_WIDTH = 32
)(
    input wire clock,
    input wire [(DATA_WIDTH+USER_WIDTH+DEST_WIDTH)-1:0] data_in [3:0],
    output reg [(DATA_WIDTH+USER_WIDTH+DEST_WIDTH)-1:0] data_out [3:0]
);

wire [(DATA_WIDTH+USER_WIDTH+DEST_WIDTH)-1:0] stage_1 [3:0];
wire [(DATA_WIDTH+USER_WIDTH+DEST_WIDTH)-1:0] stage_2 [3:0];

sort_comparator #(
    .DATA_WIDTH(DATA_WIDTH),
    .USER_WIDTH(USER_WIDTH),
    .DEST_WIDTH(DEST_WIDTH)
) cmp_1(
    .clock(clock),
    .data_in(data_in[1:0]),
    .data_out(stage_1[1:0])
);

sort_comparator #(
    .DATA_WIDTH(DATA_WIDTH),
    .USER_WIDTH(USER_WIDTH),
    .DEST_WIDTH(DEST_WIDTH)
) cmp_2(
    .clock(clock),
    .data_in(data_in[3:2]),
    .data_out(stage_1[3:2])
);


sort_comparator #(
    .DATA_WIDTH(DATA_WIDTH),
    .USER_WIDTH(USER_WIDTH),
    .DEST_WIDTH(DEST_WIDTH)
) cmp_3(
    .clock(clock),
    .data_in('{stage_1[2], stage_1[0]}),
    .data_out('{stage_2[2], stage_2[0]})
);


sort_comparator #(
    .DATA_WIDTH(DATA_WIDTH),
    .USER_WIDTH(USER_WIDTH),
    .DEST_WIDTH(DEST_WIDTH)
) cmp_4(
    .clock(clock),
    .data_in('{stage_1[3], stage_1[1]}),
    .data_out('{stage_2[3], stage_2[1]})
);



sort_comparator #(
    .DATA_WIDTH(DATA_WIDTH),
    .USER_WIDTH(USER_WIDTH),
    .DEST_WIDTH(DEST_WIDTH)
) cmp_5(
    .clock(clock),
    .data_in('{stage_2[2], stage_2[1]}),
    .data_out('{data_out[2], data_out[1]})
);


always_ff @(posedge clock) begin
    data_out[3] <= stage_2[3];
    data_out[0] <= stage_2[0];
end



endmodule