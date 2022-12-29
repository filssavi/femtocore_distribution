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

module sorter_tb ();

reg clock, reset;

wire [31:0] out_4 [3:0];
reg [31:0] in_4 [3:0];

batcher_sorter_4 UUT_1(
    .clock(clock),
    .reset(reset),
    .data_in(in_4),
    .data_out(out_4) 
);

wire [31:0] out_7 [7:0];
reg [31:0] in_7 [7:0];

batcher_sorter_8 UUT_2(
    .clock(clock),
    .reset(reset),
    .data_in(in_7),
    .data_out(out_7) 
);



initial clock = 0;
always #0.5 clock = ~clock;

initial begin
    reset = 1;
    in_4 = '{0,0,0,0};
    in_7 = '{0,0,0,0,0,0,0,0};
    #10 reset = 0;
    #3 reset = 1;

    in_4 = '{0,1,2,3};
    in_7 = '{0,1,2,3,4,5,6,7};
end

endmodule