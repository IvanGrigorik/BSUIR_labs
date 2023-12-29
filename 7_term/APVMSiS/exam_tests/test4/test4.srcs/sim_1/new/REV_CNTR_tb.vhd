library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity REV_CNTR_tb is
--  Port ( );
end REV_CNTR_tb;

architecture Behavioral of REV_CNTR_tb is
    component REV_CNTR  
        port ( 
            minus    : in    STD_LOGIC;
            nOE      : in    STD_LOGIC;
            D_out    : out   STD_LOGIC_VECTOR (7 downto 0));  
    end component;
    
    signal enable       :   std_logic   :=  '0';
    signal minus        :   std_logic   :=  '0';
    signal out_vector   :   std_logic_vector (7 downto 0)   :=  "11111111";
begin

    tst: REV_CNTR    
        port map(
            minus   =>  minus,
            nOE     =>  enable,
            D_out   =>  out_vector);

    test: process begin
        
        -- minus 1
        wait for 20 ns;
        minus <= '1';
        wait for 20 ns;
        minus <= '0';
        -- minus 2
        wait for 20 ns;
        minus <= '1';
        wait for 20 ns;
        minus <= '0';
        
        -- Disable
        wait for 13 ns;
        enable  <= '1';
        wait for 10 ns;
        enable  <= '0';

        for i in 0 to 10 loop
            minus <= '0';
            wait for 20 ns;
            minus <= '1';
            wait for 20 ns;
        end loop;
        
        wait;
    end process;
    
    
end Behavioral;
