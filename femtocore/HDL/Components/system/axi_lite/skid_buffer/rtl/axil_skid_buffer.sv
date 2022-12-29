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

module axil_skid_buffer #(
    parameter REGISTER_OUTPUT = 1,
    parameter DATA_WIDTH = 32
) (
    input wire clock,
    input wire reset,
    input wire in_valid,
    output wire in_ready,
    input wire [DATA_WIDTH-1:0] in_data,
    output wire out_valid,
    input wire out_ready,
    output reg [DATA_WIDTH-1:0] out_data
);


    // If the output is stalled the input needs to be temporarily saved in the skid buffer;

    wire input_data_available;
    assign input_data_available = in_valid && in_ready;
    wire output_stalled;
    assign output_stalled = out_valid && !out_ready;

    reg input_skidding = 0;

    always_ff @(posedge clock) begin
        if (~reset) begin
            input_skidding <= 0;
        end else if (input_data_available && output_stalled) begin
            input_skidding <= 1;
        end else if (out_ready) begin
            input_skidding <= 0;
        end
    end
    

    reg registered_ready_reset;

    always_ff @(posedge clock) begin
        registered_ready_reset <= reset;
    end

    assign in_ready = registered_ready_reset & !input_skidding;

    reg	[DATA_WIDTH-1:0] data_buffer = 0;

    // manage buffer
    always_ff @(posedge clock) begin
        if (~reset) begin
            data_buffer <= 0;
        end else if(in_ready) begin
            data_buffer <= in_data;
        end
    end

    generate
        if (!REGISTER_OUTPUT ) begin
            // Outputs are combinatorially determined from inputs
            assign	out_valid = reset && (in_valid || input_skidding);
    
            always_comb begin
                if (input_skidding) begin
                    out_data = data_buffer;
                end else if(in_valid) begin
                    out_data = in_data;
                end else begin
                    out_data = 0;    
                end
            end
            
        end else begin
            // Register our outputs
            reg	registerd_valid = 0;
    
            always_ff @(posedge clock) begin
                if (~reset) begin
                    registerd_valid <= 0;
                end if (!out_valid || out_ready) begin
                    registerd_valid <= (in_valid || input_skidding); 
                end
            end
            
            assign	out_valid = registerd_valid;
    
            always_ff @(posedge clock) begin
                if (~reset) begin
                    out_data <= 0;
                end else if (!out_valid || out_ready) begin
                    if (input_skidding) begin
                        out_data <= data_buffer;
                    end else begin
                        out_data <= in_data;
                    end
                end
            end
           
        end
    endgenerate

endmodule