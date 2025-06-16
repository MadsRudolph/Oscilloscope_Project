
LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
 
-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--USE ieee.numeric_std.ALL;
 
ENTITY FULL_BENCH IS
END FULL_BENCH;
 
ARCHITECTURE behavior OF FULL_BENCH IS 
 
    -- Component Declaration for the Unit Under Test (UUT)
 
    COMPONENT SigGenTop
    PORT(
         BTN3 : IN  std_logic;
         BTN1 : IN  std_logic;
         Clk : IN  std_logic;
         MOSI : IN  std_logic;
         SClk : IN  std_logic;
         SSnot : IN  std_logic;
         An : OUT  std_logic_vector(3 downto 0);
         Cat : OUT  std_logic_vector(7 downto 0);
         LD : OUT  std_logic_vector(7 downto 0);
         PWMOut : INOUT  std_logic
        );
    END COMPONENT;
    

   --Inputs
   signal BTN3 : std_logic := '0';
   signal Clk : std_logic := '0';
   signal MOSI : std_logic := '0';
   signal SClk : std_logic := '0';
   signal SSnot : std_logic := '1';
	signal BTN1 : std_logic := '0';

	--BiDirs
   signal PWMOut : std_logic;

 	--Outputs
   signal An : std_logic_vector(3 downto 0);
   signal Cat : std_logic_vector(7 downto 0);
   signal LD : std_logic_vector(7 downto 0);

	signal dataTB  : std_logic_vector(7 downto 0);   -- Clock period definitions

   -- Clock period definitions
   constant Clk_period : time := 10 ns;
   constant SClk_period : time := clk_period*4;
 
BEGIN
 
	-- Instantiate the Unit Under Test (UUT)
   uut: SigGenTop PORT MAP (
          BTN3 => BTN3,
          Clk => Clk,
          MOSI => MOSI,
          SClk => SClk,
          SSnot => SSnot,
          An => An,
          Cat => Cat,
          LD => LD,
          PWMOut => PWMOut,
 			 BTN1 => BTN1
        );

   -- Clock process definitions
   Clk_process :process
   begin
		Clk <= '1';
		wait for Clk_period/2;
		Clk <= '0';
		wait for Clk_period/2;
   end process;

   -- Stimulus process
   stim_proc: process
   begin		
      -- hold reset state for 100 ns.
      wait for 100 ns;	

      wait for Clk_period*10;

      -- insert stimulus here 
BTN3 <= '1';

wait for sclk_period; 

BTN3 <= '0';  
-- SEND SYNC BYTE
	

