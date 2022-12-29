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

module SPI_Components_tb();


    logic clk, rst, slw_clk;



    //main clock generation
    initial clk = 0; 
    always #0.5 clk = ~clk; 
    //slow clock generation
    initial slw_clk = 0; 
    always #1 slw_clk = ~slw_clk; 
    
    
    // reset generation
    initial begin
        rst <=1;
        #3.5 rst<=0;
        #5 rst <=1;
    end

    //TRANSFER ENGINE TEST

    logic parameter_address = 0;
    logic [31:0] parameter_data = 0;
    logic parameter_write_enable = 0;
    logic spi_sclk = 0;
    logic spi_start_transfer = 0;
    logic [31:0] cu_data_out = 0;
    logic [31:0] reg_data_out = 0;

    TransferEngine TCE(
        .clock(clk),
        .reset(rst),
        .parameter_address(parameter_address),
        .parameter_data(parameter_data),
        .parameter_write_enable(parameter_write_enable),
        .spi_sclk(slw_clk),
        .spi_start_transfer(spi_start_transfer),
        .cu_data_out(cu_data_out),
        .reg_data_out(reg_data_out)
    );


    initial begin

        //TEST LOAD PARAMETER
        #15.5 parameter_address <=0;
        parameter_data <= 12;
        parameter_write_enable<=1;
        #1 parameter_write_enable<=0;
        #5 parameter_address <=1;
        parameter_data <= 4;
        parameter_write_enable<=1;
        #1 parameter_write_enable<=0;

        //Test output transfer
        # 5 cu_data_out[11:0] <= $urandom;
        spi_start_transfer <=1;
        # 1 spi_start_transfer <=0;
    end

    //SHIFT REGISTER TESTBENCH

    logic shr_en = 0;
    logic shr_sin = 0;
    logic reg_dir = 0;
    logic reg_mode = 0;
    logic reg_load = 0;
    logic spi_mode = 0;
    logic [31:0] shr_pin = 0;
    logic [31:0] shr_pout;
    logic shr_sout;


    SpiRegister SHR(
        .clock(clk),
        .shift_clock(slw_clk),
        .reset(rst),
        .enable(shr_en),
        .serial_in(shr_sin),
        .register_direction(reg_dir),
        .register_load(reg_load),
        .parallel_in(shr_pin),
        .parallel_out(shr_pout),
        .serial_out(shr_sout)
    );


    initial begin
        shr_en <=0;
        reg_dir <=0;
        //TEST PARALLEL WRITE
        reg_load <=1;
        shr_pin <= $urandom;
        #10.5 shr_en <=1;
        #1 shr_en <=0;
        reg_load <=0;
        // TEST SERIAL READ MSB FIRST
        #3 shr_en <= 1;
        #66 shr_en <=0;
        //REGISTER RELOAD         
        reg_load <=1;
        shr_pin <= $urandom;
        #10.5 shr_en <=1;
        #1 shr_en <=0;
        reg_load <=0;
        // TEST SERIAL READ LSB FIRST
        #3 reg_dir <=1;
        shr_en <= 1;
        #66 shr_en <=0;
        //REGISTER RELOAD         
        reg_load <=1;
        shr_pin <= $urandom;
        #10.5 shr_en <=1;
        #1 shr_en <=0;
        reg_load <=0;
        // TEST SERIAL WRITE MSB FIRST
        #5 reg_dir <=0;
        shr_en <=1;
        shr_sin <= $urandom;
        #2 shr_sin <= $urandom;
        #2 shr_sin <= $urandom;
        #2 shr_sin <= $urandom;
        #2 shr_sin <= $urandom;
        #2 shr_sin <= $urandom;
        #2 shr_sin <= $urandom;
        #2 shr_sin <= $urandom;
        #2 shr_sin <= $urandom;
        #2 shr_sin <= $urandom;
        #2 shr_sin <= $urandom;
        #2 shr_sin <= $urandom;
        #2 shr_sin <= $urandom;
        #2 shr_sin <= $urandom;
        #2 shr_sin <= $urandom;
        #2 shr_sin <= $urandom;
        #2 shr_sin <= $urandom;
        #2 shr_sin <= $urandom;
        #2 shr_sin <= $urandom;
        #2 shr_sin <= $urandom;
        #2 shr_sin <= $urandom;
        #2 shr_sin <= $urandom;
        #2 shr_sin <= $urandom;
        #2 shr_sin <= $urandom;
        #2 shr_sin <= $urandom;
        #2 shr_sin <= $urandom;
        #2 shr_sin <= $urandom;
        #2 shr_sin <= $urandom;
        #2 shr_sin <= $urandom;
        #2 shr_sin <= $urandom;
        #2 shr_sin <= $urandom;
        #2 shr_sin <= $urandom;
        #2 shr_sin <= $urandom;
        #1 shr_en <=0;
        shr_sin <=0;
        //REGISTER RELOAD         
        reg_load <=1;
        shr_pin <= $urandom;
        #10.5 shr_en <=1;
        #1 shr_en <=0;
        reg_load <=0;
        // TEST SERIAL WRITE LSB FIRST
        #5 reg_dir <=1;
        shr_en <=1;
        shr_sin <= $urandom;
        #2 shr_sin <= $urandom;
        #2 shr_sin <= $urandom;
        #2 shr_sin <= $urandom;
        #2 shr_sin <= $urandom;
        #2 shr_sin <= $urandom;
        #2 shr_sin <= $urandom;
        #2 shr_sin <= $urandom;
        #2 shr_sin <= $urandom;
        #2 shr_sin <= $urandom;
        #2 shr_sin <= $urandom;
        #2 shr_sin <= $urandom;
        #2 shr_sin <= $urandom;
        #2 shr_sin <= $urandom;
        #2 shr_sin <= $urandom;
        #2 shr_sin <= $urandom;
        #2 shr_sin <= $urandom;
        #2 shr_sin <= $urandom;
        #2 shr_sin <= $urandom;
        #2 shr_sin <= $urandom;
        #2 shr_sin <= $urandom;
        #2 shr_sin <= $urandom;
        #2 shr_sin <= $urandom;
        #2 shr_sin <= $urandom;
        #2 shr_sin <= $urandom;
        #2 shr_sin <= $urandom;
        #2 shr_sin <= $urandom;
        #2 shr_sin <= $urandom;
        #2 shr_sin <= $urandom;
        #2 shr_sin <= $urandom;
        #2 shr_sin <= $urandom;
        #2 shr_sin <= $urandom;
        #2 shr_sin <= $urandom;
        #1 shr_en <=0;
        shr_sin <=0;
    end


endmodule    // reset generation
    