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
`include "axis_BFM.svh"


parameter max_data_length = 256;

parameter clock_period = 0.5;

class axis_item;
    rand bit[15:0] data;
    rand bit[15:0] dest;
    rand bit[15:0] user;    
endclass


module merge_sorter_tb ();

    timeunit 10ns;
    timeprecision 100ps;

    reg clock, reset, start;
    integer data_length = 0;
    event test_start;

    reg [15:0] data_in[max_data_length-1:0];
    reg [15:0] dest_in[max_data_length-1:0];
    reg [15:0] user_in[max_data_length-1:0];

    reg [15:0] data_out[];
    reg [15:0] dest_out[];
    reg [15:0] user_out[];

    axi_stream #(.DATA_WIDTH(16), .DEST_WIDTH(16), .USER_WIDTH(16)) sorter_in();
    axi_stream #(.DATA_WIDTH(16), .DEST_WIDTH(16), .USER_WIDTH(16)) sorter_out();

    

    axis_BFM#(16, 16, 16) in_bfm;
    
    merge_sorter #(
        .DATA_WIDTH(16),
        .DEST_WIDTH(16),
        .USER_WIDTH(16),
        .MAX_SORT_LENGTH(256)
    )UUT(
        .clock(clock),
        .reset(reset),
        .start(start),
        .data_length(data_length),
        .input_data(sorter_in),
        .output_data(sorter_out)
    );


    task read_sorted_results(
        input int length,
        output reg [15:0] data_out[],
        output reg [15:0] dest_out[],
        output reg [15:0] user_out[]
    );
        sorter_out.ready = 1;

        data_out = new[length];
        dest_out = new[length];
        user_out = new[length];

        for(int k = 0; k < max_data_length; k = k + 1) begin
            data_out[k] = 0;
            dest_out[k] = 0;
            user_out[k] = 0;
        end
        
        @(posedge sorter_out.valid)
        for(int x = 0; x < length; x = x + 1) begin
            @(negedge clock);
            data_out[x] = sorter_out.data;
            dest_out[x] = sorter_out.dest;
            user_out[x] = sorter_out.user;
            @(posedge clock);
        end
    endtask

    reg [15:0] data_expected[];
    reg [15:0] dest_expected[];
    reg [15:0] user_expected[];


    task check_result(
        input int length,
        axis_item input_data[max_data_length],
        input reg [15:0] data_out[],
        input reg [15:0] dest_out[],
        input reg [15:0] user_out[]
    );
    
        axis_item working_data[];
        reg [15:0] unique_data [$];

        working_data = new[length];

        data_expected = new [length];
        dest_expected = new [length];
        user_expected = new [length];

        for(int i = 0; i<length; i++)begin
            working_data[i] = input_data[i];
        end

        working_data.sort() with (item.data);

        for(int i = 0; i<length; i++)begin
            data_expected[i] = working_data[i].data;
            dest_expected[i] = working_data[i].dest;
            user_expected[i] = working_data[i].user;
        end
        
        

        data_sorting_check:
        assert (data_expected == data_out)
        else begin
            $display("-------------------------------------------------------------------------------------");
            $display("%m");
            $display("-------------------------------------------------------------------------------------");
            $display("Expected:");
            for(int j = 0; j < length; j = j + 1) begin
                $display(" %h", data_expected[j]);
            end
            $display("Got:");
            for(int j = 0; j < length; j = j + 1) begin
                $display(" %h", data_out[j]);
            end
            $display("-------------------------------------------------------------------------------------");
            $finish;
        end

        unique_data = data_expected.unique();

        dest_passthrough_check:
        assert (dest_expected == dest_out)
        else begin
            if(unique_data.size() ==length)begin // avoid checking if there are duplicates because the sorting is not stable
                $display("-------------------------------------------------------------------------------------");
                $display("%m");
                $display("-------------------------------------------------------------------------------------");
                $display("Expected:");
                for(int j = 0; j < length; j = j + 1) begin
                    $display(" %h", dest_expected[j]);
                end
                $display("Got:");
                for(int j = 0; j < length; j = j + 1) begin
                    $display(" %h", dest_out[j]);
                end
                $display("-------------------------------------------------------------------------------------");
                $finish;
            end
        end
        
        user_passthrough_check:
        assert (user_expected == user_out)
        else begin
            if(unique_data.size() ==length)begin // avoid checking if there are duplicates because the sorting is not stable
                $display("-------------------------------------------------------------------------------------");
                $display("%m");
                $display("-------------------------------------------------------------------------------------");
                $display("Expected:");
                for(int j = 0; j < length; j = j + 1) begin
                    $display(" %h", user_expected[j]);
                end
                $display("Got:");
                for(int j = 0; j < length; j = j + 1) begin
                    $display(" %h", user_out[j]);
                end
                $display("-------------------------------------------------------------------------------------");
                $finish;
            end
        end
        
    endtask



    initial clock = 0;
    always #clock_period clock = ~clock;


    initial begin
        for(int j = 0; j < max_data_length; j = j + 1) begin
            data_in[j] = 0;
        end
    end



    initial begin
        reset = 0;
        start = 0;
        sorter_out.ready = 1;
        in_bfm = new(sorter_in, 2*clock_period);
        #20 reset = 0;
        #clock_period;
        #20 reset = 1;

        ->test_start;
        forever begin
            axis_item item[max_data_length];

            foreach(item[i])begin
                item[i] = new();
                item[i].randomize();
            end

            data_length = $urandom_range('hff,'hf);
            //data_length = 15;

            for(int i = 0; i < data_length; i = i + 1) begin
                if(i == 0) begin
                    start = 1;
                end else begin
                    start = 0;
                end
                in_bfm.write_du(item[i].data, item[i].dest, item[i].user);
            end

            read_sorted_results(data_length, data_out, dest_out, user_out);

            #1 check_result(data_length, item, data_out, dest_out, user_out);
            #200;
        end
    end





endmodule