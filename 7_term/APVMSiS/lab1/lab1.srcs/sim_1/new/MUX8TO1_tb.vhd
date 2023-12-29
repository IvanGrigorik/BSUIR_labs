library IEEE;
use IEEE.Std_logic_1164.all;
use IEEE.Numeric_Std.all;

entity MUX8TO1_tb is
end;

architecture bench of MUX8TO1_tb is

  component MUX8TO1
      port ( 
              OE : in std_logic;
              AorB : in std_logic;
              A1 : in std_logic;         
              A2 : in std_logic;
              A3 : in std_logic;
              A4 : in std_logic;
              B1 : in std_logic;
              B2 : in std_logic;
              B3 : in std_logic;
              B4 : in std_logic;
              Y1 : out std_logic;
              Y2 : out std_logic;
              Y3 : out std_logic;
              Y4 : out std_logic);
  end component;

  signal OE: std_logic;
  signal AorB: std_logic;
  signal A1: std_logic;
  signal A2: std_logic;
  signal A3: std_logic;
  signal A4: std_logic;
  signal B1: std_logic;
  signal B2: std_logic;
  signal B3: std_logic;
  signal B4: std_logic;
  signal Y1: std_logic;
  signal Y2: std_logic;
  signal Y3: std_logic;
  signal Y4: std_logic;

begin

  uut: MUX8TO1 port map ( OE   => OE,
                          AorB => AorB,
                          A1   => A1,
                          A2   => A2,
                          A3   => A3,
                          A4   => A4,
                          B1   => B1,
                          B2   => B2,
                          B3   => B3,
                          B4   => B4,
                          Y1   => Y1,
                          Y2   => Y2,
                          Y3   => Y3,
                          Y4   => Y4 );

  stimulus: process
  begin
  
    -- Put initialisation code here


    for i in std_logic range '0' to '1' loop
        OE <= i;
        for j in std_logic range '0' to '1' loop
            AorB <= j;
            
            A1 <= '0';
            wait for 10 ns;
            A1 <= '1';
            wait for 10 ns;

            A2 <= '0';
            wait for 10 ns;
            A2 <= '1';
            wait for 10 ns;

            A3 <= '0';
            wait for 10 ns;
            A3 <= '1';
            wait for 10 ns;

            A4 <= '0';
            wait for 10 ns;
            A4 <= '1';
            wait for 10 ns;

            B1 <= '0';
            wait for 10 ns;
            B1 <= '1';
            wait for 10 ns;

            B2 <= '0';
            wait for 10 ns;
            B2 <= '1';
            wait for 10 ns;
            
            B3 <= '0';
            wait for 10 ns;
            B3 <= '1';
            wait for 10 ns;

            B4 <= '0';
            wait for 10 ns;
            B4 <= '1';
            wait for 10 ns;
           
        end loop;
    end loop;

    -- Put test bench stimulus code here

    wait;
  end process;


end;