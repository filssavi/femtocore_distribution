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

`ifndef SPI_BFM_SV
`define SPI_BFM_SV


class SPI_BFM;
    string out;
	chandle h;
    virtual SPI_if.slave SPI;
    logic ss_polarity;
    
    function new (virtual SPI_if.slave s, input logic ss_polarity);
        begin
            this.SPI = s;
            this.SPI.MISO = 0;
            this.ss_polarity = ss_polarity;
        end
    endfunction

    task transfer(input [31:0] tx_data,input [31:0] transfer_size,output [31:0] rx_data);
        integer i;
        
        if(this.ss_polarity)begin
            @(posedge this.SPI.SS);
        end else begin
            @(negedge this.SPI.SS);
        end
        rx_data = 0;
        for(i = 0; i< transfer_size; i=i+1)begin
            @(posedge this.SPI.SCLK);
            this.SPI.MISO = tx_data[transfer_size-1-i]; 
            @(negedge this.SPI.SCLK);
            rx_data[transfer_size-1-i] = this.SPI.MOSI; 
        end  
    endtask
    
    task send_msb_first(input [31:0] tx_data, integer transfer_size);
        integer i;

        //this.SPI.MISO = tx_data[23];
        //@(negedge this.SPI.SCLK) this.SPI.MISO = tx_data[22];
        this.SPI.MISO = tx_data[22];
        @(negedge this.SPI.SCLK) this.SPI.MISO = tx_data[21];
        @(negedge this.SPI.SCLK) this.SPI.MISO = tx_data[20];
        //this.SPI.MISO = tx_data[20];
        @(negedge this.SPI.SCLK) this.SPI.MISO = tx_data[19];
        @(negedge this.SPI.SCLK) this.SPI.MISO = tx_data[18];
        @(negedge this.SPI.SCLK) this.SPI.MISO = tx_data[17];
        @(negedge this.SPI.SCLK) this.SPI.MISO = tx_data[16];
        @(negedge this.SPI.SCLK) this.SPI.MISO = tx_data[15];
        @(negedge this.SPI.SCLK) this.SPI.MISO = tx_data[14];
        @(negedge this.SPI.SCLK) this.SPI.MISO = tx_data[13];
        @(negedge this.SPI.SCLK) this.SPI.MISO = tx_data[12];
        @(negedge this.SPI.SCLK) this.SPI.MISO = tx_data[11];
        @(negedge this.SPI.SCLK) this.SPI.MISO = tx_data[10];
        @(negedge this.SPI.SCLK) this.SPI.MISO = tx_data[9];
        @(negedge this.SPI.SCLK) this.SPI.MISO = tx_data[8];
        @(negedge this.SPI.SCLK) this.SPI.MISO = tx_data[7];
        @(negedge this.SPI.SCLK) this.SPI.MISO = tx_data[6];
        @(negedge this.SPI.SCLK) this.SPI.MISO = tx_data[5];
        @(negedge this.SPI.SCLK) this.SPI.MISO = tx_data[4];
        @(negedge this.SPI.SCLK) this.SPI.MISO = tx_data[3];
        @(negedge this.SPI.SCLK) this.SPI.MISO = tx_data[2];
        @(negedge this.SPI.SCLK) this.SPI.MISO = tx_data[1];
        @(negedge this.SPI.SCLK) this.SPI.MISO = tx_data[0];

    endtask


    task adc_Conversion(input [31:0] in);
        @(posedge this.SPI.SCLK) this.SPI.MISO = in[13];
        @(posedge this.SPI.SCLK) this.SPI.MISO = in[12];
        @(posedge this.SPI.SCLK) this.SPI.MISO = in[11];
        @(posedge this.SPI.SCLK) this.SPI.MISO = in[10];
        @(posedge this.SPI.SCLK) this.SPI.MISO = in[9];
        @(posedge this.SPI.SCLK) this.SPI.MISO = in[8];
        @(posedge this.SPI.SCLK) this.SPI.MISO = in[7];
        @(posedge this.SPI.SCLK) this.SPI.MISO = in[6];
        @(posedge this.SPI.SCLK) this.SPI.MISO = in[5];
        @(posedge this.SPI.SCLK) this.SPI.MISO = in[4];
        @(posedge this.SPI.SCLK) this.SPI.MISO = in[3];
        @(posedge this.SPI.SCLK) this.SPI.MISO = in[2];
        @(posedge this.SPI.SCLK) this.SPI.MISO = in[1];
        @(posedge this.SPI.SCLK) this.SPI.MISO = in[0];
    endtask

endclass

`endif