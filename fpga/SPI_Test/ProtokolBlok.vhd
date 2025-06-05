
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;


entity ProtokolBlok is
    Port ( CLK : in STD_LOGIC;
			  Sync : in  STD_LOGIC_VECTOR (7 downto 0);
           Adr : in  STD_LOGIC_VECTOR (7 downto 0);
           Data : in  STD_LOGIC_VECTOR (7 downto 0);
			  Reset : in STD_LOGIC;
			  SSnot : in STD_LOGIC;
           CheckSum : out  STD_LOGIC_VECTOR (7 downto 0));
			  
	
end ProtokolBlok;

architecture Behavioral of ProtokolBlok is

signal temp: STD_LOGIC_VECTOR (7 downto 0);

begin

process(CLK,Reset)
begin

if Reset ='1' then
temp <= "00000000"; 

elsif rising_edge(CLK) then
if SSnot = '0' then
temp <= (Sync xor Adr) xor Data;

end if;
end if;
end process;

CheckSum <= temp;
 
end Behavioral;

