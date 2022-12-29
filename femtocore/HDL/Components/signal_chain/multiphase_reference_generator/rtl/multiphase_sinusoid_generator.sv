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

module multiphase_sinusoid_generator #(parameter N_PHASES=6, BASE_ADDRESS='h43c00000, DATA_WIDTH=16)(
    input wire clock,
    input wire reset,
    input wire [DATA_WIDTH-1:0] phase_shifts [N_PHASES-1:0],
    axi_stream.slave phase,
    axi_stream.master sin_out,
    axi_stream.master cos_out
);

    reg [DATA_WIDTH-1:0] latched_phase;
    reg[$clog2(N_PHASES)-1:0] phase_in_counter;
    reg[$clog2(N_PHASES)-1:0] phase_out_counter;
    reg [N_PHASES-1:0] lut_enable;
    reg start_output_fsm;
    
    axi_stream #(
        .DATA_WIDTH(DATA_WIDTH)
    ) theta [N_PHASES]();
    axi_stream sin [N_PHASES]();
    axi_stream cos [N_PHASES]();

    axi_stream #(
        .DATA_WIDTH(DATA_WIDTH)
    ) sin_out_n();
    axi_stream #(
        .DATA_WIDTH(DATA_WIDTH)
    ) cos_out_n();

    logic [DATA_WIDTH-1:0] cos_out_data_flat [N_PHASES-1:0];
    logic [DATA_WIDTH-1:0] cos_out_dest_flat [N_PHASES-1:0];
    logic [N_PHASES-1:0] cos_out_valid_flat;

    reg [DATA_WIDTH-1:0] cos_out_dest;
    reg [DATA_WIDTH-1:0] cos_out_data;
    reg cos_out_valid;
    
    logic [DATA_WIDTH-1:0] sin_out_data_flat [N_PHASES-1:0];
    logic [DATA_WIDTH-1:0] sin_out_dest_flat [N_PHASES-1:0];
    logic [N_PHASES-1:0] sin_out_valid_flat;

    reg [DATA_WIDTH-1:0] sin_out_dest;
    reg [DATA_WIDTH-1:0] sin_out_data;
    reg sin_out_valid;

    generate
        genvar i;
        for (i = 0; i<N_PHASES; i= i+1) begin
            assign theta[i].data = (latched_phase+phase_shifts[i]);
            assign theta[i].valid = lut_enable[i];
            assign theta[i].dest = i;
            SinCosLUT cos_LUTn(
                .clock(clock),
                .reset(reset),
                .theta(theta[i]),
                .cos(cos[i]),
                .sin(sin[i])
            ); 
            assign cos_out_data_flat[i] = cos[i].data;
            assign cos_out_dest_flat[i] = cos[i].dest;
            assign cos_out_valid_flat[i] = cos[i].valid;

            assign sin_out_data_flat[i] = sin[i].data;
            assign sin_out_dest_flat[i] = sin[i].dest;
            assign sin_out_valid_flat[i] = sin[i].valid;
        
        end
    endgenerate

    always_comb begin
        cos_out_data = 0;
        cos_out_dest = 0;
        cos_out_valid = 0;
        
        sin_out_data = 0;
        sin_out_dest = 0;
        sin_out_valid = 0;
        for (integer j = 0; j<N_PHASES; j= j+1) begin
            cos_out_data |= cos_out_data_flat[j];
            cos_out_dest |= cos_out_dest_flat[j];
            cos_out_valid |= cos_out_valid_flat[j];

            sin_out_data |= sin_out_data_flat[j];
            sin_out_dest |= sin_out_dest_flat[j];
            sin_out_valid |= sin_out_valid_flat[j];
        end
    end


    always_ff @(posedge clock)begin 
        cos_out.data <= cos_out_data;
        cos_out.dest <= cos_out_dest;
        cos_out.valid <= cos_out_valid;
        
        sin_out.data <= sin_out_data;
        sin_out.dest <= sin_out_dest;
        sin_out.valid <= sin_out_valid;
    end

    enum reg {
        input_idle_state = 0,
        input_working_state = 1
    } input_state;

    always_ff @(posedge clock)begin : lut_input_fsm
        if(~reset)begin
            phase.ready <= 1;
            latched_phase <= 0;
            start_output_fsm<=0;
            input_state <= input_idle_state;
            phase_in_counter <= 0;
        end else begin
            lut_enable <= 0;
            case (input_state)
                input_idle_state: begin
                   if(phase.valid)begin
                       input_state <= input_working_state;
                       latched_phase <= phase.data;
                   end 
                end
                input_working_state: begin
                    lut_enable[phase_in_counter] <= 1;
                    if(phase_in_counter==1)start_output_fsm<=0;
                    else start_output_fsm <= 0;
                    if(phase_in_counter == N_PHASES-1)begin
                        phase_in_counter <= 0;
                        input_state <= input_idle_state;
                    end else begin
                        phase_in_counter <= phase_in_counter+1;
                    end
                end
            endcase
        end
    end


endmodule