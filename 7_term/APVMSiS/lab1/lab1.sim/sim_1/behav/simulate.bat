@echo off
set xv_path=E:\\utils\\Vivado\\Vivado\\2017.2\\bin
call %xv_path%/xsim MUX8TO1_seq_tb_behav -key {Behavioral:sim_1:Functional:MUX8TO1_seq_tb} -tclbatch MUX8TO1_seq_tb.tcl -log simulate.log
if "%errorlevel%"=="0" goto SUCCESS
if "%errorlevel%"=="1" goto END
:END
exit 1
:SUCCESS
exit 0
