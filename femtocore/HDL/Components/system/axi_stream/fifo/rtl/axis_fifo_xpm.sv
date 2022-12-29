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

module axis_fifo_xpm #(parameter DATA_WIDTH = 32, DEST_WIDTH=16, USER_WIDTH = 32, FIFO_DEPTH = 16)(
    input wire clock,
    input wire reset,
    axi_stream.slave in,
    axi_stream.master out
);


   xpm_fifo_axis #(
      .FIFO_DEPTH(FIFO_DEPTH),
      .PACKET_FIFO("false"),
      .SIM_ASSERT_CHK(1),
      .TDATA_WIDTH(DATA_WIDTH),
      .TDEST_WIDTH(DEST_WIDTH),
      .TUSER_WIDTH(USER_WIDTH),
      .USE_ADV_FEATURES("0000")
   )
   xpm_fifo_axis_inst (
      .m_axis_tdata(out.data),
      .m_axis_tdest(out.dest),
      .m_axis_tlast(out.tlast),
      .m_axis_tuser(out.user),
      .m_axis_tvalid(out.valid),
      .s_axis_tready(in.ready),
      .m_aclk(clock),
      .m_axis_tready(out.ready),
      .s_aclk(clock),
      .s_aresetn(reset),
      .s_axis_tdata(in.data), 
      .s_axis_tdest(in.dest),
      .s_axis_tuser(in.user),
      .s_axis_tlast(in.tlast),
      .s_axis_tvalid(in.valid)
   );

endmodule