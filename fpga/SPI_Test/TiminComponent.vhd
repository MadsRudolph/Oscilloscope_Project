
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

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
	elsif rising_edge(Clk) then 
		SSnotSync <= SSnot; 
		
	end if;		
	
end process;
	
-- DelReg 
process(Reset, Clk)
begin

	if Reset = '1' then
		SSnotOld <= '0';
	elsif rising_edge(Clk) then
		SSnotOld <= SSnotSync;

	end if;

end process;


	DataReady <= SSNOTSync and (not SSnotOld);

end Behavioral;



