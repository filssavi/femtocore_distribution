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

module si5351_config #(parameter BASE_ADDRESS = 0 ,WAIT_COUNT=3, AUTOMATED_WRITE_OFFSET = 32'h18)(
    input wire clock,
    input wire reset,
    input wire start,
    input wire [7:0] slave_address,
    output reg        done,
    axi_stream.master config_out
);


    reg write_in_progress;
    reg [7:0] cfg_data [49:0];
    reg [7:0] cfg_address[49:0]; 
    reg [7:0] cfg_counter;
    reg idle;   
    reg [15:0] wait_counter;

    reg [1:0] state;
    localparam idle_state = 0, write_cfg_state = 1, wait_state = 2;
    always@(posedge clock) begin
        if(~reset)begin
            cfg_data[0] <= 8'h53;
            cfg_data[1] <= 8'h00;
            cfg_data[2] <= 8'h00;
            cfg_data[3] <= 8'h00;
            cfg_data[4] <= 8'h0f;
            cfg_data[5] <= 8'h0f;
            cfg_data[6] <= 8'h8C;
            cfg_data[7] <= 8'h8C;
            cfg_data[8] <= 8'h8C;
            cfg_data[9] <= 8'h8C;
            cfg_data[10] <= 8'h8C;
            cfg_data[11] <= 8'h8C;
            cfg_data[12] <= 8'h00;
            cfg_data[13] <= 8'h01;
            cfg_data[14] <= 8'h00;
            cfg_data[15] <= 8'h10;
            cfg_data[16] <= 8'h00;
            cfg_data[17] <= 8'h00;
            cfg_data[18] <= 8'h00;
            cfg_data[19] <= 8'h00;
            cfg_data[20] <= 8'h00;
            cfg_data[21] <= 8'h02;
            cfg_data[22] <= 8'h00;
            cfg_data[23] <= 8'h09;
            cfg_data[24] <= 8'h40;
            cfg_data[25] <= 8'h00;
            cfg_data[26] <= 8'h00;
            cfg_data[27] <= 8'h00;
            cfg_data[28] <= 8'h00;
            cfg_data[29] <= 8'h02;
            cfg_data[30] <= 8'h00;
            cfg_data[31] <= 8'h09;
            cfg_data[32] <= 8'h40;
            cfg_data[33] <= 8'h00;
            cfg_data[34] <= 8'h00;
            cfg_data[35] <= 8'h00;
            cfg_data[36] <= 8'h00;
            cfg_data[37] <= 8'h00;
            cfg_data[38] <= 8'h00;
            cfg_data[39] <= 8'h00;
            cfg_data[40] <= 8'h00;
            cfg_data[41] <= 8'h00;
            cfg_data[42] <= 8'h00;
            cfg_data[43] <= 8'h00;
            cfg_data[44] <= 8'h00;
            cfg_data[45] <= 8'h00;
            cfg_data[46] <= 8'h00;
            cfg_data[47] <= 8'h00;
            cfg_data[48] <= 8'h19;
            cfg_data[49] <= 8'h92;

            cfg_address[0] <= 8'h02;
            cfg_address[1] <= 8'h03;
            cfg_address[2] <= 8'h09;
            cfg_address[3] <= 8'h0f;
            cfg_address[4] <= 8'h10;
            cfg_address[5] <= 8'h11;
            cfg_address[6] <= 8'h12;
            cfg_address[7] <= 8'h13;
            cfg_address[8] <= 8'h14;
            cfg_address[9] <= 8'h15;
            cfg_address[10] <= 8'h16;
            cfg_address[11] <= 8'h17;
            cfg_address[12] <= 8'h1a;
            cfg_address[13] <= 8'h1b;
            cfg_address[14] <= 8'h1c;
            cfg_address[15] <= 8'h1d;
            cfg_address[16] <= 8'h1e;
            cfg_address[17] <= 8'h1f;
            cfg_address[18] <= 8'h20;
            cfg_address[19] <= 8'h21;
            cfg_address[20] <= 8'h2a;
            cfg_address[21] <= 8'h2b;
            cfg_address[22] <= 8'h2c;
            cfg_address[23] <= 8'h2d;
            cfg_address[24] <= 8'h2e;
            cfg_address[25] <= 8'h2f;
            cfg_address[26] <= 8'h30;
            cfg_address[27] <= 8'h31;
            cfg_address[28] <= 8'h32;
            cfg_address[29] <= 8'h33;
            cfg_address[30] <= 8'h34;
            cfg_address[31] <= 8'h35;
            cfg_address[32] <= 8'h36;
            cfg_address[33] <= 8'h37;
            cfg_address[34] <= 8'h38;
            cfg_address[35] <= 8'h39;
            cfg_address[36] <= 8'h5a;
            cfg_address[37] <= 8'h5b;
            cfg_address[38] <= 8'h95;
            cfg_address[39] <= 8'h96;
            cfg_address[40] <= 8'h97;
            cfg_address[41] <= 8'h98;
            cfg_address[42] <= 8'h99;
            cfg_address[43] <= 8'h9a;
            cfg_address[44] <= 8'h9b;
            cfg_address[45] <= 8'ha2;
            cfg_address[46] <= 8'ha3;
            cfg_address[47] <= 8'ha4;
            cfg_address[48] <= 8'ha6;
            cfg_address[49] <= 8'hB7;
            
  
            idle <= 1;
            state <= 0;
            wait_counter <= WAIT_COUNT;
            cfg_counter <= 0;
            done <= 0;
            config_out.data <= 0;
            config_out.dest <= 0;
            config_out.valid <= 0;
            write_in_progress <= 0;
        end else begin


            case (state)
                idle_state:
                    if(start) begin
                        state <= write_cfg_state;
                    end else begin
                        state <= idle_state;
                    end
                write_cfg_state:
                    if(cfg_counter == 49) begin
                        state <= idle_state;
                        done <= 1;
                    end else begin
                        state <= wait_state;
                    end
                wait_state:
                    if(config_out.ready & wait_counter==0) begin
                        state <= write_cfg_state;
                    end else begin
                        state <= wait_state;
                    end
            endcase


            case (state)
                idle_state: begin
                    cfg_counter <= 0;
                    config_out.valid <=0;
                end
                write_cfg_state: begin
                    config_out.dest <= BASE_ADDRESS+AUTOMATED_WRITE_OFFSET;
                    config_out.data <= {cfg_data[cfg_counter][7:0],cfg_address[cfg_counter][7:0], slave_address[7:0]};
                    cfg_counter <= cfg_counter+1;
                    config_out.valid <= 1;
                    wait_counter <= WAIT_COUNT;
                end
                wait_state:begin
                    if(wait_counter > 0) wait_counter <= wait_counter-1;
                    config_out.valid <= 0;
                end
            endcase
        end
    end

endmodule