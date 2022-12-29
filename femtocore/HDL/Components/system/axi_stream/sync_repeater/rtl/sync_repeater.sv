

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


module axis_sync_repeater #(parameter DATA_WIDTH= 32, DEST_WIDTH = 8, USER_WIDTH = 8)(
    input wire        clock,
    input wire        reset,
    input wire        sync,
    axi_stream.slave in,
    axi_stream.master out
);

    axi_stream registered_stream();
    
    axis_skid_buffer #(
        .REGISTER_OUTPUT(1),
        .LATCHING(1),
        .DATA_WIDTH(32)
    ) buffer (
        .clock(clock),
        .reset(reset),
        .axis_in(in),
        .axis_out(registered_stream)
    );

    assign registered_stream.ready = out.ready;
    always_ff@(posedge clock)begin
        if(~reset)begin
            out.valid <= 0;
            out.data <= 0;
            out.dest <= 0;
            out.user <= 0;
            out.tlast <= 0;
        end else begin
            out.valid <= 0;
            if(sync)begin
                out.data <= registered_stream.data;
                out.dest <= registered_stream.dest;
                out.user <= registered_stream.user;
                out.tlast <= registered_stream.tlast;
                out.valid <= 1;
            end
        end
    end

endmodule