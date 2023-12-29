library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity SHFT_REG is
    Port ( D    :   in  STD_LOGIC;
           clk  :   in  STD_LOGIC;
           nR   :   in  STD_LOGIC   := '1';
           D_out:   out STD_LOGIC_VECTOR (7 downto 0));
end SHFT_REG;

architecture Behavioral of SHFT_REG is
    
    -- Trigger declaration
    component DC_FF is 
        port (
            clk :   in     STD_LOGIC;
            D   :   in     STD_LOGIC;
            nR  :   in     STD_LOGIC;
            Q   :   out    STD_LOGIC;
            nQ  :   out    STD_LOGIC);
    end component;
    
    -- Additional signals declaration
    signal Q_out    :   std_logic_vector (7 downto 0) := "00000000";
    signal nQ_out   :   std_logic_vector (7 downto 0) := "11111111";
begin
    
    d0: DC_FF port map(
            clk => clk, D => D, nR => nR,
            Q => Q_out(0), 
            nQ => nQ_out(0));
            
    d1: DC_FF port map(
            clk => clk, D => Q_out(0), nR => nR,
            Q => Q_out(1), 
            nQ => nQ_out(1));

    d2: DC_FF port map(
            clk => clk, D => Q_out(1), nR => nR,
            Q => Q_out(2), 
            nQ => nQ_out(2));
        
    d3: DC_FF port map(
            clk => clk, D => Q_out(2), nR => nR,
            Q => Q_out(3), 
            nQ => nQ_out(3));
        
    d4: DC_FF port map(
            clk => clk, D => Q_out(3), nR => nR,
            Q => Q_out(4), 
            nQ => nQ_out(4));
                
    d5: DC_FF port map(
            clk => clk, D => Q_out(4), nR => nR,
            Q => Q_out(5), 
            nQ => nQ_out(5));

    d6: DC_FF port map(
            clk => clk, D => Q_out(5), nR => nR,
            Q => Q_out(6), 
            nQ => nQ_out(6));
                
    d7: DC_FF port map(
            clk => clk, D => Q_out(6), nR => nR,
            Q => Q_out(7), 
            nQ => nQ_out(7));

    D_out   <=  Q_out;
end Behavioral;
