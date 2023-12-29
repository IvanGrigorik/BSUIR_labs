library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity DC_FF is
    port ( 
           clk  :   in STD_LOGIC;
           D    :   in STD_LOGIC;
           nR   :   in STD_LOGIC;
           Q    :   out STD_LOGIC := '0';
           nQ   :   out STD_LOGIC := '1');
end DC_FF;

architecture Behavioral of DC_FF is
    signal Q_out:   std_logic   := '0';
begin
    -- Trigger main process
    process (clk, D, nR) 
    begin
        
        if nR = '0' then
            Q_out <= '0';
        elsif (rising_edge(clk)) then 
            Q_out <= D;
        end if;
    end process;
    
    -- Parallel output
    Q   <=  Q_out;
    nQ  <=  not Q_out;

end Behavioral;
