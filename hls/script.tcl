############################################################
## This file is generated automatically by Vitis HLS.
## Please DO NOT edit it.
## Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
############################################################
open_project cnn
set_top cnn_top
add_files cnn_top.cpp
add_files cnn_top.h
add_files -tb cnn_tb.cpp
open_solution "solution1" -flow_target vivado
set_part {xc7z020clg484-1}
create_clock -period 20 -name default
source ./directives.tcl
csim_design
csynth_design
#cosim_design
export_design -format ip_catalog
