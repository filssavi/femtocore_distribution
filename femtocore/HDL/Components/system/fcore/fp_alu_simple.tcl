
################################################################
# This is a generated script based on design: fp_alu
#
# Though there are limitations about the generated script,
# the main purpose of this utility is to make learning
# IP Integrator Tcl commands easier.
################################################################

namespace eval _tcl {
proc get_script_folder {} {
   set script_path [file normalize [info script]]
   set script_folder [file dirname $script_path]
   return $script_folder
}
}
variable script_folder
set script_folder [_tcl::get_script_folder]

# CHANGE DESIGN NAME HERE
variable design_name
set design_name fcore_simple_alu

set cur_design [current_bd_design -quiet]
set list_cells [get_bd_cells -quiet]

  
create_bd_design $design_name
current_bd_design $design_name


##################################################################
# DESIGN PROCs
##################################################################


variable script_folder
variable design_name

set parentCell [get_bd_cells /]

# Get object for parentCell
set parentObj [get_bd_cells $parentCell]

# Make sure parentObj is hier blk
set parentType [get_property TYPE $parentObj]

# Save current instance; Restore later
set oldCurInst [current_bd_instance .]

# Set parent object as current
current_bd_instance $parentObj


set DefaultInputPortProps  [ list \
CONFIG.HAS_TKEEP {0} \
CONFIG.HAS_TLAST {0} \
CONFIG.HAS_TREADY {0} \
CONFIG.HAS_TSTRB {0} \
CONFIG.LAYERED_METADATA {undef} \
CONFIG.TDATA_NUM_BYTES {4} \
CONFIG.TDEST_WIDTH {0} \
CONFIG.TID_WIDTH {0} \
CONFIG.TUSER_WIDTH {8} \
]

# Create interface ports
set add_res [ create_bd_intf_port -mode Master -vlnv xilinx.com:interface:axis_rtl:1.0 add_res ]

set adder_a [ create_bd_intf_port -mode Slave -vlnv xilinx.com:interface:axis_rtl:1.0 adder_a ]
set_property -dict $DefaultInputPortProps $adder_a

set adder_b [ create_bd_intf_port -mode Slave -vlnv xilinx.com:interface:axis_rtl:1.0 adder_b ]
set_property -dict $DefaultInputPortProps $adder_b
set_property CONFIG.TUSER_WIDTH 0 $adder_b

set adder_op [ create_bd_intf_port -mode Slave -vlnv xilinx.com:interface:axis_rtl:1.0 adder_op ]
set_property -dict $DefaultInputPortProps $adder_op
set_property CONFIG.TDATA_NUM_BYTES 1 $adder_op
set_property CONFIG.TDEST_WIDTH 4 $adder_op

set cmp_res [ create_bd_intf_port -mode Master -vlnv xilinx.com:interface:axis_rtl:1.0 cmp_res ]

set comp_a [ create_bd_intf_port -mode Slave -vlnv xilinx.com:interface:axis_rtl:1.0 comp_a ]
set_property -dict $DefaultInputPortProps $comp_a

set comp_b [ create_bd_intf_port -mode Slave -vlnv xilinx.com:interface:axis_rtl:1.0 comp_b ]
set_property -dict $DefaultInputPortProps $comp_b

set comp_op [ create_bd_intf_port -mode Slave -vlnv xilinx.com:interface:axis_rtl:1.0 comp_op ]
set_property -dict $DefaultInputPortProps $comp_op
set_property CONFIG.TDATA_NUM_BYTES 1 $comp_op
set_property CONFIG.TDEST_WIDTH 4 $comp_op

set fti_b [ create_bd_intf_port -mode Slave -vlnv xilinx.com:interface:axis_rtl:1.0 fti_b ]
set_property -dict $DefaultInputPortProps $fti_b

set fti_res [ create_bd_intf_port -mode Master -vlnv xilinx.com:interface:axis_rtl:1.0 fti_res ]

set itf_a [ create_bd_intf_port -mode Slave -vlnv xilinx.com:interface:axis_rtl:1.0 itf_a ]
set_property -dict $DefaultInputPortProps $itf_a

set itf_res [ create_bd_intf_port -mode Master -vlnv xilinx.com:interface:axis_rtl:1.0 itf_res ]

set mul_res [ create_bd_intf_port -mode Master -vlnv xilinx.com:interface:axis_rtl:1.0 mul_res ]

set mult_a [ create_bd_intf_port -mode Slave -vlnv xilinx.com:interface:axis_rtl:1.0 mult_a ]
set_property -dict $DefaultInputPortProps $mult_a

set mult_b [ create_bd_intf_port -mode Slave -vlnv xilinx.com:interface:axis_rtl:1.0 mult_b ]
set_property -dict $DefaultInputPortProps $mult_b
set_property CONFIG.TUSER_WIDTH 0 $mult_b






set clock [ create_bd_port -dir I -type clk clock ]




