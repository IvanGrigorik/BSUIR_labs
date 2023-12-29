library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;
use ieee.std_logic_textio.all;
use std.textio.all;

entity SHFT_REG_file_tb is
end SHFT_REG_file_tb;

architecture Behavioral of SHFT_REG_file_tb is
    component SHFT_REG 
    port (  
           SRCLR   : in std_logic;  -- shift register clear
           SRCK    : in std_logic;  -- shift register clock
           SRLOAD  : in std_logic;  -- shift register load
           RCK     : in std_logic;  -- register clock (write to register only when clock at '1')
           SER     : in std_logic;  -- shift register entry data
           in_bus  : in std_logic_vector (7 downto 0);
           REG_OUT : out std_logic);
    end component;
    -- Useful inner signals
    signal SRCK     : std_logic := '1'; -- Register synchrosignal
    signal RCK      : std_logic := '0'; -- buffer synchrosignal
    signal SRCLR    : std_logic := '1'; -- clear
    signal SRLOAD   : std_logic := '1'; -- load
    signal SER      : std_logic := '0';     -- Register bit-by-bit input
    signal in_bus   : std_logic_vector (7 downto 0) := "00000000"; -- buffer bus;
    signal REG_OUT  : std_logic;     -- register out
    
    constant clock_period : time := 20 ns;
    
    -- Expected output
    signal expected : std_logic_vector (7 downto 0) := "00000000";
    
    signal line_number : std_logic_vector(31 downto 0) := (others => '0');

begin

    -- Set clocks
    SRCK <= not SRCK after clock_period / 2;
    RCK  <= not RCK  after clock_period / 2;
    
    -- I/O mapping
    uut: SHFT_REG port map (SRCLR, SRCK, SRLOAD,
                            RCK, SER, in_bus, 
                            REG_OUT);

    -- Load new line from file
    load_file: process (SRCK, RCK) is
        -- Variables for file reading
        constant file_name  : string := "REG_testlines.txt" ;
        file     test_file  : text open read_mode is file_name;
        variable v_iline    : line;
        
        -- Variables to fill the register 
        variable v_SER      : std_logic;                        -- shift entry data
        variable v_SRCLR    : std_logic;                        -- 1 to no clear
        variable v_SRLOAD   : std_logic;                        -- 1 to no load
        variable v_in_bus   : std_logic_vector (7 downto 0);    -- buffer data
        variable v_REG_OUT  : std_logic_vector (7 downto 0);    -- shift register out data in a vector view
        
        -- Separator variable 
        variable space  : character;
    begin
        if (SRCK = '1' and not endfile(test_file)) then
            readline(test_file, v_iline);
            read(v_iline,   v_SER);
            read(v_iline,   space); 
            read(v_iline,   v_SRCLR);   
            read(v_iline,   space); 
            read(v_iline,   v_SRLOAD);
            read(v_iline,   space);             
            read(v_iline,   v_in_bus);
            read(v_iline,   space); 
            read(v_iline,   v_REG_OUT);
            
            line_number <= line_number + 1;
            if v_SER = 'Z' then
                report "Simulation finished without errors!" severity note;
                std.env.stop;
            end if;

            in_bus   <= v_in_bus;
            SER      <= v_SER;
            SRCLR    <= v_SRCLR;
            SRLOAD   <= v_SRLOAD;
            expected <= v_REG_OUT;            
        end if;
    end process;
    
    -- Register output checker 
    simul: process (SRCK) is
    begin
    
        
        if expected(7) /= REG_OUT then
            report "REG is not working! Error line: " & integer'image(conv_integer(line_number)) severity error;
            std.env.stop;
        end if;
    end process;
end Behavioral;