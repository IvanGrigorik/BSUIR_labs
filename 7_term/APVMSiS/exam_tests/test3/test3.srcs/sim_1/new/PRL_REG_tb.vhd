library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity PRL_REG_tb is
end PRL_REG_tb;

architecture Behavioral of PRL_REG_tb is
    component PRL_REG is
        port( 
            D_in    : in    STD_LOGIC_VECTOR (7 downto 0);
            clk     : in    STD_LOGIC;
            nR      : in    STD_LOGIC;
            D_out   : out   STD_LOGIC_VECTOR (7 downto 0));
    end component;
    
    signal D_in_vector  :   std_logic_vector (7 downto 0)   := "01101110";
    signal reset        :   std_logic   :=  '1';
    signal clock        :   std_logic   :=  '0';
    signal s_out        :   std_logic_vector (7 downto 0)   := "00000000";
    
    constant period     :   time        :=  20 ns;
    
begin

    clock   <=  not clock after period / 2;
    
    reg: PRL_REG port map(
                    D_in    =>  D_in_vector,
                    clk     =>  clock,
                    nR      =>  reset,
                    D_out   =>  s_out);
                    
    test: process begin
        
--        wait for period * 2;
--        reset   <= '0';
--        wait for period + 4 ns;
--        reset   <= '1';
        
--        wait for 33 ns;
--        D_in_vector <=  "01110001";
    
        f1: for i in 0 to 100 loop
            f2: for ii in 0 to 1 loop
                if i = 2 then
                    exit f1;
                end if;
                report "Hi there!" severity error;
            end loop f2;
            
            report "End of F1";
        end loop f1;
        
        wait;
    end process;

end Behavioral;
