// Copyright 2021 Filippo Savi
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

module axil_simple_register_cu #(
    parameter N_READ_REGISTERS = 1,
    N_WRITE_REGISTERS = 1,
    REGISTERS_WIDTH = 32,
    N_TRIGGER_REGISTERS = 1,
    parameter [REGISTERS_WIDTH-1:0] INITIAL_OUTPUT_VALUES [N_WRITE_REGISTERS-1:0] = '{N_WRITE_REGISTERS{0}},
    parameter [31:0] TRIGGER_REGISTERS_IDX [N_TRIGGER_REGISTERS-1:0] = '{N_TRIGGER_REGISTERS{0}},
    REGISTERED_BUFFERS = 0,
    parameter [31:0] ADDRESS_MASK = 0
) (
    input wire clock,
    input wire reset,
    input wire [REGISTERS_WIDTH-1:0] input_registers [N_READ_REGISTERS-1:0],
    output reg [REGISTERS_WIDTH-1:0] output_registers [N_WRITE_REGISTERS-1:0],
    output reg [N_TRIGGER_REGISTERS-1:0] trigger_out,
    axi_lite.slave axil

);


    // function [REGISTERS_WIDTH-1:0]	apply_strobe;
    //     input [REGISTERS_WIDTH-1:0] prior_data;
    //     input [REGISTERS_WIDTH-1:0] new_data;
    //     input [REGISTERS_WIDTH/8-1:0] strobe;

    //     integer	k;
    //     for(k=0; k<REGISTERS_WIDTH/8; k=k+1)
    //     begin
    //         apply_strobe[k*8 +: 8]
    //             = strobe[k] ? new_data[k*8 +: 8] : prior_data[k*8 +: 8];
    //     end
    // endfunction


// HANDLE READ DATA CHANNEL 

logic read_ready;
logic [31:0] read_data;
logic [31:0] read_address;
logic read_address_valid;

initial axil.RVALID = 0;

always @ (posedge clock) begin
    if (~reset) begin
        axil.RVALID <= 0;
    end else begin
        if (read_ready)begin
            axil.RVALID <= 1'b1;
        end else if (axil.RREADY) begin
            axil.RVALID <= 1'b0;
        end        
    end
end
assign read_ready = read_address_valid && (~axil.RVALID || axil.RREADY);
assign	axil.RDATA = read_data;
assign	axil.RRESP = 2'b00;


// HANDLE READ ADDRESS CHANNEL

axil_skid_buffer #(
    .REGISTER_OUTPUT(REGISTERED_BUFFERS),
    .DATA_WIDTH(32)
) address_read_buffer (
    .clock(clock),
    .reset(reset),
    .in_valid(axil.ARVALID),
    .in_ready(axil.ARREADY),
    .in_data(axil.ARADDR),
    .out_valid(read_address_valid),
    .out_ready(read_ready),
    .out_data(read_address)
);

// HANDLE BRESP CHANNEL

logic write_ready;
initial axil.BVALID = 0;

always @ (posedge clock) begin
    if (~reset) begin
        axil.BVALID <= 0;
    end else begin
        if (write_ready)begin
            axil.BVALID <= 1'b1;
        end else if (axil.BREADY) begin
            axil.BVALID <= 1'b0;
        end  
    end
end

assign	axil.BRESP = 2'b00;


// HANDLE WRITE DATA AND WRITE ADDRESS CHANNEL

logic write_valid;
logic [31:0] write_data;
logic [31:0] write_address;

logic write_address_valid;

axil_skid_buffer #(
    .REGISTER_OUTPUT(REGISTERED_BUFFERS),
    .DATA_WIDTH(32)
) address_write_buffer (
    .clock(clock),
    .reset(reset),
    .in_valid(axil.AWVALID),
    .in_ready(axil.AWREADY),
    .in_data(axil.AWADDR),
    .out_valid(write_address_valid),
    .out_ready(write_ready),
    .out_data(write_address)
);

logic [3:0] write_strobe;
logic write_data_valid;

axil_skid_buffer #(
    .REGISTER_OUTPUT(REGISTERED_BUFFERS),
    .DATA_WIDTH(32+4)
) write_data_buffer (
    .clock(clock),
    .reset(reset),
    .in_valid(axil.WVALID),
    .in_ready(axil.WREADY),
    .in_data({axil.WDATA, axil.WSTRB}),
    .out_valid(write_data_valid),
    .out_ready(write_ready),
    .out_data({write_data, write_strobe})
);

assign write_ready = write_valid && (~axil.BVALID || axil.BREADY);
assign write_valid = write_data_valid && write_address_valid;


wire [31:0] register_read_address;
wire [31:0] register_write_address;

assign register_read_address = (read_address & ADDRESS_MASK) >> 2;
assign register_write_address = (write_address & ADDRESS_MASK) >> 2;


always @ (posedge clock) begin
    if (~reset) begin
        read_data <= 0;
    end else begin
        if(read_address_valid) begin
            read_data <= input_registers[register_read_address];
        end
    end
end



always_ff @(posedge clock) begin
    if (~reset) begin
        output_registers <= INITIAL_OUTPUT_VALUES;
    end else begin
        if(write_valid & write_ready) begin
            output_registers[register_write_address] <= write_data;
        end
    end
end


always @ (posedge clock) begin
    if (~reset) begin
        trigger_out <= 1'b0;
    end else begin
        trigger_out <= 1'b0;
        if(write_valid & write_ready) begin
            for(integer i = 0; i< N_TRIGGER_REGISTERS; i= i+1)begin
                if(register_write_address == TRIGGER_REGISTERS_IDX[i]) begin
                    trigger_out[i] <= 1'b1;
                end                            
            end
        end
    end
end

endmodule