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
`include "axis_BFM.svh"
`include "interfaces.svh"


module AdcProcessing_tb();

    reg  clk, reset;
    reg [31:0] sb_read_out;
    wire processed_fault;

    event configuration_done;
    axi_lite test_axi();
    
    axi_stream axis_bfm_if();

    assign processing_in.data = axis_bfm_if.data;
    assign processing_in.valid = axis_bfm_if.valid;
    assign axis_bfm_if.ready = processing_in.ready;

    axi_stream #(
        .DATA_WIDTH(16)
    ) processing_in ();
    axi_stream #(
        .DATA_WIDTH(16)
    ) processing_out();

    AdcProcessing #(
        .ENABLE_AVERAGE(1),
        .STICKY_FAULT(0)
    ) UUT (
        .clock(clk),
        .reset(reset),
        .data_in(processing_in),
        .data_out(processing_out),
        .fault(processed_fault),
        .axi_in(test_axi)
    );

    axi_lite_BFM axil_bfm;
    
    axis_BFM axis_BFM;

    reg [15:0] cal_gain = 1;
    reg [15:0] cal_offset = 5;
    reg signed [15:0] trip_high_f2 = 16'sd29000;
    reg signed [15:0] trip_high_f1 = 16'sd29000;
    reg signed [15:0] trip_low_f1 = -16'sd28999;
    reg signed [15:0] trip_low_f2 = -16'sd29000;

    reg signed [15:0] trip_high_s = 16'sd27000;
    reg signed [15:0] trip_low_s = -16'sd27000;

    //clock generation
    initial clk = 0; 
    always #0.5 clk = ~clk; 

    initial begin
        axis_BFM = new(axis_bfm_if,1);
        axil_bfm = new(test_axi,1);
        
        //Initial status
        reset <=1'h1;
        processing_out.ready <= 1;
        #1 reset <=1'h0;
        //TESTS
        #5.5 reset <=1'h1;
        //Comparators
        #1 axil_bfm.write(8'h00, {trip_low_s, trip_low_f2});
        #1 axil_bfm.write(8'h04, {trip_low_s, trip_low_f1});
        #1 axil_bfm.write(8'h08, {trip_high_s, trip_high_f1});
        #1 axil_bfm.write(8'h0C, {trip_high_s, trip_high_f2});
        //Calibration
        #1 axil_bfm.write(8'h10, {cal_gain, cal_offset});
        //CU
        #1 axil_bfm.write(8'h14, 32'h04010000);
        #1 ->configuration_done;
    end

    reg writer_started = 0;

    
    reg [19:0] accumulated_input = 0;
    integer uncalibrated_accumulator = 0;

    reg [15:0] input_data = 0;
    reg [3:0] input_counter = 0;
    initial begin
        @(configuration_done);
        forever begin
            #10;
            if(input_counter == 3) 
                input_counter = 0;
            else 
                input_counter = input_counter + 1;

            input_data = $urandom() % ((2<<15)-1);
            accumulated_input = $signed(accumulated_input) + $signed(input_data);
            uncalibrated_accumulator = $signed(uncalibrated_accumulator) + $signed(input_data);
            axis_BFM.write(input_data);
        end    
    end


    reg fast_trip_high;
    reg fast_trip_low;
    wire fast_fault;

    reg slow_trip_high;
    reg slow_trip_low;
    reg slow_fault;
   
    wire expected_fault;
    assign expected_fault = fast_fault || slow_fault;
    assign fast_fault = fast_trip_high || fast_trip_low;

    wire signed [15:0] fast_comp_in;
    assign fast_comp_in = $signed(processing_in.data);
    wire signed [15:0] slow_comp_in;
    assign slow_comp_in = $signed(uncalibrated_out);
    always_ff @(posedge clk) begin

        if(fast_trip_low) begin
            fast_trip_low <= fast_comp_in < trip_low_f1;
        end else begin
            fast_trip_low <= fast_comp_in < trip_low_f2;
        end
        
        fast_trip_high <= fast_comp_in > trip_high_f2;
        slow_trip_low <= slow_comp_in < trip_low_s;
        slow_trip_high <= slow_comp_in > trip_high_s;
        slow_fault <= slow_trip_high || slow_trip_low;
    end    


    reg [15:0] expected_out = 0;
    reg [15:0] uncalibrated_out = 0;

    initial begin
        @(configuration_done);
        forever begin
            @(posedge input_counter==0)
            #1;
            uncalibrated_out = uncalibrated_accumulator/4;
            #2;
            expected_out = ((accumulated_input>>>2) + cal_offset)*cal_gain;
            
            assert (expected_out==processing_out.data) 
            else begin
                $display("OUTPUT DATA ERROR: expected value %h | actual value %h", expected_out[15:0], processing_out.data[15:0]);
                $stop();
            end
            uncalibrated_accumulator = 0;
            accumulated_input = 0;
        end    
    end



    initial begin
        @(configuration_done);
        forever begin
            assert (expected_fault==processed_fault) 
            else begin
                $display("FAULT ERROR: Expected fault is different from fault output");
                $stop();
            end
            #1;
        end    
    end

    
endmodule