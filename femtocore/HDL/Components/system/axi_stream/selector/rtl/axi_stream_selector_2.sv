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

module axi_stream_selector_2 #(parameter DATA_WIDTH = 16, REGISTERED = 1)(
    input wire clock,
    input wire [0:0] address,
    axi_stream.slave stream_in,
    axi_stream.master stream_out_1, 
    axi_stream.master stream_out_2

);

    generate

        if(REGISTERED) begin
            always_ff@(posedge clock) begin
                stream_out_1.valid <= 0;
                stream_out_2.valid <= 0;

                case (address)
                0:begin
                        stream_out_1.data <= stream_in.data;
                        stream_out_1.dest<= stream_in.dest;
                        stream_out_1.valid <= stream_in.valid;
                        stream_out_1.user <= stream_in.user;
                        stream_out_1.tlast <= stream_in.tlast;
                end
                1:begin
                        stream_out_2.data <= stream_in.data;
                        stream_out_2.dest<= stream_in.dest;
                        stream_out_2.valid <= stream_in.valid;
                        stream_out_2.user <= stream_in.user;
                        stream_out_2.tlast <= stream_in.tlast;
                end
                endcase 
            end
        end

        always_comb begin
            case (address)
            0: stream_in.ready <= stream_out_1.ready;
            1: stream_in.ready <= stream_out_2.ready;
            default: stream_in.ready <= 0;
            endcase 
            if(~REGISTERED) begin
                case (address)
                0:begin
                        stream_out_1.data <= stream_in.data;
                        stream_out_1.dest<= stream_in.dest;
                        stream_out_1.valid <= stream_in.valid;
                        stream_out_1.user <= stream_in.user;
                        stream_out_1.tlast <= stream_in.tlast;
                        stream_out_2.data <= 0;
                        stream_out_2.dest<= 0;
                        stream_out_2.valid <= 0;
                        stream_out_2.user <= 0;
                        stream_out_2.tlast <= 0;
                        
                end
                1:begin
                        stream_out_2.data <= stream_in.data;
                        stream_out_2.dest<= stream_in.dest;
                        stream_out_2.valid <= stream_in.valid;
                        stream_out_2.user <= stream_in.user;
                        stream_out_2.tlast <= stream_in.tlast;
                        stream_out_1 .data <= 0;
                        stream_out_1.dest<= 0;
                        stream_out_1.valid <= 0;
                        stream_out_1.user <= 0;
                        stream_out_1.tlast <= 0;
                end
                endcase 
            end
        end
    
        
    endgenerate

   
endmodule