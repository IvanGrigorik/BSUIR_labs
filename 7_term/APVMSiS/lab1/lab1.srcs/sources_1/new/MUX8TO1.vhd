library ieee;
use ieee.std_logic_1164.all;

entity MUX8TO1 is
    port ( 
            OE : in std_logic;       -- NOE = not OE
            AorB : in std_logic;     -- not A and B
            A1 : in std_logic;         
            A2 : in std_logic;
            A3 : in std_logic;
            A4 : in std_logic;
            B1 : in std_logic;
            B2 : in std_logic;
            B3 : in std_logic;
            B4 : in std_logic;
            Y1 : out std_logic;
            Y2 : out std_logic;
            Y3 : out std_logic;
            Y4 : out std_logic);
end MUX8TO1;

architecture Behavioral of MUX8TO1 is
    signal AB_out : std_logic_vector(0 to 3);
    signal and1 : std_logic_vector(0 to 3);
    signal and2 : std_logic_vector(0 to 3);
begin 

    and1(0) <= A1 and not AorB;
    and2(0) <= B1 and AorB;
    AB_out(0) <= and1(0) or and2(0);
    
    and1(1) <= A2 and not AorB;
    and2(1) <= B2 and AorB;
    AB_out(1) <= and1(1) or and2(1);
    
    and1(2) <= A3 and not AorB;
    and2(2) <= B3 and AorB;
    AB_out(2) <= and1(2) or and2(2);
    
    and1(3) <= A4 and not AorB;
    and2(3) <= B4 and AorB;
    AB_out(3) <= and1(3) or and2(3);
    
    Y1 <= AB_out(0) when OE = '0' else 'Z';
    Y2 <= AB_out(1) when OE = '0' else 'Z';
    Y3 <= AB_out(2) when OE = '0' else 'Z';
    Y4 <= AB_out(3) when OE = '0' else 'Z';
    
end Behavioral;