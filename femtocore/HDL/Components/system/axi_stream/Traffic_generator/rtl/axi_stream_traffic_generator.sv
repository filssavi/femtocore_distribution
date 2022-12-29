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

module axi_stream_traffic_generator (
    input wire clock,
    input wire reset,
    input wire enable,
    axi_stream.master data_out
);



reg [39:0] ram [1023:0];
reg [9:0] address;

initial begin
    $readmemh("tgen_data.dat",ram);
end

always@(posedge clock) begin
    if(~reset) begin
        address <= 0;
        data_out.valid <= 0;
        data_out.data <= 0;
    end else begin
        if(enable)begin
            if(data_out.valid)begin
                data_out.valid <=0;
            end else begin
                if(data_out.ready) begin
                    data_out.data <= ram[address];
                    address <= address+1;
                    data_out.valid <=1;
                end
            end
        end else begin
            data_out.valid <= 0;
        end
    end
end


endmodule