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

module phase_reconstructor #(parameter N_PHASES = 6, MISSING_PHASE = 6, DATA_PATH_WIDTH = 16, TARGET_ADDRESS = 0)(
    input wire clock,
    input wire reset,
    input wire enable,
    axi_stream.slave phases_in,
    axi_stream.master phases_out
);

    enum reg [1:0] {
        wait_data = 0,
        calculate = 1,
        wait_last = 2
    } state;

    reg[$clog2(N_PHASES)-1:0] phases_counter;
    reg [2*DATA_PATH_WIDTH-1:0] phases_data_acc;
    
    // Determine the next state
    always @ (posedge clock) begin : control_state_machine
        if (~reset) begin
            phases_in.ready <= 1;
            phases_data_acc <= 0;
            phases_out.data <= 0;
            phases_out.dest <= 0;
            phases_out.valid <= 0;
            phases_counter <= 0;
            state <= wait_data;
        end else begin
            if(~enable)begin
                case (state)
                wait_data:begin
                    phases_out.valid <= 0;
                    if(phases_in.valid)begin
                        phases_data_acc <= phases_data_acc + phases_in.data[31:0];
                        phases_out.data <= phases_in.data;
                        phases_out.dest <= phases_in.dest;
                        phases_out.valid <= 1;
                        phases_counter <= phases_counter + 1;
                   end
                   if(phases_counter == N_PHASES-1)begin
                            phases_counter <= 0;
                            state <= calculate;
                    end
                end 
                calculate:begin
                    phases_out.data <= {TARGET_ADDRESS, 3*(2**DATA_PATH_WIDTH-1)-phases_data_acc};
                    phases_out.dest <= MISSING_PHASE-1;
                    phases_out.valid <= 1;
                    phases_data_acc <= 0;
                    state <= wait_last;
                end
                wait_last:begin
                    phases_out.valid <= 0;
                    if(phases_in.valid)begin
                        state <= wait_data;
                    end
                end
                endcase
            end else begin
                phases_out.data <= phases_in.data;
                phases_out.dest <= phases_in.dest;
                phases_out.valid <= phases_in.valid;
            end
            
        end
    end  

endmodule