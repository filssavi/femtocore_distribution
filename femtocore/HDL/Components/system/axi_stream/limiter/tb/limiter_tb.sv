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
							
module axis_limiter_tb();

    reg  clk, reset;
    axi_stream input_stream();
    axi_stream output_stream();

    //clock generation
    initial clk = 0; 
    always #0.5 clk = ~clk; 
    
    axi_lite axil();

    axis_BFM write_BFM;
    axis_BFM read_req_BFM;
    axis_BFM read_resp_BFM;

    axi_stream read_req();
    axi_stream read_resp();
    axi_stream write();

    axis_to_axil WRITER(
        .clock(clk),
        .reset(reset), 
        .axis_write(write),
        .axis_read_request(read_req),
        .axis_read_response(read_resp),
        .axi_out(axil)
    );
    
    axis_limiter #(
        .BASE_ADDRESS('h43c00000)
    ) UUT (
        .clock(clk),
        .reset(reset),
        .in(input_stream),
        .out(output_stream),
        .axi_in(axil)
    );
    event start_checking;
    axis_BFM stream_bfm;

    reg [31:0] input_data[6:0] = '{$urandom%120, $urandom%120, $urandom%120, $urandom%120, 4, 50, 1000};
    reg [31:0] output_data[6:0];

    integer limit_low = 20;
    integer limit_high = 100;
    initial begin
        write_BFM = new(write,1);
        read_req_BFM = new(read_req, 1);
        read_resp_BFM = new(read_resp, 1);
        stream_bfm = new(input_stream,1);
        reset <=1'h1;
        #1 reset <=1'h0;
        //TESTS
        #5.5 reset <=1'h1;
        input_stream.dest <= 123;
        input_stream.user <= 125;
        output_stream.ready <= 1;
        #5 write_BFM.write_dest(limit_high, 'h0);
        #5 write_BFM.write_dest(limit_low, 'h04);

        #5 stream_bfm.write(input_data[0]);
        #5 stream_bfm.write(input_data[1]);
        #5 stream_bfm.write(input_data[2]);

        stream_bfm.write(input_data[3]);
        stream_bfm.write(input_data[4]);
        output_stream.ready <= 0;
        #3 output_stream.ready <= 1;
        stream_bfm.write(input_data[5]);
        stream_bfm.write(input_data[6]);
        #10;
        ->start_checking;
    end

    integer out_counter = 0;
    always@(posedge clk)begin
        if(output_stream.valid)begin
            output_data[out_counter] = output_stream.data;
            out_counter = out_counter + 1;
        end
    end

    initial begin
        @(start_checking);
        for(integer i = 0; i<7; i = i+1)begin
            if(input_data[i]>limit_high)begin
                assert (output_data[i] == limit_high) 
                else begin
                    $display("FAILED HIGH SATURATION TEST: Expected %d, result%d", limit_high, output_data[i]);
                    $finish();
                end
            end else if(input_data[i]< limit_low) begin
                assert (output_data[i] == limit_low) 
                else begin
                    $display("FAILED LOW SATURATION TEST: Expected %d, result%d", limit_low, output_data[i]);
                    $finish();
                end
            end else begin
                assert (output_data[i] == input_data[i]) 
                else begin
                    $display("FAILED IN RANGE SATURATION TEST: Expected %d, result%d", input_data[i], output_data[i]);
                    $finish();
                end
            end
        end


        #5 $display("SIMULATION COMPLETED SUCCESSFULLY");
    end

endmodule