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

module uScope #(
    N_TRIGGERS = 16,
    DATA_WIDTH = 16
)(
    input wire clock,
    input wire reset,
    input wire dma_done,
    output wire [N_TRIGGERS-1:0] trigger_out,
    axi_stream.slave in_1,
    axi_stream.slave in_2,
    axi_stream.slave in_3,
    axi_stream.slave in_4,
    axi_stream.slave in_5,
    axi_stream.slave in_6,
    axi_stream.slave in_7,
    axi_stream.slave in_8,
    axi_lite.master dma_axi,
    axi_stream.master out,
    axi_lite.slave axi_in
);

    localparam CHANNEL_BUFFER_SIZE = 1024; 

    axi_stream #(
        .DATA_WIDTH(32)
    ) combined();
    
    axi_stream #(
        .DATA_WIDTH(32)
    ) combined_inhibited();
    
    axi_stream #(
        .DATA_WIDTH(32)
    ) combined_tlast();
   
    reg manager_enable;
    wire capture_inhibit;
    reg [31:0] tlast_period;
    reg [31:0] dma_buffer_base;
    reg [31:0] dma_transfer_size;
    wire [15:0] current_sample;
    reg dma_start;

    wire trigger;
    reg [31:0] cu_write_registers [5:0];
    reg [31:0] cu_read_registers [5:0];
    axil_simple_register_cu #(
        .N_READ_REGISTERS(6),
        .N_WRITE_REGISTERS(6),
        .REGISTERS_WIDTH(32),
        .N_TRIGGER_REGISTERS(1),
        .TRIGGER_REGISTERS_IDX({3}),
        .ADDRESS_MASK('h1f)
    ) CU (
        .clock(clock),
        .reset(reset),
        .input_registers(cu_read_registers),
        .output_registers(cu_write_registers),
        .trigger_out(trigger),
        .axil(axi_in)
    );
    

    reg [31:0] selected_trigger;
    reg capture_ack;
    reg [15:0] trigger_position;

    assign tlast_period = cu_write_registers[0];
    assign dma_transfer_size = cu_write_registers[0]<<2;
    assign dma_buffer_base = cu_write_registers[1];
    assign manager_enable = cu_write_registers[2];
    assign selected_trigger = cu_write_registers[3];
    assign capture_ack = cu_write_registers[4][0];
    assign trigger_position = cu_write_registers[5];


    assign cu_read_registers[0] = tlast_period;
    assign cu_read_registers[1] = dma_buffer_base;
    assign cu_read_registers[2] = {31'b0, manager_enable};
    assign cu_read_registers[3] = selected_trigger;
    assign cu_read_registers[4] = {31'b0, capture_ack};
    assign cu_read_registers[5] = {16'b0, trigger_position};


    trigger_hub #(
        .N_TRIGGERS(N_TRIGGERS) 
    ) triggers (
        .clock(clock),
        .reset(reset),
        .buffer_level(current_sample),
        .capture_done(dma_start),
        .trigger_in(trigger),
        .selected_trigger(selected_trigger),
        .trigger_position(trigger_position),
        .capture_ack(capture_ack),
        .capture_inhibit(capture_inhibit),
        .trigger_out(trigger_out)
    );


    scope_combiner #(
        .MSB_DEST_SUPPORT( "TRUE"),
        .INPUT_DATA_WIDTH(DATA_WIDTH),
        .OUTPUT_DATA_WIDTH(32)
    ) combiner(
        .clock(clock),
        .reset(reset),
        .stream_in_1(in_1),
        .stream_in_2(in_2),
        .stream_in_3(in_3),
        .stream_in_4(in_4),
        .stream_in_5(in_5),
        .stream_in_6(in_6),
        .stream_out(combined)
    );

    always_comb begin
        combined_inhibited.data <= combined.data;
        combined.ready <= combined_inhibited.ready;
        if(capture_inhibit)begin
            combined_inhibited.valid <= 0;
        end else begin
            combined_inhibited.valid <= combined.valid;
        end
    end

    tlast_generator tlast_gen(
        .clock(clock),
        .reset(reset), 
        .period(tlast_period),
        .in_valid(combined_inhibited.valid),
        .in_data(combined_inhibited.data),
        .in_ready(combined_inhibited.ready),
        .out_valid(combined_tlast.valid),
        .out_data(combined_tlast.data),
        .out_tlast(combined_tlast.tlast),
        .out_ready(combined_tlast.ready),
        .current_sample(current_sample)
    );

    
    
    always_ff @(posedge clock) begin
        dma_start <= combined_tlast.tlast;
    end
    
    DMA_manager #(
        .DMA_BASE_ADDRESS('h40400000)
    ) manager (
		.clock(clock),
		.reset(reset),
        .enable(manager_enable),
        .transfer_size(dma_transfer_size),
        .buffer_base_address(dma_buffer_base),
        .start_dma(dma_start),
		.dma_done(dma_done),
        .axi(dma_axi)
	);

    axis_fifo_xpm #(
        .DATA_WIDTH(32),
        .FIFO_DEPTH(8192)
    ) scope_fifo(
        .clock(clock),
        .reset(reset),
        .in(combined_tlast),
        .out(out)
    );



endmodule

    /**
       {
        "name": "uScope",
        "type": "peripheral",
        "registers":[
            {
                "name": "buffer_size",
                "offset": "0x0",
                "description": "Size of the scope buffer in words",
                "direction": "RW"
            },
            {
                "name": "buffer_addr",
                "offset": "0x4",
                "description": "Address of the first word in memory of the data buffer",
                "direction": "RW"
            },
            {
                "name": "enable",
                "offset": "0x8",
                "description": "Writing 1 to this register enables the scope",
                "direction": "RW"  
            },
            {
                "name": "selected_trigger",
                "offset": "0xC",
                "description": "Writing an address to this register triggers the related signal",
                "direction": "RW"  
            },
            {
                "name": "capture_ack",
                "offset": "0x10",
                "description": "Acknowledge the last captured trigger",
                "direction": "RW"  
            },
            {
                "name": "trigger_position",
                "offset": "0x14",
                "description": "Position of the trigger in the capture window",
                "direction": "RW"  
            }
        ]
    }  
    **/
