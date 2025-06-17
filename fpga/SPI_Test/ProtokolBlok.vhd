
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;


entity ProtokolBlok is
    Port ( CLK : in STD_LOGIC;
			  Reset : in STD_LOGIC;
			  DataReady : in STD_LOGIC;
			  SPIdat: in STD_LOGIC_VECTOR (7 downto 0);
			  Shape: out STD_LOGIC_VECTOR (1 downto 0);
			  Amp: out STD_LOGIC_VECTOR (7 downto 0);
			  LD: out STD_LOGIC;
			  LD2: out STD_LOGIC;
			  LD3: out STD_LOGIC;
			  Freq: out STD_LOGIC_VECTOR (7 downto 0);
			  SigEN: inout STD_LOGIC);
end ProtokolBlok;

architecture Behavioral of ProtokolBlok is

type Statetype is (IDLE, ADDRS, DataS, CheckSumEnS, CheckSumS, AmpS, ShapeS, FreqS);

signal state, nextstate : Statetype;
signal DataEN, ADDREN, AmpEN, FreqEN, ShapeEN, CheckSumEN, Chk, syncbyte, SigENEN, tusFlag, totusFlag: STD_LOGIC;
signal CheckSum, ADDR, Data: STD_LOGIC_VECTOR (7 downto 0);
signal TestCnt: STD_LOGIC_VECTOR (15 downto 0); -- Dette er til test af robust kommunikation

begin


SyncDec: syncbyte <= '1' when SPIdat = "01010101" else '0';

CheckSumDec: Chk <= '1' when Checksum = (("01010101" xor ADDR) xor Data) else '0';

Statereg: process(CLK, Reset)
    begin 
        if Reset = '1' then 
            state <= IDLE;  -- Reset state to IDLE
        elsif CLK'event and CLK = '1' then
            state <= nextstate;  -- Update state on clock edge
        end if;
    end process;

    -- Next state logic and register enable control
    StateDec: process (DataReady, state, Chk, syncbyte, ADDR)
    begin
	 	 
-- Default values
	DataEn <= '0';
	ADDREn <= '0';
	CheckSumEn <= '0';
	AmpEn <= '0';
	ShapeEn <= '0';
	FreqEn <= '0';
	SigENEN <= '0';
	
	case state is
	
	when IDLE =>
		if syncbyte  = '1' and DataReady = '1' then  -- check spidat(sync) stemmer
			SigENEN <='0';
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
			nextstate <= CheckSumEnS;
		else
			nextstate <= DataS;
		end if;
		
   when CheckSumEnS =>
		if DataReady = '1' then
			CheckSumEn <= '1';
			nextstate <= CheckSumS;
		else
			nextstate <= CheckSumEnS;
		end if;

	when CheckSumS =>
		if Chk = '1' and ADDR = "00000001" then
			nextstate <= AmpS;
			
		elsif Chk = '1' and ADDR = "00000010" then
			nextstate <= FreqS;
		elsif Chk = '1' and ADDR = "00000011" then
			nextstate <= ShapeS;
		else
			nextstate <=IDLE;			
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
			SigENEN <= '1';
			TestCnt <= TestCnt + "0001"; -- Dette er til test af robust kommunikation

end case;


end process;


Process(TestCnt)
begin
	if TestCnt < "0000011111010000" then -- led lys hvis under 2000 shapes
	tusFlag <= '1';
	totusFlag <= '0';
	elsif TestCnt >= "0000011111010000" then -- led lyser hvis over 2000 shapes 
	totusFlag <= '1';
	tusFlag <= '0';
	else 
		tusFlag <= '0';
		totusFlag <= '0';
	end if; 
end process; 

LD <= SigEn;
LD2 <= tusFlag;
LD3 <= totusFlag; 

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



ShapeReg: entity work.std_2bit_reg
	port map (
					Reset => Reset,
					Clk => Clk,
					Enable => ShapeEn,
					Data_in => Data (1 downto 0),
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

SigENReg : entity work.std_1bit_reg
	port map (
					Reset => Reset,
					Clk => Clk,
					Enable => SigENEN,
					Data_in => SigENEN,
					Data_out => SigEN
					);

end Behavioral;