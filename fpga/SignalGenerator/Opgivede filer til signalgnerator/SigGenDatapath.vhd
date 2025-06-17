--------------------------------------------------------------------------------
-- Company:        DTU
-- Engineer:       Peter Brauer
--
-- Create Date:    29/4/15
-- Design Name:    
-- Module Name:    SigGenDatapath - Behavioral
-- Project Name:   Signal Generator
-- Target Device:  Spartan 3
-- Tool versions:  
-- Description:    Datapath circuit for the Signal Generator system
--
-- Dependencies:   Lookup table "SinusLUT" for generating a sinus signal
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
-- 
--------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity SigGenDatapath is
  generic( PWMinc : std_logic_vector(6 downto 0) := "0000001" ); -- sat markant ned
  Port ( Reset  : in std_logic;	
         Clk    : in std_logic;
         SigEN  : in std_logic;
         Shape  : in std_logic_vector(1 downto 0);
         Ampl   : in std_logic_vector(7 downto 0);
         Freq   : in std_logic_vector(7 downto 0);
         PWMOut : out std_logic);
end SigGenDatapath;

architecture Behavioral of SigGenDatapath is

signal SigCnt, nSigCnt, FreqCnt: std_logic_vector(11 downto 0);
signal Sig, SigSquare, SigSaw, SigSinus : std_logic_vector(7 downto 0); 
signal SigAmpl: std_logic_vector(6 downto 0); 
signal PWMcnt: std_logic_vector(6 downto 0) := "0000000";
--signal wrapcnt : std_logic_vector(2 downto 0);
signal PWM, PWMwrap: std_logic;

begin

FreqDec: FreqCnt <= "00" & Freq(7 downto 6) & Freq(5 downto 4) & '0' & Freq(3 downto 2) & '0' & Freq(1 downto 0);

FreqAdd: nSigCnt <= SigCnt + FreqCnt;


SigReg: process (Reset, PWMwrap, Clk)
begin
  if Reset = '1' then SigCnt <= X"000";
  elsif Clk'event and Clk = '1' then
    if PWMwrap = '1' then
      SigCnt <= nSigCnt;
    end if;
  end if;
end process;

SinusDec : entity WORK.SinusLUT PORT MAP (clka => Clk, addra => SigCnt, douta => SigSinus);

PWMcount: process(Reset, Clk)
variable PWMcntvar: std_logic_vector(8 downto 0);
begin
  if Reset = '1' then PWMcntvar := "000000000";
  elsif Clk'event and Clk = '1' then
    PWMcntvar := PWMcntvar + PWMinc;
		if PWMcntvar > "111111111" then  --udviddet med 2 bit for at s�nke signalet 
			PWMcntvar := "000000000";
		end if;
		end if;
		if PWMcntvar = "000000000" then 
		PWMwrap <= '1'; 
		else 
		PWMwrap <= '0';
  end if;
  PWMcnt <= PWMcntvar(6 downto 0); -- PWMcnt er kun 7 bit da den skal t�lle hurtigere og f�lge clock direkte 
end process;     

--PWMdec: PWMwrap <= '1' when PWMcnt = "00000000" else '0'; -- denne fjernes

SquareDec: SigSquare <= "00000000" when SigCnt < X"800" else "11111111";

SawDec: SigSaw <= SigCnt(11 downto 4);

--Tridec: 

SigMux: Sig <= X"FF" when Shape = "00" else
               SigSquare when Shape = "01" else
               SigSaw when Shape = "10" else
               SigSinus;


AmplDec: process(Ampl, Sig)
variable MulA, MulB, MulC: std_logic_vector(15 downto 0);
--variable MulC: std_logic_vector(6 downto 0);
begin
  MulB := X"00" & Sig;
  MulA := X"00" & Ampl;
  MulC := X"0000";
  for j in 0 to 15 loop
    if MulA(j) = '1' then
      MulC := MulC + MulB;
    end if;
    MulB := MulB(14 downto 0) & '0';
  end loop;
--  MulC := MulC + 1;
  SigAmpl <= MulC(15 downto 9);
--  SigAmpl <= "1111111";
end process;



PWMcomp: PWM <= '1' when PWMcnt <= SigAmpl else '0';
 
PWMon: PWMout <= PWM when SigEn = '1' else '0';

end Behavioral;
