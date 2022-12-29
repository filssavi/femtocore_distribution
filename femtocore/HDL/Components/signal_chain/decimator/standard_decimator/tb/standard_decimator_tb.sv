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
`include "SPI_BFM.svh"

module standard_decimator_tb();

    axi_stream #(
        .DATA_WIDTH(16)
    ) data_in();
    axi_stream #(
        .DATA_WIDTH(16)
    ) data_out();
    reg clk, reset;

    //clock generation
    initial clk = 0; 
    always #0.5 clk = ~clk; 

    task automatic send_data(input signed [31:0] data);
        data_in.data <= data;
        data_in.dest <= 3;
        data_in.valid <= 1;
        #1 data_in.valid <= 0;
    endtask //automatic

    standard_decimator #(
        .MAX_DECIMATION_RATIO(16),
        .MAX_CHANNELS(6),
        .DATA_WIDTH(16),
        .AVERAGING(1)
    ) UUT (
        .clock(clk),
        .reset(reset),
        .data_in(data_in),
        .data_out(data_out),
        .decimation_ratio(4)
    );

    initial begin  
        data_in.valid = 0;
        data_in.data = 0;
        //Initial status
        reset <=1'h1;
        #10 reset <=1'h0;
        #5 reset <= 1;

        #5.5;

        //TESTS
        send_data(-10);
        send_data(-7);
        send_data(-3);
        send_data(4);
        
        #10 send_data(16'h7fff);
        send_data(16'h7fff);
        send_data(16'h7fff);
        send_data(16'h7fff);

        #10 send_data(16'h8000);
        send_data(16'h8000);
        send_data(16'h8000);
        send_data(16'h8000);
    end


endmodule