open_project -reset mul_hls

source ../../common/config.tcl

set period_run $period
if {[info exists ::env(CLOCK_PERIOD)]} { set period_run $::env(CLOCK_PERIOD) }
set note ""
if {[info exists ::env(VARIANT_NOTE)]} { set note $::env(VARIANT_NOTE) }
set dir_file "./mul_dir"
if {[info exists ::env(DIR_FILE)]} { set dir_file $::env(DIR_FILE) }

add_files mul.cpp -cflags "-I../../common"
add_files input.data
add_files check.data
add_files -tb ../../common/support.cpp -cflags "-I../../common -g"
add_files -tb local_support.cpp -cflags "-I../../common -g"
add_files -tb ../../common/harness.cpp -cflags "-I../../common -g"

set_top mul

open_solution -reset solution
set_part $part_name
create_clock -period $period_run
source $dir_file
csynth_design
collect_hls_results mul_hls solution mul elemwise $note

exit
