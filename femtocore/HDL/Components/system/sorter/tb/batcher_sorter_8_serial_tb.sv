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


class batcher_sorter_serial_stimulus;
    rand bit[15:0] length;
    rand bit[31:0] data[150:0];
    constraint length_bounds {length>8 && length<150;}
endclass

module batcher_sorter_8_serial_tb ();

    reg clock, reset, start;
    integer data_length = 24;

    parameter max_data_length = 150;
    reg [15:0] data_in[max_data_length-1:0];
    reg [15:0] data_out[];

    axi_stream #(.DATA_WIDTH(16)) sorter_in();
    axi_stream sorter_out();

    reg [15:0] chunk_size = 0;


    axis_BFM#(16, 32, 32) in_bfm;
        
    batcher_sorter_8_serial #(
        .DATA_WIDTH(16)
    )UUT(
        .clock(clock),
        .chunk_size(chunk_size),
        .data_in(sorter_in),
        .data_out(sorter_out)
    );

    task read_sorted_results(input int length, output reg [15:0] data_out[]);
        integer output_length;
        output_length = 0;
        sorter_out.ready = 1;
        data_out = new[length];
        for(int k = 0; k < max_data_length; k = k + 1) begin
            data_out[k] = 0;
        end

        @(posedge sorter_out.valid);
        while(sorter_out.valid==1) begin
            @(negedge clock);
            if(output_length<length)begin
                data_out[output_length] = sorter_out.data;
            end
            output_length +=1;
            @(posedge clock);
        end
        output_length = output_length-1;
        result_length_check:
        assert (output_length == length)
        else begin
            $display("-------------------------------------------------------------------------------------");
            $display("%m");
            $display("-------------------------------------------------------------------------------------");
            $display("Error, the sorter input was %d words long, the output was %d instead", length, output_length);
            $display("-------------------------------------------------------------------------------------");
        end

    endtask

    task check_result(input int length, input reg [15:0] data_in[max_data_length-1:0], input reg [15:0] data_out[]);
        reg [31:0] result_buf [];
        reg [31:0] sort_buf [];
        int n_full_chunks, last_chunk_size;
        sort_buf = new[8];
        result_buf = new[8];


        n_full_chunks = length/8;
        last_chunk_size = length%8;
        
        for(int i = 0; i < n_full_chunks; i = i + 1) begin
            for(int j = 0; j < 8; j = j + 1) begin
                sort_buf[j] = data_in[i*8+j];
                result_buf[j] = data_out[i*8+j];
            end
            sort_buf.sort();

            full_chunks_sorting_check:
            assert (sort_buf == result_buf)
            else begin
            
            $display("-------------------------------------------------------------------------------------");
            $display("%m");
            $display("-------------------------------------------------------------------------------------");
            $display("Error in chunk %d", i+1);
            $display("-------------------------------------------------------------------------------------");
            $display("Expected:");
            for(int j = 0; j < 8; j = j + 1) begin
                $display(" %h", sort_buf[j]);
            end
            $display("Got:");
            for(int j = 0; j < 8; j = j + 1) begin
                $display(" %h", result_buf[j]);
            end
            $display("-------------------------------------------------------------------------------------");
            $finish;
            end
        end

        if(last_chunk_size != 0)begin
            sort_buf = new[last_chunk_size];
            result_buf = new[last_chunk_size];
            

            for(int j = 0; j < last_chunk_size; j = j + 1) begin
                sort_buf[j] = data_in[n_full_chunks*8+j];
                result_buf[j] = data_out[n_full_chunks*8+j];
            end
            sort_buf.sort();

            last_chunks_sorting_check:
            assert (sort_buf == result_buf)
            else begin

                $display("-------------------------------------------------------------------------------------");
                $display("%m");
                $display("-------------------------------------------------------------------------------------");
                $display("Error in last chunk");
                $display("-------------------------------------------------------------------------------------");
                $display("Expected:");
                for(int j = 0; j < last_chunk_size; j = j + 1) begin
                    $display("%d --- %h", j, sort_buf[j]);
                end
                $display("Got:");
                for(int j = 0; j < last_chunk_size; j = j + 1) begin
                    $display("%d --- %h", j, result_buf[j]);
                end
                $display("-------------------------------------------------------------------------------------");
                $finish;
            end
        end
        

    endtask



    initial clock = 0;
    always #0.5 clock = ~clock;


    initial begin
        for(int j = 0; j < max_data_length; j = j + 1) begin
            data_in[j] = 0;
        end
    end


    event data_in_started;
    event check_done;

    integer data_length = 0;
    batcher_sorter_serial_stimulus stim = new();

    initial begin
        reset = 0;
        start = 0;
        chunk_size <= 8;
        sorter_out.ready = 1;
        in_bfm = new(sorter_in, 1);
        #20.5 reset = 0;
        #20 reset = 1;
        
        data_length = 22;

        forever begin
            stim.randomize();
            data_in = stim.data;
            data_length = stim.length;
            ->data_in_started;
            
            for(int i = 0; i <data_length; i = i + 1) begin
                if(i == 0) begin
                    start = 1;
                end else begin
                    start = 0;
                end

                if(data_length%8 != 0)begin
                    if(i<(data_length/8)*8) begin
                        chunk_size <= 8;
                        in_bfm.write(data_in[i]);
                    end else begin
                       chunk_size <= data_length%8;
                        in_bfm.write(data_in[i]);
                    end
                end else begin
                    chunk_size <= 8;
                    in_bfm.write(data_in[i]);
                end

            end
            @(check_done);
            #35;
        end
    end

    always begin
        @(data_in_started);
        read_sorted_results(data_length, data_out);
        #1 check_result(data_length, data_in, data_out);
        ->check_done;
    end



endmodule