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

module comparator #(parameter DATA_PATH_WIDTH = 16)(
    input wire clock,
    input wire reset,
    input wire signed [DATA_PATH_WIDTH-1:0] thresholds [0:3],
    axi_stream.slave data_in,
    input wire latching_mode,
    input wire clear_latch,
    output reg trip_high,
    output reg trip_low
);

    //      Normal mode              |        latching mode         
    // thresholds[0] = low falling   | thresholds[0] =  threshold low
    // thresholds[1] = low raising   | thresholds[1] = --------------
    // thresholds[2] = high falling  | thresholds[2] = --------------
    // thresholds[3] = high raising  | thresholds[3] = threshold high

    reg latched = 0;
    
    wire signed[DATA_PATH_WIDTH-1:0] signed_data;
    assign signed_data = $signed(data_in.data);

    always @(posedge clock or negedge reset) begin
        if(~reset)begin
            trip_high <= 0;
            trip_low <= 0;
        end else begin
            if(latching_mode) begin
                if(clear_latch) latched <= 0; 
                if(data_in.valid) begin
                    if(signed_data < thresholds[0]) begin
                        trip_low <= 1;
                        latched <=1;
                    end else if(signed_data > thresholds[1] & ~latched) begin
                        trip_low <= 0;
                    end
                    if(signed_data > thresholds[3]) begin
                        trip_high <= 1;
                        latched <=1;
                    end else if(signed_data < thresholds[2] & ~latched) begin
                        trip_high <= 0;
                    end    
                end
            end else begin
                if(data_in.valid) begin
                    if(signed_data < thresholds[0]) begin
                        trip_low <= 1;
                    end else if(signed_data > thresholds[1]) begin
                        trip_low <= 0;
                    end 
                    if(signed_data > thresholds[3]) begin
                        trip_high <=1;
                    end else if(signed_data < thresholds[2]) begin
                        trip_high <=0;
                    end
                end
            end
        end
    end



endmodule