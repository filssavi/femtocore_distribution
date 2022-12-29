//Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
//--------------------------------------------------------------------------------
//Tool Version: Vivado v.2020.1 (lin64) Build 2902540 Wed May 27 19:54:35 MDT 2020
//Date        : Tue Jun 23 15:20:18 2020
//Host        : fils running 64-bit Ubuntu 20.04 LTS
//Command     : generate_target fp_alu.bd
//Design      : fp_alu
//Purpose     : IP block netlist
//--------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

(* CORE_GENERATION_INFO = "fp_alu,IP_Integrator,{x_ipVendor=xilinx.com,x_ipLibrary=BlockDiagram,x_ipName=fp_alu,x_ipVersion=1.00.a,x_ipLanguage=VERILOG,numBlks=34,numReposBlks=18,numNonXlnxBlks=0,numHierBlks=16,maxHierDepth=0,numSysgenBlks=0,numHlsBlks=0,numHdlrefBlks=0,numPkgbdBlks=0,bdsource=USER,da_clkrst_cnt=22,synth_mode=OOC_per_IP}" *) (* HW_HANDOFF = "fp_alu.hwdef" *) 
module fp_alu
   (AXIS_A_tdata,
    AXIS_A_tdest,
    AXIS_A_tready,
    AXIS_A_tvalid,
    AXIS_B_tdata,
    AXIS_B_tdest,
    AXIS_B_tready,
    AXIS_B_tvalid,
    AXIS_OP_tdata,
    AXIS_OP_tdest,
    AXIS_OP_tready,
    AXIS_OP_tvalid,
    add_res_tdata,
    add_res_tvalid,
    clock,
    cmp_res_tdata,
    cmp_res_tvalid,
    fti_res_tdata,
    fti_res_tvalid,
    itf_res_tdata,
    itf_res_tvalid,
    mul_res_tdata,
    mul_res_tvalid,
    reset);
  (* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 AXIS_A TDATA" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME AXIS_A, CLK_DOMAIN fp_alu_clock, FREQ_HZ 100000000, HAS_TKEEP 0, HAS_TLAST 0, HAS_TREADY 1, HAS_TSTRB 0, INSERT_VIP 0, LAYERED_METADATA undef, PHASE 0.000, TDATA_NUM_BYTES 4, TDEST_WIDTH 4, TID_WIDTH 0, TUSER_WIDTH 0" *) input [31:0]AXIS_A_tdata;
  (* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 AXIS_A TDEST" *) input [3:0]AXIS_A_tdest;
  (* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 AXIS_A TREADY" *) output [0:0]AXIS_A_tready;
  (* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 AXIS_A TVALID" *) input [0:0]AXIS_A_tvalid;
  (* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 AXIS_B TDATA" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME AXIS_B, CLK_DOMAIN fp_alu_clock, FREQ_HZ 100000000, HAS_TKEEP 0, HAS_TLAST 0, HAS_TREADY 1, HAS_TSTRB 0, INSERT_VIP 0, LAYERED_METADATA undef, PHASE 0.000, TDATA_NUM_BYTES 4, TDEST_WIDTH 4, TID_WIDTH 0, TUSER_WIDTH 0" *) input [31:0]AXIS_B_tdata;
  (* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 AXIS_B TDEST" *) input [3:0]AXIS_B_tdest;
  (* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 AXIS_B TREADY" *) output [0:0]AXIS_B_tready;
  (* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 AXIS_B TVALID" *) input [0:0]AXIS_B_tvalid;
  (* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 AXIS_OP TDATA" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME AXIS_OP, CLK_DOMAIN fp_alu_clock, FREQ_HZ 100000000, HAS_TKEEP 0, HAS_TLAST 0, HAS_TREADY 1, HAS_TSTRB 0, INSERT_VIP 0, LAYERED_METADATA undef, PHASE 0.000, TDATA_NUM_BYTES 1, TDEST_WIDTH 4, TID_WIDTH 0, TUSER_WIDTH 0" *) input [7:0]AXIS_OP_tdata;
  (* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 AXIS_OP TDEST" *) input [3:0]AXIS_OP_tdest;
  (* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 AXIS_OP TREADY" *) output [0:0]AXIS_OP_tready;
  (* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 AXIS_OP TVALID" *) input [0:0]AXIS_OP_tvalid;
  (* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 add_res " *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME add_res, CLK_DOMAIN fp_alu_clock, FREQ_HZ 100000000, HAS_TKEEP 0, HAS_TLAST 0, HAS_TREADY 0, HAS_TSTRB 0, INSERT_VIP 0, LAYERED_METADATA xilinx.com:interface:datatypes:1.0 {TDATA {datatype {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value data} bitwidth {attribs {resolve_type generated dependency width format long minimum {} maximum {}} value 32} bitoffset {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 0} real {float {sigwidth {attribs {resolve_type generated dependency fractwidth format long minimum {} maximum {}} value 24}}}}} TDATA_WIDTH 32 TUSER {datatype {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value {}} bitwidth {attribs {resolve_type automatic dependency {} format long minimum {} maximum {}} value 0} bitoffset {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 0} struct {field_underflow {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value underflow} enabled {attribs {resolve_type generated dependency underflow_enabled format bool minimum {} maximum {}} value false} datatype {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value {}} bitwidth {attribs {resolve_type generated dependency underflow_bitwidth format long minimum {} maximum {}} value 0} bitoffset {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 0}}} field_overflow {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value overflow} enabled {attribs {resolve_type generated dependency overflow_enabled format bool minimum {} maximum {}} value false} datatype {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value {}} bitwidth {attribs {resolve_type generated dependency overflow_bitwidth format long minimum {} maximum {}} value 0} bitoffset {attribs {resolve_type generated dependency overflow_bitoffset format long minimum {} maximum {}} value 0}}} field_invalid_op {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value invalid_op} enabled {attribs {resolve_type generated dependency invalid_op_enabled format bool minimum {} maximum {}} value false} datatype {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value {}} bitwidth {attribs {resolve_type generated dependency invalid_op_bitwidth format long minimum {} maximum {}} value 0} bitoffset {attribs {resolve_type generated dependency invalid_op_bitoffset format long minimum {} maximum {}} value 0}}} field_div_by_zero {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value div_by_zero} enabled {attribs {resolve_type generated dependency div_by_zero_enabled format bool minimum {} maximum {}} value false} datatype {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value {}} bitwidth {attribs {resolve_type generated dependency div_by_zero_bitwidth format long minimum {} maximum {}} value 0} bitoffset {attribs {resolve_type generated dependency div_by_zero_bitoffset format long minimum {} maximum {}} value 0}}} field_accum_input_overflow {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value accum_input_overflow} enabled {attribs {resolve_type generated dependency accum_input_overflow_enabled format bool minimum {} maximum {}} value false} datatype {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value {}} bitwidth {attribs {resolve_type generated dependency accum_input_overflow_bitwidth format long minimum {} maximum {}} value 0} bitoffset {attribs {resolve_type generated dependency accum_input_overflow_bitoffset format long minimum {} maximum {}} value 0}}} field_accum_overflow {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value accum_overflow} enabled {attribs {resolve_type generated dependency accum_overflow_enabled format bool minimum {} maximum {}} value false} datatype {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value {}} bitwidth {attribs {resolve_type generated dependency accum_overflow_bitwidth format long minimum {} maximum {}} value 0} bitoffset {attribs {resolve_type generated dependency accum_overflow_bitoffset format long minimum {} maximum {}} value 0}}} field_a_tuser {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value a_tuser} enabled {attribs {resolve_type generated dependency a_tuser_enabled format bool minimum {} maximum {}} value false} datatype {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value {}} bitwidth {attribs {resolve_type generated dependency a_tuser_bitwidth format long minimum {} maximum {}} value 0} bitoffset {attribs {resolve_type generated dependency a_tuser_bitoffset format long minimum {} maximum {}} value 0}}} field_b_tuser {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value b_tuser} enabled {attribs {resolve_type generated dependency b_tuser_enabled format bool minimum {} maximum {}} value false} datatype {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value {}} bitwidth {attribs {resolve_type generated dependency b_tuser_bitwidth format long minimum {} maximum {}} value 0} bitoffset {attribs {resolve_type generated dependency b_tuser_bitoffset format long minimum {} maximum {}} value 0}}} field_c_tuser {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value c_tuser} enabled {attribs {resolve_type generated dependency c_tuser_enabled format bool minimum {} maximum {}} value false} datatype {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value {}} bitwidth {attribs {resolve_type generated dependency c_tuser_bitwidth format long minimum {} maximum {}} value 0} bitoffset {attribs {resolve_type generated dependency c_tuser_bitoffset format long minimum {} maximum {}} value 0}}} field_operation_tuser {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value operation_tuser} enabled {attribs {resolve_type generated dependency operation_tuser_enabled format bool minimum {} maximum {}} value false} datatype {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value {}} bitwidth {attribs {resolve_type generated dependency operation_tuser_bitwidth format long minimum {} maximum {}} value 0} bitoffset {attribs {resolve_type generated dependency operation_tuser_bitoffset format long minimum {} maximum {}} value 0}}}}}} TUSER_WIDTH 0}, PHASE 0.000, TDATA_NUM_BYTES 4, TDEST_WIDTH 0, TID_WIDTH 0, TUSER_WIDTH 0" *) output [31:0]add_res_tdata;
  (* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 add_res " *) output add_res_tvalid;
  (* X_INTERFACE_INFO = "xilinx.com:signal:clock:1.0 CLK.CLOCK CLK" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME CLK.CLOCK, ASSOCIATED_BUSIF AXIS_OP:AXIS_B:AXIS_A:itf_res:fti_res:cmp_res:mul_res:add_res, ASSOCIATED_RESET reset, CLK_DOMAIN fp_alu_clock, FREQ_HZ 100000000, FREQ_TOLERANCE_HZ 0, INSERT_VIP 0, PHASE 0.000" *) input clock;
  (* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 cmp_res " *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME cmp_res, CLK_DOMAIN fp_alu_clock, FREQ_HZ 100000000, HAS_TKEEP 0, HAS_TLAST 0, HAS_TREADY 0, HAS_TSTRB 0, INSERT_VIP 0, LAYERED_METADATA xilinx.com:interface:datatypes:1.0 {TDATA {datatype {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value result} bitwidth {attribs {resolve_type generated dependency width format long minimum {} maximum {}} value 1} bitoffset {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 0}}} TDATA_WIDTH 8 TUSER {datatype {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value {}} bitwidth {attribs {resolve_type automatic dependency {} format long minimum {} maximum {}} value 0} bitoffset {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 0} struct {field_underflow {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value underflow} enabled {attribs {resolve_type generated dependency underflow_enabled format bool minimum {} maximum {}} value false} datatype {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value {}} bitwidth {attribs {resolve_type generated dependency underflow_bitwidth format long minimum {} maximum {}} value 0} bitoffset {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 0}}} field_overflow {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value overflow} enabled {attribs {resolve_type generated dependency overflow_enabled format bool minimum {} maximum {}} value false} datatype {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value {}} bitwidth {attribs {resolve_type generated dependency overflow_bitwidth format long minimum {} maximum {}} value 0} bitoffset {attribs {resolve_type generated dependency overflow_bitoffset format long minimum {} maximum {}} value 0}}} field_invalid_op {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value invalid_op} enabled {attribs {resolve_type generated dependency invalid_op_enabled format bool minimum {} maximum {}} value false} datatype {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value {}} bitwidth {attribs {resolve_type generated dependency invalid_op_bitwidth format long minimum {} maximum {}} value 0} bitoffset {attribs {resolve_type generated dependency invalid_op_bitoffset format long minimum {} maximum {}} value 0}}} field_div_by_zero {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value div_by_zero} enabled {attribs {resolve_type generated dependency div_by_zero_enabled format bool minimum {} maximum {}} value false} datatype {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value {}} bitwidth {attribs {resolve_type generated dependency div_by_zero_bitwidth format long minimum {} maximum {}} value 0} bitoffset {attribs {resolve_type generated dependency div_by_zero_bitoffset format long minimum {} maximum {}} value 0}}} field_accum_input_overflow {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value accum_input_overflow} enabled {attribs {resolve_type generated dependency accum_input_overflow_enabled format bool minimum {} maximum {}} value false} datatype {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value {}} bitwidth {attribs {resolve_type generated dependency accum_input_overflow_bitwidth format long minimum {} maximum {}} value 0} bitoffset {attribs {resolve_type generated dependency accum_input_overflow_bitoffset format long minimum {} maximum {}} value 0}}} field_accum_overflow {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value accum_overflow} enabled {attribs {resolve_type generated dependency accum_overflow_enabled format bool minimum {} maximum {}} value false} datatype {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value {}} bitwidth {attribs {resolve_type generated dependency accum_overflow_bitwidth format long minimum {} maximum {}} value 0} bitoffset {attribs {resolve_type generated dependency accum_overflow_bitoffset format long minimum {} maximum {}} value 0}}} field_a_tuser {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value a_tuser} enabled {attribs {resolve_type generated dependency a_tuser_enabled format bool minimum {} maximum {}} value false} datatype {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value {}} bitwidth {attribs {resolve_type generated dependency a_tuser_bitwidth format long minimum {} maximum {}} value 0} bitoffset {attribs {resolve_type generated dependency a_tuser_bitoffset format long minimum {} maximum {}} value 0}}} field_b_tuser {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value b_tuser} enabled {attribs {resolve_type generated dependency b_tuser_enabled format bool minimum {} maximum {}} value false} datatype {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value {}} bitwidth {attribs {resolve_type generated dependency b_tuser_bitwidth format long minimum {} maximum {}} value 0} bitoffset {attribs {resolve_type generated dependency b_tuser_bitoffset format long minimum {} maximum {}} value 0}}} field_c_tuser {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value c_tuser} enabled {attribs {resolve_type generated dependency c_tuser_enabled format bool minimum {} maximum {}} value false} datatype {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value {}} bitwidth {attribs {resolve_type generated dependency c_tuser_bitwidth format long minimum {} maximum {}} value 0} bitoffset {attribs {resolve_type generated dependency c_tuser_bitoffset format long minimum {} maximum {}} value 0}}} field_operation_tuser {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value operation_tuser} enabled {attribs {resolve_type generated dependency operation_tuser_enabled format bool minimum {} maximum {}} value false} datatype {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value {}} bitwidth {attribs {resolve_type generated dependency operation_tuser_bitwidth format long minimum {} maximum {}} value 0} bitoffset {attribs {resolve_type generated dependency operation_tuser_bitoffset format long minimum {} maximum {}} value 0}}}}}} TUSER_WIDTH 0}, PHASE 0.000, TDATA_NUM_BYTES 1, TDEST_WIDTH 0, TID_WIDTH 0, TUSER_WIDTH 0" *) output [7:0]cmp_res_tdata;
  (* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 cmp_res " *) output cmp_res_tvalid;
  (* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 fti_res " *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME fti_res, CLK_DOMAIN fp_alu_clock, FREQ_HZ 100000000, HAS_TKEEP 0, HAS_TLAST 0, HAS_TREADY 0, HAS_TSTRB 0, INSERT_VIP 0, LAYERED_METADATA xilinx.com:interface:datatypes:1.0 {TDATA {datatype {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value data} bitwidth {attribs {resolve_type generated dependency width format long minimum {} maximum {}} value 32} bitoffset {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 0} real {fixed {fractwidth {attribs {resolve_type generated dependency fractwidth format long minimum {} maximum {}} value 0} signed {attribs {resolve_type immediate dependency {} format bool minimum {} maximum {}} value true}}}}} TDATA_WIDTH 32 TUSER {datatype {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value {}} bitwidth {attribs {resolve_type automatic dependency {} format long minimum {} maximum {}} value 0} bitoffset {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 0} struct {field_underflow {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value underflow} enabled {attribs {resolve_type generated dependency underflow_enabled format bool minimum {} maximum {}} value false} datatype {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value {}} bitwidth {attribs {resolve_type generated dependency underflow_bitwidth format long minimum {} maximum {}} value 0} bitoffset {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 0}}} field_overflow {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value overflow} enabled {attribs {resolve_type generated dependency overflow_enabled format bool minimum {} maximum {}} value false} datatype {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value {}} bitwidth {attribs {resolve_type generated dependency overflow_bitwidth format long minimum {} maximum {}} value 0} bitoffset {attribs {resolve_type generated dependency overflow_bitoffset format long minimum {} maximum {}} value 0}}} field_invalid_op {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value invalid_op} enabled {attribs {resolve_type generated dependency invalid_op_enabled format bool minimum {} maximum {}} value false} datatype {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value {}} bitwidth {attribs {resolve_type generated dependency invalid_op_bitwidth format long minimum {} maximum {}} value 0} bitoffset {attribs {resolve_type generated dependency invalid_op_bitoffset format long minimum {} maximum {}} value 0}}} field_div_by_zero {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value div_by_zero} enabled {attribs {resolve_type generated dependency div_by_zero_enabled format bool minimum {} maximum {}} value false} datatype {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value {}} bitwidth {attribs {resolve_type generated dependency div_by_zero_bitwidth format long minimum {} maximum {}} value 0} bitoffset {attribs {resolve_type generated dependency div_by_zero_bitoffset format long minimum {} maximum {}} value 0}}} field_accum_input_overflow {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value accum_input_overflow} enabled {attribs {resolve_type generated dependency accum_input_overflow_enabled format bool minimum {} maximum {}} value false} datatype {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value {}} bitwidth {attribs {resolve_type generated dependency accum_input_overflow_bitwidth format long minimum {} maximum {}} value 0} bitoffset {attribs {resolve_type generated dependency accum_input_overflow_bitoffset format long minimum {} maximum {}} value 0}}} field_accum_overflow {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value accum_overflow} enabled {attribs {resolve_type generated dependency accum_overflow_enabled format bool minimum {} maximum {}} value false} datatype {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value {}} bitwidth {attribs {resolve_type generated dependency accum_overflow_bitwidth format long minimum {} maximum {}} value 0} bitoffset {attribs {resolve_type generated dependency accum_overflow_bitoffset format long minimum {} maximum {}} value 0}}} field_a_tuser {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value a_tuser} enabled {attribs {resolve_type generated dependency a_tuser_enabled format bool minimum {} maximum {}} value false} datatype {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value {}} bitwidth {attribs {resolve_type generated dependency a_tuser_bitwidth format long minimum {} maximum {}} value 0} bitoffset {attribs {resolve_type generated dependency a_tuser_bitoffset format long minimum {} maximum {}} value 0}}} field_b_tuser {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value b_tuser} enabled {attribs {resolve_type generated dependency b_tuser_enabled format bool minimum {} maximum {}} value false} datatype {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value {}} bitwidth {attribs {resolve_type generated dependency b_tuser_bitwidth format long minimum {} maximum {}} value 0} bitoffset {attribs {resolve_type generated dependency b_tuser_bitoffset format long minimum {} maximum {}} value 0}}} field_c_tuser {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value c_tuser} enabled {attribs {resolve_type generated dependency c_tuser_enabled format bool minimum {} maximum {}} value false} datatype {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value {}} bitwidth {attribs {resolve_type generated dependency c_tuser_bitwidth format long minimum {} maximum {}} value 0} bitoffset {attribs {resolve_type generated dependency c_tuser_bitoffset format long minimum {} maximum {}} value 0}}} field_operation_tuser {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value operation_tuser} enabled {attribs {resolve_type generated dependency operation_tuser_enabled format bool minimum {} maximum {}} value false} datatype {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value {}} bitwidth {attribs {resolve_type generated dependency operation_tuser_bitwidth format long minimum {} maximum {}} value 0} bitoffset {attribs {resolve_type generated dependency operation_tuser_bitoffset format long minimum {} maximum {}} value 0}}}}}} TUSER_WIDTH 0}, PHASE 0.000, TDATA_NUM_BYTES 4, TDEST_WIDTH 0, TID_WIDTH 0, TUSER_WIDTH 0" *) output [31:0]fti_res_tdata;
  (* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 fti_res " *) output fti_res_tvalid;
  (* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 itf_res " *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME itf_res, CLK_DOMAIN fp_alu_clock, FREQ_HZ 100000000, HAS_TKEEP 0, HAS_TLAST 0, HAS_TREADY 0, HAS_TSTRB 0, INSERT_VIP 0, LAYERED_METADATA xilinx.com:interface:datatypes:1.0 {TDATA {datatype {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value data} bitwidth {attribs {resolve_type generated dependency width format long minimum {} maximum {}} value 32} bitoffset {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 0} real {float {sigwidth {attribs {resolve_type generated dependency fractwidth format long minimum {} maximum {}} value 24}}}}} TDATA_WIDTH 32 TUSER {datatype {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value {}} bitwidth {attribs {resolve_type automatic dependency {} format long minimum {} maximum {}} value 0} bitoffset {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 0} struct {field_underflow {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value underflow} enabled {attribs {resolve_type generated dependency underflow_enabled format bool minimum {} maximum {}} value false} datatype {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value {}} bitwidth {attribs {resolve_type generated dependency underflow_bitwidth format long minimum {} maximum {}} value 0} bitoffset {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 0}}} field_overflow {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value overflow} enabled {attribs {resolve_type generated dependency overflow_enabled format bool minimum {} maximum {}} value false} datatype {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value {}} bitwidth {attribs {resolve_type generated dependency overflow_bitwidth format long minimum {} maximum {}} value 0} bitoffset {attribs {resolve_type generated dependency overflow_bitoffset format long minimum {} maximum {}} value 0}}} field_invalid_op {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value invalid_op} enabled {attribs {resolve_type generated dependency invalid_op_enabled format bool minimum {} maximum {}} value false} datatype {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value {}} bitwidth {attribs {resolve_type generated dependency invalid_op_bitwidth format long minimum {} maximum {}} value 0} bitoffset {attribs {resolve_type generated dependency invalid_op_bitoffset format long minimum {} maximum {}} value 0}}} field_div_by_zero {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value div_by_zero} enabled {attribs {resolve_type generated dependency div_by_zero_enabled format bool minimum {} maximum {}} value false} datatype {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value {}} bitwidth {attribs {resolve_type generated dependency div_by_zero_bitwidth format long minimum {} maximum {}} value 0} bitoffset {attribs {resolve_type generated dependency div_by_zero_bitoffset format long minimum {} maximum {}} value 0}}} field_accum_input_overflow {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value accum_input_overflow} enabled {attribs {resolve_type generated dependency accum_input_overflow_enabled format bool minimum {} maximum {}} value false} datatype {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value {}} bitwidth {attribs {resolve_type generated dependency accum_input_overflow_bitwidth format long minimum {} maximum {}} value 0} bitoffset {attribs {resolve_type generated dependency accum_input_overflow_bitoffset format long minimum {} maximum {}} value 0}}} field_accum_overflow {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value accum_overflow} enabled {attribs {resolve_type generated dependency accum_overflow_enabled format bool minimum {} maximum {}} value false} datatype {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value {}} bitwidth {attribs {resolve_type generated dependency accum_overflow_bitwidth format long minimum {} maximum {}} value 0} bitoffset {attribs {resolve_type generated dependency accum_overflow_bitoffset format long minimum {} maximum {}} value 0}}} field_a_tuser {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value a_tuser} enabled {attribs {resolve_type generated dependency a_tuser_enabled format bool minimum {} maximum {}} value false} datatype {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value {}} bitwidth {attribs {resolve_type generated dependency a_tuser_bitwidth format long minimum {} maximum {}} value 0} bitoffset {attribs {resolve_type generated dependency a_tuser_bitoffset format long minimum {} maximum {}} value 0}}} field_b_tuser {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value b_tuser} enabled {attribs {resolve_type generated dependency b_tuser_enabled format bool minimum {} maximum {}} value false} datatype {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value {}} bitwidth {attribs {resolve_type generated dependency b_tuser_bitwidth format long minimum {} maximum {}} value 0} bitoffset {attribs {resolve_type generated dependency b_tuser_bitoffset format long minimum {} maximum {}} value 0}}} field_c_tuser {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value c_tuser} enabled {attribs {resolve_type generated dependency c_tuser_enabled format bool minimum {} maximum {}} value false} datatype {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value {}} bitwidth {attribs {resolve_type generated dependency c_tuser_bitwidth format long minimum {} maximum {}} value 0} bitoffset {attribs {resolve_type generated dependency c_tuser_bitoffset format long minimum {} maximum {}} value 0}}} field_operation_tuser {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value operation_tuser} enabled {attribs {resolve_type generated dependency operation_tuser_enabled format bool minimum {} maximum {}} value false} datatype {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value {}} bitwidth {attribs {resolve_type generated dependency operation_tuser_bitwidth format long minimum {} maximum {}} value 0} bitoffset {attribs {resolve_type generated dependency operation_tuser_bitoffset format long minimum {} maximum {}} value 0}}}}}} TUSER_WIDTH 0}, PHASE 0.000, TDATA_NUM_BYTES 4, TDEST_WIDTH 0, TID_WIDTH 0, TUSER_WIDTH 0" *) output [31:0]itf_res_tdata;
  (* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 itf_res " *) output itf_res_tvalid;
  (* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 mul_res " *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME mul_res, CLK_DOMAIN fp_alu_clock, FREQ_HZ 100000000, HAS_TKEEP 0, HAS_TLAST 0, HAS_TREADY 0, HAS_TSTRB 0, INSERT_VIP 0, LAYERED_METADATA xilinx.com:interface:datatypes:1.0 {TDATA {datatype {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value data} bitwidth {attribs {resolve_type generated dependency width format long minimum {} maximum {}} value 32} bitoffset {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 0} real {float {sigwidth {attribs {resolve_type generated dependency fractwidth format long minimum {} maximum {}} value 24}}}}} TDATA_WIDTH 32 TUSER {datatype {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value {}} bitwidth {attribs {resolve_type automatic dependency {} format long minimum {} maximum {}} value 0} bitoffset {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 0} struct {field_underflow {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value underflow} enabled {attribs {resolve_type generated dependency underflow_enabled format bool minimum {} maximum {}} value false} datatype {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value {}} bitwidth {attribs {resolve_type generated dependency underflow_bitwidth format long minimum {} maximum {}} value 0} bitoffset {attribs {resolve_type immediate dependency {} format long minimum {} maximum {}} value 0}}} field_overflow {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value overflow} enabled {attribs {resolve_type generated dependency overflow_enabled format bool minimum {} maximum {}} value false} datatype {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value {}} bitwidth {attribs {resolve_type generated dependency overflow_bitwidth format long minimum {} maximum {}} value 0} bitoffset {attribs {resolve_type generated dependency overflow_bitoffset format long minimum {} maximum {}} value 0}}} field_invalid_op {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value invalid_op} enabled {attribs {resolve_type generated dependency invalid_op_enabled format bool minimum {} maximum {}} value false} datatype {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value {}} bitwidth {attribs {resolve_type generated dependency invalid_op_bitwidth format long minimum {} maximum {}} value 0} bitoffset {attribs {resolve_type generated dependency invalid_op_bitoffset format long minimum {} maximum {}} value 0}}} field_div_by_zero {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value div_by_zero} enabled {attribs {resolve_type generated dependency div_by_zero_enabled format bool minimum {} maximum {}} value false} datatype {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value {}} bitwidth {attribs {resolve_type generated dependency div_by_zero_bitwidth format long minimum {} maximum {}} value 0} bitoffset {attribs {resolve_type generated dependency div_by_zero_bitoffset format long minimum {} maximum {}} value 0}}} field_accum_input_overflow {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value accum_input_overflow} enabled {attribs {resolve_type generated dependency accum_input_overflow_enabled format bool minimum {} maximum {}} value false} datatype {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value {}} bitwidth {attribs {resolve_type generated dependency accum_input_overflow_bitwidth format long minimum {} maximum {}} value 0} bitoffset {attribs {resolve_type generated dependency accum_input_overflow_bitoffset format long minimum {} maximum {}} value 0}}} field_accum_overflow {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value accum_overflow} enabled {attribs {resolve_type generated dependency accum_overflow_enabled format bool minimum {} maximum {}} value false} datatype {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value {}} bitwidth {attribs {resolve_type generated dependency accum_overflow_bitwidth format long minimum {} maximum {}} value 0} bitoffset {attribs {resolve_type generated dependency accum_overflow_bitoffset format long minimum {} maximum {}} value 0}}} field_a_tuser {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value a_tuser} enabled {attribs {resolve_type generated dependency a_tuser_enabled format bool minimum {} maximum {}} value false} datatype {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value {}} bitwidth {attribs {resolve_type generated dependency a_tuser_bitwidth format long minimum {} maximum {}} value 0} bitoffset {attribs {resolve_type generated dependency a_tuser_bitoffset format long minimum {} maximum {}} value 0}}} field_b_tuser {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value b_tuser} enabled {attribs {resolve_type generated dependency b_tuser_enabled format bool minimum {} maximum {}} value false} datatype {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value {}} bitwidth {attribs {resolve_type generated dependency b_tuser_bitwidth format long minimum {} maximum {}} value 0} bitoffset {attribs {resolve_type generated dependency b_tuser_bitoffset format long minimum {} maximum {}} value 0}}} field_c_tuser {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value c_tuser} enabled {attribs {resolve_type generated dependency c_tuser_enabled format bool minimum {} maximum {}} value false} datatype {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value {}} bitwidth {attribs {resolve_type generated dependency c_tuser_bitwidth format long minimum {} maximum {}} value 0} bitoffset {attribs {resolve_type generated dependency c_tuser_bitoffset format long minimum {} maximum {}} value 0}}} field_operation_tuser {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value operation_tuser} enabled {attribs {resolve_type generated dependency operation_tuser_enabled format bool minimum {} maximum {}} value false} datatype {name {attribs {resolve_type immediate dependency {} format string minimum {} maximum {}} value {}} bitwidth {attribs {resolve_type generated dependency operation_tuser_bitwidth format long minimum {} maximum {}} value 0} bitoffset {attribs {resolve_type generated dependency operation_tuser_bitoffset format long minimum {} maximum {}} value 0}}}}}} TUSER_WIDTH 0}, PHASE 0.000, TDATA_NUM_BYTES 4, TDEST_WIDTH 0, TID_WIDTH 0, TUSER_WIDTH 0" *) output [31:0]mul_res_tdata;
  (* X_INTERFACE_INFO = "xilinx.com:interface:axis:1.0 mul_res " *) output mul_res_tvalid;
  (* X_INTERFACE_INFO = "xilinx.com:signal:reset:1.0 RST.RESET RST" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME RST.RESET, INSERT_VIP 0, POLARITY ACTIVE_LOW" *) input reset;

  wire ARESETN_0_1;
  wire [31:0]AXIS_A_1_TDATA;
  wire [3:0]AXIS_A_1_TDEST;
  wire [0:0]AXIS_A_1_TREADY;
  wire [0:0]AXIS_A_1_TVALID;
  wire [31:0]AXIS_B_1_TDATA;
  wire [3:0]AXIS_B_1_TDEST;
  wire [0:0]AXIS_B_1_TREADY;
  wire [0:0]AXIS_B_1_TVALID;
  wire [7:0]AXIS_OP_1_TDATA;
  wire [3:0]AXIS_OP_1_TDEST;
  wire [0:0]AXIS_OP_1_TREADY;
  wire [0:0]AXIS_OP_1_TVALID;
  wire [31:0]FP_adder_M_AXIS_RESULT_TDATA;
  wire FP_adder_M_AXIS_RESULT_TVALID;
  wire [7:0]FP_comparer_M_AXIS_RESULT_TDATA;
  wire FP_comparer_M_AXIS_RESULT_TVALID;
  wire [31:0]FP_multiplier_M_AXIS_RESULT_TDATA;
  wire FP_multiplier_M_AXIS_RESULT_TVALID;
  wire aclk_0_1;
  wire [31:0]axis_interconnect_1_M00_AXIS_TDATA;
  wire axis_interconnect_1_M00_AXIS_TVALID;
  wire [31:0]axis_interconnect_1_M01_AXIS_TDATA;
  wire axis_interconnect_1_M01_AXIS_TREADY;
  wire axis_interconnect_1_M01_AXIS_TVALID;
  wire [31:0]axis_interconnect_1_M02_AXIS_TDATA;
  wire axis_interconnect_1_M02_AXIS_TVALID;
  wire [31:0]axis_interconnect_1_M03_AXIS_TDATA;
  wire axis_interconnect_1_M03_AXIS_TVALID;
  wire [31:0]axis_interconnect_2_M00_AXIS_TDATA;
  wire axis_interconnect_2_M00_AXIS_TVALID;
  wire [31:0]axis_interconnect_2_M01_AXIS_TDATA;
  wire axis_interconnect_2_M01_AXIS_TREADY;
  wire axis_interconnect_2_M01_AXIS_TVALID;
  wire [31:0]axis_interconnect_2_M02_AXIS_TDATA;
  wire axis_interconnect_2_M02_AXIS_TVALID;
  wire [31:0]axis_interconnect_2_M03_AXIS_TDATA;
  wire axis_interconnect_2_M03_AXIS_TVALID;
  wire [7:0]axis_interconnect_3_M00_AXIS_TDATA;
  wire axis_interconnect_3_M00_AXIS_TVALID;
  wire [7:0]axis_interconnect_3_M01_AXIS_TDATA;
  wire axis_interconnect_3_M01_AXIS_TREADY;
  wire axis_interconnect_3_M01_AXIS_TVALID;
  wire [31:0]fixed_to_float_M_AXIS_RESULT_TDATA;
  wire fixed_to_float_M_AXIS_RESULT_TVALID;
  wire [31:0]float_to_fixed_M_AXIS_RESULT_TDATA;
  wire float_to_fixed_M_AXIS_RESULT_TVALID;

  assign ARESETN_0_1 = reset;
  assign AXIS_A_1_TDATA = AXIS_A_tdata[31:0];
  assign AXIS_A_1_TDEST = AXIS_A_tdest[3:0];
  assign AXIS_A_1_TVALID = AXIS_A_tvalid[0];
  assign AXIS_A_tready[0] = AXIS_A_1_TREADY;
  assign AXIS_B_1_TDATA = AXIS_B_tdata[31:0];
  assign AXIS_B_1_TDEST = AXIS_B_tdest[3:0];
  assign AXIS_B_1_TVALID = AXIS_B_tvalid[0];
  assign AXIS_B_tready[0] = AXIS_B_1_TREADY;
  assign AXIS_OP_1_TDATA = AXIS_OP_tdata[7:0];
  assign AXIS_OP_1_TDEST = AXIS_OP_tdest[3:0];
  assign AXIS_OP_1_TVALID = AXIS_OP_tvalid[0];
  assign AXIS_OP_tready[0] = AXIS_OP_1_TREADY;
  assign aclk_0_1 = clock;
  assign add_res_tdata[31:0] = FP_adder_M_AXIS_RESULT_TDATA;
  assign add_res_tvalid = FP_adder_M_AXIS_RESULT_TVALID;
  assign cmp_res_tdata[7:0] = FP_comparer_M_AXIS_RESULT_TDATA;
  assign cmp_res_tvalid = FP_comparer_M_AXIS_RESULT_TVALID;
  assign fti_res_tdata[31:0] = float_to_fixed_M_AXIS_RESULT_TDATA;
  assign fti_res_tvalid = float_to_fixed_M_AXIS_RESULT_TVALID;
  assign itf_res_tdata[31:0] = fixed_to_float_M_AXIS_RESULT_TDATA;
  assign itf_res_tvalid = fixed_to_float_M_AXIS_RESULT_TVALID;
  assign mul_res_tdata[31:0] = FP_multiplier_M_AXIS_RESULT_TDATA;
  assign mul_res_tvalid = FP_multiplier_M_AXIS_RESULT_TVALID;
  fp_alu_FP_adder_0 FP_adder
       (.aclk(aclk_0_1),
        .aresetn(ARESETN_0_1),
        .m_axis_result_tdata(FP_adder_M_AXIS_RESULT_TDATA),
        .m_axis_result_tvalid(FP_adder_M_AXIS_RESULT_TVALID),
        .s_axis_a_tdata(axis_interconnect_1_M01_AXIS_TDATA),
        .s_axis_a_tready(axis_interconnect_1_M01_AXIS_TREADY),
        .s_axis_a_tvalid(axis_interconnect_1_M01_AXIS_TVALID),
        .s_axis_b_tdata(axis_interconnect_2_M01_AXIS_TDATA),
        .s_axis_b_tready(axis_interconnect_2_M01_AXIS_TREADY),
        .s_axis_b_tvalid(axis_interconnect_2_M01_AXIS_TVALID),
        .s_axis_operation_tdata(axis_interconnect_3_M01_AXIS_TDATA),
        .s_axis_operation_tready(axis_interconnect_3_M01_AXIS_TREADY),
        .s_axis_operation_tvalid(axis_interconnect_3_M01_AXIS_TVALID));
  fp_alu_FP_comparer_0 FP_comparer
       (.aclk(aclk_0_1),
        .aresetn(ARESETN_0_1),
        .m_axis_result_tdata(FP_comparer_M_AXIS_RESULT_TDATA),
        .m_axis_result_tvalid(FP_comparer_M_AXIS_RESULT_TVALID),
        .s_axis_a_tdata(axis_interconnect_1_M02_AXIS_TDATA),
        .s_axis_a_tvalid(axis_interconnect_1_M02_AXIS_TVALID),
        .s_axis_b_tdata(axis_interconnect_2_M02_AXIS_TDATA),
        .s_axis_b_tvalid(axis_interconnect_2_M02_AXIS_TVALID),
        .s_axis_operation_tdata(axis_interconnect_3_M00_AXIS_TDATA),
        .s_axis_operation_tvalid(axis_interconnect_3_M00_AXIS_TVALID));
  fp_alu_FP_multiplier_0 FP_multiplier
       (.aclk(aclk_0_1),
        .aresetn(ARESETN_0_1),
        .m_axis_result_tdata(FP_multiplier_M_AXIS_RESULT_TDATA),
        .m_axis_result_tvalid(FP_multiplier_M_AXIS_RESULT_TVALID),
        .s_axis_a_tdata(axis_interconnect_1_M00_AXIS_TDATA),
        .s_axis_a_tvalid(axis_interconnect_1_M00_AXIS_TVALID),
        .s_axis_b_tdata(axis_interconnect_2_M00_AXIS_TDATA),
        .s_axis_b_tvalid(axis_interconnect_2_M00_AXIS_TVALID));
  fp_alu_axis_interconnect_0_1 axis_interconnect_1
       (.ACLK(aclk_0_1),
        .ARESETN(ARESETN_0_1),
        .M00_AXIS_ACLK(aclk_0_1),
        .M00_AXIS_ARESETN(ARESETN_0_1),
        .M00_AXIS_tdata(axis_interconnect_1_M00_AXIS_TDATA),
        .M00_AXIS_tvalid(axis_interconnect_1_M00_AXIS_TVALID),
        .M01_AXIS_ACLK(aclk_0_1),
        .M01_AXIS_ARESETN(ARESETN_0_1),
        .M01_AXIS_tdata(axis_interconnect_1_M01_AXIS_TDATA),
        .M01_AXIS_tready(axis_interconnect_1_M01_AXIS_TREADY),
        .M01_AXIS_tvalid(axis_interconnect_1_M01_AXIS_TVALID),
        .M02_AXIS_ACLK(aclk_0_1),
        .M02_AXIS_ARESETN(ARESETN_0_1),
        .M02_AXIS_tdata(axis_interconnect_1_M02_AXIS_TDATA),
        .M02_AXIS_tvalid(axis_interconnect_1_M02_AXIS_TVALID),
        .M03_AXIS_ACLK(aclk_0_1),
        .M03_AXIS_ARESETN(ARESETN_0_1),
        .M03_AXIS_tdata(axis_interconnect_1_M03_AXIS_TDATA),
        .M03_AXIS_tvalid(axis_interconnect_1_M03_AXIS_TVALID),
        .S00_AXIS_ACLK(aclk_0_1),
        .S00_AXIS_ARESETN(ARESETN_0_1),
        .S00_AXIS_tdata(AXIS_A_1_TDATA),
        .S00_AXIS_tdest(AXIS_A_1_TDEST),
        .S00_AXIS_tready(AXIS_A_1_TREADY),
        .S00_AXIS_tvalid(AXIS_A_1_TVALID));
  fp_alu_axis_interconnect_1_0 axis_interconnect_2
       (.ACLK(aclk_0_1),
        .ARESETN(ARESETN_0_1),
        .M00_AXIS_ACLK(aclk_0_1),
        .M00_AXIS_ARESETN(ARESETN_0_1),
        .M00_AXIS_tdata(axis_interconnect_2_M00_AXIS_TDATA),
        .M00_AXIS_tvalid(axis_interconnect_2_M00_AXIS_TVALID),
        .M01_AXIS_ACLK(aclk_0_1),
        .M01_AXIS_ARESETN(ARESETN_0_1),
        .M01_AXIS_tdata(axis_interconnect_2_M01_AXIS_TDATA),
        .M01_AXIS_tready(axis_interconnect_2_M01_AXIS_TREADY),
        .M01_AXIS_tvalid(axis_interconnect_2_M01_AXIS_TVALID),
        .M02_AXIS_ACLK(aclk_0_1),
        .M02_AXIS_ARESETN(ARESETN_0_1),
        .M02_AXIS_tdata(axis_interconnect_2_M02_AXIS_TDATA),
        .M02_AXIS_tvalid(axis_interconnect_2_M02_AXIS_TVALID),
        .M03_AXIS_ACLK(aclk_0_1),
        .M03_AXIS_ARESETN(ARESETN_0_1),
        .M03_AXIS_tdata(axis_interconnect_2_M03_AXIS_TDATA),
        .M03_AXIS_tvalid(axis_interconnect_2_M03_AXIS_TVALID),
        .S00_AXIS_ACLK(aclk_0_1),
        .S00_AXIS_ARESETN(ARESETN_0_1),
        .S00_AXIS_tdata(AXIS_B_1_TDATA),
        .S00_AXIS_tdest(AXIS_B_1_TDEST),
        .S00_AXIS_tready(AXIS_B_1_TREADY),
        .S00_AXIS_tvalid(AXIS_B_1_TVALID));
  fp_alu_axis_interconnect_1_1 axis_interconnect_3
       (.ACLK(aclk_0_1),
        .ARESETN(ARESETN_0_1),
        .M00_AXIS_ACLK(aclk_0_1),
        .M00_AXIS_ARESETN(ARESETN_0_1),
        .M00_AXIS_tdata(axis_interconnect_3_M00_AXIS_TDATA),
        .M00_AXIS_tvalid(axis_interconnect_3_M00_AXIS_TVALID),
        .M01_AXIS_ACLK(aclk_0_1),
        .M01_AXIS_ARESETN(ARESETN_0_1),
        .M01_AXIS_tdata(axis_interconnect_3_M01_AXIS_TDATA),
        .M01_AXIS_tready(axis_interconnect_3_M01_AXIS_TREADY),
        .M01_AXIS_tvalid(axis_interconnect_3_M01_AXIS_TVALID),
        .S00_AXIS_ACLK(aclk_0_1),
        .S00_AXIS_ARESETN(ARESETN_0_1),
        .S00_AXIS_tdata(AXIS_OP_1_TDATA),
        .S00_AXIS_tdest(AXIS_OP_1_TDEST),
        .S00_AXIS_tready(AXIS_OP_1_TREADY),
        .S00_AXIS_tvalid(AXIS_OP_1_TVALID));
  fp_alu_fixed_to_float_0 fixed_to_float
       (.aclk(aclk_0_1),
        .aresetn(ARESETN_0_1),
        .m_axis_result_tdata(fixed_to_float_M_AXIS_RESULT_TDATA),
        .m_axis_result_tvalid(fixed_to_float_M_AXIS_RESULT_TVALID),
        .s_axis_a_tdata(axis_interconnect_1_M03_AXIS_TDATA),
        .s_axis_a_tvalid(axis_interconnect_1_M03_AXIS_TVALID));
  fp_alu_float_to_fixed_0 float_to_fixed
       (.aclk(aclk_0_1),
        .aresetn(ARESETN_0_1),
        .m_axis_result_tdata(float_to_fixed_M_AXIS_RESULT_TDATA),
        .m_axis_result_tvalid(float_to_fixed_M_AXIS_RESULT_TVALID),
        .s_axis_a_tdata(axis_interconnect_2_M03_AXIS_TDATA),
        .s_axis_a_tvalid(axis_interconnect_2_M03_AXIS_TVALID));
endmodule

module fp_alu_axis_interconnect_0_1
   (ACLK,
    ARESETN,
    M00_AXIS_ACLK,
    M00_AXIS_ARESETN,
    M00_AXIS_tdata,
    M00_AXIS_tvalid,
    M01_AXIS_ACLK,
    M01_AXIS_ARESETN,
    M01_AXIS_tdata,
    M01_AXIS_tready,
    M01_AXIS_tvalid,
    M02_AXIS_ACLK,
    M02_AXIS_ARESETN,
    M02_AXIS_tdata,
    M02_AXIS_tvalid,
    M03_AXIS_ACLK,
    M03_AXIS_ARESETN,
    M03_AXIS_tdata,
    M03_AXIS_tvalid,
    S00_AXIS_ACLK,
    S00_AXIS_ARESETN,
    S00_AXIS_tdata,
    S00_AXIS_tdest,
    S00_AXIS_tready,
    S00_AXIS_tvalid);
  input ACLK;
  input ARESETN;
  input M00_AXIS_ACLK;
  input M00_AXIS_ARESETN;
  output [31:0]M00_AXIS_tdata;
  output M00_AXIS_tvalid;
  input M01_AXIS_ACLK;
  input M01_AXIS_ARESETN;
  output [31:0]M01_AXIS_tdata;
  input M01_AXIS_tready;
  output M01_AXIS_tvalid;
  input M02_AXIS_ACLK;
  input M02_AXIS_ARESETN;
  output [31:0]M02_AXIS_tdata;
  output M02_AXIS_tvalid;
  input M03_AXIS_ACLK;
  input M03_AXIS_ARESETN;
  output [31:0]M03_AXIS_tdata;
  output M03_AXIS_tvalid;
  input S00_AXIS_ACLK;
  input S00_AXIS_ARESETN;
  input [31:0]S00_AXIS_tdata;
  input [3:0]S00_AXIS_tdest;
  output [0:0]S00_AXIS_tready;
  input [0:0]S00_AXIS_tvalid;

  wire axis_interconnect_1_ACLK_net;
  wire axis_interconnect_1_ARESETN_net;
  wire [31:0]axis_interconnect_1_to_s00_couplers_TDATA;
  wire [3:0]axis_interconnect_1_to_s00_couplers_TDEST;
  wire [0:0]axis_interconnect_1_to_s00_couplers_TREADY;
  wire [0:0]axis_interconnect_1_to_s00_couplers_TVALID;
  wire [31:0]m00_couplers_to_axis_interconnect_1_TDATA;
  wire m00_couplers_to_axis_interconnect_1_TVALID;
  wire [31:0]m01_couplers_to_axis_interconnect_1_TDATA;
  wire m01_couplers_to_axis_interconnect_1_TREADY;
  wire m01_couplers_to_axis_interconnect_1_TVALID;
  wire [31:0]m02_couplers_to_axis_interconnect_1_TDATA;
  wire m02_couplers_to_axis_interconnect_1_TVALID;
  wire [31:0]m03_couplers_to_axis_interconnect_1_TDATA;
  wire m03_couplers_to_axis_interconnect_1_TVALID;
  wire [31:0]s00_couplers_to_xbar_TDATA;
  wire [3:0]s00_couplers_to_xbar_TDEST;
  wire [0:0]s00_couplers_to_xbar_TREADY;
  wire [0:0]s00_couplers_to_xbar_TVALID;
  wire [31:0]xbar_to_m00_couplers_TDATA;
  wire [3:0]xbar_to_m00_couplers_TDEST;
  wire xbar_to_m00_couplers_TREADY;
  wire [0:0]xbar_to_m00_couplers_TVALID;
  wire [63:32]xbar_to_m01_couplers_TDATA;
  wire [7:4]xbar_to_m01_couplers_TDEST;
  wire xbar_to_m01_couplers_TREADY;
  wire [1:1]xbar_to_m01_couplers_TVALID;
  wire [95:64]xbar_to_m02_couplers_TDATA;
  wire [11:8]xbar_to_m02_couplers_TDEST;
  wire xbar_to_m02_couplers_TREADY;
  wire [2:2]xbar_to_m02_couplers_TVALID;
  wire [127:96]xbar_to_m03_couplers_TDATA;
  wire [15:12]xbar_to_m03_couplers_TDEST;
  wire xbar_to_m03_couplers_TREADY;
  wire [3:3]xbar_to_m03_couplers_TVALID;

  assign M00_AXIS_tdata[31:0] = m00_couplers_to_axis_interconnect_1_TDATA;
  assign M00_AXIS_tvalid = m00_couplers_to_axis_interconnect_1_TVALID;
  assign M01_AXIS_tdata[31:0] = m01_couplers_to_axis_interconnect_1_TDATA;
  assign M01_AXIS_tvalid = m01_couplers_to_axis_interconnect_1_TVALID;
  assign M02_AXIS_tdata[31:0] = m02_couplers_to_axis_interconnect_1_TDATA;
  assign M02_AXIS_tvalid = m02_couplers_to_axis_interconnect_1_TVALID;
  assign M03_AXIS_tdata[31:0] = m03_couplers_to_axis_interconnect_1_TDATA;
  assign M03_AXIS_tvalid = m03_couplers_to_axis_interconnect_1_TVALID;
  assign S00_AXIS_tready[0] = axis_interconnect_1_to_s00_couplers_TREADY;
  assign axis_interconnect_1_ACLK_net = ACLK;
  assign axis_interconnect_1_ARESETN_net = ARESETN;
  assign axis_interconnect_1_to_s00_couplers_TDATA = S00_AXIS_tdata[31:0];
  assign axis_interconnect_1_to_s00_couplers_TDEST = S00_AXIS_tdest[3:0];
  assign axis_interconnect_1_to_s00_couplers_TVALID = S00_AXIS_tvalid[0];
  assign m01_couplers_to_axis_interconnect_1_TREADY = M01_AXIS_tready;
  m00_couplers_imp_3M6IPR m00_couplers
       (.M_AXIS_ACLK(axis_interconnect_1_ACLK_net),
        .M_AXIS_ARESETN(axis_interconnect_1_ARESETN_net),
        .M_AXIS_tdata(m00_couplers_to_axis_interconnect_1_TDATA),
        .M_AXIS_tvalid(m00_couplers_to_axis_interconnect_1_TVALID),
        .S_AXIS_ACLK(axis_interconnect_1_ACLK_net),
        .S_AXIS_ARESETN(axis_interconnect_1_ARESETN_net),
        .S_AXIS_tdata(xbar_to_m00_couplers_TDATA),
        .S_AXIS_tdest(xbar_to_m00_couplers_TDEST),
        .S_AXIS_tready(xbar_to_m00_couplers_TREADY),
        .S_AXIS_tvalid(xbar_to_m00_couplers_TVALID));
  m01_couplers_imp_19BY0TQ m01_couplers
       (.M_AXIS_ACLK(axis_interconnect_1_ACLK_net),
        .M_AXIS_ARESETN(axis_interconnect_1_ARESETN_net),
        .M_AXIS_tdata(m01_couplers_to_axis_interconnect_1_TDATA),
        .M_AXIS_tready(m01_couplers_to_axis_interconnect_1_TREADY),
        .M_AXIS_tvalid(m01_couplers_to_axis_interconnect_1_TVALID),
        .S_AXIS_ACLK(axis_interconnect_1_ACLK_net),
        .S_AXIS_ARESETN(axis_interconnect_1_ARESETN_net),
        .S_AXIS_tdata(xbar_to_m01_couplers_TDATA),
        .S_AXIS_tdest(xbar_to_m01_couplers_TDEST),
        .S_AXIS_tready(xbar_to_m01_couplers_TREADY),
        .S_AXIS_tvalid(xbar_to_m01_couplers_TVALID));
  m02_couplers_imp_12H0BJ0 m02_couplers
       (.M_AXIS_ACLK(axis_interconnect_1_ACLK_net),
        .M_AXIS_ARESETN(axis_interconnect_1_ARESETN_net),
        .M_AXIS_tdata(m02_couplers_to_axis_interconnect_1_TDATA),
        .M_AXIS_tvalid(m02_couplers_to_axis_interconnect_1_TVALID),
        .S_AXIS_ACLK(axis_interconnect_1_ACLK_net),
        .S_AXIS_ARESETN(axis_interconnect_1_ARESETN_net),
        .S_AXIS_tdata(xbar_to_m02_couplers_TDATA),
        .S_AXIS_tdest(xbar_to_m02_couplers_TDEST),
        .S_AXIS_tready(xbar_to_m02_couplers_TREADY),
        .S_AXIS_tvalid(xbar_to_m02_couplers_TVALID));
  m03_couplers_imp_A748GD m03_couplers
       (.M_AXIS_ACLK(axis_interconnect_1_ACLK_net),
        .M_AXIS_ARESETN(axis_interconnect_1_ARESETN_net),
        .M_AXIS_tdata(m03_couplers_to_axis_interconnect_1_TDATA),
        .M_AXIS_tvalid(m03_couplers_to_axis_interconnect_1_TVALID),
        .S_AXIS_ACLK(axis_interconnect_1_ACLK_net),
        .S_AXIS_ARESETN(axis_interconnect_1_ARESETN_net),
        .S_AXIS_tdata(xbar_to_m03_couplers_TDATA),
        .S_AXIS_tdest(xbar_to_m03_couplers_TDEST),
        .S_AXIS_tready(xbar_to_m03_couplers_TREADY),
        .S_AXIS_tvalid(xbar_to_m03_couplers_TVALID));
  s00_couplers_imp_G8KWBY s00_couplers
       (.M_AXIS_ACLK(axis_interconnect_1_ACLK_net),
        .M_AXIS_ARESETN(axis_interconnect_1_ARESETN_net),
        .M_AXIS_tdata(s00_couplers_to_xbar_TDATA),
        .M_AXIS_tdest(s00_couplers_to_xbar_TDEST),
        .M_AXIS_tready(s00_couplers_to_xbar_TREADY),
        .M_AXIS_tvalid(s00_couplers_to_xbar_TVALID),
        .S_AXIS_ACLK(axis_interconnect_1_ACLK_net),
        .S_AXIS_ARESETN(axis_interconnect_1_ARESETN_net),
        .S_AXIS_tdata(axis_interconnect_1_to_s00_couplers_TDATA),
        .S_AXIS_tdest(axis_interconnect_1_to_s00_couplers_TDEST),
        .S_AXIS_tready(axis_interconnect_1_to_s00_couplers_TREADY),
        .S_AXIS_tvalid(axis_interconnect_1_to_s00_couplers_TVALID));
  fp_alu_xbar_1 xbar
       (.aclk(axis_interconnect_1_ACLK_net),
        .aresetn(axis_interconnect_1_ARESETN_net),
        .m_axis_tdata({xbar_to_m03_couplers_TDATA,xbar_to_m02_couplers_TDATA,xbar_to_m01_couplers_TDATA,xbar_to_m00_couplers_TDATA}),
        .m_axis_tdest({xbar_to_m03_couplers_TDEST,xbar_to_m02_couplers_TDEST,xbar_to_m01_couplers_TDEST,xbar_to_m00_couplers_TDEST}),
        .m_axis_tready({xbar_to_m03_couplers_TREADY,xbar_to_m02_couplers_TREADY,xbar_to_m01_couplers_TREADY,xbar_to_m00_couplers_TREADY}),
        .m_axis_tvalid({xbar_to_m03_couplers_TVALID,xbar_to_m02_couplers_TVALID,xbar_to_m01_couplers_TVALID,xbar_to_m00_couplers_TVALID}),
        .s_axis_tdata(s00_couplers_to_xbar_TDATA),
        .s_axis_tdest(s00_couplers_to_xbar_TDEST),
        .s_axis_tready(s00_couplers_to_xbar_TREADY),
        .s_axis_tvalid(s00_couplers_to_xbar_TVALID));
endmodule

module fp_alu_axis_interconnect_1_0
   (ACLK,
    ARESETN,
    M00_AXIS_ACLK,
    M00_AXIS_ARESETN,
    M00_AXIS_tdata,
    M00_AXIS_tvalid,
    M01_AXIS_ACLK,
    M01_AXIS_ARESETN,
    M01_AXIS_tdata,
    M01_AXIS_tready,
    M01_AXIS_tvalid,
    M02_AXIS_ACLK,
    M02_AXIS_ARESETN,
    M02_AXIS_tdata,
    M02_AXIS_tvalid,
    M03_AXIS_ACLK,
    M03_AXIS_ARESETN,
    M03_AXIS_tdata,
    M03_AXIS_tvalid,
    S00_AXIS_ACLK,
    S00_AXIS_ARESETN,
    S00_AXIS_tdata,
    S00_AXIS_tdest,
    S00_AXIS_tready,
    S00_AXIS_tvalid);
  input ACLK;
  input ARESETN;
  input M00_AXIS_ACLK;
  input M00_AXIS_ARESETN;
  output [31:0]M00_AXIS_tdata;
  output M00_AXIS_tvalid;
  input M01_AXIS_ACLK;
  input M01_AXIS_ARESETN;
  output [31:0]M01_AXIS_tdata;
  input M01_AXIS_tready;
  output M01_AXIS_tvalid;
  input M02_AXIS_ACLK;
  input M02_AXIS_ARESETN;
  output [31:0]M02_AXIS_tdata;
  output M02_AXIS_tvalid;
  input M03_AXIS_ACLK;
  input M03_AXIS_ARESETN;
  output [31:0]M03_AXIS_tdata;
  output M03_AXIS_tvalid;
  input S00_AXIS_ACLK;
  input S00_AXIS_ARESETN;
  input [31:0]S00_AXIS_tdata;
  input [3:0]S00_AXIS_tdest;
  output [0:0]S00_AXIS_tready;
  input [0:0]S00_AXIS_tvalid;

  wire axis_interconnect_2_ACLK_net;
  wire axis_interconnect_2_ARESETN_net;
  wire [31:0]axis_interconnect_2_to_s00_couplers_TDATA;
  wire [3:0]axis_interconnect_2_to_s00_couplers_TDEST;
  wire [0:0]axis_interconnect_2_to_s00_couplers_TREADY;
  wire [0:0]axis_interconnect_2_to_s00_couplers_TVALID;
  wire [31:0]m00_couplers_to_axis_interconnect_2_TDATA;
  wire m00_couplers_to_axis_interconnect_2_TVALID;
  wire [31:0]m01_couplers_to_axis_interconnect_2_TDATA;
  wire m01_couplers_to_axis_interconnect_2_TREADY;
  wire m01_couplers_to_axis_interconnect_2_TVALID;
  wire [31:0]m02_couplers_to_axis_interconnect_2_TDATA;
  wire m02_couplers_to_axis_interconnect_2_TVALID;
  wire [31:0]m03_couplers_to_axis_interconnect_2_TDATA;
  wire m03_couplers_to_axis_interconnect_2_TVALID;
  wire [31:0]s00_couplers_to_xbar_TDATA;
  wire [3:0]s00_couplers_to_xbar_TDEST;
  wire [0:0]s00_couplers_to_xbar_TREADY;
  wire [0:0]s00_couplers_to_xbar_TVALID;
  wire [31:0]xbar_to_m00_couplers_TDATA;
  wire [3:0]xbar_to_m00_couplers_TDEST;
  wire xbar_to_m00_couplers_TREADY;
  wire [0:0]xbar_to_m00_couplers_TVALID;
  wire [63:32]xbar_to_m01_couplers_TDATA;
  wire [7:4]xbar_to_m01_couplers_TDEST;
  wire xbar_to_m01_couplers_TREADY;
  wire [1:1]xbar_to_m01_couplers_TVALID;
  wire [95:64]xbar_to_m02_couplers_TDATA;
  wire [11:8]xbar_to_m02_couplers_TDEST;
  wire xbar_to_m02_couplers_TREADY;
  wire [2:2]xbar_to_m02_couplers_TVALID;
  wire [127:96]xbar_to_m03_couplers_TDATA;
  wire [15:12]xbar_to_m03_couplers_TDEST;
  wire xbar_to_m03_couplers_TREADY;
  wire [3:3]xbar_to_m03_couplers_TVALID;

  assign M00_AXIS_tdata[31:0] = m00_couplers_to_axis_interconnect_2_TDATA;
  assign M00_AXIS_tvalid = m00_couplers_to_axis_interconnect_2_TVALID;
  assign M01_AXIS_tdata[31:0] = m01_couplers_to_axis_interconnect_2_TDATA;
  assign M01_AXIS_tvalid = m01_couplers_to_axis_interconnect_2_TVALID;
  assign M02_AXIS_tdata[31:0] = m02_couplers_to_axis_interconnect_2_TDATA;
  assign M02_AXIS_tvalid = m02_couplers_to_axis_interconnect_2_TVALID;
  assign M03_AXIS_tdata[31:0] = m03_couplers_to_axis_interconnect_2_TDATA;
  assign M03_AXIS_tvalid = m03_couplers_to_axis_interconnect_2_TVALID;
  assign S00_AXIS_tready[0] = axis_interconnect_2_to_s00_couplers_TREADY;
  assign axis_interconnect_2_ACLK_net = ACLK;
  assign axis_interconnect_2_ARESETN_net = ARESETN;
  assign axis_interconnect_2_to_s00_couplers_TDATA = S00_AXIS_tdata[31:0];
  assign axis_interconnect_2_to_s00_couplers_TDEST = S00_AXIS_tdest[3:0];
  assign axis_interconnect_2_to_s00_couplers_TVALID = S00_AXIS_tvalid[0];
  assign m01_couplers_to_axis_interconnect_2_TREADY = M01_AXIS_tready;
  m00_couplers_imp_194GM45 m00_couplers
       (.M_AXIS_ACLK(axis_interconnect_2_ACLK_net),
        .M_AXIS_ARESETN(axis_interconnect_2_ARESETN_net),
        .M_AXIS_tdata(m00_couplers_to_axis_interconnect_2_TDATA),
        .M_AXIS_tvalid(m00_couplers_to_axis_interconnect_2_TVALID),
        .S_AXIS_ACLK(axis_interconnect_2_ACLK_net),
        .S_AXIS_ARESETN(axis_interconnect_2_ARESETN_net),
        .S_AXIS_tdata(xbar_to_m00_couplers_TDATA),
        .S_AXIS_tdest(xbar_to_m00_couplers_TDEST),
        .S_AXIS_tready(xbar_to_m00_couplers_TREADY),
        .S_AXIS_tvalid(xbar_to_m00_couplers_TVALID));
  m01_couplers_imp_3JQHK4 m01_couplers
       (.M_AXIS_ACLK(axis_interconnect_2_ACLK_net),
        .M_AXIS_ARESETN(axis_interconnect_2_ARESETN_net),
        .M_AXIS_tdata(m01_couplers_to_axis_interconnect_2_TDATA),
        .M_AXIS_tready(m01_couplers_to_axis_interconnect_2_TREADY),
        .M_AXIS_tvalid(m01_couplers_to_axis_interconnect_2_TVALID),
        .S_AXIS_ACLK(axis_interconnect_2_ACLK_net),
        .S_AXIS_ARESETN(axis_interconnect_2_ARESETN_net),
        .S_AXIS_tdata(xbar_to_m01_couplers_TDATA),
        .S_AXIS_tdest(xbar_to_m01_couplers_TDEST),
        .S_AXIS_tready(xbar_to_m01_couplers_TREADY),
        .S_AXIS_tvalid(xbar_to_m01_couplers_TVALID));
  m02_couplers_imp_A9MGLY m02_couplers
       (.M_AXIS_ACLK(axis_interconnect_2_ACLK_net),
        .M_AXIS_ARESETN(axis_interconnect_2_ARESETN_net),
        .M_AXIS_tdata(m02_couplers_to_axis_interconnect_2_TDATA),
        .M_AXIS_tvalid(m02_couplers_to_axis_interconnect_2_TVALID),
        .S_AXIS_ACLK(axis_interconnect_2_ACLK_net),
        .S_AXIS_ARESETN(axis_interconnect_2_ARESETN_net),
        .S_AXIS_tdata(xbar_to_m02_couplers_TDATA),
        .S_AXIS_tdest(xbar_to_m02_couplers_TDEST),
        .S_AXIS_tready(xbar_to_m02_couplers_TREADY),
        .S_AXIS_tvalid(xbar_to_m02_couplers_TVALID));
  m03_couplers_imp_12OJX8N m03_couplers
       (.M_AXIS_ACLK(axis_interconnect_2_ACLK_net),
        .M_AXIS_ARESETN(axis_interconnect_2_ARESETN_net),
        .M_AXIS_tdata(m03_couplers_to_axis_interconnect_2_TDATA),
        .M_AXIS_tvalid(m03_couplers_to_axis_interconnect_2_TVALID),
        .S_AXIS_ACLK(axis_interconnect_2_ACLK_net),
        .S_AXIS_ARESETN(axis_interconnect_2_ARESETN_net),
        .S_AXIS_tdata(xbar_to_m03_couplers_TDATA),
        .S_AXIS_tdest(xbar_to_m03_couplers_TDEST),
        .S_AXIS_tready(xbar_to_m03_couplers_TREADY),
        .S_AXIS_tvalid(xbar_to_m03_couplers_TVALID));
  s00_couplers_imp_15E62QS s00_couplers
       (.M_AXIS_ACLK(axis_interconnect_2_ACLK_net),
        .M_AXIS_ARESETN(axis_interconnect_2_ARESETN_net),
        .M_AXIS_tdata(s00_couplers_to_xbar_TDATA),
        .M_AXIS_tdest(s00_couplers_to_xbar_TDEST),
        .M_AXIS_tready(s00_couplers_to_xbar_TREADY),
        .M_AXIS_tvalid(s00_couplers_to_xbar_TVALID),
        .S_AXIS_ACLK(axis_interconnect_2_ACLK_net),
        .S_AXIS_ARESETN(axis_interconnect_2_ARESETN_net),
        .S_AXIS_tdata(axis_interconnect_2_to_s00_couplers_TDATA),
        .S_AXIS_tdest(axis_interconnect_2_to_s00_couplers_TDEST),
        .S_AXIS_tready(axis_interconnect_2_to_s00_couplers_TREADY),
        .S_AXIS_tvalid(axis_interconnect_2_to_s00_couplers_TVALID));
  fp_alu_xbar_2 xbar
       (.aclk(axis_interconnect_2_ACLK_net),
        .aresetn(axis_interconnect_2_ARESETN_net),
        .m_axis_tdata({xbar_to_m03_couplers_TDATA,xbar_to_m02_couplers_TDATA,xbar_to_m01_couplers_TDATA,xbar_to_m00_couplers_TDATA}),
        .m_axis_tdest({xbar_to_m03_couplers_TDEST,xbar_to_m02_couplers_TDEST,xbar_to_m01_couplers_TDEST,xbar_to_m00_couplers_TDEST}),
        .m_axis_tready({xbar_to_m03_couplers_TREADY,xbar_to_m02_couplers_TREADY,xbar_to_m01_couplers_TREADY,xbar_to_m00_couplers_TREADY}),
        .m_axis_tvalid({xbar_to_m03_couplers_TVALID,xbar_to_m02_couplers_TVALID,xbar_to_m01_couplers_TVALID,xbar_to_m00_couplers_TVALID}),
        .s_axis_tdata(s00_couplers_to_xbar_TDATA),
        .s_axis_tdest(s00_couplers_to_xbar_TDEST),
        .s_axis_tready(s00_couplers_to_xbar_TREADY),
        .s_axis_tvalid(s00_couplers_to_xbar_TVALID));
endmodule

module fp_alu_axis_interconnect_1_1
   (ACLK,
    ARESETN,
    M00_AXIS_ACLK,
    M00_AXIS_ARESETN,
    M00_AXIS_tdata,
    M00_AXIS_tvalid,
    M01_AXIS_ACLK,
    M01_AXIS_ARESETN,
    M01_AXIS_tdata,
    M01_AXIS_tready,
    M01_AXIS_tvalid,
    S00_AXIS_ACLK,
    S00_AXIS_ARESETN,
    S00_AXIS_tdata,
    S00_AXIS_tdest,
    S00_AXIS_tready,
    S00_AXIS_tvalid);
  input ACLK;
  input ARESETN;
  input M00_AXIS_ACLK;
  input M00_AXIS_ARESETN;
  output [7:0]M00_AXIS_tdata;
  output M00_AXIS_tvalid;
  input M01_AXIS_ACLK;
  input M01_AXIS_ARESETN;
  output [7:0]M01_AXIS_tdata;
  input M01_AXIS_tready;
  output M01_AXIS_tvalid;
  input S00_AXIS_ACLK;
  input S00_AXIS_ARESETN;
  input [7:0]S00_AXIS_tdata;
  input [3:0]S00_AXIS_tdest;
  output [0:0]S00_AXIS_tready;
  input [0:0]S00_AXIS_tvalid;

  wire axis_interconnect_3_ACLK_net;
  wire axis_interconnect_3_ARESETN_net;
  wire [7:0]axis_interconnect_3_to_s00_couplers_TDATA;
  wire [3:0]axis_interconnect_3_to_s00_couplers_TDEST;
  wire [0:0]axis_interconnect_3_to_s00_couplers_TREADY;
  wire [0:0]axis_interconnect_3_to_s00_couplers_TVALID;
  wire [7:0]m00_couplers_to_axis_interconnect_3_TDATA;
  wire m00_couplers_to_axis_interconnect_3_TVALID;
  wire [7:0]m01_couplers_to_axis_interconnect_3_TDATA;
  wire m01_couplers_to_axis_interconnect_3_TREADY;
  wire m01_couplers_to_axis_interconnect_3_TVALID;
  wire [7:0]s00_couplers_to_xbar_TDATA;
  wire [3:0]s00_couplers_to_xbar_TDEST;
  wire [0:0]s00_couplers_to_xbar_TREADY;
  wire [0:0]s00_couplers_to_xbar_TVALID;
  wire [7:0]xbar_to_m00_couplers_TDATA;
  wire [3:0]xbar_to_m00_couplers_TDEST;
  wire xbar_to_m00_couplers_TREADY;
  wire [0:0]xbar_to_m00_couplers_TVALID;
  wire [15:8]xbar_to_m01_couplers_TDATA;
  wire [7:4]xbar_to_m01_couplers_TDEST;
  wire xbar_to_m01_couplers_TREADY;
  wire [1:1]xbar_to_m01_couplers_TVALID;

  assign M00_AXIS_tdata[7:0] = m00_couplers_to_axis_interconnect_3_TDATA;
  assign M00_AXIS_tvalid = m00_couplers_to_axis_interconnect_3_TVALID;
  assign M01_AXIS_tdata[7:0] = m01_couplers_to_axis_interconnect_3_TDATA;
  assign M01_AXIS_tvalid = m01_couplers_to_axis_interconnect_3_TVALID;
  assign S00_AXIS_tready[0] = axis_interconnect_3_to_s00_couplers_TREADY;
  assign axis_interconnect_3_ACLK_net = ACLK;
  assign axis_interconnect_3_ARESETN_net = ARESETN;
  assign axis_interconnect_3_to_s00_couplers_TDATA = S00_AXIS_tdata[7:0];
  assign axis_interconnect_3_to_s00_couplers_TDEST = S00_AXIS_tdest[3:0];
  assign axis_interconnect_3_to_s00_couplers_TVALID = S00_AXIS_tvalid[0];
  assign m01_couplers_to_axis_interconnect_3_TREADY = M01_AXIS_tready;
  m00_couplers_imp_1JFHEWJ m00_couplers
       (.M_AXIS_ACLK(axis_interconnect_3_ACLK_net),
        .M_AXIS_ARESETN(axis_interconnect_3_ARESETN_net),
        .M_AXIS_tdata(m00_couplers_to_axis_interconnect_3_TDATA),
        .M_AXIS_tvalid(m00_couplers_to_axis_interconnect_3_TVALID),
        .S_AXIS_ACLK(axis_interconnect_3_ACLK_net),
        .S_AXIS_ARESETN(axis_interconnect_3_ARESETN_net),
        .S_AXIS_tdata(xbar_to_m00_couplers_TDATA),
        .S_AXIS_tdest(xbar_to_m00_couplers_TDEST),
        .S_AXIS_tready(xbar_to_m00_couplers_TREADY),
        .S_AXIS_tvalid(xbar_to_m00_couplers_TVALID));
  m01_couplers_imp_TBMHIA m01_couplers
       (.M_AXIS_ACLK(axis_interconnect_3_ACLK_net),
        .M_AXIS_ARESETN(axis_interconnect_3_ARESETN_net),
        .M_AXIS_tdata(m01_couplers_to_axis_interconnect_3_TDATA),
        .M_AXIS_tready(m01_couplers_to_axis_interconnect_3_TREADY),
        .M_AXIS_tvalid(m01_couplers_to_axis_interconnect_3_TVALID),
        .S_AXIS_ACLK(axis_interconnect_3_ACLK_net),
        .S_AXIS_ARESETN(axis_interconnect_3_ARESETN_net),
        .S_AXIS_tdata(xbar_to_m01_couplers_TDATA),
        .S_AXIS_tdest(xbar_to_m01_couplers_TDEST),
        .S_AXIS_tready(xbar_to_m01_couplers_TREADY),
        .S_AXIS_tvalid(xbar_to_m01_couplers_TVALID));
  s00_couplers_imp_1UO47C2 s00_couplers
       (.M_AXIS_ACLK(axis_interconnect_3_ACLK_net),
        .M_AXIS_ARESETN(axis_interconnect_3_ARESETN_net),
        .M_AXIS_tdata(s00_couplers_to_xbar_TDATA),
        .M_AXIS_tdest(s00_couplers_to_xbar_TDEST),
        .M_AXIS_tready(s00_couplers_to_xbar_TREADY),
        .M_AXIS_tvalid(s00_couplers_to_xbar_TVALID),
        .S_AXIS_ACLK(axis_interconnect_3_ACLK_net),
        .S_AXIS_ARESETN(axis_interconnect_3_ARESETN_net),
        .S_AXIS_tdata(axis_interconnect_3_to_s00_couplers_TDATA),
        .S_AXIS_tdest(axis_interconnect_3_to_s00_couplers_TDEST),
        .S_AXIS_tready(axis_interconnect_3_to_s00_couplers_TREADY),
        .S_AXIS_tvalid(axis_interconnect_3_to_s00_couplers_TVALID));
  fp_alu_xbar_3 xbar
       (.aclk(axis_interconnect_3_ACLK_net),
        .aresetn(axis_interconnect_3_ARESETN_net),
        .m_axis_tdata({xbar_to_m01_couplers_TDATA,xbar_to_m00_couplers_TDATA}),
        .m_axis_tdest({xbar_to_m01_couplers_TDEST,xbar_to_m00_couplers_TDEST}),
        .m_axis_tready({xbar_to_m01_couplers_TREADY,xbar_to_m00_couplers_TREADY}),
        .m_axis_tvalid({xbar_to_m01_couplers_TVALID,xbar_to_m00_couplers_TVALID}),
        .s_axis_tdata(s00_couplers_to_xbar_TDATA),
        .s_axis_tdest(s00_couplers_to_xbar_TDEST),
        .s_axis_tready(s00_couplers_to_xbar_TREADY),
        .s_axis_tvalid(s00_couplers_to_xbar_TVALID));
endmodule

module m00_couplers_imp_194GM45
   (M_AXIS_ACLK,
    M_AXIS_ARESETN,
    M_AXIS_tdata,
    M_AXIS_tvalid,
    S_AXIS_ACLK,
    S_AXIS_ARESETN,
    S_AXIS_tdata,
    S_AXIS_tdest,
    S_AXIS_tready,
    S_AXIS_tvalid);
  input M_AXIS_ACLK;
  input M_AXIS_ARESETN;
  output [31:0]M_AXIS_tdata;
  output M_AXIS_tvalid;
  input S_AXIS_ACLK;
  input S_AXIS_ARESETN;
  input [31:0]S_AXIS_tdata;
  input [3:0]S_AXIS_tdest;
  output S_AXIS_tready;
  input S_AXIS_tvalid;

  wire S_AXIS_ACLK_1;
  wire S_AXIS_ARESETN_1;
  wire [31:0]auto_ss_slidr_to_m00_couplers_TDATA;
  wire auto_ss_slidr_to_m00_couplers_TVALID;
  wire [31:0]m00_couplers_to_auto_ss_slidr_TDATA;
  wire [3:0]m00_couplers_to_auto_ss_slidr_TDEST;
  wire m00_couplers_to_auto_ss_slidr_TREADY;
  wire m00_couplers_to_auto_ss_slidr_TVALID;

  assign M_AXIS_tdata[31:0] = auto_ss_slidr_to_m00_couplers_TDATA;
  assign M_AXIS_tvalid = auto_ss_slidr_to_m00_couplers_TVALID;
  assign S_AXIS_ACLK_1 = S_AXIS_ACLK;
  assign S_AXIS_ARESETN_1 = S_AXIS_ARESETN;
  assign S_AXIS_tready = m00_couplers_to_auto_ss_slidr_TREADY;
  assign m00_couplers_to_auto_ss_slidr_TDATA = S_AXIS_tdata[31:0];
  assign m00_couplers_to_auto_ss_slidr_TDEST = S_AXIS_tdest[3:0];
  assign m00_couplers_to_auto_ss_slidr_TVALID = S_AXIS_tvalid;
  fp_alu_auto_ss_slidr_4 auto_ss_slidr
       (.aclk(S_AXIS_ACLK_1),
        .aresetn(S_AXIS_ARESETN_1),
        .m_axis_tdata(auto_ss_slidr_to_m00_couplers_TDATA),
        .m_axis_tvalid(auto_ss_slidr_to_m00_couplers_TVALID),
        .s_axis_tdata(m00_couplers_to_auto_ss_slidr_TDATA),
        .s_axis_tdest(m00_couplers_to_auto_ss_slidr_TDEST),
        .s_axis_tready(m00_couplers_to_auto_ss_slidr_TREADY),
        .s_axis_tvalid(m00_couplers_to_auto_ss_slidr_TVALID));
endmodule

module m00_couplers_imp_1JFHEWJ
   (M_AXIS_ACLK,
    M_AXIS_ARESETN,
    M_AXIS_tdata,
    M_AXIS_tvalid,
    S_AXIS_ACLK,
    S_AXIS_ARESETN,
    S_AXIS_tdata,
    S_AXIS_tdest,
    S_AXIS_tready,
    S_AXIS_tvalid);
  input M_AXIS_ACLK;
  input M_AXIS_ARESETN;
  output [7:0]M_AXIS_tdata;
  output M_AXIS_tvalid;
  input S_AXIS_ACLK;
  input S_AXIS_ARESETN;
  input [7:0]S_AXIS_tdata;
  input [3:0]S_AXIS_tdest;
  output S_AXIS_tready;
  input S_AXIS_tvalid;

  wire S_AXIS_ACLK_1;
  wire S_AXIS_ARESETN_1;
  wire [7:0]auto_ss_slidr_to_m00_couplers_TDATA;
  wire auto_ss_slidr_to_m00_couplers_TVALID;
  wire [7:0]m00_couplers_to_auto_ss_slidr_TDATA;
  wire [3:0]m00_couplers_to_auto_ss_slidr_TDEST;
  wire m00_couplers_to_auto_ss_slidr_TREADY;
  wire m00_couplers_to_auto_ss_slidr_TVALID;

  assign M_AXIS_tdata[7:0] = auto_ss_slidr_to_m00_couplers_TDATA;
  assign M_AXIS_tvalid = auto_ss_slidr_to_m00_couplers_TVALID;
  assign S_AXIS_ACLK_1 = S_AXIS_ACLK;
  assign S_AXIS_ARESETN_1 = S_AXIS_ARESETN;
  assign S_AXIS_tready = m00_couplers_to_auto_ss_slidr_TREADY;
  assign m00_couplers_to_auto_ss_slidr_TDATA = S_AXIS_tdata[7:0];
  assign m00_couplers_to_auto_ss_slidr_TDEST = S_AXIS_tdest[3:0];
  assign m00_couplers_to_auto_ss_slidr_TVALID = S_AXIS_tvalid;
  fp_alu_auto_ss_slidr_8 auto_ss_slidr
       (.aclk(S_AXIS_ACLK_1),
        .aresetn(S_AXIS_ARESETN_1),
        .m_axis_tdata(auto_ss_slidr_to_m00_couplers_TDATA),
        .m_axis_tvalid(auto_ss_slidr_to_m00_couplers_TVALID),
        .s_axis_tdata(m00_couplers_to_auto_ss_slidr_TDATA),
        .s_axis_tdest(m00_couplers_to_auto_ss_slidr_TDEST),
        .s_axis_tready(m00_couplers_to_auto_ss_slidr_TREADY),
        .s_axis_tvalid(m00_couplers_to_auto_ss_slidr_TVALID));
endmodule

module m00_couplers_imp_3M6IPR
   (M_AXIS_ACLK,
    M_AXIS_ARESETN,
    M_AXIS_tdata,
    M_AXIS_tvalid,
    S_AXIS_ACLK,
    S_AXIS_ARESETN,
    S_AXIS_tdata,
    S_AXIS_tdest,
    S_AXIS_tready,
    S_AXIS_tvalid);
  input M_AXIS_ACLK;
  input M_AXIS_ARESETN;
  output [31:0]M_AXIS_tdata;
  output M_AXIS_tvalid;
  input S_AXIS_ACLK;
  input S_AXIS_ARESETN;
  input [31:0]S_AXIS_tdata;
  input [3:0]S_AXIS_tdest;
  output S_AXIS_tready;
  input S_AXIS_tvalid;

  wire S_AXIS_ACLK_1;
  wire S_AXIS_ARESETN_1;
  wire [31:0]auto_ss_slidr_to_m00_couplers_TDATA;
  wire auto_ss_slidr_to_m00_couplers_TVALID;
  wire [31:0]m00_couplers_to_auto_ss_slidr_TDATA;
  wire [3:0]m00_couplers_to_auto_ss_slidr_TDEST;
  wire m00_couplers_to_auto_ss_slidr_TREADY;
  wire m00_couplers_to_auto_ss_slidr_TVALID;

  assign M_AXIS_tdata[31:0] = auto_ss_slidr_to_m00_couplers_TDATA;
  assign M_AXIS_tvalid = auto_ss_slidr_to_m00_couplers_TVALID;
  assign S_AXIS_ACLK_1 = S_AXIS_ACLK;
  assign S_AXIS_ARESETN_1 = S_AXIS_ARESETN;
  assign S_AXIS_tready = m00_couplers_to_auto_ss_slidr_TREADY;
  assign m00_couplers_to_auto_ss_slidr_TDATA = S_AXIS_tdata[31:0];
  assign m00_couplers_to_auto_ss_slidr_TDEST = S_AXIS_tdest[3:0];
  assign m00_couplers_to_auto_ss_slidr_TVALID = S_AXIS_tvalid;
  fp_alu_auto_ss_slidr_0 auto_ss_slidr
       (.aclk(S_AXIS_ACLK_1),
        .aresetn(S_AXIS_ARESETN_1),
        .m_axis_tdata(auto_ss_slidr_to_m00_couplers_TDATA),
        .m_axis_tvalid(auto_ss_slidr_to_m00_couplers_TVALID),
        .s_axis_tdata(m00_couplers_to_auto_ss_slidr_TDATA),
        .s_axis_tdest(m00_couplers_to_auto_ss_slidr_TDEST),
        .s_axis_tready(m00_couplers_to_auto_ss_slidr_TREADY),
        .s_axis_tvalid(m00_couplers_to_auto_ss_slidr_TVALID));
endmodule

module m01_couplers_imp_19BY0TQ
   (M_AXIS_ACLK,
    M_AXIS_ARESETN,
    M_AXIS_tdata,
    M_AXIS_tready,
    M_AXIS_tvalid,
    S_AXIS_ACLK,
    S_AXIS_ARESETN,
    S_AXIS_tdata,
    S_AXIS_tdest,
    S_AXIS_tready,
    S_AXIS_tvalid);
  input M_AXIS_ACLK;
  input M_AXIS_ARESETN;
  output [31:0]M_AXIS_tdata;
  input M_AXIS_tready;
  output M_AXIS_tvalid;
  input S_AXIS_ACLK;
  input S_AXIS_ARESETN;
  input [31:0]S_AXIS_tdata;
  input [3:0]S_AXIS_tdest;
  output S_AXIS_tready;
  input S_AXIS_tvalid;

  wire S_AXIS_ACLK_1;
  wire S_AXIS_ARESETN_1;
  wire [31:0]auto_ss_slidr_to_m01_couplers_TDATA;
  wire auto_ss_slidr_to_m01_couplers_TREADY;
  wire auto_ss_slidr_to_m01_couplers_TVALID;
  wire [31:0]m01_couplers_to_auto_ss_slidr_TDATA;
  wire [3:0]m01_couplers_to_auto_ss_slidr_TDEST;
  wire m01_couplers_to_auto_ss_slidr_TREADY;
  wire m01_couplers_to_auto_ss_slidr_TVALID;

  assign M_AXIS_tdata[31:0] = auto_ss_slidr_to_m01_couplers_TDATA;
  assign M_AXIS_tvalid = auto_ss_slidr_to_m01_couplers_TVALID;
  assign S_AXIS_ACLK_1 = S_AXIS_ACLK;
  assign S_AXIS_ARESETN_1 = S_AXIS_ARESETN;
  assign S_AXIS_tready = m01_couplers_to_auto_ss_slidr_TREADY;
  assign auto_ss_slidr_to_m01_couplers_TREADY = M_AXIS_tready;
  assign m01_couplers_to_auto_ss_slidr_TDATA = S_AXIS_tdata[31:0];
  assign m01_couplers_to_auto_ss_slidr_TDEST = S_AXIS_tdest[3:0];
  assign m01_couplers_to_auto_ss_slidr_TVALID = S_AXIS_tvalid;
  fp_alu_auto_ss_slidr_1 auto_ss_slidr
       (.aclk(S_AXIS_ACLK_1),
        .aresetn(S_AXIS_ARESETN_1),
        .m_axis_tdata(auto_ss_slidr_to_m01_couplers_TDATA),
        .m_axis_tready(auto_ss_slidr_to_m01_couplers_TREADY),
        .m_axis_tvalid(auto_ss_slidr_to_m01_couplers_TVALID),
        .s_axis_tdata(m01_couplers_to_auto_ss_slidr_TDATA),
        .s_axis_tdest(m01_couplers_to_auto_ss_slidr_TDEST),
        .s_axis_tready(m01_couplers_to_auto_ss_slidr_TREADY),
        .s_axis_tvalid(m01_couplers_to_auto_ss_slidr_TVALID));
endmodule

module m01_couplers_imp_3JQHK4
   (M_AXIS_ACLK,
    M_AXIS_ARESETN,
    M_AXIS_tdata,
    M_AXIS_tready,
    M_AXIS_tvalid,
    S_AXIS_ACLK,
    S_AXIS_ARESETN,
    S_AXIS_tdata,
    S_AXIS_tdest,
    S_AXIS_tready,
    S_AXIS_tvalid);
  input M_AXIS_ACLK;
  input M_AXIS_ARESETN;
  output [31:0]M_AXIS_tdata;
  input M_AXIS_tready;
  output M_AXIS_tvalid;
  input S_AXIS_ACLK;
  input S_AXIS_ARESETN;
  input [31:0]S_AXIS_tdata;
  input [3:0]S_AXIS_tdest;
  output S_AXIS_tready;
  input S_AXIS_tvalid;

  wire S_AXIS_ACLK_1;
  wire S_AXIS_ARESETN_1;
  wire [31:0]auto_ss_slidr_to_m01_couplers_TDATA;
  wire auto_ss_slidr_to_m01_couplers_TREADY;
  wire auto_ss_slidr_to_m01_couplers_TVALID;
  wire [31:0]m01_couplers_to_auto_ss_slidr_TDATA;
  wire [3:0]m01_couplers_to_auto_ss_slidr_TDEST;
  wire m01_couplers_to_auto_ss_slidr_TREADY;
  wire m01_couplers_to_auto_ss_slidr_TVALID;

  assign M_AXIS_tdata[31:0] = auto_ss_slidr_to_m01_couplers_TDATA;
  assign M_AXIS_tvalid = auto_ss_slidr_to_m01_couplers_TVALID;
  assign S_AXIS_ACLK_1 = S_AXIS_ACLK;
  assign S_AXIS_ARESETN_1 = S_AXIS_ARESETN;
  assign S_AXIS_tready = m01_couplers_to_auto_ss_slidr_TREADY;
  assign auto_ss_slidr_to_m01_couplers_TREADY = M_AXIS_tready;
  assign m01_couplers_to_auto_ss_slidr_TDATA = S_AXIS_tdata[31:0];
  assign m01_couplers_to_auto_ss_slidr_TDEST = S_AXIS_tdest[3:0];
  assign m01_couplers_to_auto_ss_slidr_TVALID = S_AXIS_tvalid;
  fp_alu_auto_ss_slidr_5 auto_ss_slidr
       (.aclk(S_AXIS_ACLK_1),
        .aresetn(S_AXIS_ARESETN_1),
        .m_axis_tdata(auto_ss_slidr_to_m01_couplers_TDATA),
        .m_axis_tready(auto_ss_slidr_to_m01_couplers_TREADY),
        .m_axis_tvalid(auto_ss_slidr_to_m01_couplers_TVALID),
        .s_axis_tdata(m01_couplers_to_auto_ss_slidr_TDATA),
        .s_axis_tdest(m01_couplers_to_auto_ss_slidr_TDEST),
        .s_axis_tready(m01_couplers_to_auto_ss_slidr_TREADY),
        .s_axis_tvalid(m01_couplers_to_auto_ss_slidr_TVALID));
endmodule

module m01_couplers_imp_TBMHIA
   (M_AXIS_ACLK,
    M_AXIS_ARESETN,
    M_AXIS_tdata,
    M_AXIS_tready,
    M_AXIS_tvalid,
    S_AXIS_ACLK,
    S_AXIS_ARESETN,
    S_AXIS_tdata,
    S_AXIS_tdest,
    S_AXIS_tready,
    S_AXIS_tvalid);
  input M_AXIS_ACLK;
  input M_AXIS_ARESETN;
  output [7:0]M_AXIS_tdata;
  input M_AXIS_tready;
  output M_AXIS_tvalid;
  input S_AXIS_ACLK;
  input S_AXIS_ARESETN;
  input [7:0]S_AXIS_tdata;
  input [3:0]S_AXIS_tdest;
  output S_AXIS_tready;
  input S_AXIS_tvalid;

  wire S_AXIS_ACLK_1;
  wire S_AXIS_ARESETN_1;
  wire [7:0]auto_ss_slidr_to_m01_couplers_TDATA;
  wire auto_ss_slidr_to_m01_couplers_TREADY;
  wire auto_ss_slidr_to_m01_couplers_TVALID;
  wire [7:0]m01_couplers_to_auto_ss_slidr_TDATA;
  wire [3:0]m01_couplers_to_auto_ss_slidr_TDEST;
  wire m01_couplers_to_auto_ss_slidr_TREADY;
  wire m01_couplers_to_auto_ss_slidr_TVALID;

  assign M_AXIS_tdata[7:0] = auto_ss_slidr_to_m01_couplers_TDATA;
  assign M_AXIS_tvalid = auto_ss_slidr_to_m01_couplers_TVALID;
  assign S_AXIS_ACLK_1 = S_AXIS_ACLK;
  assign S_AXIS_ARESETN_1 = S_AXIS_ARESETN;
  assign S_AXIS_tready = m01_couplers_to_auto_ss_slidr_TREADY;
  assign auto_ss_slidr_to_m01_couplers_TREADY = M_AXIS_tready;
  assign m01_couplers_to_auto_ss_slidr_TDATA = S_AXIS_tdata[7:0];
  assign m01_couplers_to_auto_ss_slidr_TDEST = S_AXIS_tdest[3:0];
  assign m01_couplers_to_auto_ss_slidr_TVALID = S_AXIS_tvalid;
  fp_alu_auto_ss_slidr_9 auto_ss_slidr
       (.aclk(S_AXIS_ACLK_1),
        .aresetn(S_AXIS_ARESETN_1),
        .m_axis_tdata(auto_ss_slidr_to_m01_couplers_TDATA),
        .m_axis_tready(auto_ss_slidr_to_m01_couplers_TREADY),
        .m_axis_tvalid(auto_ss_slidr_to_m01_couplers_TVALID),
        .s_axis_tdata(m01_couplers_to_auto_ss_slidr_TDATA),
        .s_axis_tdest(m01_couplers_to_auto_ss_slidr_TDEST),
        .s_axis_tready(m01_couplers_to_auto_ss_slidr_TREADY),
        .s_axis_tvalid(m01_couplers_to_auto_ss_slidr_TVALID));
endmodule

module m02_couplers_imp_12H0BJ0
   (M_AXIS_ACLK,
    M_AXIS_ARESETN,
    M_AXIS_tdata,
    M_AXIS_tvalid,
    S_AXIS_ACLK,
    S_AXIS_ARESETN,
    S_AXIS_tdata,
    S_AXIS_tdest,
    S_AXIS_tready,
    S_AXIS_tvalid);
  input M_AXIS_ACLK;
  input M_AXIS_ARESETN;
  output [31:0]M_AXIS_tdata;
  output M_AXIS_tvalid;
  input S_AXIS_ACLK;
  input S_AXIS_ARESETN;
  input [31:0]S_AXIS_tdata;
  input [3:0]S_AXIS_tdest;
  output S_AXIS_tready;
  input S_AXIS_tvalid;

  wire S_AXIS_ACLK_1;
  wire S_AXIS_ARESETN_1;
  wire [31:0]auto_ss_slidr_to_m02_couplers_TDATA;
  wire auto_ss_slidr_to_m02_couplers_TVALID;
  wire [31:0]m02_couplers_to_auto_ss_slidr_TDATA;
  wire [3:0]m02_couplers_to_auto_ss_slidr_TDEST;
  wire m02_couplers_to_auto_ss_slidr_TREADY;
  wire m02_couplers_to_auto_ss_slidr_TVALID;

  assign M_AXIS_tdata[31:0] = auto_ss_slidr_to_m02_couplers_TDATA;
  assign M_AXIS_tvalid = auto_ss_slidr_to_m02_couplers_TVALID;
  assign S_AXIS_ACLK_1 = S_AXIS_ACLK;
  assign S_AXIS_ARESETN_1 = S_AXIS_ARESETN;
  assign S_AXIS_tready = m02_couplers_to_auto_ss_slidr_TREADY;
  assign m02_couplers_to_auto_ss_slidr_TDATA = S_AXIS_tdata[31:0];
  assign m02_couplers_to_auto_ss_slidr_TDEST = S_AXIS_tdest[3:0];
  assign m02_couplers_to_auto_ss_slidr_TVALID = S_AXIS_tvalid;
  fp_alu_auto_ss_slidr_2 auto_ss_slidr
       (.aclk(S_AXIS_ACLK_1),
        .aresetn(S_AXIS_ARESETN_1),
        .m_axis_tdata(auto_ss_slidr_to_m02_couplers_TDATA),
        .m_axis_tvalid(auto_ss_slidr_to_m02_couplers_TVALID),
        .s_axis_tdata(m02_couplers_to_auto_ss_slidr_TDATA),
        .s_axis_tdest(m02_couplers_to_auto_ss_slidr_TDEST),
        .s_axis_tready(m02_couplers_to_auto_ss_slidr_TREADY),
        .s_axis_tvalid(m02_couplers_to_auto_ss_slidr_TVALID));
endmodule

module m02_couplers_imp_A9MGLY
   (M_AXIS_ACLK,
    M_AXIS_ARESETN,
    M_AXIS_tdata,
    M_AXIS_tvalid,
    S_AXIS_ACLK,
    S_AXIS_ARESETN,
    S_AXIS_tdata,
    S_AXIS_tdest,
    S_AXIS_tready,
    S_AXIS_tvalid);
  input M_AXIS_ACLK;
  input M_AXIS_ARESETN;
  output [31:0]M_AXIS_tdata;
  output M_AXIS_tvalid;
  input S_AXIS_ACLK;
  input S_AXIS_ARESETN;
  input [31:0]S_AXIS_tdata;
  input [3:0]S_AXIS_tdest;
  output S_AXIS_tready;
  input S_AXIS_tvalid;

  wire S_AXIS_ACLK_1;
  wire S_AXIS_ARESETN_1;
  wire [31:0]auto_ss_slidr_to_m02_couplers_TDATA;
  wire auto_ss_slidr_to_m02_couplers_TVALID;
  wire [31:0]m02_couplers_to_auto_ss_slidr_TDATA;
  wire [3:0]m02_couplers_to_auto_ss_slidr_TDEST;
  wire m02_couplers_to_auto_ss_slidr_TREADY;
  wire m02_couplers_to_auto_ss_slidr_TVALID;

  assign M_AXIS_tdata[31:0] = auto_ss_slidr_to_m02_couplers_TDATA;
  assign M_AXIS_tvalid = auto_ss_slidr_to_m02_couplers_TVALID;
  assign S_AXIS_ACLK_1 = S_AXIS_ACLK;
  assign S_AXIS_ARESETN_1 = S_AXIS_ARESETN;
  assign S_AXIS_tready = m02_couplers_to_auto_ss_slidr_TREADY;
  assign m02_couplers_to_auto_ss_slidr_TDATA = S_AXIS_tdata[31:0];
  assign m02_couplers_to_auto_ss_slidr_TDEST = S_AXIS_tdest[3:0];
  assign m02_couplers_to_auto_ss_slidr_TVALID = S_AXIS_tvalid;
  fp_alu_auto_ss_slidr_6 auto_ss_slidr
       (.aclk(S_AXIS_ACLK_1),
        .aresetn(S_AXIS_ARESETN_1),
        .m_axis_tdata(auto_ss_slidr_to_m02_couplers_TDATA),
        .m_axis_tvalid(auto_ss_slidr_to_m02_couplers_TVALID),
        .s_axis_tdata(m02_couplers_to_auto_ss_slidr_TDATA),
        .s_axis_tdest(m02_couplers_to_auto_ss_slidr_TDEST),
        .s_axis_tready(m02_couplers_to_auto_ss_slidr_TREADY),
        .s_axis_tvalid(m02_couplers_to_auto_ss_slidr_TVALID));
endmodule

module m03_couplers_imp_12OJX8N
   (M_AXIS_ACLK,
    M_AXIS_ARESETN,
    M_AXIS_tdata,
    M_AXIS_tvalid,
    S_AXIS_ACLK,
    S_AXIS_ARESETN,
    S_AXIS_tdata,
    S_AXIS_tdest,
    S_AXIS_tready,
    S_AXIS_tvalid);
  input M_AXIS_ACLK;
  input M_AXIS_ARESETN;
  output [31:0]M_AXIS_tdata;
  output M_AXIS_tvalid;
  input S_AXIS_ACLK;
  input S_AXIS_ARESETN;
  input [31:0]S_AXIS_tdata;
  input [3:0]S_AXIS_tdest;
  output S_AXIS_tready;
  input S_AXIS_tvalid;

  wire S_AXIS_ACLK_1;
  wire S_AXIS_ARESETN_1;
  wire [31:0]auto_ss_slidr_to_m03_couplers_TDATA;
  wire auto_ss_slidr_to_m03_couplers_TVALID;
  wire [31:0]m03_couplers_to_auto_ss_slidr_TDATA;
  wire [3:0]m03_couplers_to_auto_ss_slidr_TDEST;
  wire m03_couplers_to_auto_ss_slidr_TREADY;
  wire m03_couplers_to_auto_ss_slidr_TVALID;

  assign M_AXIS_tdata[31:0] = auto_ss_slidr_to_m03_couplers_TDATA;
  assign M_AXIS_tvalid = auto_ss_slidr_to_m03_couplers_TVALID;
  assign S_AXIS_ACLK_1 = S_AXIS_ACLK;
  assign S_AXIS_ARESETN_1 = S_AXIS_ARESETN;
  assign S_AXIS_tready = m03_couplers_to_auto_ss_slidr_TREADY;
  assign m03_couplers_to_auto_ss_slidr_TDATA = S_AXIS_tdata[31:0];
  assign m03_couplers_to_auto_ss_slidr_TDEST = S_AXIS_tdest[3:0];
  assign m03_couplers_to_auto_ss_slidr_TVALID = S_AXIS_tvalid;
  fp_alu_auto_ss_slidr_7 auto_ss_slidr
       (.aclk(S_AXIS_ACLK_1),
        .aresetn(S_AXIS_ARESETN_1),
        .m_axis_tdata(auto_ss_slidr_to_m03_couplers_TDATA),
        .m_axis_tvalid(auto_ss_slidr_to_m03_couplers_TVALID),
        .s_axis_tdata(m03_couplers_to_auto_ss_slidr_TDATA),
        .s_axis_tdest(m03_couplers_to_auto_ss_slidr_TDEST),
        .s_axis_tready(m03_couplers_to_auto_ss_slidr_TREADY),
        .s_axis_tvalid(m03_couplers_to_auto_ss_slidr_TVALID));
endmodule

module m03_couplers_imp_A748GD
   (M_AXIS_ACLK,
    M_AXIS_ARESETN,
    M_AXIS_tdata,
    M_AXIS_tvalid,
    S_AXIS_ACLK,
    S_AXIS_ARESETN,
    S_AXIS_tdata,
    S_AXIS_tdest,
    S_AXIS_tready,
    S_AXIS_tvalid);
  input M_AXIS_ACLK;
  input M_AXIS_ARESETN;
  output [31:0]M_AXIS_tdata;
  output M_AXIS_tvalid;
  input S_AXIS_ACLK;
  input S_AXIS_ARESETN;
  input [31:0]S_AXIS_tdata;
  input [3:0]S_AXIS_tdest;
  output S_AXIS_tready;
  input S_AXIS_tvalid;

  wire S_AXIS_ACLK_1;
  wire S_AXIS_ARESETN_1;
  wire [31:0]auto_ss_slidr_to_m03_couplers_TDATA;
  wire auto_ss_slidr_to_m03_couplers_TVALID;
  wire [31:0]m03_couplers_to_auto_ss_slidr_TDATA;
  wire [3:0]m03_couplers_to_auto_ss_slidr_TDEST;
  wire m03_couplers_to_auto_ss_slidr_TREADY;
  wire m03_couplers_to_auto_ss_slidr_TVALID;

  assign M_AXIS_tdata[31:0] = auto_ss_slidr_to_m03_couplers_TDATA;
  assign M_AXIS_tvalid = auto_ss_slidr_to_m03_couplers_TVALID;
  assign S_AXIS_ACLK_1 = S_AXIS_ACLK;
  assign S_AXIS_ARESETN_1 = S_AXIS_ARESETN;
  assign S_AXIS_tready = m03_couplers_to_auto_ss_slidr_TREADY;
  assign m03_couplers_to_auto_ss_slidr_TDATA = S_AXIS_tdata[31:0];
  assign m03_couplers_to_auto_ss_slidr_TDEST = S_AXIS_tdest[3:0];
  assign m03_couplers_to_auto_ss_slidr_TVALID = S_AXIS_tvalid;
  fp_alu_auto_ss_slidr_3 auto_ss_slidr
       (.aclk(S_AXIS_ACLK_1),
        .aresetn(S_AXIS_ARESETN_1),
        .m_axis_tdata(auto_ss_slidr_to_m03_couplers_TDATA),
        .m_axis_tvalid(auto_ss_slidr_to_m03_couplers_TVALID),
        .s_axis_tdata(m03_couplers_to_auto_ss_slidr_TDATA),
        .s_axis_tdest(m03_couplers_to_auto_ss_slidr_TDEST),
        .s_axis_tready(m03_couplers_to_auto_ss_slidr_TREADY),
        .s_axis_tvalid(m03_couplers_to_auto_ss_slidr_TVALID));
endmodule

module s00_couplers_imp_15E62QS
   (M_AXIS_ACLK,
    M_AXIS_ARESETN,
    M_AXIS_tdata,
    M_AXIS_tdest,
    M_AXIS_tready,
    M_AXIS_tvalid,
    S_AXIS_ACLK,
    S_AXIS_ARESETN,
    S_AXIS_tdata,
    S_AXIS_tdest,
    S_AXIS_tready,
    S_AXIS_tvalid);
  input M_AXIS_ACLK;
  input M_AXIS_ARESETN;
  output [31:0]M_AXIS_tdata;
  output [3:0]M_AXIS_tdest;
  input [0:0]M_AXIS_tready;
  output [0:0]M_AXIS_tvalid;
  input S_AXIS_ACLK;
  input S_AXIS_ARESETN;
  input [31:0]S_AXIS_tdata;
  input [3:0]S_AXIS_tdest;
  output [0:0]S_AXIS_tready;
  input [0:0]S_AXIS_tvalid;

  wire [31:0]s00_couplers_to_s00_couplers_TDATA;
  wire [3:0]s00_couplers_to_s00_couplers_TDEST;
  wire [0:0]s00_couplers_to_s00_couplers_TREADY;
  wire [0:0]s00_couplers_to_s00_couplers_TVALID;

  assign M_AXIS_tdata[31:0] = s00_couplers_to_s00_couplers_TDATA;
  assign M_AXIS_tdest[3:0] = s00_couplers_to_s00_couplers_TDEST;
  assign M_AXIS_tvalid[0] = s00_couplers_to_s00_couplers_TVALID;
  assign S_AXIS_tready[0] = s00_couplers_to_s00_couplers_TREADY;
  assign s00_couplers_to_s00_couplers_TDATA = S_AXIS_tdata[31:0];
  assign s00_couplers_to_s00_couplers_TDEST = S_AXIS_tdest[3:0];
  assign s00_couplers_to_s00_couplers_TREADY = M_AXIS_tready[0];
  assign s00_couplers_to_s00_couplers_TVALID = S_AXIS_tvalid[0];
endmodule

module s00_couplers_imp_1UO47C2
   (M_AXIS_ACLK,
    M_AXIS_ARESETN,
    M_AXIS_tdata,
    M_AXIS_tdest,
    M_AXIS_tready,
    M_AXIS_tvalid,
    S_AXIS_ACLK,
    S_AXIS_ARESETN,
    S_AXIS_tdata,
    S_AXIS_tdest,
    S_AXIS_tready,
    S_AXIS_tvalid);
  input M_AXIS_ACLK;
  input M_AXIS_ARESETN;
  output [7:0]M_AXIS_tdata;
  output [3:0]M_AXIS_tdest;
  input [0:0]M_AXIS_tready;
  output [0:0]M_AXIS_tvalid;
  input S_AXIS_ACLK;
  input S_AXIS_ARESETN;
  input [7:0]S_AXIS_tdata;
  input [3:0]S_AXIS_tdest;
  output [0:0]S_AXIS_tready;
  input [0:0]S_AXIS_tvalid;

  wire [7:0]s00_couplers_to_s00_couplers_TDATA;
  wire [3:0]s00_couplers_to_s00_couplers_TDEST;
  wire [0:0]s00_couplers_to_s00_couplers_TREADY;
  wire [0:0]s00_couplers_to_s00_couplers_TVALID;

  assign M_AXIS_tdata[7:0] = s00_couplers_to_s00_couplers_TDATA;
  assign M_AXIS_tdest[3:0] = s00_couplers_to_s00_couplers_TDEST;
  assign M_AXIS_tvalid[0] = s00_couplers_to_s00_couplers_TVALID;
  assign S_AXIS_tready[0] = s00_couplers_to_s00_couplers_TREADY;
  assign s00_couplers_to_s00_couplers_TDATA = S_AXIS_tdata[7:0];
  assign s00_couplers_to_s00_couplers_TDEST = S_AXIS_tdest[3:0];
  assign s00_couplers_to_s00_couplers_TREADY = M_AXIS_tready[0];
  assign s00_couplers_to_s00_couplers_TVALID = S_AXIS_tvalid[0];
endmodule

module s00_couplers_imp_G8KWBY
   (M_AXIS_ACLK,
    M_AXIS_ARESETN,
    M_AXIS_tdata,
    M_AXIS_tdest,
    M_AXIS_tready,
    M_AXIS_tvalid,
    S_AXIS_ACLK,
    S_AXIS_ARESETN,
    S_AXIS_tdata,
    S_AXIS_tdest,
    S_AXIS_tready,
    S_AXIS_tvalid);
  input M_AXIS_ACLK;
  input M_AXIS_ARESETN;
  output [31:0]M_AXIS_tdata;
  output [3:0]M_AXIS_tdest;
  input [0:0]M_AXIS_tready;
  output [0:0]M_AXIS_tvalid;
  input S_AXIS_ACLK;
  input S_AXIS_ARESETN;
  input [31:0]S_AXIS_tdata;
  input [3:0]S_AXIS_tdest;
  output [0:0]S_AXIS_tready;
  input [0:0]S_AXIS_tvalid;

  wire [31:0]s00_couplers_to_s00_couplers_TDATA;
  wire [3:0]s00_couplers_to_s00_couplers_TDEST;
  wire [0:0]s00_couplers_to_s00_couplers_TREADY;
  wire [0:0]s00_couplers_to_s00_couplers_TVALID;

  assign M_AXIS_tdata[31:0] = s00_couplers_to_s00_couplers_TDATA;
  assign M_AXIS_tdest[3:0] = s00_couplers_to_s00_couplers_TDEST;
  assign M_AXIS_tvalid[0] = s00_couplers_to_s00_couplers_TVALID;
  assign S_AXIS_tready[0] = s00_couplers_to_s00_couplers_TREADY;
  assign s00_couplers_to_s00_couplers_TDATA = S_AXIS_tdata[31:0];
  assign s00_couplers_to_s00_couplers_TDEST = S_AXIS_tdest[3:0];
  assign s00_couplers_to_s00_couplers_TREADY = M_AXIS_tready[0];
  assign s00_couplers_to_s00_couplers_TVALID = S_AXIS_tvalid[0];
endmodule
