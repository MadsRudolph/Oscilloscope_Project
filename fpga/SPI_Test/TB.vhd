
LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
 
ENTITY TB IS
END TB;
 
ARCHITECTURE behavior OF TB IS 
 
    -- Component Declaration for the Unit Under Test (UUT)
 
    COMPONENT 
    SigGenSPIControl is
    Port ( CLK : in  STD_LOGIC;
           Reset : in  STD_LOGIC;
           SCK : in  STD_LOGIC;
           MOSI : in  STD_LOGIC;
           SSnot : in  STD_LOGIC;
           Shape : out  STD_LOGIC_VECTOR (7 downto 0);
           Amp : out  STD_LOGIC_VECTOR (7 downto 0);
           Freq : out  STD_LOGIC_VECTOR (7 downto 0);
           SigEN : out  STD_LOGIC);
end Component;
 
   --Inputs
   signal SCK : std_logic := '0';
   signal MOSI : std_logic := '0';
   signal RESET : std_logic := '0';
	signal SSnot : std_logic := '1';

 	--Outputs
   signal SPIdat : std_logic_vector(7 downto 0);

   -- Clock period definitions
	constant SCK_period : time := 10 ns; 
BEGIN
 
	-- Instantiate the Unit Under Test (UUT)
   uut: SigGenSPIControl PORT MAP (
          SCK => SCK,
          MOSI => MOSI,
          RESET => RESET,
          SPIdat => SPIdat,
			 SSnot => SSnot
        );
 
  -- Clock process definitions
   SCK_process :process
   begin
		SCK <= '0';
		wait for SCK_period/2;
		SCK <= '1';
		wait for SCK_period/2;
   end process;

   -- Stimulus process
   stim_proc: process
   begin		
      -- hold reset state for 100 ns.
     

      -- insert stimulus here 
	
			-- sync 1 
      RESET <= '1'; 
		wait for SCK_period; 
		RESET <= '0';
		 
		wait for SCK_period;
		
		SSnot <= '0';
		
		MOSI <= '1';
		
		wait for SCK_period; 
		MOSI <= '0';
		
		wait for SCK_period; 
		MOSI <= '1';
		
		wait for SCK_period; 
		MOSI <= '0';
		
		wait for SCK_period; 
		MOSI <= '1';
		
		wait for SCK_period; 
		MOSI <= '0';
		
		wait for SCK_period; 
		MOSI <= '1';
		
		wait for SCK_period; 
		MOSI <= '0';
		
		wait for SCK_period;
		SSnot <= '0';
		
		wait for SCK_period; 
		
		
		
		-- sync 2 
    
		 
		MOSI <= '0';
		
		wait for SCK_period; 
		MOSI <= '1';
		
		wait for SCK_period; 
		MOSI <= '0';
		
		wait for SCK_period; 
		MOSI <= '1';
		
		wait for SCK_period; 
		MOSI <= '0';
		
		wait for SCK_period; 
		MOSI <= '1';
		
		wait for SCK_period; 
		MOSI <= '0';
		
		wait for SCK_period; 
		MOSI <= '1';
		
		
		wait for SCK_period; 
		
		
		
		-- length 1 
		
		MOSI <= '0';
		
		wait for SCK_period; 
		MOSI <= '0';
		
		wait for SCK_period; 
		MOSI <= '0';
		
		wait for SCK_period; 
		MOSI <= '0';
		
		wait for SCK_period; 
		MOSI <= '0';
		
		wait for SCK_period; 
		MOSI <= '0';
		
		wait for SCK_period; 
		MOSI <= '0';
		
		wait for SCK_period; 
		MOSI <= '0';
		
		
		wait for SCK_period; 
		
			
		-- length 2

		SSnot <= '0';
		
		MOSI <= '0';
		
		wait for SCK_period; 
		MOSI <= '1';
		
		wait for SCK_period; 
		MOSI <= '0';
		
		wait for SCK_period; 
		MOSI <= '1';
		
		wait for SCK_period; 
		MOSI <= '0';
		
		wait for SCK_period; 
		MOSI <= '0';
		
		wait for SCK_period; 
		MOSI <= '0';
		
		wait for SCK_period; 
		MOSI <= '0';
		
		wait for SCK_period;
		SSnot <= '0';
		
		wait for SCK_period; 
		
		
		
			--Type
    
		MOSI <= '0';
		
		wait for SCK_period; 
		MOSI <= '1';
		
		wait for SCK_period; 
		MOSI <= '0';
		
		wait for SCK_period; 
		MOSI <= '0';
		
		wait for SCK_period; 
		MOSI <= '0';
		
		wait for SCK_period; 
		MOSI <= '0';
		
		wait for SCK_period; 
		MOSI <= '0';
		
		wait for SCK_period; 
		MOSI <= '0';
		

		
		wait for SCK_period; 
		
		
			--Shape
    
		
		MOSI <= '1';
		
		wait for SCK_period; 
		MOSI <= '0';
		
		wait for SCK_period; 
		MOSI <= '0';
		
		wait for SCK_period; 
		MOSI <= '0';
		
		wait for SCK_period; 
		MOSI <= '0';
		
		wait for SCK_period; 
		MOSI <= '0';
		
		wait for SCK_period; 
		MOSI <= '0';
		
		wait for SCK_period; 
		MOSI <= '0';
		

		wait for SCK_period; 
		
		
		
			--Amp
    
		 
		MOSI <= '0';
		
		wait for SCK_period; 
		MOSI <= '1';
		
		wait for SCK_period; 
		MOSI <= '0';
		
		wait for SCK_period; 
		MOSI <= '0';
		
		wait for SCK_period; 
		MOSI <= '0';
		
		wait for SCK_period; 
		MOSI <= '0';
		
		wait for SCK_period; 
		MOSI <= '0';
		
		wait for SCK_period; 
		MOSI <= '0';
		

		wait for SCK_period; 
		
		
		
		
			--Freq
    
		
		MOSI <= '1';
		
		wait for SCK_period; 
		MOSI <= '1';
		
		wait for SCK_period; 
		MOSI <= '0';
		
		wait for SCK_period; 
		MOSI <= '0';
		
		wait for SCK_period; 
		MOSI <= '0';
		
		wait for SCK_period; 
		MOSI <= '0';
		
		wait for SCK_period; 
		MOSI <= '0';
		
		wait for SCK_period; 
		MOSI <= '0';
		

		wait for SCK_period; 
		
		
		
		
			--CRC 1

		
		MOSI <= '0';
		
		wait for SCK_period; 
		MOSI <= '0';
		
		wait for SCK_period; 
		MOSI <= '0';
		
		wait for SCK_period; 
		MOSI <= '0';
		
		wait for SCK_period; 
		MOSI <= '0';
		
		wait for SCK_period; 
		MOSI <= '0';
		
		wait for SCK_period; 
		MOSI <= '0';
		
		wait for SCK_period; 
		MOSI <= '0';
		

		wait for SCK_period; 
		
		
		
		
		--CRC 2
		
		MOSI <= '0';
		
		wait for SCK_period; 
		MOSI <= '0';
		
		wait for SCK_period; 
		MOSI <= '0';
		
		wait for SCK_period; 
		MOSI <= '0';
		
		wait for SCK_period; 
		MOSI <= '0';
		
		wait for SCK_period; 
		MOSI <= '0';
		
		wait for SCK_period; 
		MOSI <= '0';
		
		wait for SCK_period; 
		MOSI <= '0';
		

		wait for SCK_period; 
		
					-- sync 1 
		
		SSnot <= '0';
		
		MOSI <= '1';
		
		wait for SCK_period; 
		MOSI <= '0';
		
		wait for SCK_period; 
		MOSI <= '1';
		
		wait for SCK_period; 
		MOSI <= '0';
		
		wait for SCK_period; 
		MOSI <= '1';
		
		wait for SCK_period; 
		MOSI <= '0';
		
		wait for SCK_period; 
		MOSI <= '1';
		
		wait for SCK_period; 
		MOSI <= '0';
		
		wait for SCK_period;
		SSnot <= '0';
		
		wait for SCK_period; 
		
		
		
		-- sync 2 
  
		
		MOSI <= '0';
		
		wait for SCK_period; 
		MOSI <= '1';
		
		wait for SCK_period; 
		MOSI <= '0';
		
		wait for SCK_period; 
		MOSI <= '1';
		
		wait for SCK_period; 
		MOSI <= '0';
		
		wait for SCK_period; 
		MOSI <= '1';
		
		wait for SCK_period; 
		MOSI <= '0';
		
		wait for SCK_period; 
		MOSI <= '1';
		
		
		wait for SCK_period; 
		
		
		
		-- length 1 
		
		
		MOSI <= '0';
		
		wait for SCK_period; 
		MOSI <= '0';
		
		wait for SCK_period; 
		MOSI <= '0';
		
		wait for SCK_period; 
		MOSI <= '0';
		
		wait for SCK_period; 
		MOSI <= '0';
		
		wait for SCK_period; 
		MOSI <= '0';
		
		wait for SCK_period; 
		MOSI <= '0';
		
		wait for SCK_period; 
		MOSI <= '0';
		
		
		wait for SCK_period; 
		
		
		
		
		
			
		-- length 2
		
		SSnot <= '0';
		
		MOSI <= '0';
		
		wait for SCK_period; 
		MOSI <= '1';
		
		wait for SCK_period; 
		MOSI <= '0';
		
		wait for SCK_period; 
		MOSI <= '1';
		
		wait for SCK_period; 
		MOSI <= '0';
		
		wait for SCK_period; 
		MOSI <= '0';
		
		wait for SCK_period; 
		MOSI <= '0';
		
		wait for SCK_period; 
		MOSI <= '0';
		
		wait for SCK_period;
		SSnot <= '0';
		
		wait for SCK_period; 
		
		
		
			--Type
    
		
		
		MOSI <= '0';
		
		wait for SCK_period; 
		MOSI <= '1';
		
		wait for SCK_period; 
		MOSI <= '0';
		
		wait for SCK_period; 
		MOSI <= '0';
		
		wait for SCK_period; 
		MOSI <= '0';
		
		wait for SCK_period; 
		MOSI <= '0';
		
		wait for SCK_period; 
		MOSI <= '0';
		
		wait for SCK_period; 
		MOSI <= '0';
		

		
		wait for SCK_period; 
		
		
			--Shape
    
		
		MOSI <= '0';
		
		wait for SCK_period; 
		MOSI <= '0';
		
		wait for SCK_period; 
		MOSI <= '0';
		
		wait for SCK_period; 
		MOSI <= '0';
		
		wait for SCK_period; 
		MOSI <= '0';
		
		wait for SCK_period; 
		MOSI <= '0';
		
		wait for SCK_period; 
		MOSI <= '0';
		
		wait for SCK_period; 
		MOSI <= '1';
		

		wait for SCK_period; 
		
		
		
			--Amp
    
		
		MOSI <= '0';
		
		wait for SCK_period; 
		MOSI <= '0';
		
		wait for SCK_period; 
		MOSI <= '0';
		
		wait for SCK_period; 
		MOSI <= '0';
		
		wait for SCK_period; 
		MOSI <= '0';
		
		wait for SCK_period; 
		MOSI <= '0';
		
		wait for SCK_period; 
		MOSI <= '1';
		
		wait for SCK_period; 
		MOSI <= '0';
		

		wait for SCK_period; 
		
		
		
		
			--Freq
    
		
		MOSI <= '0';
		
		wait for SCK_period; 
		MOSI <= '0';
		
		wait for SCK_period; 
		MOSI <= '0';
		
		wait for SCK_period; 
		MOSI <= '0';
		
		wait for SCK_period; 
		MOSI <= '0';
		
		wait for SCK_period; 
		MOSI <= '0';
		
		wait for SCK_period; 
		MOSI <= '1';
		
		wait for SCK_period; 
		MOSI <= '1';
		

		wait for SCK_period; 
		
		
		
		
			--CRC 1

		
		MOSI <= '0';
		
		wait for SCK_period; 
		MOSI <= '0';
		
		wait for SCK_period; 
		MOSI <= '0';
		
		wait for SCK_period; 
		MOSI <= '0';
		
		wait for SCK_period; 
		MOSI <= '0';
		
		wait for SCK_period; 
		MOSI <= '0';
		
		wait for SCK_period; 
		MOSI <= '0';
		
		wait for SCK_period; 
		MOSI <= '0';
		

		wait for SCK_period; 
		
		
		
		
		--CRC 2
    
		
		MOSI <= '0';
		
		wait for SCK_period; 
		MOSI <= '0';
		
		wait for SCK_period; 
		MOSI <= '0';
		
		wait for SCK_period; 
		MOSI <= '0';
		
		wait for SCK_period; 
		MOSI <= '0';
		
		wait for SCK_period; 
		MOSI <= '0';
		
		wait for SCK_period; 
		MOSI <= '0';
		
		wait for SCK_period; 
		MOSI <= '0';
		

		wait for SCK_period; 
		wait;
   end process;

END;