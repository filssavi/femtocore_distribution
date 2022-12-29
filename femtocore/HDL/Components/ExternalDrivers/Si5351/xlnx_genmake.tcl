set project_name "i2c"
set origin_dir "."

set components_dir /home/filssavi/git/sicdrive-hdl/Components
set applications_dir /home/filssavi/git/sicdrive-hdl/Applications
set commons_dir /home/filssavi/git/sicdrive-hdl/Components/Common
set current_dir /home/filssavi/git/sicdrive-hdl/Components/ExternalDrivers/Si5351

set synth_sources [list  $current_dir/rtl/Si5351_configurator.v] 

set sim_sources [list  $current_dir/tb/Si5351_configurator_tb.sv.sv] 

# Create project
create_project ${project_name} ./${project_name} -part xc7z020clg400-1

# Set the directory path for the new project
set proj_dir [get_property directory [current_project]]

set obj [current_project]
 

add_files -norecurse $synth_sources
set_property top si5351_config [get_filesets sources_1]
set_property include_dirs $commons_dir [get_filesets sources_1]

set_property SOURCE_SET sources_1 [get_filesets sim_1]
add_files -fileset sim_1 -norecurse $sim_sources
set_property top si5351_config_tb [get_filesets sim_1]

update_compile_order