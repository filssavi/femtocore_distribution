
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

################################################################
# Check if script is running in correct Vivado version.
################################################################
set scripts_vivado_version 2020.2
set current_vivado_version [version -short]



################################################################
# START
################################################################

# To test this script, run the following commands from Vivado Tcl console:
# source fp_alu_script.tcl

# If there is no project opened, this script will create a
# project, but make sure you do not have an existing project
# <./myproj/project_1.xpr> in the current working folder.

set list_projs [get_projects -quiet]
if { $list_projs eq "" } {
   create_project project_1 myproj -part xc7z010clg400-1
   set_property BOARD_PART em.avnet.com:microzed_7010:part0:1.1 [current_project]
}


# CHANGE DESIGN NAME HERE
variable design_name
set design_name fp_alu

# If you do not already have an existing IP Integrator design open,
# you can create a design using the following command:
#    create_bd_design $design_name

# Creating design if needed
set errMsg ""
set nRet 0

set cur_design [current_bd_design -quiet]
set list_cells [get_bd_cells -quiet]

if { ${design_name} eq "" } {
   # USE CASES:
   #    1) Design_name not set

   set errMsg "Please set the variable <design_name> to a non-empty value."
   set nRet 1

} elseif { ${cur_design} ne "" && ${list_cells} eq "" } {
   # USE CASES:
   #    2): Current design opened AND is empty AND names same.
   #    3): Current design opened AND is empty AND names diff; design_name NOT in project.
   #    4): Current design opened AND is empty AND names diff; design_name exists in project.

   if { $cur_design ne $design_name } {
      common::send_gid_msg -ssname BD::TCL -id 2001 -severity "INFO" "Changing value of <design_name> from <$design_name> to <$cur_design> since current design is empty."
      set design_name [get_property NAME $cur_design]
   }
   common::send_gid_msg -ssname BD::TCL -id 2002 -severity "INFO" "Constructing design in IPI design <$cur_design>..."

} elseif { ${cur_design} ne "" && $list_cells ne "" && $cur_design eq $design_name } {
   # USE CASES:
   #    5) Current design opened AND has components AND same names.

   set errMsg "Design <$design_name> already exists in your project, please set the variable <design_name> to another value."
   set nRet 1
} elseif { [get_files -quiet ${design_name}.bd] ne "" } {
   # USE CASES: 
   #    6) Current opened design, has components, but diff names, design_name exists in project.
   #    7) No opened design, design_name exists in project.

   set errMsg "Design <$design_name> already exists in your project, please set the variable <design_name> to another value."
   set nRet 2

} else {
   # USE CASES:
   #    8) No opened design, design_name not in project.
   #    9) Current opened design, has components, but diff names, design_name not in project.

   common::send_gid_msg -ssname BD::TCL -id 2003 -severity "INFO" "Currently there is no design <$design_name> in project, so creating one..."

   create_bd_design $design_name

   common::send_gid_msg -ssname BD::TCL -id 2004 -severity "INFO" "Making design <$design_name> as current_bd_design."
   current_bd_design $design_name

}

common::send_gid_msg -ssname BD::TCL -id 2005 -severity "INFO" "Currently the variable <design_name> is equal to \"$design_name\"."

if { $nRet != 0 } {
   catch {common::send_gid_msg -ssname BD::TCL -id 2006 -severity "ERROR" $errMsg}
   return $nRet
}

set bCheckIPsPassed 1
##################################################################
# CHECK IPs
##################################################################
set bCheckIPs 1
if { $bCheckIPs == 1 } {
   set list_check_ips "\ 
xilinx.com:ip:floating_point:7.1\
xilinx.com:ip:axis_register_slice:1.1\
"

   set list_ips_missing ""
   common::send_gid_msg -ssname BD::TCL -id 2011 -severity "INFO" "Checking if the following IPs exist in the project's IP catalog: $list_check_ips ."

   foreach ip_vlnv $list_check_ips {
      set ip_obj [get_ipdefs -all $ip_vlnv]
      if { $ip_obj eq "" } {
         lappend list_ips_missing $ip_vlnv
      }
   }

   if { $list_ips_missing ne "" } {
      catch {common::send_gid_msg -ssname BD::TCL -id 2012 -severity "ERROR" "The following IPs are not found in the IP Catalog:\n  $list_ips_missing\n\nResolution: Please add the repository containing the IP(s) to the project." }
      set bCheckIPsPassed 0
   }

}

