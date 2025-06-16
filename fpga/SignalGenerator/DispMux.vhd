
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_unsigned.all;


entity DispMux is
    Port ( Shape : in  STD_LOGIC_VECTOR (1 downto 0);
			  Amp : in  STD_LOGIC_VECTOR (7 downto 0);
			  Freq : in  STD_LOGIC_VECTOR (7 downto 0);
			  Reset : in std_logic; 
			  Clk : in std_logic;
			  BTN1 : in std_logic; 
           Disp : out  STD_LOGIC_VECTOR (19 downto 0));
end DispMux;

architecture Behavioral of DispMux is
signal DispSel : std_logic_vector(1 downto 0); 


begin
	
	process(BTN1, Reset)
	begin 
		if Reset = '1' then 
			DispSel <= "00";
		elsif rising_edge(Clk) then
			if BTN1 = '1' then
				case DispSel is
					when "00" => DispSel <= "01";
					when "01" => DispSel <= "10";
					when "10" => DispSel <= "00";
					when others => DispSel <= "00";
				end case;
			end if;
		end if; 
	end process;

	
	
	process(DispSel, Shape, Amp, Freq)
	begin 
		
		if DispSel = "00" then 
		Disp <= x"450" & "000000" & shape; 
		
		
		elsif DispSel = "01" then  
		
		Disp <= x"4A0" & Amp; 
		
		elsif DispSel = "10" then  
		
		Disp <= x"4F0" & Freq; 
						
		end if; 
		end process; 

end Behavioral;