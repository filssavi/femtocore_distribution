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

module axis_data_mover #(
    parameter DATA_WIDTH = 32,
    ADDRESS_WIDTH = 32,
    CHANNEL_NUMBER=1,
    parameter [ADDRESS_WIDTH-1:0] SOURCE_ADDR [CHANNEL_NUMBER-1:0] = '{CHANNEL_NUMBER{{ADDRESS_WIDTH{1'b0}}}},
    parameter [ADDRESS_WIDTH-1:0] TARGET_ADDR [CHANNEL_NUMBER-1:0] = '{CHANNEL_NUMBER{{ADDRESS_WIDTH{1'b0}}}}
)(
    input wire clock,
    input wire reset,
    input wire start,
    axi_stream.master data_request,
    axi_stream.slave data_response,
    axi_stream.master data_out
);

reg mover_active;
reg [$clog2(CHANNEL_NUMBER)-1:0] channel_sequencer;

enum reg [1:0] { 
    idle = 0, 
    read_source = 1,
    wait_response = 2
} sequencer_state;

always_ff @(posedge clock) begin
    if(!reset) begin
        data_response.ready <= 1;
        data_out.valid <= 0;
        data_request.data <= 0;
        data_request.valid <= 0;
        data_out.data <= 0;
        data_out.dest <= 0;
        channel_sequencer <= 0;
        mover_active <= 0;
        sequencer_state <= idle;
    end else begin
        data_out.valid <= 0;
        data_request.valid <= 0; 
        case (sequencer_state)
            idle :begin
                if(start) begin
                    sequencer_state <= read_source;
                end
            end 
            read_source: begin
                data_request.data <= SOURCE_ADDR[channel_sequencer];
                data_request.valid <= 1;  
                sequencer_state <= wait_response;
            end
            wait_response: begin
                if(data_response.valid)begin
                    data_out.data <= data_response.data;
                    data_out.dest <= TARGET_ADDR[channel_sequencer];
                    data_out.valid <= data_response.valid;
                    if(channel_sequencer == CHANNEL_NUMBER-1)begin
                        channel_sequencer <= 0;
                        sequencer_state <= idle;
                    end else begin
                        channel_sequencer <= channel_sequencer + 1;
                        sequencer_state <= read_source;
                    end
                end
            end
        endcase
    end
end

endmodule