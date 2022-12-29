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

`ifndef AXIS_BFM_SV
`define AXIS_BFM_SV


class axis_BFM #(int DATA_WIDTH = 32,int USER_WIDTH = 32, int DEST_WIDTH = 32);

    virtual axi_stream #(DATA_WIDTH, USER_WIDTH, DEST_WIDTH) axis;
    real clock_period;


    function new (virtual axi_stream #(DATA_WIDTH, USER_WIDTH, DEST_WIDTH)  stream, real period);
        begin
            this.axis = stream;
            this.axis.data <= 32'b0;
            this.axis.user <= 32'b0;
            this.axis.dest <= 32'b0;
            this.axis.valid <= 32'b0;
            this.axis.tlast <= 1'b0;
            this.clock_period = period;
        end
    endfunction

    task write(input logic [31:0] write_data);
        this.axis.data <= write_data;
        wait(this.axis.ready) this.axis.valid <= 1'b1;
        #(this.clock_period) this.axis.valid <= 1'b0;
    endtask
    
    task write_dest(input logic [31:0] write_data, logic [31:0] destination);
        this.axis.data <= write_data;
        this.axis.dest <= destination;
        wait(this.axis.ready) this.axis.valid <= 1'b1;
        #(this.clock_period) this.axis.valid <= 1'b0;
    endtask

    task write_du(input logic [31:0] write_data, logic [31:0] destination, logic [31:0] user);
        this.axis.data <= write_data;
        this.axis.dest <= destination;
        this.axis.user <= user;
        wait(this.axis.ready) this.axis.valid <= 1'b1;
        #(this.clock_period) this.axis.valid <= 1'b0;
    endtask

    task write_complete(input logic [31:0] write_data, logic [31:0] destination, logic [31:0] user, logic tlast, logic wait_ready);
        this.axis.data <= write_data;
        this.axis.dest <= destination;
        this.axis.user <= user;
        this.axis.tlast <= tlast;
        if(wait_ready)begin
            wait(this.axis.ready) this.axis.valid <= 1'b1;
            #(this.clock_period) this.axis.valid <= 1'b0;
        end else begin
            this.axis.valid <= 1'b1;
            #(this.clock_period) this.axis.valid <= 1'b0;
        end

    endtask
    
    task  read(output logic [31:0] data);
        this.axis.ready <= 1;
        wait(this.axis.valid);
        data = this.axis.data;
    endtask

    task reset();
        this.axis.data <= 32'b0;
        this.axis.valid <= 32'b0;
        this.axis.tlast <= 1'b0;
    endtask

endclass

`endif