set_property -dict [ list \
CONFIG.ASSOCIATED_BUSIF {adder_op:itf_res:fti_res:cmp_res:mul_res:add_res:adder_a:adder_b:mult_a:mult_b:itf_a:fti_b:comp_a:comp_b} \
CONFIG.ASSOCIATED_RESET {reset} \
] $clock







set reset [ create_bd_port -dir I -type rst reset ]


# Create instance: FP_adder, and set properties
set FP_adder [ create_bd_cell -type ip -vlnv xilinx.com:ip:floating_point:7.1 FP_adder ]
set_property -dict [ list \
CONFIG.A_TUSER_Width {32} \
CONFIG.C_Accum_Input_Msb {15} \
CONFIG.C_Accum_Lsb {-24} \
CONFIG.C_Latency {5} \
CONFIG.C_Mult_Usage {Full_Usage} \
CONFIG.Flow_Control {NonBlocking} \
CONFIG.Has_ARESETn {true} \
CONFIG.Has_A_TUSER {true} \
CONFIG.Has_RESULT_TREADY {false} \
CONFIG.Maximum_Latency {false} \
CONFIG.Operation_Type {Add_Subtract} \
] $FP_adder

# Create instance: FP_comparer, and set properties
set FP_comparer [ create_bd_cell -type ip -vlnv xilinx.com:ip:floating_point:7.1 FP_comparer ]
set_property -dict [ list \
CONFIG.A_TUSER_Width {32} \
CONFIG.C_Accum_Input_Msb {15} \
CONFIG.C_Accum_Lsb {-24} \
CONFIG.C_Compare_Operation {Programmable} \
CONFIG.C_Latency {2} \
CONFIG.C_Mult_Usage {No_Usage} \
CONFIG.C_Result_Exponent_Width {1} \
CONFIG.C_Result_Fraction_Width {0} \
CONFIG.Flow_Control {NonBlocking} \
CONFIG.Has_ARESETn {true} \
CONFIG.Has_A_TUSER {true} \
CONFIG.Has_RESULT_TREADY {false} \
CONFIG.Maximum_Latency {false} \
CONFIG.Operation_Type {Compare} \
CONFIG.Result_Precision_Type {Custom} \
] $FP_comparer

# Create instance: FP_multiplier, and set properties
set FP_multiplier [ create_bd_cell -type ip -vlnv xilinx.com:ip:floating_point:7.1 FP_multiplier ]
set_property -dict [ list \
CONFIG.A_TUSER_Width {32} \
CONFIG.C_Latency {5} \
CONFIG.C_Mult_Usage {Max_Usage} \
CONFIG.Flow_Control {NonBlocking} \
CONFIG.Has_ARESETn {true} \
CONFIG.Has_A_TUSER {true} \
CONFIG.Has_RESULT_TREADY {false} \
CONFIG.Maximum_Latency {false} \
CONFIG.Operation_Type {Multiply} \
] $FP_multiplier





set axis_cmp_0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:axis_register_slice:1.1 axis_cmp_0 ]
set_property -dict [ list CONFIG.REG_CONFIG {1} CONFIG.TUSER_WIDTH {32} ] $axis_cmp_0

set axis_cmp_1 [ create_bd_cell -type ip -vlnv xilinx.com:ip:axis_register_slice:1.1 axis_cmp_1 ]
set_property -dict [ list CONFIG.REG_CONFIG {1} CONFIG.TUSER_WIDTH {32} ] $axis_cmp_1

set axis_cmp_2 [ create_bd_cell -type ip -vlnv xilinx.com:ip:axis_register_slice:1.1 axis_cmp_2 ]
set_property -dict [ list CONFIG.REG_CONFIG {1} CONFIG.TUSER_WIDTH {32} ] $axis_cmp_2


# Create instance: fixed_to_float, and set properties
set fixed_to_float [ create_bd_cell -type ip -vlnv xilinx.com:ip:floating_point:7.1 fixed_to_float ]
set_property -dict [ list \
CONFIG.A_TUSER_Width {32} \
CONFIG.C_Latency {5} \
CONFIG.Flow_Control {NonBlocking} \
CONFIG.Has_ARESETn {true} \
CONFIG.Has_A_TUSER {true} \
CONFIG.Has_RESULT_TREADY {false} \
CONFIG.Maximum_Latency {false} \
CONFIG.Operation_Type {Fixed_to_float} \
] $fixed_to_float

# Create instance: float_to_fixed, and set properties
set float_to_fixed [ create_bd_cell -type ip -vlnv xilinx.com:ip:floating_point:7.1 float_to_fixed ]
set_property -dict [ list \
CONFIG.A_TUSER_Width {32} \
CONFIG.C_Latency {5} \
CONFIG.C_Result_Exponent_Width {32} \
CONFIG.C_Result_Fraction_Width {0} \
CONFIG.Flow_Control {NonBlocking} \
CONFIG.Has_ARESETn {true} \
CONFIG.Has_A_TUSER {true} \
CONFIG.Has_RESULT_TREADY {false} \
CONFIG.Maximum_Latency {false} \
CONFIG.Operation_Type {Float_to_fixed} \
CONFIG.Result_Precision_Type {Int32} \
] $float_to_fixed


