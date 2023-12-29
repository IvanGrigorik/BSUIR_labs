
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;


entity Top_leds is
  Port ( 
        i_clk :         in  std_logic;
        i_data:         in  std_logic;
        i_load_n:       in  std_logic;
        i_areset:       in  std_logic;
        i_load_data:   in  std_logic_vector(3 downto 0);
        o_leds :        out std_logic_vector(7 downto 0)
  );
end Top_leds;

architecture Behavioral of Top_leds is

    component Counter 
    port (
        i_areset : in STD_LOGIC;
        i_clk: in STD_LOGIC;
        o_clk: out STD_LOGIC
    );
    end component;

    component SHFT_REG 
    port(
        SRCLR   : in std_logic;-- := '1';  -- shift register clear
        SRCK    : in std_logic;-- := '0';  -- shift register clock
        SRLOAD  : in std_logic;-- := '1';  -- shift register load
        RCK     : in std_logic;-- := '0';  -- register clock (write to register only when clock at '1')
        SER     : in std_logic;--:= '0';  -- shift register entry data
        in_bus  : in std_logic_vector (7 downto 0);-- := (others => '0'); 
        REG_OUT : out std_logic-- := '0');
    );
    end component;

    signal divider_clk : std_logic;
    signal shift_out: std_logic_vector(7 downto 0) := "00000000";
    
   
    signal load_data: std_logic_vector(7 downto 0) := "00000000";
    signal reset_low: std_logic;
    signal load_high: std_logic;
    
begin
    load_high <= not i_load_n;
    reset_low <= not i_areset;
    
    load_data(4) <= i_load_data(0);
    load_data(5) <= i_load_data(1);
    load_data(6) <= i_load_data(2);
    load_data(7) <= i_load_data(3);
        
    
    
    Counter_divider: Counter 
    port map (i_areset => i_areset, i_clk => i_clk, o_clk => divider_clk);

    Shift_reg: SHFT_REG
    port map(srclr => reset_low, srck => divider_clk, srload => load_high, rck => divider_clk, ser => i_data, in_bus => load_data, reg_out => shift_out(0));

    

    o_leds(0) <= shift_out(0);
    o_leds(1) <= divider_clk;
    
    o_leds(4) <= i_load_data(0);
    o_leds(5) <= i_load_data(1);
    o_leds(6) <= i_load_data(2);
    o_leds(7) <= i_load_data(3);
    
--    o_leds(4) 
--    o_leds(4) <= reset_low;
--    o_leds(5) <= i_areset;
--    o_leds(6) <= i_clk;
--    o_leds(7) <= i_data;
--    o_leds(6) <= shift_out(6);
--    o_leds(7) <= shift_out(7);
    
--    o_leds(0) <= i_data;
--    o_leds(1) <= divider_clk;
--    o_leds(2) <= i_clk;
--    o_leds(3) <= i_areset;
end Behavioral;
