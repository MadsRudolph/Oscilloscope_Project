library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_unsigned.all;


entity Skifte_reg_til_Parallel is
    Port ( SCK : in  STD_LOGIC;
           MOSI : in  STD_LOGIC;
           RESET : in  STD_LOGIC;
           LED : out  STD_LOGIC_VECTOR (7 downto 0);
			  SSnot : in STD_LOGIC);
			 

end Skifte_reg_til_Parallel;

architecture Behavioral of Skifte_reg_til_Parallel is
signal skift_reg : std_logic_vector (7 downto 0);

begin
	
	process(SCK, RESET, SSnot)
		begin
			if RESET = '1' then 
				skift_reg <= "00000000";
					elsif rising_edge(SCK) and SSnot = '0' then
				skift_reg <= MOSI & skift_reg(7 downto 1);  	
			end if;
	end process; 	 

LED <= skift_reg when SSnot = '1' else (others => 'Z'); 

end Behavioral;