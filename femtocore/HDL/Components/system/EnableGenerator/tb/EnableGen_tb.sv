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
module EnableGen_tb();
    
    logic clk, rst;
    logic gen_en;
    wire en_out;

    //clock generation
    initial clk = 1; 
    always #0.5 clk = ~clk; 
    
    // reset generation
    initial begin
        rst <=1;
        #3 rst<=0;
        #5 rst <=1;
    end

    axi_lite axil();


    enable_generator gen(
        .clock(clk),
        .reset(rst),
        .ext_timebase(0),
        .gen_enable_in(gen_en),
        .enable_out(en_out),
        .axil(axil)
    );
    
    axi_lite_BFM axi_bfm;
    reg [31:0] period;

    initial begin
        //INITIAL SETTINGS AND INSTANTIATIONS OF CLASSES
        axi_bfm = new(axil,1);
        gen_en = 0;
        period = 'h10;
        #10 axi_bfm.write(32'h4, period);
        #3 axi_bfm.write(32'h8,32'h4);
        #5 gen_en =1;
        #2000 
        period = 'h20;
        axi_bfm.write(32'h4, period);
        #100 axi_bfm.write(32'h8,32'h10);
    end
    
    reg [31:0] check_counter = 0;

    always_ff @(posedge clk) begin
        if(gen_en)begin
            check_counter <= check_counter + 1;    
        end
    end

    reg [31:0] expected_period = 0;

    initial begin
        expected_period <= 'h10;
        #2130;
        expected_period = 43;
        #30;
        expected_period = 'h20;
    end

    reg initialized_checker = 0;
    reg [31:0] prev_check_counter = 0;
    
    wire [31:0] current_period;
    assign current_period = check_counter - prev_check_counter;


    always @(posedge en_out) begin
        if(check_counter % 4 != 0) begin
            $error("Wrong enable output phase");
        end

        if(!initialized_checker) begin
            initialized_checker <= 1;
        end else begin
            if(expected_period == period)begin
                if(prev_check_counter != check_counter-expected_period) begin
                    $error("Wrong enable output period");
                end    
            end
            
        end
        prev_check_counter <= check_counter;
    end

endmodule