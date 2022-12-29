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
`include "axis_BFM.svh"

class axis_sync_tb_item;
    rand bit[31:0] data;
    rand bit[7:0] dest;
    rand bit[7:0] user;
    rand bit tlast;
endclass



module axis_sync_repeater_tb();

    reg  clk, reset, sync;
    axi_stream input_stream();
    axi_stream output_stream();
    //clock generation
    initial clk = 0; 
    always #0.5 clk = ~clk; 
    
    
     axis_sync_repeater #(
        .SYNC_DELAY(2),
        .DATA_WIDTH(32),
        .DEST_WIDTH(8),
        .USER_WIDTH(8)
     ) UUT (
        .clock(clk),
        .reset(reset),
        .sync(sync),
        .in(input_stream),
        .out(output_stream)
    );

    axis_BFM stream_bfm;
    
    initial begin : generate_sync
        sync = 0;
        #6.5;
        #70;
        forever begin
            sync <= 1;
            #1 sync <= 0;
            #100;
        end
    end 
    axis_sync_tb_item item;
    initial begin : apply_stimulus
        item = new();

        stream_bfm = new(input_stream,1);
        reset <=1'h1;
        output_stream.ready <= 1;
        #1 reset <=1'h0;
        //TESTS
        #5.5 reset <=1'h1;
        
        #100;

        forever begin
            item.randomize();
            stream_bfm.write_complete(item.data, item.dest, item.user, item.tlast, 0);
            #100;
        end

    end

    logic dbg = 0;

    initial begin
        #6.5;
        #101.5;
        forever begin
        valid_leakage_check:
        assert (output_stream.valid == 0)
        else begin
                $display("-------------------------------------------------------------------------------------");
                $display("%m");
                $display("-------------------------------------------------------------------------------------");
                $display("ERROR: UNSYNCHRONIZED VALID SIGNAL LEAKAGE DETECTED:");
                $display("-------------------------------------------------------------------------------------");
                $finish;
        end
        #101;
        end
        
    end 


    initial begin
        #6.5;
        #100;
        #71;
        forever begin
            idle_output_state:
            assert (output_stream.valid == 0)
            else begin
                    $display("-------------------------------------------------------------------------------------");
                    $display("%m");
                    $display("-------------------------------------------------------------------------------------");
                    $display("ERROR: OUTPUT STREAM NOT IN IDLE STATE BEFORE SYNC");
                    $display("-------------------------------------------------------------------------------------");
                    $finish;
            end
            #1.5;
            assert (output_stream.valid == 1)
            else begin
                    $display("-------------------------------------------------------------------------------------");
                    $display("EFFECTIVE SYNC CHECK");
                    $display("-------------------------------------------------------------------------------------");
                    $display("ERROR: OUTPUT STREAM OUTPUT NOT VALID UPON SYNC");
                    $display("-------------------------------------------------------------------------------------");
                    $finish;
            end

            data_correctness:
            assert (output_stream.data == item.data)
            else begin
                    $display("-------------------------------------------------------------------------------------");
                    $display("DATA_CORRECTNESS CHECK");
                    $display("-------------------------------------------------------------------------------------");
                    $display("ERROR: WRONG VALUE ON THE OUTPUT STREAM DATA CHANNEL");
                    $display("-------------------------------------------------------------------------------------");
                    $finish;
            end
            
            dest_correctness:
            assert (output_stream.dest == item.dest)
            else begin
                    $display("-------------------------------------------------------------------------------------");
                    $display("DEST CORRECTNESS CHECK");
                    $display("-------------------------------------------------------------------------------------");
                    $display("ERROR: WRONG VALUE ON THE OUTPUT STREAM DEST CHANNEL");
                    $display("-------------------------------------------------------------------------------------");
                    $finish;
            end

            user_correctness:
            assert (output_stream.user == item.user)
            else begin
                    $display("-------------------------------------------------------------------------------------");
                    $display("USER CORRECTNESS CHECK");
                    $display("-------------------------------------------------------------------------------------");
                    $display("ERROR: WRONG VALUE ON THE OUTPUT STREAM USER CHANNEL");
                    $display("-------------------------------------------------------------------------------------");
                    $finish;
            end

            tlast_correctness:
            assert (output_stream.user == item.user)
            else begin
                    $display("-------------------------------------------------------------------------------------");
                    $display("TLAST CORRECTNESS CHECK");
                    $display("-------------------------------------------------------------------------------------");
                    $display("ERROR: WRONG VALUE ON THE OUTPUT STREAM TLAST CHANNEL");
                    $display("-------------------------------------------------------------------------------------");
                    $finish;
            end

        #99.5;
        end
        
    end 


endmodule