library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity CNTR is
    Port ( 
        plus    : in    STD_LOGIC   := '0';
        nOE     : in    STD_LOGIC   := '0';
        D       : out   STD_LOGIC_VECTOR (7 downto 0));
end CNTR;

architecture Behavioral of CNTR is
    component JK_FF 
        port(
            J   : in    STD_LOGIC;
            K   : in    STD_LOGIC;
            clk : in    STD_LOGIC;
            Q   : out   STD_LOGIC;
            nQ  : out   STD_LOGIC);
    end component;
    
    signal D_out    :   std_logic_vector (7 downto 0)   := "00000000";
    signal nD_out   :   std_logic_vector (7 downto 0)   := "11111111";
begin
    
    jk0: JK_FF 
        port map(
            J   =>  '1',
            K   =>  '1',
            clk =>  plus,
            Q   =>  D_out(0),
            nQ  =>  nD_out(0));
            
--    jk1: JK_FF 
--        port map(
--            J   =>  '1',
--            K   =>  '1',
--            clk =>  nD_out(0),
--            Q   =>  D_out(1),
--            nQ  =>  nD_out(1));
    
    gen: for i in 0 to 6 generate
        jk: JK_FF port map(
            J   => '1',
            K   => '1',
            clk => nD_out(i),
            Q   => D_out(i+1),
            nQ  => nD_out(i+1));
    end generate;
    
    D <= D_out when nOE = '0' else "ZZZZZZZZ";
end Behavioral;