wait for sclk_period; 
	
		dataTB <= "01010101";
		wait for sclk_period;

		SSnot <= '0';
		for i in 0 to 7 loop
            mosi <= dataTB(i);
            SCLK <= '0';
            wait for 2*sclk_period / 2;
            SCLK <= '1';  -- Data is valid on rising edge
            wait for 2*sclk_period / 2;
      end loop;
		

		SSnot <= '1';
      sclk <= '0';
		wait for 2*sclk_period;
		
		
		-- SEND ADDR BYTE AAMP
		
		dataTB <= "00000001";
		wait for sclk_period;

		SSnot <= '0';
		for i in 0 to 7 loop
            mosi <= dataTB(i);
            SCLK <= '0';
            wait for 2*sclk_period / 2;
            SCLK <= '1';  -- Data is valid on rising edge
            wait for 2*sclk_period / 2;
      end loop;




		SSnot <= '1';
      sclk <= '0';
		wait for 2*sclk_period;
		
		-- SEND DATA BYTE
		
		dataTB <= "10000000";
		wait for sclk_period;

		SSnot <= '0';
		for i in 0 to 7 loop
            mosi <= dataTB(i);
            SCLK <= '0';
            wait for 2*sclk_period / 2;
            SCLK <= '1';  -- Data is valid on rising edge
            wait for 2*sclk_period / 2;
      end loop;
		
		
		SSnot <= '1';
      sclk <= '0';
		wait for 2*sclk_period*2;		
		-- SEND CHECKSUM BYTE
		
		dataTB <= "11010100";
		wait for sclk_period;

		SSnot <= '0';
		for i in 0 to 7 loop
            mosi <= dataTB(i);
            SCLK <= '0';
            wait for 2*sclk_period / 2;
            SCLK <= '1';  -- Data is valid on rising edge
            wait for 2*sclk_period / 2;
      end loop;
		
		
		SSnot <= '1';
      sclk <= '0';
		wait for 2*sclk_period;






		-- SEND SYNC BYTE 2

		dataTB <= "01010101";
		wait for sclk_period;

		SSnot <= '0';
		for i in 0 to 7 loop
            mosi <= dataTB(i);
            SCLK <= '0';
            wait for 2*sclk_period / 2;
            SCLK <= '1';  -- Data is valid on rising edge
            wait for 2*sclk_period / 2;
      end loop;
		

		SSnot <= '1';
      sclk <= '0';
		wait for 2*sclk_period;
		
		
		-- SEND ADDR BYTE 2 FREQ
		
		dataTB <= "00000010";
		wait for sclk_period;

		SSnot <= '0';
		for i in 0 to 7 loop
            mosi <= dataTB(i);
            SCLK <= '0';
            wait for 2*sclk_period / 2;
            SCLK <= '1';  -- Data is valid on rising edge
            wait for 2*sclk_period / 2;
      end loop;




		SSnot <= '1';
      sclk <= '0';
		wait for 2*sclk_period;
		
		-- SEND DATA BYTE 2
		
		dataTB <= "10001010";
		wait for sclk_period;

		SSnot <= '0';
		for i in 0 to 7 loop
            mosi <= dataTB(i);
            SCLK <= '0';
            wait for 2*sclk_period / 2;
            SCLK <= '1';  -- Data is valid on rising edge
            wait for 2*sclk_period / 2;
      end loop;

		SSnot <= '1';
      sclk <= '0';
		wait for 2*sclk_period*2;
		
		-- SEND CHECKSUM BYTE 2
		dataTB <= "11011101";
		wait for sclk_period;

		SSnot <= '0';
		for i in 0 to 7 loop
            mosi <= dataTB(i);
            SCLK <= '0';
            wait for 2*sclk_period / 2;
            SCLK <= '1';  -- Data is valid on rising edge
            wait for 2*sclk_period / 2;
      end loop;
		
		SSnot <= '1';
      sclk <= '0';
		wait for 2*sclk_period;
		
		
		
		
		-- SEND SYNC BYTE 3
		dataTB <= "01010101";
		wait for sclk_period;

		SSnot <= '0';
		for i in 0 to 7 loop
            mosi <= dataTB(i);
            SCLK <= '0';
            wait for 2*sclk_period / 2;
            SCLK <= '1';  -- Data is valid on rising edge
            wait for 2*sclk_period / 2;
      end loop;
		

		SSnot <= '1';
      sclk <= '0';
		wait for 2*sclk_period;
		
		
		-- SEND ADDR BYTE 3 SHAPE
		
		dataTB <= "00000011";
		wait for sclk_period;

		SSnot <= '0';
		for i in 0 to 7 loop
            mosi <= dataTB(i);
            SCLK <= '0';
            wait for 2*sclk_period / 2;
            SCLK <= '1';  -- Data is valid on rising edge
            wait for 2*sclk_period / 2;
      end loop;




		SSnot <= '1';
		wait for 2*sclk_period;
		
		-- SEND DATA BYTE 3 
		
		dataTB <= "10011010";
		SCLK <= '1';
		wait for sclk_period;

		SSnot <= '0';
		for i in 0 to 7 loop
            mosi <= dataTB(i);
            SCLK <= '0';
            wait for 2*sclk_period / 2;
            SCLK <= '1';  -- Data is valid on rising edge
            wait for 2*sclk_period / 2;
      end loop;

		SSnot <= '1';
      sclk <= '0';
		wait for 2*sclk_period*2;		
		-- SEND CHECKSUM BYTE 3
		
		dataTB <= "11001100";
		wait for sclk_period;

		SSnot <= '0';
		for i in 0 to 7 loop
            mosi <= dataTB(i);
            SCLK <= '0';
            wait for 2*sclk_period / 2;
            SCLK <= '1';  -- Data is valid on rising edge
            wait for 2*sclk_period / 2;
      end loop;
		
		SSnot <= '1';
      sclk <= '0';
		wait for 2*sclk_period;


		dataTB <= "01010101";
		wait for sclk_period;

		SSnot <= '0';
		for i in 0 to 7 loop
            mosi <= dataTB(i);
            SCLK <= '0';
            wait for 2*sclk_period / 2;
            SCLK <= '1';  -- Data is valid on rising edge
            wait for 2*sclk_period / 2;
      end loop;
		

		SSnot <= '1';
      sclk <= '0';
		wait for 2*sclk_period;

      wait;
   end process;

END;
