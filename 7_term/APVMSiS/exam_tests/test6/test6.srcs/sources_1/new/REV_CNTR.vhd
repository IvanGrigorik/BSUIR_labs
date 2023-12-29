library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity REV_CNTR is
    Port ( minus    : in STD_LOGIC  := '0';
           nR       : in STD_LOGIC  := '1';
           D        : out STD_LOGIC_VECTOR (7 downto 0));
end REV_CNTR;

architecture Behavioral of REV_CNTR is
    component JK_FF 
        port (
            J    : in    STD_LOGIC;
            K    : in    STD_LOGIC;
            clk  : in    STD_LOGIC;
            nR   : in    STD_LOGIC   :=  '1';
            Q    : out   STD_LOGIC;
            nQ   : out   STD_LOGIC);
    end component;
    
    signal D_out   :   std_logic_vector (7 downto 0);
    signal nD_out  :   std_logic_vector (7 downto 0);
begin
    
    jk0: JK_FF 
        port map(
            J   => '1',
            K   => '1',
            clk => minus,
            nR  => nR,
            Q   => D(0),
            nQ  => nD_out(0));
    
    jk: for i in 1 to 7 generate
        jk_trigger: JK_FF port map(
                J   => '1',
                K   => '1',
                clk => nD_out(i - 1),
                nR  =>  nR,
                Q   =>  D(i),
                nQ  =>  nD_out(i));
    end generate;
    
end Behavioral;
