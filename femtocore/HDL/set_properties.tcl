set_property part xc7z020clg400-1 [current_project]

set_property -name "default_lib" -value "xil_defaultlib" -objects $obj
set_property -name "enable_vhdl_2008" -value "1" -objects $obj
set_property -name "ip_cache_permissions" -value "read write" -objects $obj
set_property -name "ip_output_repo" -value "$proj_dir/${project_name}.cache/ip" -objects $obj
set_property -name "mem.enable_memory_map_generation" -value "1" -objects $obj
set_property -name "sim.central_dir" -value "$proj_dir/${project_name}.ip_user_files" -objects $obj
set_property -name "sim.ip.auto_export_scripts" -value "1" -objects $obj
set_property -name "simulator_language" -value "Mixed" -objects $obj
set_property -name "webtalk.activehdl_export_sim" -value "1" -objects $obj
set_property -name "webtalk.ies_export_sim" -value "1" -objects $obj
set_property -name "webtalk.modelsim_export_sim" -value "1" -objects $obj
set_property -name "webtalk.questa_export_sim" -value "1" -objects $obj
set_property -name "webtalk.riviera_export_sim" -value "1" -objects $obj
set_property -name "webtalk.vcs_export_sim" -value "1" -objects $obj
set_property -name "webtalk.xcelium_export_sim" -value "1" -objects $obj
set_property -name "webtalk.xsim_export_sim" -value "1" -objects $obj
set_property -name "xpm_libraries" -value "XPM_FIFO XPM_MEMORY" -objects $obj