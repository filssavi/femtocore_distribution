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

							
module FP_saturator_tb();


    reg pos_pos_test = 0;
    event positive_positive_sat;
    reg pos_neg_test = 0;
    event positive_negative_sat;
    reg neg_neg_test = 0;
    event negative_negative_sat;

    reg  clk, reset;
    axi_stream operation();
    axi_stream operation2();
    axi_stream result();
    axi_stream result2();

    //clock generation
    initial clk = 0; 
    always #0.5 clk = ~clk; 
    

    real operand;
    real saturation;
    real saturation2;
    real final_result;

    wire [31:0] op_a;
    wire [31:0] op_b;
    wire [31:0] op_b2;

    FP_saturator #(
        .DATA_WIDTH(32),
        .REG_ADDR_WIDTH(4)
    ) UUT(
        .clock(clk),
        .reset(reset),
        .operand_a(op_a),
        .operand_b(op_b),
        .operation(operation),
        .result(result)
    );


    FP_saturator #(
        .DATA_WIDTH(32),
        .REG_ADDR_WIDTH(4)
    ) UUT2(
        .clock(clk),
        .reset(reset),
        .operand_a(result.data),
        .operand_b(op_b2),
        .operation(operation2),
        .result(result2)
    );


    assign op_a = $shortrealtobits(operand);
    assign op_b = $shortrealtobits(saturation);
    assign op_b2 = $shortrealtobits(saturation2);
    assign final_result = $bitstoshortreal(result2.data);
    initial begin
        reset <=1'h1;
        operation.dest <= 6;
        operation2.dest <= 6;
        #1 reset <=1'h0;
        //TESTS
        #5.5 reset <=1'h1;

        #10 ->positive_positive_sat;
        #4 pos_pos_test <= 1;
        #1000;
        disable positive_positive_gen;
        operation.valid <= 0;
        operation2.valid <= 0;
        #2 pos_pos_test <= 0;

        #1000 ->positive_negative_sat;
        #4 pos_neg_test <= 1;
        #1000;
        disable positive_negative_gen;
        operation.valid <= 0;
        operation2.valid <= 0;
        #2 pos_neg_test <= 0;

        #1000 ->negative_negative_sat;
        #4 neg_neg_test <= 1;
        #1000;
        disable negative_negative_gen;   
        operation.valid <= 0;
        operation2.valid <= 0;
        #2 neg_neg_test <= 0;



    end

    property pos_pos_assert;
        @(posedge clk) 
        disable iff (~pos_pos_test) (final_result >= 4.0) && (final_result <= 24.0);
    endproperty

    assert property (pos_pos_assert);

    initial begin : positive_positive_gen
        @(positive_positive_sat);
            saturation <= 24.0;
            saturation2 <= 4.0;
        forever begin
            operand <= ($random() % 1000)*0.0547;
            operation.data <= 1;
            operation2.data <= 0;
            operation2.user <= result.user;
            operation.user <= $urandom % 15;
            operation.valid <= 1;
            operation2.valid <= 1;
            #1 operation.valid <= 0;
            operation2.valid <= 0;
        end
    end
    
    property pos_neg_assert;
        @(posedge clk) 
        disable iff (~pos_neg_test) (final_result >= -24.0) && (final_result <= 24.0);
    endproperty

    assert property (pos_neg_assert);

    initial begin : positive_negative_gen
        @(positive_negative_sat);
            saturation <= 24.0;
            saturation2 <= -24.0;
        forever begin
            operand <= ($random() % 1000)*0.0547;
            operation.data <= 1;
            operation2.data <= 0;
            operation2.user <= result.user;
            operation.user <= $urandom % 15;
            operation.valid <= 1;
            operation2.valid <= 1;
            #1 operation.valid <= 0;
            operation2.valid <= 0;
        end
    end


    property neg_neg_assert;
        @(posedge clk) 
        disable iff (~neg_neg_test) (final_result >= -24.0) && (final_result <= -4.0);
    endproperty

    assert property (neg_neg_assert);

    initial begin : negative_negative_gen
        @(negative_negative_sat);
            saturation <= -4.0;
            saturation2 <= -24.0;
        forever begin
            operand <= ($random() % 1000)*0.0547;
            operation.data <= 1;
            operation2.data <= 0;
            operation2.user <= result.user;
            operation.user <= $urandom % 15;
            operation.valid <= 1;
            operation2.valid <= 1;
            #1 operation.valid <= 0;
            operation2.valid <= 0;
        end
    end


endmodule