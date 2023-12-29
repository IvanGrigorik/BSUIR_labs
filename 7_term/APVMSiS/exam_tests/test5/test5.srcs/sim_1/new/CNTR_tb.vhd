library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity CNTR_tb is
--  Port ( );
end CNTR_tb;

architecture Behavioral of CNTR_tb is
    component CNTR 
        port (
            plus    : in    STD_LOGIC   := '0';
            nOE     : in    STD_LOGIC   := '1';
            D       : out   STD_LOGIC_VECTOR (7 downto 0));
    end component;
    
    signal plus     :   std_logic   := '0';
    signal enable   :   std_logic   := '0';
    signal D_out    :   std_logic_vector (7 downto 0)   := "00000000";
begin

    count: CNTR port map(
        plus    =>  plus,
        nOE     =>  enable,
        D       =>  D_out);
    
    
    tb: process begin
        wait for 20 ns;
        for i in 0 to 10 loop
            plus <= '1';
            wait for 10 ns;
            plus <= '0';
            wait for 10 ns;
        end loop;
        
        enable  <= '1';
        wait for 144 ns;
    
        for i in 0 to 254 loop
        
            if i = 32 then
                enable  <= '0';
            end if;
            
            plus <= '1';
            wait for 10 ns;
            plus <= '0';
            wait for 10 ns;
        end loop;
    
    wait;
    end process;
    
end Behavioral;
