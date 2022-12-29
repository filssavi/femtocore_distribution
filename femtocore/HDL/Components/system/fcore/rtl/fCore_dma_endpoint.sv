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


module fCore_dma_endpoint #(
    parameter BASE_ADDRESS = 32'h43c00000,
    DATAPATH_WIDTH = 20,
    REG_ADDR_WIDTH = 8,
    REGISTER_FILE_DEPTH = 64
)(
    input wire clock,
    input wire reset,
    axi_lite.slave axi_in,
    axi_stream.master reg_dma_write,
    output reg [REG_ADDR_WIDTH-1:0] dma_read_addr,
    input wire [DATAPATH_WIDTH-1:0] dma_read_data,
    output reg [$clog2(REG_ADDR_WIDTH)-1:0] n_channels,
    output reg [15:0] program_size,
    axi_stream.slave axis_dma_write,
    axi_stream.slave axis_dma_read_request,
    axi_stream.master axis_dma_read_response
    );

    
    axi_stream axi_read_addr();
    axi_stream axi_read_data();
    axi_stream axi_write_data();

    axil_external_registers_cu #(
        .BASE_ADDRESS(BASE_ADDRESS)
    ) AXI_endpoint (
        .clock(clock),
        .reset(reset),
        .read_address(axi_read_addr),
        .read_data(axi_read_data),
        .write_data(axi_write_data),
        .axi_in(axi_in)
    );


    reg [31:0] translation_table [REGISTER_FILE_DEPTH-1:0];
    reg [$clog2(REGISTER_FILE_DEPTH)-1:0] translation_table_address;

    initial begin
        for(integer i = 0; i< REGISTER_FILE_DEPTH; i++)begin
            translation_table[i] <= i;
        end
    end

    assign axi_write_data.ready = 1;
    assign axis_dma_write.ready = 1;

    always_ff @(posedge clock) begin
        if(axis_dma_write.valid)begin
            if(axis_dma_write.dest != 0) begin
                reg_dma_write.dest <= translation_table[axis_dma_write.dest];
                reg_dma_write.data <= axis_dma_write.data;
                reg_dma_write.valid <= 1;   
            end
        end else if(axi_write_data.valid)begin
            if(axi_write_data.dest == 0) begin
                n_channels <= axi_write_data.data[15:0];
                program_size <= axi_write_data.data[31:16];
                reg_dma_write.valid <= 0;
                reg_dma_write.dest <= 0;
                reg_dma_write.data <= 0;
            end else if(axi_write_data.dest == 1) begin
                translation_table_address <= axi_write_data.data;
            end else if(axi_write_data.dest == 2) begin
                translation_table[translation_table_address] <= axi_write_data.data;
            end else begin
                reg_dma_write.dest <= translation_table[axi_write_data.dest-2];
                reg_dma_write.data <= axi_write_data.data;
                reg_dma_write.valid <= 1;    
            end
        end else begin
            reg_dma_write.valid <= 0;
            reg_dma_write.dest <= 0;
            reg_dma_write.data <= 0;
        end
    end

    enum reg [2:0] {
        idle = 0,
        bus_read = 1,
        axis_read = 2,
        wait_read = 3
    } state;

    reg [31:0] bus_read_data;
    reg bus_read_valid;
    reg [31:0] stream_read_data;
    reg stream_read_valid;

    assign axi_read_data.data = bus_read_data | stream_read_data;
    assign axi_read_data.valid = bus_read_valid | stream_read_valid;

    reg read_n_channels;
    reg read_translation_addr;
    reg read_translation_data;

    always_ff @(posedge clock) begin
        if(!reset)begin
            axi_read_addr.ready <= 1;
            axis_dma_read_request.ready <= 1;
            dma_read_addr <= 0;
            stream_read_data <= 0;
            read_n_channels <= 0;
            read_translation_addr <= 0;
            read_translation_data <= 0;
            state <= idle;
        end else begin
            case (state)
                idle: begin
                    stream_read_valid <= 0;
                    if(axis_dma_read_request.valid)begin
                        if(axis_dma_read_request.data > 0) begin
                            dma_read_addr <= translation_table[axis_dma_read_request.data];
                            state <= wait_read;
                            axis_dma_read_request.ready <= 0;
                            axi_read_addr.ready <= 0;
                        end
                    end else if(axi_read_addr.valid) begin
                        if(axi_read_addr.data == 0) begin
                            read_n_channels <= 1;
                        end else if(axi_read_addr.data == 1)begin
                            read_translation_addr <= 1;
                        end else if(axi_read_addr.data == 2)begin
                            read_translation_data <= 1;
                        end
                        dma_read_addr <= translation_table[axi_read_addr.data-2];
                        state <= bus_read;
                        axis_dma_read_request.ready <= 0;
                        axi_read_addr.ready <= 0;
                    end
                end
                wait_read:begin
                    state <= axis_read;
                end
                bus_read: begin
                    axi_read_addr.ready <= 1;
                    read_n_channels <= 0;
                    read_translation_addr <= 0;
                    read_translation_data <= 0;
                    axis_dma_read_request.ready <= 1;
                    state <= idle;
                end
                axis_read: begin
                    axis_dma_read_request.ready <= 1;
                    axi_read_addr.ready <= 1;
                    state <= idle;
                end
                default: state <= idle;
            endcase
        end
    end

    always_comb begin
        case (state)
            idle: begin
                axis_dma_read_response.data <= 0;
                axis_dma_read_response.valid <= 0;
                bus_read_valid <= 0;
                bus_read_data <= 0;
            end
            bus_read: begin
                axis_dma_read_response.data <= 0;
                axis_dma_read_response.valid <= 0;
                bus_read_valid <= 1;
                if(read_n_channels) begin
                    bus_read_data <= {program_size,{16-$clog2(REG_ADDR_WIDTH){1'b0}}, n_channels};
                end else if(read_translation_addr)begin
                    bus_read_data <= translation_table_address;
                end else if(read_translation_data)begin
                    bus_read_data <= translation_table[translation_table_address];
                end else begin
                    bus_read_data <= dma_read_data;
                end
            end
            axis_read: begin
                axis_dma_read_response.data <= dma_read_data;
                axis_dma_read_response.valid <= 1;
                bus_read_data <= 0;
                bus_read_valid <= 0;
            end
            default: begin
                axis_dma_read_response.data <= 0;
                axis_dma_read_response.valid <= 0;
                bus_read_data <= 0;
                bus_read_valid <= 0;
            end
            
        endcase
    end



endmodule
 


    /**
    {
        "name": "fCore_dma_endpoint",
        "type": "peripheral",
        "registers":[
            {
                "name": "n_channel",
                "offset": "0x0",
                "description": "Number active channels for the active program",
                "direction": "RW"
            }, 
            {
                "name": "io_translation_address",
                "offset": "0x4",
                "description": "Address of the IO translation table access window",
                "direction": "RW"
            },
            {
                "name": "io_translation_data",
                "offset": "0x8",
                "description": "IO translation table access window",
                "direction": "RW"
            }
        ]
    }  
    **/