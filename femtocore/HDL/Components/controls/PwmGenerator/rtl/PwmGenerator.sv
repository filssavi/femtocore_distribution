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

module PwmGenerator #(parameter BASE_ADDRESS = 32'h43c00000, COUNTER_WIDTH=16, INITIAL_STOPPED_STATE = 0)(
    input wire clock,
    input wire reset,
    input wire ext_timebase,
    input wire fault,
    output wire timebase,
    output reg [11:0] pwm_out,
    axi_lite.slave axi_in
);

    //Common signals
    wire internal_timebase,timebase_enable,sync;
    wire [2:0] dividerSetting;
    wire counter_run;
    reg selected_timebase;
    wire ext_timebase_enable;
    wire [1:0] counter_status;
    wire [11:0] counter_stopped_state;
    wire [11:0] internal_pwm_out;

    reg [1:0] stop_chain = 0;
    assign timebase = internal_timebase;
    
    always@(posedge clock)begin
        if(counter_status[0] & internal_pwm_out[5:0] == counter_stopped_state[5:0])begin
            stop_chain[0]<=1;
        end else 
            stop_chain[0] <= 0;

        if(counter_status[0] & ~fault)begin
            pwm_out[5:0] = internal_pwm_out[5:0];
        end else begin
            pwm_out[5:0] = counter_stopped_state[5:0];
        end
        
        if(counter_status[1] & internal_pwm_out[11:6] == counter_stopped_state[11:6])begin
            stop_chain[1]<=1;
        end else 
            stop_chain[1] <= 0;

        if(counter_status[1] & ~fault)begin
            pwm_out[11:6] = internal_pwm_out[11:6];
        end else begin
            pwm_out[11:6] = counter_stopped_state[11:6];
        end
        
    end


    always@(posedge clock)begin
        if(~reset)begin
            selected_timebase<=internal_timebase;
        end else begin
            if(ext_timebase_enable)
                selected_timebase <= ext_timebase;
            else
            selected_timebase <= internal_timebase;
        
        end
    end



    localparam GEN_CONTROLLER_ADDRESS_AXI = BASE_ADDRESS;
    localparam CHAIN_1_ADDRESS_AXI = BASE_ADDRESS+'h100;
    localparam CHAIN_2_ADDRESS_AXI = BASE_ADDRESS+'h200;

    axi_lite #(.INTERFACE_NAME("CONTROLLER")) controller_axi();
    axi_lite #(.INTERFACE_NAME("CHAIN 1")) chain_1_axi();
    axi_lite #(.INTERFACE_NAME("CHAIN 2")) chain_2_axi();

    axil_crossbar_interface #(
        .DATA_WIDTH(32),
        .ADDR_WIDTH(32),
        .NM(1),
        .NS(3),
        .SLAVE_ADDR('{GEN_CONTROLLER_ADDRESS_AXI, CHAIN_1_ADDRESS_AXI, CHAIN_2_ADDRESS_AXI}),
        .SLAVE_MASK('{3{32'hf00}})
    ) axi_xbar (
        .clock(clock),
        .reset(reset),
        .slaves('{axi_in}),
        .masters('{controller_axi, chain_1_axi, chain_2_axi})
    );

    
    
    PwmControlUnit #(
        .INITIAL_STOPPED_STATE(INITIAL_STOPPED_STATE)
    ) pwm_cu(
        .clock(clock),
        .reset(reset),
        .counter_status(counter_status),
        .timebase_setting(dividerSetting),
        .timebase_enable(timebase_enable),
        .timebase_external_enable(ext_timebase_enable),
        .counter_run(counter_run),
        .sync(sync),
        .counter_stopped_state(counter_stopped_state),
        .axi_in(controller_axi)
    );

    TimebaseGenerator timebase_generator(
        .clockIn(clock),
        .reset(reset),
        .enable(timebase_enable),
        .timebaseOut(internal_timebase),
        .dividerSetting(dividerSetting)
    );

    pwmChain #(
        .COUNTER_WIDTH(COUNTER_WIDTH)
    ) chain_1(
        .clock(clock),
        .reset(reset),
        .sync(sync),
        .stop_request(stop_chain[0]),
        .timebase(selected_timebase),
        .external_counter_run(counter_run),
        .counter_status(counter_status[0]),
        .out_a(internal_pwm_out[2:0]),
        .out_b(internal_pwm_out[5:3]),
        .axi_in(chain_1_axi)
    );

    
    pwmChain #(
        .COUNTER_WIDTH(COUNTER_WIDTH)
    ) chain_2(
        .clock(clock),
        .reset(reset),
        .sync(sync),
        .stop_request(stop_chain[1]),
        .timebase(selected_timebase),
        .external_counter_run(counter_run),
        .counter_status(counter_status[1]),
        .out_a(internal_pwm_out[8:6]),
        .out_b(internal_pwm_out[11:9]),
        .axi_in(chain_2_axi)
    );


    
endmodule


    /**
        {
            "name": "PwmGenerator",
            "type": "module_hierarchy",
            "children": [
                {
                    "type": "PwmControlUnit",
                    "instance": "pwm_cu",
                    "offset": "0",
                    "children":[]
                },
                {
                    "type": "ChainControlUnit",
                    "instance": "chain_1",
                    "offset": "0x100",
                    "children":[]
                },
                {
                    "type": "ChainControlUnit",
                    "instance": "chain_2",
                    "offset": "0x200",
                    "children":[]
                }
            ]    
        }
    **/
