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

module batcher_sorter_8 #(
    parameter DATA_WIDTH = 32,
    parameter USER_WIDTH = 32,
    parameter DEST_WIDTH = 32
)(
    input wire clock,
    input wire [3:0] chunk_size_in,
    input wire [(DATA_WIDTH+USER_WIDTH+DEST_WIDTH)-1:0] data_in [7:0],
    input wire data_in_valid,
    output reg [3:0] chunk_size_out,
    output reg [(DATA_WIDTH+USER_WIDTH+DEST_WIDTH)-1:0] data_out [7:0],
    output reg data_out_valid
);

wire [(DATA_WIDTH+USER_WIDTH+DEST_WIDTH)-1:0] stage_1 [7:0];
wire [(DATA_WIDTH+USER_WIDTH+DEST_WIDTH)-1:0] stage_2 [7:0];
logic [(DATA_WIDTH+USER_WIDTH+DEST_WIDTH)-1:0] stage_3 [7:0];

reg [3:0]chunk_delay [4:0];

always_ff @(posedge clock) begin
    chunk_delay[0] <= chunk_size_in;
    chunk_delay[1] <= chunk_delay[0];
    chunk_delay[2] <= chunk_delay[1];
    chunk_delay[3] <= chunk_delay[2];
    chunk_delay[4] <= chunk_delay[3];
    chunk_size_out <= chunk_delay[4];
end

reg [4:0] valid_delay;

always_ff @(posedge clock) begin
    valid_delay[0] <= data_in_valid;
    valid_delay[1] <= valid_delay[0];
    valid_delay[2] <= valid_delay[1];
    valid_delay[3] <= valid_delay[2];
    valid_delay[4] <= valid_delay[3];
    data_out_valid <= valid_delay[4];
end

//////////////////////////////////////////////////////////
/////                       stage 1                  /////
//////////////////////////////////////////////////////////

batcher_sorter_4 #(
    .DATA_WIDTH(DATA_WIDTH),
    .USER_WIDTH(USER_WIDTH),
    .DEST_WIDTH(DEST_WIDTH)
) sub_sorter_1(
    .clock(clock),
    .data_in(data_in[3:0]),
    .data_out(stage_1[3:0])
);

batcher_sorter_4 #(
    .DATA_WIDTH(DATA_WIDTH),
    .USER_WIDTH(USER_WIDTH),
    .DEST_WIDTH(DEST_WIDTH)
) sub_sorter_2(
    .clock(clock),
    .data_in(data_in[7:4]),
    .data_out(stage_1[7:4])
);

//////////////////////////////////////////////////////////
/////                       stage 2                  /////
//////////////////////////////////////////////////////////

sort_comparator #(
    .DATA_WIDTH(DATA_WIDTH),
    .USER_WIDTH(USER_WIDTH),
    .DEST_WIDTH(DEST_WIDTH)
) cmp_1(
    .clock(clock),
    .data_in('{stage_1[4], stage_1[0]}),
    .data_out('{stage_2[4], stage_2[0]})
);

sort_comparator #(
    .DATA_WIDTH(DATA_WIDTH),
    .USER_WIDTH(USER_WIDTH),
    .DEST_WIDTH(DEST_WIDTH)
) cmp_2(
    .clock(clock),
    .data_in('{stage_1[5], stage_1[1]}),
    .data_out('{stage_2[5], stage_2[1]})
);

sort_comparator #(
    .DATA_WIDTH(DATA_WIDTH),
    .USER_WIDTH(USER_WIDTH),
    .DEST_WIDTH(DEST_WIDTH)
) cmp_3(
    .clock(clock),
    .data_in('{stage_1[6], stage_1[2]}),
    .data_out('{stage_2[6], stage_2[2]})
);

sort_comparator #(
    .DATA_WIDTH(DATA_WIDTH),
    .USER_WIDTH(USER_WIDTH),
    .DEST_WIDTH(DEST_WIDTH)
) cmp_4(
    .clock(clock),
    .data_in('{stage_1[7], stage_1[3]}),
    .data_out('{stage_2[7], stage_2[3]})
);

//////////////////////////////////////////////////////////
/////                       stage 3                  /////
//////////////////////////////////////////////////////////


sort_comparator #(
    .DATA_WIDTH(DATA_WIDTH),
    .USER_WIDTH(USER_WIDTH),
    .DEST_WIDTH(DEST_WIDTH)
) cmp_5(
    .clock(clock),
    .data_in('{stage_2[4], stage_2[2]}),
    .data_out('{stage_3[4], stage_3[2]})
);

sort_comparator #(
    .DATA_WIDTH(DATA_WIDTH),
    .USER_WIDTH(USER_WIDTH),
    .DEST_WIDTH(DEST_WIDTH)
) cmp_6(
    .clock(clock),
    .data_in('{stage_2[5], stage_2[3]}),
    .data_out('{stage_3[5], stage_3[3]})
);

//////////////////////////////////////////////////////////
/////                       stage 4                  /////
//////////////////////////////////////////////////////////


sort_comparator #(
    .DATA_WIDTH(DATA_WIDTH),
    .USER_WIDTH(USER_WIDTH),
    .DEST_WIDTH(DEST_WIDTH)
) cmp_7(
    .clock(clock),
    .data_in('{stage_3[2], stage_3[1]}),
    .data_out('{data_out[2], data_out[1]})
);

sort_comparator #(
    .DATA_WIDTH(DATA_WIDTH),
    .USER_WIDTH(USER_WIDTH),
    .DEST_WIDTH(DEST_WIDTH)
) cmp_8(
    .clock(clock),
    .data_in('{stage_3[4], stage_3[3]}),
    .data_out('{data_out[4], data_out[3]})
);

sort_comparator #(
    .DATA_WIDTH(DATA_WIDTH),
    .USER_WIDTH(USER_WIDTH),
    .DEST_WIDTH(DEST_WIDTH)
) cmp_9(
    .clock(clock),
    .data_in('{stage_3[6], stage_3[5]}),
    .data_out('{data_out[6], data_out[5]})
);





always_ff @(posedge clock) begin
    stage_3[0] <= stage_2[0];
    stage_3[1] <= stage_2[1];
    stage_3[6] <= stage_2[6];
    stage_3[7] <= stage_2[7];
    data_out[0] <= stage_3[0];
    data_out[7] <= stage_3[7];
end



endmodule