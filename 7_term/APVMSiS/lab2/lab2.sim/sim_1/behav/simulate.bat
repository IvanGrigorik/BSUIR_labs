@echo off
set xv_path=E:\\utils\\Vivado\\Vivado\\2017.2\\bin
call %xv_path%/xsim SHFT_REG_tb_behav -key {Behavioral:sim_1:Functional:SHFT_REG_tb} -tclbatch SHFT_REG_tb.tcl -log simulate.log
if "%errorlevel%"=="0" goto SUCCESS
if "%errorlevel%"=="1" goto END
:END
exit 1
:SUCCESS
exit 0
