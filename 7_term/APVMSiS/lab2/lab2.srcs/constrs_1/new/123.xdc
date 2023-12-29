set_property PACKAGE_PIN R3 [get_ports clk_in1_p]
set_property IOSTANDARD LVCMOS33 [get_ports clk_in1_p]

#create_clock -name clk_in1_p -period 5.0 [get_ports {clk_in1_p}]
#create_generated_clock -name clk1sec -source [get_ports i_clk] -divide_by 200000000 \ [get_pins Counter_divider/o_clk]
set_property CLOCK_DEDICATED_ROUTE [get_nets i_clk_IBUF]


set_property PACKAGE_PIN U4 [get_ports reset]
set_property IOSTANDARD SSTL15 [get_ports reset]

# pushbuttons (SW3 - data in, SW7 - load in)
set_property PACKAGE_PIN P6 [get_ports i_data]
set_property IOSTANDARD SSTL15 [get_ports i_data]
set_property PACKAGE_PIN R5 [get_ports i_load_n]
set_property IOSTANDARD SSTL15 [get_ports i_load_n]

# DIP switches
set_property PACKAGE_PIN R8 [get_ports dipswitch[0]]
set_property IOSTANDARD SSTL15 [get_ports dipswitch[0]]
set_property PACKAGE_PIN P8 [get_ports dipswitch[1]]
set_property IOSTANDARD SSTL15 [get_ports dipswitch[1]]
set_property PACKAGE_PIN R7 [get_ports dipswitch[2]]
set_property IOSTANDARD SSTL15 [get_ports dipswitch[2]]
set_property PACKAGE_PIN R6 [get_ports dipswitch[3]]
set_property IOSTANDARD SSTL15 [get_ports dipswitch[3]]

set_property PACKAGE_PIN R26 [get_ports {o_leds[3]}]
set_property PACKAGE_PIN T25 [get_ports {o_leds[2]}]
set_property PACKAGE_PIN T24 [get_ports {o_leds[1]}]
set_property PACKAGE_PIN M26 [get_ports {o_leds[0]}]
set_property IOSTANDARD LVCMOS33 [get_ports {o_leds[3]}]
set_property IOSTANDARD LVCMOS33 [get_ports {o_leds[2]}]
set_property IOSTANDARD LVCMOS33 [get_ports {o_leds[1]}]
set_property IOSTANDARD LVCMOS33 [get_ports {o_leds[0]}]

set_property PACKAGE_PIN F25 [get_ports o_leds[4]]
set_property PACKAGE_PIN G25 [get_ports o_leds[5]]
set_property PACKAGE_PIN G26 [get_ports o_leds[6]]
set_property PACKAGE_PIN H26 [get_ports o_leds[7]]
set_property IOSTANDARD LVCMOS25 [get_ports o_leds[4]]
set_property IOSTANDARD LVCMOS25 [get_ports o_leds[5]]
set_property IOSTANDARD LVCMOS25 [get_ports o_leds[6]]
set_property IOSTANDARD LVCMOS25 [get_ports o_leds[7]]

