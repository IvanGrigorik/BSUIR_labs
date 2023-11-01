library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity RS_sync is
  port ( 
        C : in std_logic    := '0';
        S : in std_logic    := '0';
        R : in std_logic    := '0';
        D : in std_logic    := '0';
        Q : out std_logic   := '0';
        nQ : out std_logic  := '1');

end RS_sync;

architecture Behavioral of RS_sync is
begin
    process (C, S, R, D) is 
    begin
    -- ???? ?????? ???????? ? R ? S. ????????? (? ?? ??????? ?????? ??? ??????????)

        if (C'event and C = '1') then
            if (R = '1') then
                Q <= '0';
                nQ  <= '1';    
            elsif (S = '1') then
                Q   <= '1';
                nQ  <= '0';
            else
                Q <= D;
                nQ <= not D;
            end if;
        end if;
    end process;

end Behavioral;
