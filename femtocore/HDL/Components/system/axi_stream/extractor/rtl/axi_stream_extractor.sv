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

`timescale 10ns / 1ns
`include "interfaces.svh"

module axi_stream_extractor #(parameter DATA_WIDTH = 16, DEST_WIDTH = 8, REGISTERED = 0)(
    input wire clock,
    input wire [DEST_WIDTH-1:0] selector,
    input wire [DEST_WIDTH-1:0] out_dest,
    axi_stream.slave stream_in,
    axi_stream.master stream_out
);


    generate
        if(REGISTERED) begin
            always_ff @(posedge clock) begin

                if(stream_in.dest == selector)begin
                    stream_out.data <= stream_in.data;
                    stream_out.user <= stream_in.user;
                    stream_out.dest <= out_dest;
                    stream_out.tlast <= stream_in.tlast;
                    stream_out.valid <= stream_in.valid;
                end else begin
                    stream_out.valid <= 0;
                end
            end
        end else begin
            always_comb begin
                if(stream_in.dest == selector)begin
                    stream_out.data <= stream_in.data;
                    stream_out.user <= stream_in.user;
                    stream_out.dest <= out_dest;
                    stream_out.tlast <= stream_in.tlast;
                    stream_out.valid <= stream_in.valid;
                end else begin
                    stream_out.data <= 0;
                    stream_out.user <= 0;
                    stream_out.dest <= 0;
                    stream_out.tlast <= 0;
                    stream_out.valid <= 0;
                end
            end
        end

        
    
        
    endgenerate

   
endmodule