library IEEE;
use IEEE.Std_logic_1164.all;
use IEEE.Numeric_Std.all;

entity MUX8TO1_seq_tb is
end;

architecture bench of MUX8TO1_seq_tb is

  component MUX8TO1_seq
      port ( 
             OE : in std_logic;
             AorB : in std_logic;
             As : in std_logic_vector (0 to 3);
             Bs : in std_logic_vector (0 to 3);
             Ys : out std_logic_vector (0 to 3));
  end component;

  signal OE: std_logic;
  signal AorB: std_logic;
  signal As: std_logic_vector (0 to 3);
  signal Bs: std_logic_vector (0 to 3);
  signal Ys: std_logic_vector (0 to 3);

begin

  uut: MUX8TO1_seq port map ( OE   => OE,
                              AorB => AorB,
                              As   => As,
                              Bs   => Bs,
                              Ys   => Ys );

  stimulus: process
  begin
  
    -- Put initialisation code here


    for i in std_logic range '0' to '1' loop
        OE <= not i;
        for j in std_logic range '0' to '1' loop
            AorB <= j;
            wait for 10 ns;
            
            for n in 0 to 3 loop
                As(n) <= '0';
                wait for 10 ns;
                As(n) <= '1';
                wait for 10 ns;
            end loop;
            
            for n in 0 to 3 loop
                Bs(n) <= '0';
                wait for 10 ns;
                Bs(n) <= '1';
                wait for 10 ns;
            end loop;
            
        end loop;
    end loop;


    -- Put test bench stimulus code here

    wait;
    end process;


end;
    