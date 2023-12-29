library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity D_sync is
    port (
            D : in std_logic := '0';
            C : in std_logic;
            Q : out std_logic := '0';
            nQ : out std_logic := '1');
end D_sync;

architecture Behavioral of D_sync is
begin
    process (C, D)
    begin
        if (rising_edge(C)) then
            Q <= D;
            nQ <= not D;
        end if;
    end process;
    
end Behavioral;
