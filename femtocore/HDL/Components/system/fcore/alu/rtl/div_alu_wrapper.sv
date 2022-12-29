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


module div_alu_wrapper (
    input wire clock,
    input wire reset,
    axi_stream.slave operand_a,
    axi_stream.slave operand_b,
    axi_stream.slave operation,
    axi_stream.master add_result,
    axi_stream.master fti_result,
    axi_stream.master itf_result,
    axi_stream.master mul_result,
    axi_stream.master reciprocal_result
);

    fcore_div_alu div_alu_bd(
        .clock(clock),
        .reset(reset),
        .add_res_tdata(add_result.data),
        .add_res_tuser(add_result.user),
        .add_res_tvalid(add_result.valid),
        .adder_a_tdata(operand_a.data),
        .adder_a_tuser(operand_a.user),
        .adder_a_tvalid(operand_a.valid),
        .adder_b_tdata(operand_b.data),
        .adder_b_tvalid(operand_b.valid),
        .adder_op_tdata(operation.data),
        .adder_op_tvalid(operation.valid),
        .fti_b_tdata(operand_b.data),
        .fti_b_tuser(operand_b.user),
        .fti_b_tvalid(operand_b.valid),
        .fti_res_tdata(fti_result.data),
        .fti_res_tuser(fti_result.user),
        .fti_res_tvalid(fti_result.valid),
        .itf_a_tdata(operand_a.data),
        .itf_a_tuser(operand_a.user),
        .itf_a_tvalid(operand_a.valid),
        .itf_res_tdata(itf_result.data),
        .itf_res_tuser(itf_result.user),
        .itf_res_tvalid(itf_result.valid),
        .mul_res_tdata(mul_result.data),
        .mul_res_tuser(mul_result.user),
        .mul_res_tvalid(mul_result.valid),
        .mult_a_tdata(operand_a.data),
        .mult_a_tuser(operand_a.user),
        .mult_a_tvalid(operand_a.valid),
        .mult_b_tdata(operand_b.data),
        .mult_b_tvalid(operand_b.valid),
        .rec_a_tdata(operand_a.data),
        .rec_a_tuser(operand_a.user),
        .rec_a_tvalid(operand_a.valid),
        .rec_res_tdata(reciprocal_result.data),
        .rec_res_tuser(reciprocal_result.user),
        .rec_res_tvalid(reciprocal_result.valid)
    );

endmodule