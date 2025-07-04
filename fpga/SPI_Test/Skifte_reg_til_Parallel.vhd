library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_unsigned.all;


entity Skifte_reg_til_Parallel is
    Port ( MOSI : in  STD_LOGIC;
           RESET : in  STD_LOGIC;
           SPIdat : out  STD_LOGIC_VECTOR (7 downto 0);
			  SClk : in STD_LOGIC);

end Skifte_reg_til_Parallel;

architecture Behavioral of Skifte_reg_til_Parallel is
signal skift_reg : std_logic_vector (7 downto 0); -- Register hvor MOSI data gemmes.


begin
	
	process(SClk, RESET)
		begin
			if RESET = '1' then 
				skift_reg <= "00000000"; -- Register tømmes ved reset.
			elsif rising_edge(SClk) then
				skift_reg <= MOSI & skift_reg(7 downto 1);  	-- Skifte register, læser MOSI bit.
			end if;
	end process; 	 

SPIdat <= skift_reg; -- Parallel indlæsing mellem skifteregister og SPIdat


end Behavioral;



