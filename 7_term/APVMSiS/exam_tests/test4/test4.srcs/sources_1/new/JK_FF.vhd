library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity JK_FF is
    Port ( J    : in    STD_LOGIC   :=  '0';
           K    : in    STD_LOGIC   :=  '0';
           clk  : in    STD_LOGIC   :=  '0';
           Q    : out   STD_LOGIC   :=  '1';
           nQ   : out   STD_LOGIC   :=  '0');
end JK_FF;

architecture Behavioral of JK_FF is
    signal state    :   std_logic   :=  '1';
begin
    
    process (clk) begin
    
        if (falling_edge(clk)) then
            if J = '1' and K = '1' then
                state <= not state;
            elsif J = '1' then
                state <= '1';
            elsif K = '1' then
                state <= '0';
            end if;
        end if;
    
    end process;
    
    Q   <=  state;
    nQ  <=  not state;
end Behavioral;
