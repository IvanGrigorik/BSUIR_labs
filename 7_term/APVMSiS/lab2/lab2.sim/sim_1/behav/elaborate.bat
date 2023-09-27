@echo off
set xv_path=E:\\utils\\Vivado\\Vivado\\2017.2\\bin
call %xv_path%/xelab  -wto f915ddb5a9b1461195eee266249d0b57 -m64 --debug typical --relax --mt 2 -L xil_defaultlib -L secureip --snapshot SHFT_REG_tb_behav xil_defaultlib.SHFT_REG_tb -log elaborate.log
if "%errorlevel%"=="0" goto SUCCESS
if "%errorlevel%"=="1" goto END
:END
exit 1
:SUCCESS
exit 0
