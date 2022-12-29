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

module scope_combiner #(parameter INPUT_DATA_WIDTH = 16, OUTPUT_DATA_WIDTH = 32, MSB_DEST_SUPPORT = "TRUE", N_CHANNELS = 6)(
    input wire clock,
    input wire reset,
    axi_stream.slave stream_in_1,
    axi_stream.slave stream_in_2,
    axi_stream.slave stream_in_3,
    axi_stream.slave stream_in_4,
    axi_stream.slave stream_in_5,
    axi_stream.slave stream_in_6,
    axi_stream.master stream_out
);

    reg [INPUT_DATA_WIDTH-1:0] input_buffer_data [N_CHANNELS-1:0];
    reg [INPUT_DATA_WIDTH-1:0] input_buffer_dest [N_CHANNELS-1:0];
    reg [N_CHANNELS-1:0] memory_status;
    reg [INPUT_DATA_WIDTH-1:0] combined_data;
    reg [7:0] combined_dest;
    reg [7:0] combined_user;
    reg combined_valid;
    reg combined_tlast;

    generate
        assign stream_out.tlast = combined_tlast;
        assign stream_out.user = combined_user;
        assign stream_out.valid = combined_valid;
        assign stream_out.dest = combined_dest;
        if(MSB_DEST_SUPPORT == "TRUE")
            if(OUTPUT_DATA_WIDTH == INPUT_DATA_WIDTH+8) begin
                assign stream_out.data = {combined_dest, combined_data}; 
            end else begin
                assign stream_out.data = {combined_dest, {(OUTPUT_DATA_WIDTH-INPUT_DATA_WIDTH-8){combined_data[INPUT_DATA_WIDTH-1]} }, combined_data}; 
            end
        else
            assign stream_out.data = {{(OUTPUT_DATA_WIDTH-INPUT_DATA_WIDTH){1'b0}},combined_data};
    endgenerate

    ///////////////STREAM COMBINATION SECTION///////////////

    assign stream_in_1.ready = stream_out.ready;
    assign stream_in_2.ready = stream_out.ready;
    assign stream_in_3.ready = stream_out.ready;
    assign stream_in_4.ready = stream_out.ready;
    assign stream_in_5.ready = stream_out.ready;
    assign stream_in_6.ready = stream_out.ready; 

    always@(posedge clock)begin
        if(~reset)begin
            combined_dest <= 0;
            combined_valid <= 0;
            combined_tlast <= 0;
            combined_data <= 0;
            memory_status <= 0;
        end else begin
            if(stream_in_1.valid) begin
                input_buffer_data[0] <= stream_in_1.data;
                input_buffer_dest[0] <= stream_in_1.dest;
                memory_status[0] <= 1;
            end

            if(stream_in_2.valid) begin
                input_buffer_data[1] <= stream_in_2.data;
                input_buffer_dest[1] <= stream_in_2.dest;
                memory_status[1] <= 1;
            end

            if(stream_in_3.valid) begin
                input_buffer_data[2] <= stream_in_3.data;
                input_buffer_dest[2] <= stream_in_3.dest;
                memory_status[2] <= 1;
            end

            if(stream_in_4.valid) begin
                input_buffer_data[3] <= stream_in_4.data;
                input_buffer_dest[3] <= stream_in_4.dest;
                memory_status[3] <= 1;
            end

            if(stream_in_5.valid) begin
                input_buffer_data[4] <= stream_in_5.data;
                input_buffer_dest[4] <= stream_in_5.dest;
                memory_status[4] <= 1;
            end

            if(stream_in_6.valid) begin
                input_buffer_data[5] <= stream_in_6.data;
                input_buffer_dest[5] <= stream_in_6.dest;
                memory_status[5] <= 1;
            end
            if(stream_out.ready)begin
                if(memory_status[0])begin
                    combined_data <= input_buffer_data[0];
                    combined_dest <= input_buffer_dest[0];
                    memory_status[0] <= 0;
                    combined_valid <=1;
                end else if(memory_status[1])begin
                    combined_data <= input_buffer_data[1];
                    combined_dest <= input_buffer_dest[1];
                    memory_status[1] <= 0;
                    combined_valid <=1;
                end else if(memory_status[2])begin
                    combined_data <= input_buffer_data[2];
                    combined_dest <= input_buffer_dest[2];
                    memory_status[2] <= 0;
                    combined_valid <=1;
                end else if(memory_status[3])begin
                    combined_data <= input_buffer_data[3];
                    combined_dest <= input_buffer_dest[3];
                    memory_status[3] <= 0;
                    combined_valid <=1;
                end else if(memory_status[4])begin
                    combined_data <= input_buffer_data[4];
                    combined_dest <= input_buffer_dest[4];
                    memory_status[4] <= 0;
                    combined_valid <=1;
                end else if(memory_status[5])begin
                    combined_data <= input_buffer_data[5];
                    combined_dest <= input_buffer_dest[5];
                    memory_status[5] <= 0;
                    combined_valid <=1;
                end else begin
                    combined_valid <= 0;
                end
            end

        end
    end

endmodule