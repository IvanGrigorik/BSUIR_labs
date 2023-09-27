library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library DC_trigger;
use DC_trigger.all;

entity SHFT_REG is
    port ( 
        SRCLR : in std_logic := '1';   -- shift register clear
        SRCK : in std_logic := '0';    -- shift register clock
        SRLOAD : in std_logic := '1';  -- shift register load
        RCK : in std_logic := '0';     -- register clock (write to register only when clock at '1')
        SER : in std_logic := '0';     -- shift register entry data

        A: in std_logic := '0';
        B : in std_logic := '0';
        C : in std_logic := '0';
        D : in std_logic := '0';
        E : in std_logic := '0';
        F : in std_logic := '0';
        G : in std_logic := '0';
        H : in std_logic := '0';
        REG_OUT : out std_logic := '0');
end SHFT_REG;

architecture Behavioral of SHFT_REG is
    
    -- store buffers (redundant for schematic matching)
    signal DC_Q : std_logic_vector(7 downto 0) := "00000000";
    signal DC_nQ : std_logic_vector(7 downto 0) := "00000000";
    signal setAnd : std_logic_vector(7 downto 0) := "00000000";
    signal resetAnd : std_logic_vector(7 downto 0) := "00000000";
    signal resetOr : std_logic_vector(7 downto 0) := "00000000";
    signal RS_Q : std_logic_vector(7 downto 0) := "00000000";
    
    -- negative signals (redundant for schematic matching)
    signal nSRLOAD : std_logic := '0';
    signal nSRCLR : std_logic := '0';
    signal nSRCK : std_logic := '0';
    signal nRCK : std_logic := '0';

begin
    nRCK <= not RCK;
    nSRLOAD <= not SRLOAD;
    nSRCLR <= not SRCLR;
    nSRCK <= not SRCK;
    
    process (SRCK) is
    begin
        if SRCK = '1' then

        DC_Q(0) <= A and not nRCK;
        DC_nQ(0) <= not (A and not nRCK);
        DC_Q(1) <= B and not nRCK;
        DC_nQ(1) <= not (B and not nRCK);
        DC_Q(2) <= C and not nRCK;
        DC_nQ(2) <= not (C and not nRCK);
        DC_Q(3) <= D and not nRCK;
        DC_nQ(3) <= not (D and not nRCK);
        DC_Q(4) <= E and not nRCK;
        DC_nQ(4) <= not (E and not nRCK);
        DC_Q(5) <= F and not nRCK;
        DC_nQ(5) <= not (F and not nRCK);
        DC_Q(6) <= G and not nRCK;
        DC_nQ(6) <= not (G and not nRCK);
        DC_Q(7) <= H and not nRCK;
        DC_nQ(7) <= not (H and not nRCK);
        
        for i in 0 to 7 loop
            setAnd(i) <= not (DC_Q(i) and nSRLOAD);
            resetAnd(i) <= not (DC_nQ(i) and nSRLOAD);
            resetOr(i) <= not (not resetAnd(i) or not SRCLR);
        end loop;
    
--        If set or reset flag signal on
        
--            if (not resetOr(0)) = '1' then
--                for i in 0 to 7 loop
--                    RS_Q(i) <= '0';
--                end loop;
--            elsif (not setAnd(0) = '1') then
--                for i in 0 to 7 loop
--                    RS_Q(i) <= not setAnd(i);
--                end loop;
--            else
----                For first trigger
--                RS_Q(0) <= SER;
                
--                For all other triggers
                for i in 1 to 7 loop
                    RS_Q(i) <= RS_Q(i-1); 
                end loop;
            end if;
            
        end if;
        
        REG_OUT <= RS_Q(7);
        
        
--        RS_Q(0) <= '0' when not resetOr(0) else '1' when not setAnd(0) else SER;
    end process;
    
    
    
    
end Behavioral;