# Create interface connections

connect_bd_intf_net -intf_net adder_a [get_bd_intf_ports adder_a] [get_bd_intf_pins FP_adder/S_AXIS_A]
connect_bd_intf_net -intf_net adder_b [get_bd_intf_ports adder_b] [get_bd_intf_pins FP_adder/S_AXIS_B]
connect_bd_intf_net -intf_net adder_op [get_bd_intf_ports adder_op] [get_bd_intf_pins FP_adder/S_AXIS_OPERATION]


connect_bd_intf_net -intf_net adder_result_c [get_bd_intf_pins FP_adder/M_AXIS_RESULT] [get_bd_intf_pins add_res]




connect_bd_intf_net -intf_net multiplier_result_c [get_bd_intf_pins FP_multiplier/M_AXIS_RESULT] [get_bd_intf_pins mul_res]


connect_bd_intf_net -intf_net itf_a [get_bd_intf_ports itf_a] [get_bd_intf_pins fixed_to_float/S_AXIS_A]


connect_bd_intf_net -intf_net itf_result_c [get_bd_intf_pins fixed_to_float/M_AXIS_RESULT] [get_bd_intf_pins itf_res]



connect_bd_intf_net -intf_net fti_b [get_bd_intf_ports fti_b] [get_bd_intf_pins float_to_fixed/S_AXIS_A]


connect_bd_intf_net -intf_net fti_result_c [get_bd_intf_pins float_to_fixed/M_AXIS_RESULT] [get_bd_intf_pins fti_res]



connect_bd_intf_net -intf_net mult_a [get_bd_intf_ports mult_a] [get_bd_intf_pins FP_multiplier/S_AXIS_A]
connect_bd_intf_net -intf_net mult_b [get_bd_intf_ports mult_b] [get_bd_intf_pins FP_multiplier/S_AXIS_B]




connect_bd_intf_net -intf_net comp_a [get_bd_intf_ports comp_a] [get_bd_intf_pins FP_comparer/S_AXIS_A]
connect_bd_intf_net -intf_net comp_b [get_bd_intf_ports comp_b] [get_bd_intf_pins FP_comparer/S_AXIS_B]
connect_bd_intf_net -intf_net comp_op [get_bd_intf_ports comp_op] [get_bd_intf_pins FP_comparer/S_AXIS_OPERATION]

connect_bd_intf_net -intf_net cmp_result_c [get_bd_intf_pins FP_comparer/M_AXIS_RESULT] [get_bd_intf_pins axis_cmp_0/S_AXIS]
connect_bd_intf_net -intf_net cmp_del_0_c [get_bd_intf_pins axis_cmp_0/M_AXIS] [get_bd_intf_pins axis_cmp_1/S_AXIS]
connect_bd_intf_net -intf_net cmp_del_1_c [get_bd_intf_pins axis_cmp_1/M_AXIS] [get_bd_intf_pins axis_cmp_2/S_AXIS]


connect_bd_intf_net -intf_net cmp_del_2_c [get_bd_intf_pins axis_cmp_2/M_AXIS] [get_bd_intf_pins cmp_res]



# Create port connections
connect_bd_net -net ARESETN_0_1 [get_bd_ports reset] [get_bd_pins FP_adder/aresetn] [get_bd_pins FP_comparer/aresetn] [get_bd_pins FP_multiplier/aresetn] [get_bd_pins fixed_to_float/aresetn] [get_bd_pins float_to_fixed/aresetn]
connect_bd_net -net aclk_0_1 [get_bd_ports clock] [get_bd_pins FP_adder/aclk] [get_bd_pins FP_comparer/aclk] [get_bd_pins FP_multiplier/aclk] [get_bd_pins fixed_to_float/aclk] [get_bd_pins float_to_fixed/aclk]



connect_bd_net -net ARESETN_0_1 [get_bd_ports reset] [get_bd_pins axis_cmp_0/aresetn]

connect_bd_net -net ARESETN_0_1 [get_bd_ports reset] [get_bd_pins axis_cmp_1/aresetn]

connect_bd_net -net ARESETN_0_1 [get_bd_ports reset] [get_bd_pins axis_cmp_2/aresetn]



connect_bd_net -net aclk_0_1 [get_bd_ports clock] [get_bd_pins axis_cmp_0/aclk]

connect_bd_net -net aclk_0_1 [get_bd_ports clock] [get_bd_pins axis_cmp_1/aclk]

connect_bd_net -net aclk_0_1 [get_bd_ports clock] [get_bd_pins axis_cmp_2/aclk]





 
# Restore current instance
current_bd_instance $oldCurInst

validate_bd_design
regenerate_bd_layout
save_bd_design


