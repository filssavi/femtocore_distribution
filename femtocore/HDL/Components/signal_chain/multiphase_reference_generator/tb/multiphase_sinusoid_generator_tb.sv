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
`include "axi_lite_BFM.svh"
`include "interfaces.svh"

module multiphase_sinusoid_generator_tb();
    
    reg [15:0] Ia;
    reg [15:0] Ib;
    reg [15:0] Ic;
    reg [15:0] Id;
    reg [15:0] Ie;
    reg [15:0] If; 

    localparam N_PHASES = 6;

    axi_lite axil();
    axi_lite_BFM axil_bfm;

    axi_stream phase();
    axi_stream #(
        .DATA_WIDTH(16)
    ) currents();
    axi_stream angle_out();
    reg clk, reset;

    reg timing_test;
    integer frequency;
    reg [15:0] phase_accumulator;
    reg [15:0] iq;

    reg [15:0] phase_shifts [N_PHASES-1:0];
    reg sync;

    multiphase_reference_generator UUT(
        .clock(clk),
        .reset(reset),
        .phase(phase),
        .sync(sync),
        .Id(100),
        .Iq(iq),
        .angle_out(angle_out),
        .reference_out(currents),
        .phase_shifts(phase_shifts),
        .axil(axil)
    );
    //clock generation
    initial clk = 0; 
    always #0.5 clk = ~clk; 

    initial begin  
        phase.valid = 0;
        phase.data = 0;
        phase_shifts = '{0, 4000, 8000, 12000, 16000, 20000};
        iq = 0;
        axil_bfm = new(axil,1);
        phase_accumulator <= 0;
        frequency = 1;
        //Initial status
        reset <=1'h1;
        #10 reset <=1'h0;
        //TESTS
        #20.5 reset <=1'h1;

        #2000000 iq = 200;
        //#100000 frequency = 3;
    end

    reg [31:0] sync_counter = 0;

    always_ff @(posedge clk) begin
        
        if(sync_counter == 30)begin
            sync_counter <= 0;
            sync <= 1;
        end else begin
            sync <= 0;
            sync_counter <= sync_counter +1;
        end

    end


    initial begin
        #35.5
        forever begin
        phase.data = frequency*(phase_accumulator)%16'hffff;
        phase.valid = 1;
        phase_accumulator = phase_accumulator+1;
        #1 phase.valid = 0;
        #2;
        end
    end

    always @(posedge clk) begin
        if(currents.valid)begin
            case (currents.dest)
                0: Ia <= currents.data;
                1: Ib <= currents.data;
                2: Ic <= currents.data;
                3: Id <= currents.data;
                4: Ie <= currents.data;
                5: If <= currents.data;
            endcase
        end
    end

endmodule