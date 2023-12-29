library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity REV_CNTR_tb is
--  Port ( );
end REV_CNTR_tb;

architecture Behavioral of REV_CNTR_tb is
    component REV_CNTR
        port (
            minus    : in STD_LOGIC  := '0';
            nR       : in STD_LOGIC  := '1';
            D        : out STD_LOGIC_VECTOR (7 downto 0));
    end component;
    
    signal minus    : std_logic := '0';
    signal reset    : std_logic := '1';
    signal out_vec  : std_logic_vector(7 downto 0) := "00000000";
begin

    cntr: REV_CNTR 
        port map(minus => minus, nR => reset, D => out_vec);

    tb: process begin
        
        for i in 0 to 400 loop
            -- reset check
            if i = 32 then
                wait for 23 ns;
                reset <= '0';
            elsif i = 62 then
                reset <= '1';
            end if;
            
            -- minus check
            wait for 10 ns;
            minus <= '1';
            wait for 10 ns;
            minus <= '0';
        end loop; 
        
        wait;
    end process;
end Behavioral;
