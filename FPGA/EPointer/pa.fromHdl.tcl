
# PlanAhead Launch Script for Pre-Synthesis Floorplanning, created by Project Navigator

hdi::project new -name EPointer -dir "C:/Users/bjtu/ISEWork/EPointer/EPointer/patmp"
hdi::project setArch -name EPointer -arch spartan3a
hdi::design setOptions -project EPointer -top top  
hdi::param set -name project.paUcfFile -svalue "C:/Users/bjtu/ISEWork/EPointer/src/top.ucf"
hdi::floorplan new -name floorplan_1 -part xc3s50antqg144-4 -project EPointer
hdi::port import -project EPointer \
    -verilog {ipcore_dir/dual_port_ram1024.v work} \
    -verilog {../src/data_proc.v work} \
    -verilog {../src/cmos_ctrl.v work} \
    -verilog {clock_gene.v work} \
    -verilog {../src/top.v work}
hdi::port export -project EPointer -file EPointer_pa_ports.v -format verilog
hdi::pconst import -project EPointer -floorplan floorplan_1 -file "C:/Users/bjtu/ISEWork/EPointer/src/top.ucf"