if { $bCheckIPsPassed != 1 } {
  common::send_gid_msg -ssname BD::TCL -id 2023 -severity "WARNING" "Will not continue with creation of design due to the error(s) above."
  return 3
}

##################################################################
# DESIGN PROCs
##################################################################



# Procedure to create entire design; Provide argument to make
# procedure reusable. If parentCell is "", will use root.
proc create_root_design { parentCell } {

  variable script_folder
  variable design_name

  if { $parentCell eq "" } {
     set parentCell [get_bd_cells /]
  }

  # Get object for parentCell
  set parentObj [get_bd_cells $parentCell]
  if { $parentObj == "" } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2090 -severity "ERROR" "Unable to find parent cell <$parentCell>!"}
     return
  }

  # Make sure parentObj is hier blk
  set parentType [get_property TYPE $parentObj]
  if { $parentType ne "hier" } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2091 -severity "ERROR" "Parent <$parentObj> has TYPE = <$parentType>. Expected to be <hier>."}
     return
  }

  # Save current instance; Restore later
  set oldCurInst [current_bd_instance .]

  # Set parent object as current
  current_bd_instance $parentObj


  # Create interface ports
  set add_res [ create_bd_intf_port -mode Master -vlnv xilinx.com:interface:axis_rtl:1.0 add_res ]

  set adder_a [ create_bd_intf_port -mode Slave -vlnv xilinx.com:interface:axis_rtl:1.0 adder_a ]
  set_property -dict [ list \
   CONFIG.HAS_TKEEP {0} \
   CONFIG.HAS_TLAST {0} \
   CONFIG.HAS_TREADY {0} \
   CONFIG.HAS_TSTRB {0} \
   CONFIG.LAYERED_METADATA {undef} \
   CONFIG.TDATA_NUM_BYTES {4} \
   CONFIG.TDEST_WIDTH {0} \
   CONFIG.TID_WIDTH {0} \
   CONFIG.TUSER_WIDTH {8} \
   ] $adder_a

  set adder_b [ create_bd_intf_port -mode Slave -vlnv xilinx.com:interface:axis_rtl:1.0 adder_b ]
  set_property -dict [ list \
   CONFIG.HAS_TKEEP {0} \
   CONFIG.HAS_TLAST {0} \
   CONFIG.HAS_TREADY {0} \
   CONFIG.HAS_TSTRB {0} \
   CONFIG.LAYERED_METADATA {undef} \
   CONFIG.TDATA_NUM_BYTES {4} \
   CONFIG.TDEST_WIDTH {0} \
   CONFIG.TID_WIDTH {0} \
   CONFIG.TUSER_WIDTH {0} \
   ] $adder_b

  set adder_op [ create_bd_intf_port -mode Slave -vlnv xilinx.com:interface:axis_rtl:1.0 adder_op ]
  set_property -dict [ list \
   CONFIG.HAS_TKEEP {0} \
   CONFIG.HAS_TLAST {0} \
   CONFIG.HAS_TREADY {1} \
   CONFIG.HAS_TSTRB {0} \
   CONFIG.LAYERED_METADATA {undef} \
   CONFIG.TDATA_NUM_BYTES {1} \
   CONFIG.TDEST_WIDTH {4} \
   CONFIG.TID_WIDTH {0} \
   CONFIG.TUSER_WIDTH {8} \
   ] $adder_op

  set cmp_res [ create_bd_intf_port -mode Master -vlnv xilinx.com:interface:axis_rtl:1.0 cmp_res ]

  set comp_a [ create_bd_intf_port -mode Slave -vlnv xilinx.com:interface:axis_rtl:1.0 comp_a ]
  set_property -dict [ list \
   CONFIG.HAS_TKEEP {0} \
   CONFIG.HAS_TLAST {0} \
   CONFIG.HAS_TREADY {0} \
   CONFIG.HAS_TSTRB {0} \
   CONFIG.LAYERED_METADATA {undef} \
   CONFIG.TDATA_NUM_BYTES {4} \
   CONFIG.TDEST_WIDTH {0} \
   CONFIG.TID_WIDTH {0} \
   CONFIG.TUSER_WIDTH {8} \
   ] $comp_a

  set comp_b [ create_bd_intf_port -mode Slave -vlnv xilinx.com:interface:axis_rtl:1.0 comp_b ]
  set_property -dict [ list \
   CONFIG.HAS_TKEEP {0} \
   CONFIG.HAS_TLAST {0} \
   CONFIG.HAS_TREADY {0} \
   CONFIG.HAS_TSTRB {0} \
   CONFIG.LAYERED_METADATA {undef} \
   CONFIG.TDATA_NUM_BYTES {4} \
   CONFIG.TDEST_WIDTH {0} \
   CONFIG.TID_WIDTH {0} \
   CONFIG.TUSER_WIDTH {0} \
   ] $comp_b

  set fti_b [ create_bd_intf_port -mode Slave -vlnv xilinx.com:interface:axis_rtl:1.0 fti_b ]
  set_property -dict [ list \
   CONFIG.HAS_TKEEP {0} \
   CONFIG.HAS_TLAST {0} \
   CONFIG.HAS_TREADY {0} \
   CONFIG.HAS_TSTRB {0} \
   CONFIG.LAYERED_METADATA {undef} \
   CONFIG.TDATA_NUM_BYTES {4} \
   CONFIG.TDEST_WIDTH {0} \
   CONFIG.TID_WIDTH {0} \
   CONFIG.TUSER_WIDTH {8} \
   ] $fti_b

  set fti_res [ create_bd_intf_port -mode Master -vlnv xilinx.com:interface:axis_rtl:1.0 fti_res ]

  set itf_a [ create_bd_intf_port -mode Slave -vlnv xilinx.com:interface:axis_rtl:1.0 itf_a ]
  set_property -dict [ list \
   CONFIG.HAS_TKEEP {0} \
   CONFIG.HAS_TLAST {0} \
   CONFIG.HAS_TREADY {0} \
   CONFIG.HAS_TSTRB {0} \
   CONFIG.LAYERED_METADATA {undef} \
   CONFIG.TDATA_NUM_BYTES {4} \
   CONFIG.TDEST_WIDTH {0} \
   CONFIG.TID_WIDTH {0} \
   CONFIG.TUSER_WIDTH {8} \
   ] $itf_a

  set itf_res [ create_bd_intf_port -mode Master -vlnv xilinx.com:interface:axis_rtl:1.0 itf_res ]

  set mul_res [ create_bd_intf_port -mode Master -vlnv xilinx.com:interface:axis_rtl:1.0 mul_res ]

  set mult_a [ create_bd_intf_port -mode Slave -vlnv xilinx.com:interface:axis_rtl:1.0 mult_a ]
  set_property -dict [ list \
   CONFIG.HAS_TKEEP {0} \
   CONFIG.HAS_TLAST {0} \
   CONFIG.HAS_TREADY {0} \
   CONFIG.HAS_TSTRB {0} \
   CONFIG.LAYERED_METADATA {undef} \
   CONFIG.TDATA_NUM_BYTES {4} \
   CONFIG.TDEST_WIDTH {0} \
   CONFIG.TID_WIDTH {0} \
   CONFIG.TUSER_WIDTH {8} \
   ] $mult_a

  set mult_b [ create_bd_intf_port -mode Slave -vlnv xilinx.com:interface:axis_rtl:1.0 mult_b ]
  set_property -dict [ list \
   CONFIG.HAS_TKEEP {0} \
   CONFIG.HAS_TLAST {0} \
   CONFIG.HAS_TREADY {0} \
   CONFIG.HAS_TSTRB {0} \
   CONFIG.LAYERED_METADATA {undef} \
   CONFIG.TDATA_NUM_BYTES {4} \
   CONFIG.TDEST_WIDTH {0} \
   CONFIG.TID_WIDTH {0} \
   CONFIG.TUSER_WIDTH {0} \
   ] $mult_b


  # Create ports
  set clock [ create_bd_port -dir I -type clk clock ]
  set_property -dict [ list \
   CONFIG.ASSOCIATED_BUSIF {adder_op:itf_res:fti_res:cmp_res:mul_res:add_res:adder_a:adder_b:mult_a:mult_b:itf_a:fti_b:comp_a:comp_b} \
   CONFIG.ASSOCIATED_RESET {reset} \
 ] $clock
  set reset [ create_bd_port -dir I -type rst reset ]

  # Create instance: FP_adder, and set properties
  set FP_adder [ create_bd_cell -type ip -vlnv xilinx.com:ip:floating_point:7.1 FP_adder ]
  set_property -dict [ list \
   CONFIG.A_Precision_Type {Single} \
   CONFIG.A_TUSER_Width {32} \
   CONFIG.Axi_Optimize_Goal {Resources} \
   CONFIG.B_TUSER_Width {1} \
   CONFIG.C_A_Exponent_Width {8} \
   CONFIG.C_A_Fraction_Width {24} \
   CONFIG.C_Accum_Input_Msb {15} \
   CONFIG.C_Accum_Lsb {-24} \
   CONFIG.C_Accum_Msb {32} \
   CONFIG.C_Latency {5} \
   CONFIG.C_Mult_Usage {Full_Usage} \
   CONFIG.C_Optimization {Speed_Optimized} \
   CONFIG.C_Rate {1} \
   CONFIG.C_Result_Exponent_Width {8} \
   CONFIG.C_Result_Fraction_Width {24} \
   CONFIG.Flow_Control {NonBlocking} \
   CONFIG.Has_ARESETn {true} \
   CONFIG.Has_A_TLAST {false} \
   CONFIG.Has_A_TUSER {true} \
   CONFIG.Has_B_TLAST {false} \
   CONFIG.Has_B_TUSER {false} \
   CONFIG.Has_RESULT_TREADY {false} \
   CONFIG.Maximum_Latency {false} \
   CONFIG.Operation_Type {Add_Subtract} \
   CONFIG.RESULT_TLAST_Behv {Null} \
   CONFIG.Result_Precision_Type {Single} \
 ] $FP_adder

  # Create instance: FP_comparer, and set properties
  set FP_comparer [ create_bd_cell -type ip -vlnv xilinx.com:ip:floating_point:7.1 FP_comparer ]
  set_property -dict [ list \
   CONFIG.A_Precision_Type {Single} \
   CONFIG.A_TUSER_Width {32} \
   CONFIG.Axi_Optimize_Goal {Resources} \
   CONFIG.C_A_Exponent_Width {8} \
   CONFIG.C_A_Fraction_Width {24} \
   CONFIG.C_Accum_Input_Msb {15} \
   CONFIG.C_Accum_Lsb {-24} \
   CONFIG.C_Accum_Msb {32} \
   CONFIG.C_Compare_Operation {Greater_Than} \
   CONFIG.C_Latency {2} \
   CONFIG.C_Mult_Usage {No_Usage} \
   CONFIG.C_Rate {1} \
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
   CONFIG.Axi_Optimize_Goal {Resources} \
   CONFIG.C_Latency {5} \
   CONFIG.C_Mult_Usage {Max_Usage} \
   CONFIG.C_Rate {1} \
   CONFIG.C_Result_Exponent_Width {8} \
   CONFIG.C_Result_Fraction_Width {24} \
   CONFIG.Flow_Control {NonBlocking} \
   CONFIG.Has_ARESETn {true} \
   CONFIG.Has_A_TUSER {true} \
   CONFIG.Has_RESULT_TREADY {false} \
   CONFIG.Maximum_Latency {false} \
   CONFIG.Operation_Type {Multiply} \
   CONFIG.Result_Precision_Type {Single} \
 ] $FP_multiplier

  # Create instance: axis_register_slice_0, and set properties
  set axis_register_slice_0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:axis_register_slice:1.1 axis_register_slice_0 ]
  set_property -dict [ list \
   CONFIG.REG_CONFIG {1} \
   CONFIG.TUSER_WIDTH {32} \
 ] $axis_register_slice_0

  # Create instance: axis_register_slice_1, and set properties
  set axis_register_slice_1 [ create_bd_cell -type ip -vlnv xilinx.com:ip:axis_register_slice:1.1 axis_register_slice_1 ]
  set_property -dict [ list \
   CONFIG.REG_CONFIG {1} \
   CONFIG.TUSER_WIDTH {32} \
 ] $axis_register_slice_1

  # Create instance: axis_register_slice_2, and set properties
  set axis_register_slice_2 [ create_bd_cell -type ip -vlnv xilinx.com:ip:axis_register_slice:1.1 axis_register_slice_2 ]
  set_property -dict [ list \
   CONFIG.REG_CONFIG {1} \
   CONFIG.TUSER_WIDTH {32} \
 ] $axis_register_slice_2

  # Create instance: fixed_to_float, and set properties
  set fixed_to_float [ create_bd_cell -type ip -vlnv xilinx.com:ip:floating_point:7.1 fixed_to_float ]
  set_property -dict [ list \
   CONFIG.A_TUSER_Width {32} \
   CONFIG.Axi_Optimize_Goal {Resources} \
   CONFIG.C_Accum_Input_Msb {32} \
   CONFIG.C_Accum_Lsb {-31} \
   CONFIG.C_Accum_Msb {32} \
   CONFIG.C_Latency {5} \
   CONFIG.C_Mult_Usage {No_Usage} \
   CONFIG.C_Rate {1} \
   CONFIG.C_Result_Exponent_Width {8} \
   CONFIG.C_Result_Fraction_Width {24} \
   CONFIG.Flow_Control {NonBlocking} \
   CONFIG.Has_ARESETn {true} \
   CONFIG.Has_A_TUSER {true} \
   CONFIG.Has_RESULT_TREADY {false} \
   CONFIG.Maximum_Latency {false} \
   CONFIG.Operation_Type {Fixed_to_float} \
   CONFIG.Result_Precision_Type {Single} \
 ] $fixed_to_float

  # Create instance: float_to_fixed, and set properties
  set float_to_fixed [ create_bd_cell -type ip -vlnv xilinx.com:ip:floating_point:7.1 float_to_fixed ]
  set_property -dict [ list \
   CONFIG.A_TUSER_Width {32} \
   CONFIG.Axi_Optimize_Goal {Resources} \
   CONFIG.C_Accum_Input_Msb {32} \
   CONFIG.C_Accum_Lsb {-31} \
   CONFIG.C_Accum_Msb {32} \
   CONFIG.C_Latency {5} \
   CONFIG.C_Mult_Usage {No_Usage} \
   CONFIG.C_Rate {1} \
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
  connect_bd_intf_net -intf_net FP_adder_M_AXIS_RESULT [get_bd_intf_ports add_res] [get_bd_intf_pins FP_adder/M_AXIS_RESULT]
  connect_bd_intf_net -intf_net FP_comparer_M_AXIS_RESULT [get_bd_intf_pins FP_comparer/M_AXIS_RESULT] [get_bd_intf_pins axis_register_slice_0/S_AXIS]
  connect_bd_intf_net -intf_net FP_multiplier_M_AXIS_RESULT [get_bd_intf_ports mul_res] [get_bd_intf_pins FP_multiplier/M_AXIS_RESULT]
  connect_bd_intf_net -intf_net adder_a [get_bd_intf_ports adder_a] [get_bd_intf_pins FP_adder/S_AXIS_A]
  connect_bd_intf_net -intf_net adder_b [get_bd_intf_ports adder_b] [get_bd_intf_pins FP_adder/S_AXIS_B]
  connect_bd_intf_net -intf_net adder_op [get_bd_intf_ports adder_op] [get_bd_intf_pins FP_adder/S_AXIS_OPERATION]
  connect_bd_intf_net -intf_net axis_register_slice_0_M_AXIS [get_bd_intf_pins axis_register_slice_0/M_AXIS] [get_bd_intf_pins axis_register_slice_1/S_AXIS]
  connect_bd_intf_net -intf_net axis_register_slice_1_M_AXIS [get_bd_intf_pins axis_register_slice_1/M_AXIS] [get_bd_intf_pins axis_register_slice_2/S_AXIS]
  connect_bd_intf_net -intf_net axis_register_slice_2_M_AXIS [get_bd_intf_ports cmp_res] [get_bd_intf_pins axis_register_slice_2/M_AXIS]
  connect_bd_intf_net -intf_net comp_a [get_bd_intf_ports comp_a] [get_bd_intf_pins FP_comparer/S_AXIS_A]
  connect_bd_intf_net -intf_net comp_b [get_bd_intf_ports comp_b] [get_bd_intf_pins FP_comparer/S_AXIS_B]
  connect_bd_intf_net -intf_net fixed_to_float_M_AXIS_RESULT [get_bd_intf_ports itf_res] [get_bd_intf_pins fixed_to_float/M_AXIS_RESULT]
  connect_bd_intf_net -intf_net float_to_fixed_M_AXIS_RESULT [get_bd_intf_ports fti_res] [get_bd_intf_pins float_to_fixed/M_AXIS_RESULT]
  connect_bd_intf_net -intf_net fti_b [get_bd_intf_ports fti_b] [get_bd_intf_pins float_to_fixed/S_AXIS_A]
  connect_bd_intf_net -intf_net itf_a [get_bd_intf_ports itf_a] [get_bd_intf_pins fixed_to_float/S_AXIS_A]
  connect_bd_intf_net -intf_net mult_a [get_bd_intf_ports mult_a] [get_bd_intf_pins FP_multiplier/S_AXIS_A]
  connect_bd_intf_net -intf_net mult_b [get_bd_intf_ports mult_b] [get_bd_intf_pins FP_multiplier/S_AXIS_B]

  # Create port connections
  connect_bd_net -net ARESETN_0_1 [get_bd_ports reset] [get_bd_pins FP_adder/aresetn] [get_bd_pins FP_comparer/aresetn] [get_bd_pins FP_multiplier/aresetn] [get_bd_pins axis_register_slice_0/aresetn] [get_bd_pins axis_register_slice_1/aresetn] [get_bd_pins axis_register_slice_2/aresetn] [get_bd_pins fixed_to_float/aresetn] [get_bd_pins float_to_fixed/aresetn]
  connect_bd_net -net aclk_0_1 [get_bd_ports clock] [get_bd_pins FP_adder/aclk] [get_bd_pins FP_comparer/aclk] [get_bd_pins FP_multiplier/aclk] [get_bd_pins axis_register_slice_0/aclk] [get_bd_pins axis_register_slice_1/aclk] [get_bd_pins axis_register_slice_2/aclk] [get_bd_pins fixed_to_float/aclk] [get_bd_pins float_to_fixed/aclk]

  # Create address segments


  # Restore current instance
  current_bd_instance $oldCurInst

  save_bd_design
}
# End of create_root_design()


##################################################################
# MAIN FLOW
##################################################################

create_root_design ""


common::send_gid_msg -ssname BD::TCL -id 2053 -severity "WARNING" "This Tcl script was generated from a block design that has not been validated. It is possible that design <$design_name> may result in errors during validation."

