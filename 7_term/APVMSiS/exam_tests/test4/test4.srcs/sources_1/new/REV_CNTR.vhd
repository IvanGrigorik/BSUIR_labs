library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity REV_CNTR is
    Port ( 
        minus    : in    STD_LOGIC  :=  '0';
        nOE      : in    STD_LOGIC  :=  '0';
        D_out    : out   STD_LOGIC_VECTOR (7 downto 0));
end REV_CNTR;

architecture Behavioral of REV_CNTR is
    component JK_FF 
        port (
            J    : in    STD_LOGIC   :=  '0';
            K    : in    STD_LOGIC   :=  '0';
            clk  : in    STD_LOGIC   :=  '0';
            Q    : out   STD_LOGIC   :=  '0';
            nQ   : out   STD_LOGIC);
    end component;
    
    signal not_minus    :   std_logic   :=  '1';
    signal sD_out       :   std_logic_vector (7 downto 0) :=  "11111111";
    signal snD_out      :   std_logic_vector (7 downto 0) :=  "00000000";
begin

    not_minus   <=  not minus;

    jk0: JK_FF 
        port map(
            J   =>  '1',
            K   =>  '1',
            clk =>  minus,
            Q   =>  sD_out(0),
            nQ  =>  snD_out(0));

    jk1: JK_FF 
        port map(
            J   =>  '1',
            K   =>  '1',
            clk =>  snD_out(0),
            Q   =>  sD_out(1),
            nQ  =>  snD_out(1));

    jk2: JK_FF 
        port map(
            J   =>  '1',
            K   =>  '1',
            clk =>  snD_out(1),
            Q   =>  sD_out(2),
            nQ  =>  snD_out(2));

    jk3: JK_FF 
        port map(
            J   =>  '1',
            K   =>  '1',
            clk =>  snD_out(2),
            Q   =>  sD_out(3),
            nQ  =>  snD_out(3));

    jk4: JK_FF 
        port map(
            J   =>  '1',
            K   =>  '1',
            clk =>  snD_out(3),
            Q   =>  sD_out(4),
            nQ  =>  snD_out(4));

    jk5: JK_FF 
        port map(
            J   =>  '1',
            K   =>  '1',
            clk =>  snD_out(4),
            Q   =>  sD_out(5),
            nQ  =>  snD_out(5));
            
    jk6: JK_FF 
        port map(
            J   =>  '1',
            K   =>  '1',
            clk =>  snD_out(5),
            Q   =>  sD_out(6),
            nQ  =>  snD_out(6));

    jk7: JK_FF 
        port map(
            J   =>  '1',
            K   =>  '1',
            clk =>  snD_out(6),
            Q   =>  sD_out(7),
            nQ  =>  snD_out(7));

    D_out   <=  sD_out when nOE = '0' else "ZZZZZZZZ";
end Behavioral;
