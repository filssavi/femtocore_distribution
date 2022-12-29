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

`ifndef APB_BFM_SV
`define APB_BFM_SV


class apb_BFM;

    virtual APB.master apb;
    integer clock_period;


    function new (virtual APB.master test_if, integer period);
        begin
            this.apb = test_if;
            this.apb.PWDATA <= 0;
            this.apb.PPROT <= 0;
            this.apb.PSTRB <= 0;
            this.apb.PRDATA <= 0;
            this.apb.PADDR <= 0;
            this.apb.PWRITE <= 0;
            this.apb.PSEL <= 0;
            this.apb.PENABLE <= 0;
            this.clock_period = period;
        end
    endfunction

    task write(input logic [31:0] address, input logic [31:0] data);
        this.apb.PWDATA <= data;
        this.apb.PADDR <= address;
        this.apb.PWRITE <= 1;
        this.apb.PSEL <= 1;
        this.apb.PENABLE <= 1;
        #1 this.apb.PENABLE <= 0;
        #1 this.apb.PSEL <= 0;
        this.apb.PWRITE <= 0;

    endtask

    task read(input logic [31:0] address, output logic [31:0] data);
        this.apb.PADDR <= address;
        this.apb.PWRITE <= 0;
        this.apb.PSEL <= 1;
        #1 this.apb.PENABLE <= 1;
        wait(this.apb.PREADY) this.apb.PENABLE <= 0;
        this.apb.PSEL <= 0;
    endtask

endclass

`endif