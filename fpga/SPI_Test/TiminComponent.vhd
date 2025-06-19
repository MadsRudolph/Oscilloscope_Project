
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
 -- Component som synkroniserer Masterenhedens SSnot signal med den interne clock i FPGA-enheden
entity TimingComponent is
    Port ( SSNot: in STD_LOGIC;
           Clk : in  STD_LOGIC;
           Reset : in  STD_LOGIC;
			  DataReady: out STD_LOGIC);
end TimingComponent;

architecture Behavioral of TimingComponent is

signal SSnotOld: STD_LOGIC;
signal SSnotSync: STD_LOGIC;

begin


-- SyncReg
Process(Reset, Clk)
begin 
	if reset ='1' then 
		SSnotSync <= '0';
	elsif rising_edge(Clk) then --  SSnot signal fra Master synkroniseres med intern clock i FPGA
		SSnotSync <= SSnot; 
		
	end if;		
	
end process;
	
-- DelReg 
process(Reset, Clk) 
begin

	if Reset = '1' then
		SSnotOld <= '0'; -- Nulstiller tidligere SSnot værdi
	elsif rising_edge(Clk) thenSS
		SSnotOld <= SSnotSync; -- Gemmer forrige SSNOT værdi

	end if;

end process;


	DataReady <= SSNOTSync and (not SSnotOld); -- Flanke detektion - Dataready = 1, når SSNOT går fra 0 til 1

end Behavioral;



