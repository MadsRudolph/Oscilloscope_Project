--------------------------------------------------------------------------------
-- Company: 
-- Engineer:
--
-- Create Date:   14:31:43 06/04/2025
-- Design Name:   
-- Module Name:   /home/Andreas/Oscilloscope_Project/fpga/SPI_Test/TB.vhd
-- Project Name:  SPI_Test
-- Target Device:  
-- Tool versions:  
-- Description:   
-- 
-- VHDL Test Bench Created by ISE for module: Skifte_reg_til_Parallel
-- 
-- Dependencies:
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
--
-- Notes: 
-- This testbench has been automatically generated using types std_logic and
-- std_logic_vector for the ports of the unit under test.  Xilinx recommends
-- that these types always be used for the top-level I/O of a design in order
-- to guarantee that the testbench will bind correctly to the post-implementation 
-- simulation model.
--------------------------------------------------------------------------------
LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
 
-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--USE ieee.numeric_std.ALL;
 
ENTITY TB IS
END TB;
 
ARCHITECTURE behavior OF TB IS 
 
    -- Component Declaration for the Unit Under Test (UUT)
 
    COMPONENT Skifte_reg_til_Parallel
    PORT(
         SCK : IN  std_logic;
         MOSI : IN  std_logic;
         RESET : IN  std_logic;
         LED : OUT  std_logic_vector(7 downto 0);
			SSnot : IN std_logic
        );
    END COMPONENT;
 
   --Inputs
   signal SCK : std_logic := '0';
   signal MOSI : std_logic := '0';
   signal RESET : std_logic := '0';
	signal SSnot : std_logic := '1';

 	--Outputs
   signal LED : std_logic_vector(7 downto 0);

   -- Clock period definitions
	constant SCK_period : time := 10 ns; 
BEGIN
 
	-- Instantiate the Unit Under Test (UUT)
   uut: Skifte_reg_til_Parallel PORT MAP (
          SCK => SCK,
          MOSI => MOSI,
          RESET => RESET,
          LED => LED,
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
		MOSI <= '1';
		
		wait for SCK_period; 
		MOSI <= '1';
		
		wait for SCK_period; 
		MOSI <= '1';
		
		wait for SCK_period; 
		MOSI <= '1';
		
		wait for SCK_period; 
		MOSI <= '1';
		
		wait for 2*SCK_period;
		SSnot <= '1';
		
		wait for SCK_period; 
		
		
		wait;
   end process;

END;