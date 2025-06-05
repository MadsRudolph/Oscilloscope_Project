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
signal para_reg : std_logic_vector (7 downto 0);
signal Counter : integer range 0 to 9; 

begin
	process (SCK, RESET)
	begin
	if RESET = '1' then
	Counter <= 0;
	elsif rising_edge(SCK) then
	if SSnot = '1' then
	Counter <= 0;
	elsif Counter <= 8 and SSnot = '0' then
	Counter <= Counter + 1;
	elsif Counter = 9 then
	Counter <= 0;
	end if; 
	end if;
	end process;
	
	
	process(SCK, RESET, SSnot)
		begin
			if RESET = '1' or SSnot = '1' then 
			skift_reg <= "00000000";
				elsif rising_edge(SCK) and SSnot = '0' then
				 if Counter <= 8 then
					skift_reg <= MOSI & skift_reg(7 downto 1); 
				 end if; 	
			end if; 
		end process; 	 
			 
			 
		process(SCK, Reset)
			begin
			if RESET = '1' then
			para_reg <= "00000000";
				elsif rising_edge(SCK) and counter = 8 then 
				para_reg <= skift_reg; 
			end if; 
		
	end process; 
	
		LED <= para_reg; 
	
end Behavioral;