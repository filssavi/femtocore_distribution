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


module TopLevel (
  	inout wire i2c_scl,
	inout wire i2c_sda,
	output wire test_clock,
	output wire test_start
);


    wire sda_in, sda_out, i2c_sda_out_en;
    wire scl_in, scl_out, i2c_scl_out_en;
	
    wire [31:0] sb_address;
    wire [31:0] sb_read_data;
    wire [31:0] sb_write_data;
    wire sb_ready, sb_write_strobe, sb_read_strobe;

	assign test_start = start;  
	assign test_clock = sb_ready;
	
    wire internal_rst, fast_clock;
	wire clk;
	
	reg start,unconfigured;
	reg [18:0] start_counter;
	reg [7:0] address_counter;
		
	BB_B scl (
	  .T_N (i2c_scl_out_en & ~scl_out),  // I
	  .I   (0),  // I
	  .O   (scl_in),  // O
	  .B   (i2c_scl)   // IO
	);

	BB_B sda (
	  .T_N (i2c_sda_out_en & !sda_out),  // I
	  .I   (0),  // I
	  .O   (sda_in),  // O
	  .B   (i2c_sda)   // IO
	);
	
	always@(posedge fast_clock) begin
        if(~internal_rst)begin
			address_counter <= 8'h62;
            start_counter <= 0;
            start <= 0;
			unconfigured <= 1;
        end else begin
			if(unconfigured)begin
				if(start_counter==4095) begin
					start <= 1;
					unconfigured <= 0;
				end
				start_counter <= start_counter+1;
			end else begin
				start <= 0;
			end
        end
	end


	HSOSC #(
		.CLKHF_DIV("0b00")
	) clk_source (
		.CLKHFEN(1'b1),
		.CLKHFPU(1'b1),
		.CLKHF(clk)
	);

    PLL pll1 (
        .ref_clk_i(clk),
        .rst_n_i(1),
        .lock_o(internal_rst),
        .outglobal_o(fast_clock)
    );


    si5351_config configurator(
        .clock(fast_clock),
        .reset(internal_rst),
        .start(start),
        .slave_address(8'h62),
        .config_out(write)
    );
    
	axi_lite axi_master();
	axi_stream write();
	axi_stream read_dummy_1();
	axi_stream read_dummy_2();

    axis_to_axil WRITER(
        .clock(clk),
        .reset(rst), 
        .axis_write(write),
        .axis_read_request(read_dummy_1),
        .axis_read_response(read_dummy_2),
        .axi_out(axi_master)
    );
    

    I2c #(
		.FIXED_PERIOD("TRUE")
	) i2c_interface (
        .clock(fast_clock),
        .reset(internal_rst),
        .axi(axi_master),
        .i2c_scl_in(scl_in),
        .i2c_scl_out(scl_out),
		.i2c_scl_out_en(i2c_scl_out_en),
        .i2c_sda_in(sda_in),
        .i2c_sda_out(sda_out),
		.i2c_sda_out_en(i2c_sda_out_en)
    );
endmodule