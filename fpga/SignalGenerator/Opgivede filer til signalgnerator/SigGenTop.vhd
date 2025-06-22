
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity SigGenTop is
  Port ( BTN3   : in std_logic;
			BTN1   : in std_logic; 
         Clk    : in std_logic;
			MOSI   : in std_logic;
			SClk   : in std_logic;
			SSnot  : in std_logic;
			An     : out std_logic_vector(3 downto 0);
			Cat    : out std_logic_vector(7 downto 0);
			LD		 : out std_logic;
			LD2		 : out std_logic;
			LD3		 : out std_logic;
         LD4		 : out std_logic;
			PWMOut : inout std_logic);
end SigGenTop;

architecture Behavioral of SigGenTop is
signal DispClk, SigEN, BTN1db, LED, LED2, LED3, LED4: std_logic;
signal Disp: std_logic_vector(19 downto 0); 
signal Amp, Freq : std_logic_vector(7 downto 0);
signal Shape : std_logic_vector(2 downto 0);


begin
	 
U1: entity WORK.SigGenSPIControl
	 port map (CLK => Clk,
           Reset => BTN3,
           SClk => SClk,
           MOSI => MOSI,
           SSnot => SSnot,
           Shape => Shape,
           Amp => Amp,
           Freq => Freq,
           SigEN => SigEN,
			  LD2 => LED2,
			  LD3 => LED3,
			  LD4 => LED4,
			  LD => LED); --DETTE ER EN TEST, SLET I ENDELIG VERSION
			  
							
U2: entity WORK.SigGenDataPath generic map (PWMinc => "0000001") 
    port map(Reset => BTN3, Clk => Clk, Shape => Shape(2 downto 0), Ampl => Amp, Freq => Freq, SigEN => SigEN, PWMOut => PWMOut);


U3: entity WORK.SevenSeg5 
    port map(Reset => BTN3, Clk => DispClk, Data => Disp, An => An, Cat => Cat);  


U4: entity WORK.DivClk 
    port map(Reset => BTN3, Clk => Clk, TimeP => 50e3, Clk1 => DispClk);


LD <= LED; --Run signal
LD2 <= LED2; 
LD3 <= LED3; 
LD4 <= LED4; 
U5: entity WORK.DispMux
		port map(
			Shape => Shape,
			Amp => Amp,
			Freq => Freq,
			Clk => Clk,
			Reset => BTN3,
			BTN1 => BTN1db,
			Disp => Disp); 

 
U6: entity WORK.BTNdb
		port map( 
			Reset => BTN3,
			Clk => Clk,
			BTNin => BTN1,
			BTNout => BTN1db 
			);
			

	
	
end Behavioral;
