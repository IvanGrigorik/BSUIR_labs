library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;
use ieee.std_logic_textio.all;
use std.textio.all;

entity MUX8TO1_seq_file_tb is
end MUX8TO1_seq_file_tb;

architecture Behavioral of MUX8TO1_seq_file_tb is
    component MUX8TO1_seq port ( 
           OE   : in std_logic;
           AorB : in std_logic;
           As   : in std_logic_vector (0 to 3);
           Bs   : in std_logic_vector (0 to 3);
           Ys   : out std_logic_vector (0 to 3));
    end component;
    
    signal OE       : std_logic;
    signal AorB     : std_logic;
    signal As       : std_logic_vector (0 to 3);
    signal Bs       : std_logic_vector (0 to 3);
    signal Ys       : std_logic_vector (0 to 3);
    signal read_new : std_logic;
    signal expected : std_logic_vector (0 to 3);     
    
begin
    
    mapping: MUX8TO1_seq port map (OE, AorB, As, Bs, Ys);
    
    -- Load testbench info from file
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
            As <= v_As;
            Bs <= v_Bs;
            AorB <= v_AorB;
            OE <= v_OE;
            expected <= v_Ys;
        elsif endfile(test_file) then
            std.env.stop;
        end if;
    end process;
                          
    
    siml: process 
    begin
    
        while true loop
            read_new <= '1';
            wait for 5 ns;
            if (expected /= Ys) then 
                report "MUX is not working" severity error;
                std.env.stop;
            else 
                report "Mux is working fine" severity note;    
            end if;
            read_new <= '0';
            wait for 5 ns;
     end loop;
        
    wait;
    end process;
     
end Behavioral;
