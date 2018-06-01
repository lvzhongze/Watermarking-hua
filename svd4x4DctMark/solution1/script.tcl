############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 1986-2017 Xilinx, Inc. All Rights Reserved.
############################################################
open_project svdDctMark
add_files svdDctMark/dct.cpp
add_files svdDctMark/dct.h
add_files svdDctMark/svd.cpp
add_files svdDctMark/svd.h
add_files svdDctMark/svdEmbed.cpp
add_files svdDctMark/svdEmbed.h
add_files -tb svdDctMark/01.jpg
add_files -tb svdDctMark/1.jpg
add_files -tb svdDctMark/2.jpg
add_files -tb svdDctMark/3.jpg
add_files -tb svdDctMark/4.jpg
add_files -tb svdDctMark/5.jpg
add_files -tb svdDctMark/6.jpg
add_files -tb svdDctMark/7.jpg
add_files -tb svdDctMark/8.jpg
add_files -tb svdDctMark/9.jpg
add_files -tb svdDctMark/basicData.cpp
add_files -tb svdDctMark/basicData.h
add_files -tb svdDctMark/main_tb.cpp
open_solution "solution1"
set_part {xc7z045ffg900-2} -tool vivado
create_clock -period 10 -name default
#source "./svdDctMark/solution1/directives.tcl"
csim_design -clean
csynth_design
cosim_design
export_design -format ip_catalog
