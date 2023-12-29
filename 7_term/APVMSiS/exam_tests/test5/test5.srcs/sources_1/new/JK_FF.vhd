library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity JK_FF is
    Port ( 
        J   : in    STD_LOGIC;
        K   : in    STD_LOGIC;
        clk : in    STD_LOGIC;
        Q   : out   STD_LOGIC;
        nQ  : out   STD_LOGIC);
end JK_FF;

architecture Behavioral of JK_FF is
    signal state    :   std_logic   :=  '0';
begin

    process (clk) begin
        
        if rising_edge(clk) then
            if J = '1' and K = '1' then
                state <= not state;
            elsif J = '1' then
                state <= '1';
            elsif K = '1' then
                state <= '0';
            end if;
        end if;
    
    end process;

    Q   <= state;
    nQ  <= not state;
end Behavioral;
