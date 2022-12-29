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

`timescale 10 ns/100ps

`include "axis_BFM.svh"
`include "interfaces.svh"

module phase_reconstructor_tb();


    reg clk, reset;
    axi_stream in();
    axi_stream out();

    axis_BFM BFM;

    phase_reconstructor #(
        .N_PHASES(6),
        .MISSING_PHASE(6),
        .DATA_PATH_WIDTH(16)
    ) UUT (
        .clock(clk),
        .reset(reset),
        .phases_in(in),
        .phases_out(out)
    );

    //clock generation
    initial clk = 0; 
    always #0.5 clk = ~clk; 

    initial begin  
        BFM = new(in,1);
        //Initial status
        reset <=1'h1;
        #1 reset <=1'h0;
        //TESTS
        #5.5 reset <=1'h1;

        #35 BFM.write_dest(63938, 0);
        #2 BFM.write_dest(57105, 1);
        #2 BFM.write_dest(25935, 2);
        #2 BFM.write_dest(1597, 3);
        #2 BFM.write_dest(8430, 4);
    end
    

    
endmodule