library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library DC_trigger;
use DC_trigger.all;

--
-- entity declartion
--
entity SHFT_REG is
    port ( 
        SRCLR : in std_logic := '1';   -- shift register clear
        SRCK : in std_logic := '0';    -- shift register clock
        SRLOAD : in std_logic := '1';  -- shift register load
        RCK : in std_logic := '0';     -- register clock (write to register only when clock at '1')
        SER : in std_logic := '0';     -- shift register entry data
        
        in_bus : in std_logic_vector (7 downto 0) := "00000000";
        REG_OUT : out std_logic := '0');
end SHFT_REG;


 --
 -- arch
 --
architecture Behavioral of SHFT_REG is
    
    -- store buffers (redundant for schematic matching)
    signal DC_Q : std_logic_vector(7 downto 0) := "00000000";
    signal nDC_Q : std_logic_vector(7 downto 0) := "11111111";
    signal RS_Q : std_logic_vector(7 downto 0) := "00000000";
    signal nRS_Q : std_logic_vector(7 downto 0) := "11111111";
    signal setAnd : std_logic_vector(7 downto 0) := "00000000";
    signal resetAnd : std_logic_vector(7 downto 0) := "00000000";
    signal resetOr : std_logic_vector(7 downto 0) := "00000000";

    -- negative signals (redundant for schematic matching)
    signal nSRLOAD : std_logic := '0';
    signal nSRCLR : std_logic := '0';
    signal nSRCK : std_logic := '0';
    signal nRCK : std_logic := '0';
    
    -- RS triggers
    component RS_sync is
          port ( 
          C : in std_logic;
          S : in std_logic;
          R : in std_logic;
          D : in std_logic;
          Q : out std_logic;
          nQ : out std_logic);
    end component;      
    
    -- D triggers
    component D_sync is
          port ( 
          C : in std_logic;
          D : in std_logic;
          Q : out std_logic;
          nQ : out std_logic);
    end component;
    
    begin

    ---------------------------------------- Start of arch
    nRCK <= not RCK;
    nSRLOAD <= not SRLOAD;
    nSRCLR <= not SRCLR;
    nSRCK <= not SRCK;
    
    proc: process (RCK, SRLOAD, SRCK, SRCLR, in_bus)
    begin
    ---------------------------------------- Start of process 
        for i in 0 to 7 loop
            setAnd(i) <= (DC_Q(i) and nSRLOAD);
            resetAnd(i) <= not (nDC_Q(i) and nSRLOAD);
            resetOr(i) <= (not resetAnd(i) or not SRCLR);
        end loop;
    end process;
    ---------------------------------------- End of the process

    Rs_shifter: for i in 0 to 7 generate
        rs_shift_0: if (i = 0) generate
            shifter:    
                RS_sync port map (
                    C => SRCK,
                    S => setAnd(0),
                    R => resetOr(0),
                    D => SER,
                    Q => RS_Q(0),
                    nQ => nRS_Q(0));
        end generate rs_shift_0;
        rs_shift_other: if (i /= 0) generate
            shifter:    
                RS_sync port map (
                    C => SRCK,
                    S => setAnd(i),
                    R => resetOr(i),
                    D => RS_Q(i-1),
                    Q => RS_Q(i),
                    nQ => nRS_Q(i)
                );        
            
        end generate rs_shift_other;
    end generate Rs_shifter;
                
    D_buff_generate: for i in 0 to 7 generate
        D_buff: D_sync port map (
                        C => RCK,
                        D => in_bus(i),
                        Q => DC_Q(i),
                        nQ => nDC_Q(i));
                        
        REG_OUT <= RS_Q(7);
    end generate D_buff_generate;
    
    
end Behavioral;
