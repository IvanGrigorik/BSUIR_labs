library IEEE;
use IEEE.STD_LOGIC_1164.ALL;


entity SHFT_REG_tb is
end SHFT_REG_tb;

architecture Behavioral of SHFT_REG_tb is
    
    component SHFT_REG is
        port (
            D       :   in  STD_LOGIC;
            clk     :   in  STD_LOGIC;
            nR      :   in  STD_LOGIC   := '1';
            D_out   :   out STD_LOGIC_VECTOR (7 downto 0));
    end component;
    
    signal in_signal:   std_logic_vector (7 downto 0)   := "01101011";
    signal D_in     :   std_logic := in_signal(0);
    signal Q_out    :   std_logic_vector (7 downto 0)   := "00000000";
    signal n_reset  :   std_logic := '1';
    signal clk      :   std_logic := '0';
    constant period :   time      := 20 ns;
begin
    
    clk <= not clk after period/2;
    
    reg: SHFT_REG port map(
            D       => D_in,
            clk     => clk,
            nR      => n_reset,
            D_out   => Q_out);

    process begin
        for i in 0 to 7 loop
            D_in    <=  in_signal(7 - i);
            
            if i = 4 then
                wait for 4 ns;
                n_reset <= '0';
                wait for 4 ns;
                n_reset <= '1';
            end if;
        
        wait for period;
        D_in <= '0';
        end loop;
        
    wait;
    end process;

end Behavioral;
