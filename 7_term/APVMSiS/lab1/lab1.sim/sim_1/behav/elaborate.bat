@echo off
set xv_path=E:\\utils\\Vivado\\Vivado\\2017.2\\bin
call %xv_path%/xelab  -wto 89e8db05da66405a95c1e4aa3d045b15 -m64 --debug typical --relax --mt 2 -L xil_defaultlib -L secureip --snapshot MUX8TO1_seq_tb_behav xil_defaultlib.MUX8TO1_seq_tb -log elaborate.log
if "%errorlevel%"=="0" goto SUCCESS
if "%errorlevel%"=="1" goto END
:END
exit 1
:SUCCESS
exit 0
