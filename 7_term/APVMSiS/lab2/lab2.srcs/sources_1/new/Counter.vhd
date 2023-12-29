

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity Counter is

  port (
    i_areset : in std_logic;
    i_clk : in std_logic;
    o_clk : out std_logic
   );
end Counter;

architecture Div_200M of Counter is

    constant DIVIDER : positive := 200000000;

    signal counter : std_logic_vector(31 downto 0) := (others => '0');
    signal temp_out : std_logic := '0';
begin

    process (i_areset, i_clk) begin
        
        if(i_areset = '1') then
            counter <= (others => '0');
            temp_out <= '0';
        elsif(i_clk'event and i_clk = '1') then
            if(counter = DIVIDER) then 
                temp_out <= not temp_out;
                counter <= (others => '0');
            else
                counter <= counter + 1;
            end if;
        end if;
    
    end process;

    o_clk <= temp_out;

end Div_200M;
