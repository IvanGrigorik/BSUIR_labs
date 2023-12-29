library ieee;
use ieee.std_logic_1164.all;

entity MUX8TO1_seq is
    port ( 
           OE : in std_logic;       
           AorB : in std_logic;     
           As : in std_logic_vector (0 to 3);
           Bs : in std_logic_vector (0 to 3);
           Ys : out std_logic_vector (0 to 3));
end MUX8TO1_seq;

architecture Behavioral of MUX8TO1_seq is
    signal AB_out : std_logic_vector(0 to 3);
begin 
    
    process (AorB, As, Bs, OE)
    begin
   
        if OE = '1' then
            for i in 0 to 3 loop
                Ys(i) <= 'Z';
            end loop;
        elsif AorB = '0' then
            for i in 0 to 3 loop
                Ys(i) <= As(i);
            end loop;
        elsif AorB = '1' then 
            for i in 0 to 3 loop
                Ys(i) <= Bs(i);
            end loop;
        end if;
    end process;
    
    
end Behavioral;
