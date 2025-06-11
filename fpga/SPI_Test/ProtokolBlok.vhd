
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;


entity ProtokolBlok is
    Port ( CLK : in STD_LOGIC;
			  Reset : in STD_LOGIC;
			  DataReady : in STD_LOGIC;
			  SPIdat: in STD_LOGIC_VECTOR (7 downto 0);
			  Shape: out STD_LOGIC_VECTOR (7 downto 0);
			  Ampl: out STD_LOGIC_VECTOR (7 downto 0);
			  Freq: out STD_LOGIC_VECTOR (7 downto 0);
			  SigEN: out STD_LOGIC);
end ProtokolBlok;

architecture Behavioral of ProtokolBlok is

type Statetype is (IDLE, CheckSum, ShapeS, AmpS, FreqS);

signal state, nextstate : Statetype;
signal sync2_flag, sync1_flag, CRC_flag: STD_LOGIC;
signal SyncReg1, SyncReg2, LengthReg1, LengthReg2, AmpReg, FreqReg, ShapeReg, CheckSumReg: STD_LOGIC_VECTOR(7 downto 0);

  


begin

Statereg: process(CLK, Reset)
    begin 
        if Reset = '1' then 
            state <= IDLE;  -- Reset state to IDLE
        elsif CLK'event and CLK = '1' then
            state <= nextstate;  -- Update state on clock edge
        end if;
    end process;

    -- Next state logic and register enable control
    StateDec: process (SPIdat, DataReady)
    begin
	 
	 
-- Default values
	
	CheckSumReg <= "00000000";

	
	case state is
	when IDLE =>
		CRC_flag <= '0';
	
		if SPIdat = "01010101" then -- check spidat(sync) stemmer
			SigEN <= '0';
			SyncReg1 <= SPIdat;
			sync1_flag <= '1';
		elsif (SPIdat xor SyncReg1) = "11111111" then -- XOR første og andet sync byte, forventet "11111111"
			SyncReg2 <= SPIdat;
			sync2_flag <= '1';
		elsif (SPIdat and SyncReg2) = "00000000" and sync1_flag = '1' and sync2_flag = '1' then -- AND samlet sync med første length byte samt to flag for at sikre begge sync er opnået først
			LengthReg1 <= SPIdat;
			sync1_flag <= '0';
			sync2_flag <= '0';
		elsif (SPIdat xor LengthReg1) = "00001010" then -- XOR værdien fra LengthReg med næste length byte
			LengthReg2 <= SPIdat;
		elsif (SPIdat xor LengthReg2) = "00001000" then -- XOR samlet byte kontrol med type, hvorfra vi kan gå videre til ShapeS
			nextstate <= ShapeS;
		else 
			nextstate <= IDLE;
		end if; 


	when ShapeS =>
		if DataReady = '1' then
			ShapeReg <= SPIdat;
			nextstate <= AmpS;
		else 
			nextstate <=ShapeS;
		end if;

	when AmpS =>
	if DataReady = '1' then
		AmpReg <= SPIdat;
		nextstate <= FreqS;
	else 
		nextstate<=AmpS;

	end if; 
	
	when FreqS =>
	if DataReady = '1' then
		FreqReg <= SPIdat;
		nextstate <= CheckSum;
	else 
		nextstate <=FreqS;

	end if; 
	

	when CheckSum =>
		CheckSumReg <=	(AmpReg xor FreqReg) xor ShapeReg;
		
		if SPIdat = "00000000" and CRC_flag ='0' and DataReady = '1' then 
			CRC_flag <= '1';
			nextstate <= CheckSum; 
		
		elsif CheckSumReg = SPIdat and CRC_flag = '1' then 		
				SigEn <= '1';
				nextstate <= IDLE;
		elsif CheckSumReg /= SPIdat and CRC_flag = '1' then	
			 nextstate <= IDLE;
			else 
				nextstate <= CheckSum; --Tjekke om CRC kan bruges, ellers hvad sker der hvis den ikke passer. 

			end if;					
			


end case;
end process;

Ampl <= AmpReg;
Freq <= FreqReg;
Shape <= ShapeReg;
 
end Behavioral;
