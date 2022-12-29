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

module axi_stream_combiner_3 #(parameter INPUT_DATA_WIDTH = 16, OUTPUT_DATA_WIDTH = 32, TLAST_PERIOD = 1024, MSB_DEST_SUPPORT = "TRUE")(
    input wire clock,
    input wire reset,
    axi_stream.slave stream_in_1,
    axi_stream.slave stream_in_2,
    axi_stream.slave stream_in_3,
    axi_stream.master stream_out
);

    reg [INPUT_DATA_WIDTH-1:0] combined_data;
    reg [7:0] combined_dest;
    reg [7:0] combined_user;
    reg combined_valid;
    wire combined_tlast;

    generate
        assign stream_out.tlast = combined_tlast;
        assign stream_out.user = combined_user;
        assign stream_out.valid = combined_valid;
        assign stream_out.dest = combined_dest;
        if(MSB_DEST_SUPPORT == "TRUE")begin
            assign stream_out.data = {combined_dest, {(OUTPUT_DATA_WIDTH-INPUT_DATA_WIDTH-8){combined_data[INPUT_DATA_WIDTH-1]} }, combined_data};
        end else begin
            assign stream_out.data = {{(OUTPUT_DATA_WIDTH-INPUT_DATA_WIDTH){combined_data[INPUT_DATA_WIDTH-1]}},combined_data};
        end  
    endgenerate



    ///////////////STREAM COMBINATION SECTION///////////////

    reg int_stream_1_ready, int_stream_2_ready, int_stream_3_ready;

    assign stream_in_1.ready = int_stream_1_ready & stream_out.ready;
    assign stream_in_2.ready = int_stream_2_ready & stream_out.ready;
    assign stream_in_3.ready = int_stream_3_ready & stream_out.ready; 

    always@(posedge clock)begin
        if(~reset)begin
            int_stream_1_ready <= 0;
            int_stream_2_ready <= 0;
            int_stream_3_ready <= 0; 
            combined_dest <= 0;
            combined_user <= 0;
            combined_valid <= 0;
            combined_data <= 0;
        end else begin

            if(stream_in_1.valid & stream_out.ready)begin
                int_stream_2_ready <= 0;
                int_stream_3_ready <= 0; 
                combined_user <= stream_in_1.user;            
                combined_dest <= stream_in_1.dest;
                combined_data <= stream_in_1.data;
                combined_valid <=1;

            end else if(stream_in_2.valid & stream_out.ready)begin
                int_stream_1_ready <= 0;
                int_stream_3_ready <= 0; 
                combined_user <= stream_in_2.user;            
                combined_dest <= stream_in_2.dest;
                combined_data <= stream_in_2.data;
                combined_valid <=1;

            end else if(stream_in_3.valid & stream_out.ready)begin
                int_stream_1_ready <= 0;
                int_stream_2_ready <= 0; 
                combined_user <= stream_in_3.user;            
                combined_dest <= stream_in_3.dest;
                combined_data <= stream_in_3.data;
                combined_valid <=1;

            end else begin
                combined_valid <= 0;
                int_stream_1_ready <= 1;
                int_stream_2_ready <= 1;
                int_stream_3_ready <= 1; 
            end
        end
    end



    ///////////////TLAST GENERATION SECTION///////////////

    reg [15:0] tlast_counter_1;
    reg [15:0] tlast_counter_2;
    reg [15:0] tlast_counter_3; 

    reg stream_1_prev_val, stream_2_prev_val, stream_3_prev_val;
    reg int_tlast_1, int_tlast_2, int_tlast_3;

    assign combined_tlast = int_tlast_1 | int_tlast_2 | int_tlast_3;

    always@(posedge clock)begin
        if(~reset)begin
            tlast_counter_1 <= 0;
            stream_1_prev_val <= 0;
            int_tlast_1 <= 0;
        
            tlast_counter_2 <= 0;
            stream_2_prev_val <= 0;
            int_tlast_2 <= 0;
        
            tlast_counter_3 <= 0;
            stream_3_prev_val <= 0;
            int_tlast_3 <= 0;
         
        end else begin
            if(stream_in_1.valid & ~stream_1_prev_val)begin
                    if(tlast_counter_1==TLAST_PERIOD-1)begin
                        tlast_counter_1 <= 0;
                        int_tlast_1 <= 1;
                    end else begin
                        tlast_counter_1 <= tlast_counter_1+1;
                    end

                end else if(stream_in_2.valid & ~stream_2_prev_val)begin
                    if(tlast_counter_2==TLAST_PERIOD-1)begin
                        tlast_counter_2 <= 0;
                        int_tlast_2 <= 1;
                    end else begin
                        tlast_counter_2 <= tlast_counter_2+1;
                    end

                end else if(stream_in_3.valid & ~stream_3_prev_val)begin
                    if(tlast_counter_3==TLAST_PERIOD-1)begin
                        tlast_counter_3 <= 0;
                        int_tlast_3 <= 1;
                    end else begin
                        tlast_counter_3 <= tlast_counter_3+1;
                    end

                end else begin
                    int_tlast_1 <= 0;
                    int_tlast_2 <= 0;
                    int_tlast_3 <= 0; 
                end    
        end
        stream_1_prev_val <= stream_in_1.valid;
        stream_2_prev_val <= stream_in_2.valid;
        stream_3_prev_val <= stream_in_3.valid; 
    end
endmodule