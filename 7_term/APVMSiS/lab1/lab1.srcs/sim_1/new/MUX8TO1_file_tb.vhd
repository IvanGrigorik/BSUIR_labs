library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use ieee.std_logic_textio.all;
use std.textio.all;

entity MUX8TO1_file_tb is
end MUX8TO1_file_tb;

architecture Behavioral of MUX8TO1_file_tb is 
    
    component MUX8TO1 port ( 
        OE      : in std_logic;       -- NOE = not OE
        AorB    : in std_logic;     -- not A and B
        A1      : in std_logic;        
        A2      : in std_logic;
        A3      : in std_logic;
        A4      : in std_logic;
        B1      : in std_logic;
        B2      : in std_logic;
        B3      : in std_logic;
        B4      : in std_logic;
        Y1      : out std_logic;
        Y2      : out std_logic;
        Y3      : out std_logic;
        Y4      : out std_logic);
    end component;
    
    -- Signals for testbench
    signal OE   : std_logic;       -- NOE = not OE
    signal AorB : std_logic;     -- not A and B
    signal As   : std_logic_vector (3 downto 0);
    signal Bs   : std_logic_vector (3 downto 0);
    signal Ys   : std_logic_vector (3 downto 0);
    
    -- Expected output result
    signal expected :  std_logic_vector (3 downto 0);
    
    -- Boolean for read new line from file
    signal read_new : std_logic;
begin

    uuid: MUX8TO1 port map (OE, AorB, 
                            As(0), As(1), As(2), As(3), 
                            Bs(0), Bs(1), Bs(2), Bs(3), 
                            Ys(0), Ys(1), Ys(2), Ys(3));
    
    load_info: process (read_new)
        constant file_name : string := "MUX_testlines.txt";
        file     test_file : text open read_mode is file_name;
        variable v_iline   : line;
        
        variable v_As   : std_logic_vector (0 to 3);
        variable v_Bs   : std_logic_vector (0 to 3);
        variable v_AorB : std_logic;
        variable v_OE   : std_logic;
        variable v_Ys   : std_logic_vector (0 to 3);
        variable v_sep  : character;
    begin
        if read_new = '1' and not endfile(test_file) then
            readline(test_file, v_iline);
            read(v_iline, v_As  );
            read(v_iline, v_sep );
            read(v_iline, v_Bs  );
            read(v_iline, v_sep );
            read(v_iline, v_AorB);
            read(v_iline, v_sep );
            read(v_iline, v_OE  );
            read(v_iline, v_sep );
            read(v_iline, v_Ys  );
            As       <= v_As;
            Bs       <= v_Bs;
            AorB     <= v_AorB;
            OE       <= v_OE;
            expected <= v_Ys;
        end if;
    end process;

    simulate: process 
    begin
    
        for i in 0 to 11 loop
            read_new <= '1';
            wait for 5 ns;
            if (expected /= Ys) then 
                report "MUX is not working"  severity error;
            else 
                report "Mux is working fine" severity note;    
            end if;
            read_new <= '0';
            wait for 5 ns;
         end loop;
        
    wait;
    end process;

end Behavioral;