library IEEE;
use IEEE.Std_logic_1164.all;
use IEEE.Numeric_Std.all;

entity SHFT_REG_tb is
end;

architecture bench of SHFT_REG_tb is

  component SHFT_REG
      port ( 
          SRCLR : in std_logic  := '1';
          SRCK : in std_logic := '0';
          SRLOAD : in std_logic := '1';
          RCK : in std_logic := '0';
          SER : in std_logic := '0';
          A: in std_logic := '0';
          B : in std_logic := '0';
          C : in std_logic := '0';
          D : in std_logic := '0';
          E : in std_logic := '0';
          F : in std_logic := '0';
          G : in std_logic := '0';
          H : in std_logic := '0';
          REG_OUT : out std_logic := '0');
  end component;

  signal SRCLR: std_logic;
  signal SRCK: std_logic;
  signal SRLOAD: std_logic;
  signal RCK: std_logic;
  signal SER: std_logic;
  signal A: std_logic;
  signal B: std_logic;
  signal C: std_logic;
  signal D: std_logic;
  signal E: std_logic;
  signal F: std_logic;
  signal G: std_logic;
  signal H: std_logic;
  signal REG_OUT: std_logic := '0';

begin

  uut: SHFT_REG port map ( SRCLR   => SRCLR,
                           SRCK    => SRCK,
                           SRLOAD  => SRLOAD,
                           RCK     => RCK,
                           SER     => SER,
                           A       => A,
                           B       => B,
                           C       => C,
                           D       => D,
                           E       => E,
                           F       => F,
                           G       => G,
                           H       => H,
                           REG_OUT => REG_OUT );

  stimulus: process
  begin
  
    -- Put initialisation code here
    wait for 1 us;
    SRCK <= '1';         --  1
    SER <= '1';
    wait for 1 us;
    SRCK <= '0';    
    wait for 1 us;
    
    SRCK <= '1';        --  01XXXXXX
    SER <= '0';
    wait for 1 us;
    SRCK <= '0';    
    wait for 1 us;
    
    SRCK <= '1';         --  001XXXXX
    SER <= '0';
    wait for 1 us;
    SRCK <= '0';    
    wait for 1 us;
    
    SRCK <= '1';         --  1001XXXX
    SER <= '1';
    wait for 1 us;
    SRCK <= '0';    
    wait for 1 us;
    
    SRCK <= '1';         --  11001XXX
    SER <= '1';
    wait for 1 us;
    SRCK <= '0';    
    wait for 1 us; 
    
    SRCK <= '1';         --  011001XX
    SER <= '0';
    wait for 1 us;
    SRCK <= '0';    
    wait for 1 us;
    
    SRCK <= '1';         --  1011001X
    SER <= '1';
    wait for 1 us;
    SRCK <= '0';    
    wait for 1 us;
    
    SRCK <= '1';         --  01011001 q: 1
    SER <= '0';
    wait for 1 us;
    SRCK <= '0';    
    wait for 1 us;

    SRCK <= '1';         --  10101100 q: 0
    SER <= '1';
    wait for 1 us;
    SRCK <= '0';    
    wait for 1 us;
    
    SRCK <= '1';         --  11010110 q: 0
    SER <= '1';
    wait for 1 us;
    SRCK <= '0';    
    wait for 1 us;
    -- Put test bench stimulus code here

    wait;
  end process;


end;
  