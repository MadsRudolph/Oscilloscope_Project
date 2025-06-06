
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

type Statetype is (IDLE, ADDR, Data, CheckSum, ShapeS, AmpS, FreqS);

signal state, nextstate : Statetype;
signal flag, FreqFlag, ShapeFlag, AmpFlag: STD_LOGIC;
signal ADDRReg, DataReg, SyncReg, AmpReg, FreqReg, ShapeReg, CheckSumReg: STD_LOGIC_VECTOR(7 downto 0);




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
		if SPIdat = "00000000" and DataReady = '1' then -- check spidat(sync) stemmer
		flag <='1';	
		SyncReg <= SPIdat;
		nextstate <= ADDR; 
		else 
		nextstate <= IDLE; 
		end if;
		
	when ADDR => 
		if flag = '1' and DataReady = '1' then 
			ADDRReg <= SPIdat; 
			flag <= '1';
			nextstate <= Data;
		else 
		nextstate <= ADDR;
		end if;
	
	when Data => 
		if flag = '1' and DataReady = '1' then 
			DataReg <= SPIdat; 
			nextstate <= CheckSum;
		else
			nextstate <= Data;
	end if;

	when Checksum =>
		CheckSumReg <=	(SyncReg xor ADDRReg) xor DataReg;		
			if CheckSumReg = SPIdat then
				if ADDRReg(0) = '1' and ADDRReg(1) = '0' then -- LAV OM IFT ADDR
				nextstate <= AmpS;
			elsif ADDRReg(0) = '0' and ADDRReg(1) = '1' then
				nextstate <= ShapeS;
			elsif ADDRReg(0) = '1' and ADDRReg(1) = '1' then
				nextstate <= FreqS;
			else 
				nextstate <= checksum;
			end if;
			end if;

					
			
	when AmpS =>
	AmpFlag <='1';
	AmpReg <= DataReg;
	nextstate <= IDLE;
	
	when ShapeS =>
	ShapeFlag <='1';
	ShapeReg <= DataReg;
	nextstate <= IDLE;
	
	when FreqS =>
	FreqFlag <='1';
	FreqReg <= DataReg;
	nextstate <= IDLE;	


if FreqFlag = '1' and ShapeFlag = '1' and AmpFlag = '1' then
SigEN <= '1';
end if;

end case;
end process;

Ampl <= AmpReg;
Freq <= FreqReg;
Shape <= ShapeReg;
 
end Behavioral;
