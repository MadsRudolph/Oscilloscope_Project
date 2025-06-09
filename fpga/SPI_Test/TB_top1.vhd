
LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
 
ENTITY TB IS
END TB;
 
ARCHITECTURE behavior OF TB IS 
 
    -- Component Declaration for the Unit Under Test (UUT)
 
    COMPONENT Skifte_reg_til_Parallel
    PORT(
         SCK : IN  std_logic;
         MOSI : IN  std_logic;
         RESET : IN  std_logic;
         SPIdat : OUT  std_logic_vector(7 downto 0);
			SSnot : IN std_logic
        );
    END COMPONENT;
 
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
   uut: Skifte_reg_til_Parallel PORT MAP (
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
		SSnot <= '1';
		
		wait for SCK_period; 
		
		
		
		-- sync 2 
    
		 
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
		MOSI <= '0';
		
		
		wait for SCK_period; 
		
		
		
		-- length 1 
    
		 
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
		MOSI <= '0';
		
		
		wait for SCK_period; 
		
		
		
		
		
			
		-- length 2
    
		 
		wait for SCK_period;
		
		SSnot <= '0';
		
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
		MOSI <= '1';
		
		wait for SCK_period;
		SSnot <= '0';
		
		wait for SCK_period; 
		
		
		
			--Type
    
		 
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
		MOSI <= '0';
		

		
		wait for SCK_period; 
		
		
			--Shape
    
		 
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
		MOSI <= '1';
		

		wait for SCK_period; 
		
		
		
			--Amp
    
		 
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
		MOSI <= '0';
		

		wait for SCK_period; 
		
		
		
		
			--Freq
    
		 
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
		MOSI <= '1';
		

		wait for SCK_period; 
		
		
		
		
			--CRC 1
    
		 
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
		MOSI <= '0';
		

		wait for SCK_period; 
		
		
		
		
		--CRC 
    
		 
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
		MOSI <= '0';
		

		wait for SCK_period; 
		
		
		
	
		
		wait;
   end process;

END;