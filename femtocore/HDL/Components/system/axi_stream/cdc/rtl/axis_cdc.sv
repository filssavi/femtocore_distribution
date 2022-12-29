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

module axis_cdc #(
parameter CDC_STYLE = "FF",
    N_STAGES_IN = 2,
    N_STAGES_OUT = 3,
    DATA_WIDTH = 32,
    USER_WIDTH = 32, 
    DEST_WIDTH = 32
  )(
    input wire reset,
    input wire clock_in,
    input wire clock_out,
    axi_stream.slave in,
    axi_stream.master out
    );




    generate
    if(CDC_STYLE == "FF")begin
    
        localparam N_STAGES = N_STAGES_IN;
        reg [DATA_WIDTH-1:0] data_meta[N_STAGES-1:0];
        reg [USER_WIDTH-1:0] user_meta[N_STAGES-1:0];
        reg [DEST_WIDTH-1:0] dest_meta[N_STAGES-1:0];
        reg [N_STAGES-1:0] valid_meta, ready_meta;
        
        assign out.data = data_meta[N_STAGES-1];
        assign out.user = user_meta[N_STAGES-1];
        assign out.dest = dest_meta[N_STAGES-1];
        assign out.valid = valid_meta[N_STAGES-1];
        

        always @(posedge clock_out) begin
            for(integer i = 0; i< N_STAGES; i = i+1)begin
                data_meta[i+1] <= data_meta[i];
            end
            data_meta[0] <= in.data;

            for(integer i = 0; i< N_STAGES; i = i+1)begin
                user_meta[i+1] <= user_meta[i];
            end
            user_meta[0] <= in.user;

            for(integer i = 0; i< N_STAGES; i = i+1)begin
                dest_meta[i+1] <= dest_meta[i];
            end
            dest_meta[0] <= in.dest;

            for(integer i = 0; i< N_STAGES; i = i+1)begin
                valid_meta[i+1] <= valid_meta[i];
            end
            valid_meta[0] <= in.valid;

            in.ready <= out.ready;
        end

    end else if(CDC_STYLE == "HANDSHAKE")begin

        reg cdc_ready_b, cdc_valid_b;
        always@(posedge clock_in)begin
            if(~reset)begin

                cdc_valid_b <= 0;
                in.ready <= 1;
            end else begin
                if(in.valid)begin
                    cdc_valid_b <= 1;
                    in.ready <= 0;
                end
                if(cdc_ready_b) begin
                    cdc_valid_b <= 0;
                end
                if(~cdc_ready_b & ~in.valid & ~cdc_valid_b )begin
                    in.ready <= 1;
                end
            end
        end

    // xpm_cdc_array_single #(
    //     .DEST_SYNC_FF(4),   // DECIMAL; range: 2-10
    //     .INIT_SYNC_FF(0),   // DECIMAL; 0=disable simulation init values, 1=enable simulation init values
    //     .SIM_ASSERT_CHK(0), // DECIMAL; 0=disable simulation messages, 1=enable simulation messages
    //     .SRC_INPUT_REG(1),  // DECIMAL; 0=do not register input, 1=register input
    //     .WIDTH(2)           // DECIMAL; range: 1-1024
    // )
    // xpm_cdc_array_single_inst (
    //     .dest_out(dest_out), // WIDTH-bit output: src_in synchronized to the destination clock domain. This
    //                         // output is registered.

    //     .dest_clk(dest_clk), // 1-bit input: Clock signal for the destination clock domain.
    //     .src_clk(src_clk),   // 1-bit input: optional; required when SRC_INPUT_REG = 1
    //     .src_in(src_in)      // WIDTH-bit input: Input single-bit array to be synchronized to destination clock
    //                         // domain. It is assumed that each bit of the array is unrelated to the others. This
    //                         // is reflected in the constraints applied to this macro. To transfer a binary value
    //                         // losslessly across the two clock domains, use the XPM_CDC_GRAY macro instead.

    // );



        xpm_cdc_handshake #(
            .DEST_EXT_HSK(0),
            .DEST_SYNC_FF(N_STAGES_OUT),
            .INIT_SYNC_FF(1),
            .SIM_ASSERT_CHK(1),
            .SRC_SYNC_FF(N_STAGES_IN),
            .WIDTH(DATA_WIDTH)
        ) op_cdc_data (
            .dest_out(out.data),
            .dest_req(out.valid),
            .src_rcv(cdc_ready_b),
            .dest_clk(clock_out),
            .src_clk(clock_in),
            .src_in(in.data),
            .src_send(cdc_valid_b)
        );
    

        xpm_cdc_handshake #(
            .DEST_EXT_HSK(0),
            .DEST_SYNC_FF(N_STAGES_OUT),
            .INIT_SYNC_FF(1),
            .SIM_ASSERT_CHK(1),
            .SRC_SYNC_FF(N_STAGES_IN),
            .WIDTH(DATA_WIDTH)
        ) op_cdc_dest (
            .dest_out(out.dest),
            .dest_clk(clock_out),
            .src_clk(clock_in),
            .src_in(in.dest),
            .src_send(cdc_valid_b)
        );

    end
    
    endgenerate

endmodule
