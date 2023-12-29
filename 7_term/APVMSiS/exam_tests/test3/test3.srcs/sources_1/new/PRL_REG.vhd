library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity PRL_REG is
    Port ( 
            D_in    : in    STD_LOGIC_VECTOR (7 downto 0);
            clk     : in    STD_LOGIC;
            nR      : in    STD_LOGIC;
            D_out   : out   STD_LOGIC_VECTOR (7 downto 0));
end PRL_REG;

architecture Behavioral of PRL_REG is
    component JK_FF is 
        port (            
                J   : in    STD_LOGIC;
                K   : in    STD_LOGIC;
                clk : in    STD_LOGIC;
                nR  : in    STD_LOGIC;
                Q   : out   STD_LOGIC;
                nQ  : out   STD_LOGIC);
    end component;
    
    signal nD_out   :   std_logic_vector (7 downto 0);
    signal nD_in    :   std_logic_vector (7 downto 0);
begin
    
    nD_in <= not D_in;
    
    jk0: JK_FF port map (
                        J   => D_in(0),
                        K   => nD_in(0),
                        clk => clk,
                        nR  => nR,
                        Q   => D_out(0),
                        nQ  => nD_out(0));    
    
    jk1: JK_FF port map (
                        J   => D_in(1),
                        K   => nD_in(1),
                        clk => clk,
                        nR  => nR,
                        Q   => D_out(1),
                        nQ  => nD_out(1));   

    jk2: JK_FF port map (
                        J   => D_in(2),
                        K   => nD_in(2),
                        clk => clk,
                        nR  => nR,
                        Q   => D_out(2),
                        nQ  => nD_out(2));    
    
    jk3: JK_FF port map (
                        J   => D_in(3),
                        K   => nD_in(3),
                        clk => clk,
                        nR  => nR,
                        Q   => D_out(3),
                        nQ  => nD_out(3));   
                        
                        
    jk4: JK_FF port map (
                        J   => D_in(4),
                        K   => nD_in(4),
                        clk => clk,
                        nR  => nR,
                        Q   => D_out(4),
                        nQ  => nD_out(4));    
    
    jk5: JK_FF port map (
                        J   => D_in(5),
                        K   => nD_in(5),
                        clk => clk,
                        nR  => nR,
                        Q   => D_out(5),
                        nQ  => nD_out(5));   

    jk6: JK_FF port map (
                        J   => D_in(6),
                        K   => nD_in(6),
                        clk => clk,
                        nR  => nR,
                        Q   => D_out(6),
                        nQ  => nD_out(6));    
    
    jk7: JK_FF port map (
                        J   => D_in(7),
                        K   => nD_in(7),
                        clk => clk,
                        nR  => nR,
                        Q   => D_out(7),
                        nQ  => nD_out(7));  
end Behavioral;
