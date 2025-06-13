
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;


entity ProtokolBlok is
    Port ( CLK : in STD_LOGIC;
			  Reset : in STD_LOGIC;
			  DataReady : in STD_LOGIC;
			  SPIdat: in STD_LOGIC_VECTOR (7 downto 0);
			  Shape: out STD_LOGIC_VECTOR (7 downto 0);
			  Amp: out STD_LOGIC_VECTOR (7 downto 0);
			  Freq: out STD_LOGIC_VECTOR (7 downto 0);
			  SigEN: out STD_LOGIC);
end ProtokolBlok;

architecture Behavioral of ProtokolBlok is

type Statetype is (IDLE, ADDRS, DataS, CheckSumS, AmpS, ShapeS, FreqS);

signal state, nextstate : Statetype;
signal DataEN, ADDREN, AmpEN, FreqEN, ShapeEN, CheckSumEN, Chk, syncbyte: STD_LOGIC;
signal CheckSum, ADDR, Data: STD_LOGIC_VECTOR (7 downto 0);

  


begin


SyncDec: syncbyte <= '1' when SPIdat = "01010101" else '0';

CheckSumDec: Chk <= '1' when Checksum = ("01010101" xor ADDR xor Data) else '0';


Statereg: process(CLK, Reset)
    begin 
        if Reset = '1' then 
            state <= IDLE;  -- Reset state to IDLE
        elsif CLK'event and CLK = '1' then
            state <= nextstate;  -- Update state on clock edge
        end if;
    end process;

    -- Next state logic and register enable control
    StateDec: process (SPIdat, DataReady, state, Chk, syncbyte)
    begin
	 
	 
-- Default values
	DataEn <= '0';
	ADDREn <= '0';
	CheckSumEn <= '0';
	AmpEn <= '0';
	ShapeEn <= '0';
	FreqEn <= '0';
	
	
	case state is
	
	when IDLE =>
		
		if syncbyte  = '1' and DataReady = '1' then  -- check spidat(sync) stemmer
			SigEN <='0';
			nextstate <= ADDRS;
		else
			nextstate <= IDLE;
		end if; 
	
	when ADDRS =>
	
		if DataReady = '1' then
			ADDREN <= '1';
			nextstate <= DataS;
		else
			nextstate <= ADDRS;
		end if;
	
	
	when DataS =>
		
		if DataReady = '1' then
			DataEN <= '1';
			nextstate <= CheckSumS;
		else
			nextstate <= DataS;
		end if;
	

	when CheckSumS =>
	CheckSumEn <= '1';
		
		if Chk = '1' and ADDR = "00000001" then
			nextstate <= AmpS;
		elsif Chk = '1' and ADDR = "00000010" then
			nextstate <= FreqS;
		elsif Chk = '1' and ADDR = "00000011" then
			nextstate <= ShapeS;
		elsif 
			DataReady = '1' and Chk = '0' then -- Hvis checksum ikke passer.
			nextstate <=IDLE;
		else 
			nextstate <= CheckSumS;
		end if;
		

	when AmpS =>
			AmpEN <= '1';
			nextstate <= IDLE;

	
	when FreqS =>
			FreqEN <= '1';
			nextstate <= IDLE;

			
	when ShapeS =>
			ShapeEN <= '1';
			nextstate <= IDLE;
			SigEN <= '1';




end case;

end process;

ADDRReg: entity work.std_8bit_reg
	port map (
					Reset => Reset,
					Clk => Clk,
					Enable => ADDREn,
					Data_in => SPIdat,
					Data_out => ADDR
					);
					
DataReg: entity work.std_8bit_reg
	port map (
					Reset => Reset,
					Clk => Clk,
					Enable => DataEN,
					Data_in => SPIdat,
					Data_out => Data 
					);

CheckSumReg: entity work.std_8bit_reg
	port map (
					Reset => Reset,
					Clk => Clk,
					Enable => CheckSumEn,
					Data_in => SPIdat,
					Data_out => CheckSum 
					);



ShapeReg: entity work.std_8bit_reg
	port map (
					Reset => Reset,
					Clk => Clk,
					Enable => ShapeEn,
					Data_in => Data,
					Data_out => Shape 
					);


AmpReg: entity work.std_8bit_reg
	port map (
					Reset => Reset,
					Clk => Clk,
					Enable => AmpEn,
					Data_in => Data,
					Data_out => Amp 
					);


FreqReg: entity work.std_8bit_reg
	port map (
					Reset => Reset,
					Clk => Clk,
					Enable => FreqEn,
					Data_in => Data,
					Data_out => Freq
					);



end Behavioral;