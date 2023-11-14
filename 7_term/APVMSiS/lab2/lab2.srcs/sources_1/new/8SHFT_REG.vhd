library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library DC_trigger;
use DC_trigger.all;

--
-- entity declartion
--
entity SHFT_REG is
    port ( 
        SRCLR   : in std_logic := '1';  -- shift register clear
        SRCK    : in std_logic := '0';  -- shift register clock
        SRLOAD  : in std_logic := '1';  -- shift register load
        RCK     : in std_logic := '0';  -- register clock (write to register only when clock at '1')
        SER     : in std_logic := '0';  -- shift register entry data
        in_bus  : in std_logic_vector (7 downto 0) := (others => '0'); 
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

    setAnd(0)   <= DC_Q(0) and not SRLOAD;
    resetAnd(0) <= not DC_Q(0) and not SRLOAD;
    resetOr(0)  <= resetAnd(0) or not SRCLR;
    
    setAnd(1)   <= DC_Q(1) and not SRLOAD;
    resetAnd(1) <= not DC_Q(1) and not SRLOAD;
    resetOr(1)  <= resetAnd(1) or not SRCLR;
    
    setAnd(2)   <= DC_Q(2) and not SRLOAD;
    resetAnd(2) <= not DC_Q(2) and not SRLOAD;
    resetOr(2)  <= resetAnd(2) or not SRCLR;
    
    setAnd(3)   <= DC_Q(3) and not SRLOAD;
    resetAnd(3) <= not DC_Q(3) and not SRLOAD;
    resetOr(3)  <= resetAnd(3) or not SRCLR;
    
    setAnd(4)   <= DC_Q(4) and not SRLOAD;
    resetAnd(4) <= not DC_Q(4) and not SRLOAD;
    resetOr(4)  <= resetAnd(4) or not SRCLR;
    
    setAnd(5)   <= DC_Q(5) and not SRLOAD;
    resetAnd(5) <= not DC_Q(5) and not SRLOAD;
    resetOr(5)  <= resetAnd(5) or not SRCLR;
    
    setAnd(6)   <= DC_Q(6) and not SRLOAD;
    resetAnd(6) <= not DC_Q(6) and not SRLOAD;
    resetOr(6)  <= resetAnd(6) or not SRCLR;
    
    setAnd(7)   <= DC_Q(7) and not SRLOAD;
    resetAnd(7) <= not DC_Q(7) and not SRLOAD;
    resetOr(7)  <= resetAnd(7) or not SRCLR;
    
    ---------------------------------------- Start of process 
--    proc: process
--    begin
--        for i in 0 to 7 loop
--            setAnd(i)   <= (DC_Q(i) and nSRLOAD);
--            resetAnd(i) <= not (nDC_Q(i) and nSRLOAD);
--            resetOr(i)  <= (not resetAnd(i) or not SRCLR);
--        end loop;
--    end process;
    ---------------------------------------- End of the process
    
    ---------------------------------------- Generate RS triggers 
--    RS1: RS_sync port map (C  => SRCK, 
--                           S  => setAnd(0),
--                           R  => resetOr(0),
--                           D  => SER,
--                           Q  => RS_Q(0),
--                           nQ => nRS_Q(0));
    
--    RS2: RS_sync port map (C  => SRCK, 
--                           S  => setAnd(1),
--                           R  => resetOr(1),
--                           D  => RS_Q(0),
--                           Q  => RS_Q(1),
--                           nQ => nRS_Q(1));
                            
          
--     RS3: RS_sync port map (C  => SRCK, 
--                            S  => setAnd(2),
--                            R  => resetOr(2),
--                            D  => RS_Q(1),
--                            Q  => RS_Q(2),
--                            nQ => nRS_Q(2));                
    
--    RS4: RS_sync port map (C  => SRCK, 
--                           S  => setAnd(3),
--                           R  => resetOr(3),
--                           D  => RS_Q(2),
--                           Q  => RS_Q(3),
--                           nQ => nRS_Q(3)); 
                           
--    RS5: RS_sync port map (C  => SRCK, 
--                           S  => setAnd(4),
--                           R  => resetOr(4),
--                           D  => RS_Q(3),
--                           Q  => RS_Q(4),
--                           nQ => nRS_Q(4)); 
                           
                           
--   RS6: RS_sync port map (C  => SRCK, 
--                          S  => setAnd(5),
--                          R  => resetOr(5),
--                          D  => RS_Q(4),
--                          Q  => RS_Q(5),
--                          nQ => nRS_Q(5)); 
                          
--    RS7: RS_sync port map (C  => SRCK, 
--                           S  => setAnd(6),
--                           R  => resetOr(6),
--                           D  => RS_Q(5),
--                           Q  => RS_Q(6),
--                           nQ => nRS_Q(6)); 
                           
--    RS8: RS_sync port map (C  => SRCK, 
--                           S  => setAnd(7),
--                           R  => resetOr(7),
--                           D  => RS_Q(6),
--                           Q  => RS_Q(7),
--                           nQ => nRS_Q(7)); 
    
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
                
    ---------------------------------------- Generate buffers
    D_buff_generate: for i in 0 to 7 generate
        D_buff: D_sync port map (
                        C => RCK,
                        D => in_bus(i),
                        Q => DC_Q(i),
                        nQ => nDC_Q(i)
                    );
    end generate D_buff_generate;
    
    REG_OUT <= RS_Q(7);

end Behavioral;
