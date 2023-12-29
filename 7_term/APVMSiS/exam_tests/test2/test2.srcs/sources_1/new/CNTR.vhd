library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity CNTR is
    Port ( ADD  :   in STD_LOGIC    := '0';
           nR   :   in STD_LOGIC    := '1';
           D_out:   out STD_LOGIC_VECTOR (3 downto 0)   := "0000");
end CNTR;

architecture Behavioral of CNTR is
    component JK_FF is
        port (
            J   : in    STD_LOGIC;
            K   : in    STD_LOGIC;
            clk : in    STD_LOGIC;
            nR  : in    STD_LOGIC;
            Q   : out   STD_LOGIC;
            nQ  : out   STD_LOGIC);
    end component;
    
    signal out_signal   :   std_logic_vector (3 downto 0)   :=  "0000";
    signal nout_signal  :   std_logic_vector (3 downto 0)   :=  "1111";

begin
    
    jk0: JK_FF port map(
                J => '1', K => '1',
                clk => ADD, nR => nR,
                Q => out_signal(0),
                nQ => nout_signal(0));    

    jk1: JK_FF port map(
                J => '1', K => '1',
                clk => nout_signal(0), nR => nR,
                Q => out_signal(1),
                nQ => nout_signal(1));
  
    jk2: JK_FF port map(
                J => '1', K => '1',
                clk => nout_signal(1), nR => nR,
                Q => out_signal(2),
                nQ => nout_signal(2));  

    jk3: JK_FF port map(
                J => '1', K => '1',
                clk => nout_signal(2), nR => nR,
                Q => out_signal(3),
                nQ => nout_signal(3));
                
    D_out <= out_signal;
end Behavioral;
