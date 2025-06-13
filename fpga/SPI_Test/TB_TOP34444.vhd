
LIBRARY ieee;
USE ieee.std_logic_1164.ALL;

 
ENTITY TB_TOP34444 IS
END TB_TOP34444;
 
ARCHITECTURE behavior OF TB_TOP34444 IS 
 
    -- Component Declaration for the Unit Under Test (UUT)
 
    COMPONENT SigGenSPIControl
    PORT(
         CLK : IN  std_logic;
         Reset : IN  std_logic;
         MOSI : IN  std_logic;
         SSnot : IN  std_logic;
         Shape : OUT  std_logic_vector(1 downto 0);
         Amp : OUT  std_logic_vector(7 downto 0);
         Freq : OUT  std_logic_vector(7 downto 0);
         SigEN : OUT  std_logic;
			SClk: IN std_logic
        );
    END COMPONENT;
    

   --Inputs
   signal CLK : std_logic := '0';
   signal Reset : std_logic := '0';
	signal SCLK : std_logic := '1';
   signal MOSI : std_logic := '0';
   signal SSnot : std_logic := '1';

 	--Outputs
   signal Shape : std_logic_vector(1 downto 0);
   signal Amp : std_logic_vector(7 downto 0);
   signal Freq : std_logic_vector(7 downto 0);
   signal SigEN : std_logic;
	
	signal dataTB  : std_logic_vector(7 downto 0);   -- Clock period definitions
	
	
   constant Clk_period : time := 10 ns;
	constant sclk_period : time := clk_period * 4;

 
BEGIN
 
	-- Instantiate the Unit Under Test (UUT)
   uut: SigGenSPIControl PORT MAP (
          CLK => CLK,
          Reset => Reset,
          SClk => SClk,
          MOSI => MOSI,
          SSnot => SSnot,
          Shape => Shape,
          Amp => Amp,
          Freq => Freq,
          SigEN => SigEN
        );

    -- Clock process definitions
   Clk_process :process
   begin
		Clk <= '0';
		wait for Clk_period/2;
		Clk <= '1';
		wait for Clk_period/2;
   end process;
 

   -- Stimulus process
   stim_proc: process
   begin		
      -- hold reset state for 100 ns.
      wait for 100 ns;	

      wait for Clk_period*10;




      -- insert stimulus here 
		
		-- SEND SYNC BYTE
		
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
      sclk <= '1';
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
      sclk <= '1';
		wait for 2*sclk_period;
		
		-- SEND DATA BYTE
		
		dataTB <= "00001010";
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
      sclk <= '1';
		wait for 2*sclk_period*2;		
		-- SEND CHECKSUM BYTE
		
		dataTB <= "01011110";
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
      sclk <= '1';
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
      sclk <= '1';
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
      sclk <= '1';
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
      sclk <= '1';
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
      sclk <= '1';
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
      sclk <= '1';
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
      sclk <= '1';
		wait for 2*sclk_period;
		
		-- SEND DATA BYTE 3 
		
		dataTB <= "10011010";
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
      sclk <= '1';
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
      sclk <= '1';
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
      sclk <= '1';
		wait for 2*sclk_period;
      wait;
   end process;

END;
