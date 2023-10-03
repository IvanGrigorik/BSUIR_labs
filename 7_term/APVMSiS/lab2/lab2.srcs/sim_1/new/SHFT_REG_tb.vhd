library IEEE;
use IEEE.Std_logic_1164.all;

entity SHFT_REG_tb is
end;

architecture bench of SHFT_REG_tb is

  component SHFT_REG
      port ( 
          SRCLR : in std_logic := '1';
          SRCK : in std_logic := '0';
          SRLOAD : in std_logic := '1';
          RCK : in std_logic := '0';
          SER : in std_logic := '0';
          in_bus : in std_logic_vector (7 downto 0);
          REG_OUT : out std_logic := '0');
  end component;

  signal SRCLR: std_logic := '1';
  signal SRCK: std_logic := '0';
  signal SRLOAD: std_logic := '1';
  signal RCK: std_logic := '1';
  signal SER: std_logic := '0';
  signal in_bus: std_logic_vector (7 downto 0) := "00000000";
  signal REG_OUT: std_logic := '0';

  constant clock_period: time := 20 ns;
  
  signal input_array : std_logic_vector (15 downto 0) := "0110101100010110"; 
  signal input_array2 : std_logic_vector (15 downto 0) := "0101010101010101"; 
  signal input_bus : std_logic_vector (7 downto 0) := "01101111";
  signal is_reseted : boolean := false;

begin

  uut: SHFT_REG port map ( SRCLR   => SRCLR,
                           SRCK    => SRCK,
                           SRLOAD  => SRLOAD,
                           RCK     => RCK,
                           SER     => SER,
                           in_bus  => in_bus,
                           REG_OUT => REG_OUT );

  SRCK <= not SRCK after clock_period / 2;
  RCK <= not RCK after clock_period / 2;
  
  
  stimulus: process
  begin
  
    -- Put initialisation code here
    SER <= '0';
    in_bus <= input_bus;
    wait for clock_period / 2;
    -- Put test bench stimulus code here
    
    for i in 0 to 15 loop
        if (i = 12 and not is_reseted) then
            SRCLR <= '0';
            is_reseted <= true;
            wait for clock_period / 2;
            SRCLR <= '1';
        else 
            SER <= input_array(i);
            wait for clock_period;
        end if; 
    end loop;
    
    for i in 0 to 15 loop
        SER <= input_array2(i);
        wait for clock_period;
    end loop;
    
    wait for clock_period * 8;
    SRLOAD <= '0';
    wait for clock_period;
    SRLOAD <= '1';
        
        
    wait for clock_period * 10;
    SRLOAD <= '0';
    wait for clock_period;
    SRLOAD <= '1';
        
        
    
    -- Put test bench stimulus code here
    wait;
  end process;


--  clocking: process
--  begin
--    while not stop_the_clock loop
--      SRCK <= '0', '1' after clock_period / 2;
--      wait for clock_period;
--    end loop;
--    wait;
--  end process;

end;
