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

module axil_external_registers_cu #(
    parameter REGISTERS_WIDTH = 32,
    REGISTERED_BUFFERS = 0,
    BASE_ADDRESS = 0,
    READ_DELAY = 0
) (
    input wire clock,
    input wire reset,
    axi_stream.master read_address,
    axi_stream.slave read_data,
    axi_stream.master write_data,
    axi_lite.slave axi_in
);


    function [REGISTERS_WIDTH-1:0]	apply_strobe;
        input [REGISTERS_WIDTH-1:0] prior_data;
        input [REGISTERS_WIDTH-1:0] new_data;
        input [REGISTERS_WIDTH/8-1:0] strobe;

        integer	k;
        for(k=0; k<REGISTERS_WIDTH/8; k=k+1)
        begin
            apply_strobe[k*8 +: 8]
                = strobe[k] ? new_data[k*8 +: 8] : prior_data[k*8 +: 8];
        end
    endfunction


// HANDLE READ ADDRESS CHANNEL

logic [31:0] internal_read_address;
logic read_address_valid;
logic read_ready;

axil_skid_buffer #(
    .REGISTER_OUTPUT(REGISTERED_BUFFERS),
    .DATA_WIDTH(32)
) address_read_buffer (
    .clock(clock),
    .reset(reset),
    .in_valid(axi_in.ARVALID),
    .in_ready(axi_in.ARREADY),
    .in_data(axi_in.ARADDR),
    .out_valid(read_address_valid),
    .out_ready(read_ready),
    .out_data(internal_read_address)
);

// HANDLE BRESP CHANNEL

logic write_ready;
initial axi_in.BVALID = 0;

always @ (posedge clock) begin
    if (~reset) begin
        axi_in.BVALID <= 0;
    end else begin
        if (write_ready)begin
            axi_in.BVALID <= 1'b1;
        end else if (axi_in.BREADY) begin
            axi_in.BVALID <= 1'b0;
        end  
    end
end

assign	axi_in.BRESP = 2'b00;


// HANDLE WRITE DATA AND WRITE ADDRESS CHANNEL

logic write_valid;
logic [31:0] internal_write_data;
logic [31:0] write_address;

logic write_address_valid;

axil_skid_buffer #(
    .REGISTER_OUTPUT(REGISTERED_BUFFERS),
    .DATA_WIDTH(32)
) address_write_buffer (
    .clock(clock),
    .reset(reset),
    .in_valid(axi_in.AWVALID),
    .in_ready(axi_in.AWREADY),
    .in_data(axi_in.AWADDR),
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
    .in_valid(axi_in.WVALID),
    .in_ready(axi_in.WREADY),
    .in_data({axi_in.WDATA, axi_in.WSTRB}),
    .out_valid(write_data_valid),
    .out_ready(write_ready),
    .out_data({internal_write_data, write_strobe})
);

assign write_ready = write_valid && (~axi_in.BVALID || axi_in.BREADY);
assign write_valid = write_data_valid && write_address_valid;


// HANDLE READ DATA CHANNEL 

wire [31:0] register_read_address;
assign register_read_address = (internal_read_address - BASE_ADDRESS) >> 2;


initial axi_in.RVALID = 0;

always @ (posedge clock) begin
    if (~reset) begin
        axi_in.RVALID <= 0;
    end else begin
        if (read_data.valid)begin
            axi_in.RVALID <= 1'b1;
            axi_in.RDATA <= read_data.data;
        end else if (axi_in.RREADY) begin
            axi_in.RVALID <= 1'b0;
        end        
    end
end

assign read_ready = read_address_valid && (~axi_in.RVALID || axi_in.RREADY);
assign	axi_in.RRESP = 2'b00;


assign read_address.data = register_read_address;
assign read_address.valid = read_address_valid;
assign read_data.ready = read_ready;

wire [31:0] register_write_address;
assign register_write_address = (write_address - BASE_ADDRESS) >> 2;

assign write_data.data = internal_write_data;
assign write_data.dest = register_write_address;
assign write_data.user = write_strobe;
assign write_data.valid = write_valid & write_ready;

endmodule