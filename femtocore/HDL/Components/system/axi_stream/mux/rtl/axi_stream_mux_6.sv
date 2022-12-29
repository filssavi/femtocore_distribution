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

module axi_stream_mux_6 #(parameter DATA_WIDTH = 16)(
    input wire clock,
    input wire reset,
    input wire [2:0] address,
    axi_stream.slave stream_in_1,
    axi_stream.slave stream_in_2,
    axi_stream.slave stream_in_3,
    axi_stream.slave stream_in_4,
    axi_stream.slave stream_in_5,
    axi_stream.slave stream_in_6,
    axi_stream.master stream_out
);

    always_ff@(posedge clock) begin
        if(~reset)begin
            stream_in_1.ready <=0;
            stream_in_2.ready <=0;
            stream_in_3.ready <=0;
            stream_in_4.ready <=0;
            stream_in_5.ready <=0;
            stream_in_6.ready <=0;
        end else begin
            case (address)
            0:begin
                    stream_out.data <= stream_in_1.data;
                    stream_out.dest <= stream_in_1.dest;
                    stream_out.valid <= stream_in_1.valid;
                    stream_out.user <= stream_in_1.user;
                    stream_out.tlast <= stream_in_1.tlast;
                    stream_in_1.ready <= stream_out.ready;
            end
            1:begin
                    stream_out.data <= stream_in_2.data;
                    stream_out.dest <= stream_in_2.dest;
                    stream_out.valid <= stream_in_2.valid;
                    stream_out.user <= stream_in_2.user;
                    stream_out.tlast <= stream_in_2.tlast;
                    stream_in_2.ready <= stream_out.ready;
            end
            2:begin
                    stream_out.data <= stream_in_3.data;
                    stream_out.dest <= stream_in_3.dest;
                    stream_out.valid <= stream_in_3.valid;
                    stream_out.user <= stream_in_3.user;
                    stream_out.tlast <= stream_in_3.tlast;
                    stream_in_3.ready <= stream_out.ready;
            end
            3:begin
                    stream_out.data <= stream_in_4.data;
                    stream_out.dest <= stream_in_4.dest;
                    stream_out.valid <= stream_in_4.valid;
                    stream_out.user <= stream_in_4.user;
                    stream_out.tlast <= stream_in_4.tlast;
                    stream_in_4.ready <= stream_out.ready;
            end
            4:begin
                    stream_out.data <= stream_in_5.data;
                    stream_out.dest <= stream_in_5.dest;
                    stream_out.valid <= stream_in_5.valid;
                    stream_out.user <= stream_in_5.user;
                    stream_out.tlast <= stream_in_5.tlast;
                    stream_in_5.ready <= stream_out.ready;
            end
            5:begin
                    stream_out.data <= stream_in_6.data;
                    stream_out.dest <= stream_in_6.dest;
                    stream_out.valid <= stream_in_6.valid;
                    stream_out.user <= stream_in_6.user;
                    stream_out.tlast <= stream_in_6.tlast;
                    stream_in_6.ready <= stream_out.ready;
            end
            endcase 
        end
    end
  

endmodule