library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity JK_FF is
    Port ( J    : in    STD_LOGIC;
           K    : in    STD_LOGIC;
           clk  : in    STD_LOGIC;
           nR   : in    STD_LOGIC   := '1';
           Q    : out   STD_LOGIC   := '0';
           nQ   : out   STD_LOGIC   := '1');
end JK_FF;

architecture Behavioral of JK_FF is
    signal state:   std_logic   :=  '0';
begin

    process (clk, nR) begin
        
        if nR = '0' then 
            state <= '0';
        elsif rising_edge(clk) then
            
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
