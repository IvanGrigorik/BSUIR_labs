library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity CNTR_tb is
--  Port ( );
end CNTR_tb;

architecture Behavioral of CNTR_tb is
    component CNTR is 
        port(   ADD  :   in STD_LOGIC;
                nR   :   in STD_LOGIC;
                D_out:   out STD_LOGIC_VECTOR (3 downto 0));
    end component;
    
    signal reset    :   std_logic   := '1';
    signal add      :   std_logic   := '0';
    signal d_out    :   std_logic_vector (3 downto 0)   :=  "0000";
begin
    
    counter: CNTR port map(
                    ADD     => add,
                    nR      => reset,
                    D_out   => d_out
                    );
    
    add <= not add after 10 ns;

    tb: process begin
    
        
        
        for i in 0 to 16 loop
            wait for 20 ns;

            if i = 13 then
                reset <= '0';
                wait for 10 ns;
                reset <= '1';
            end if;
            
            
        end loop;
    
    wait;
    end process;

end Behavioral;
