--------------------------------------------------------------------------------
-- Company: 
-- Engineer:
--
-- Create Date:   15:37:01 06/10/2025
-- Design Name:   
-- Module Name:   C:/Users/s240324/Oscilloscope_Project/fpga/SPI_Test/TB_snot.vhd
-- Project Name:  SPI_Test
-- Target Device:  
-- Tool versions:  
-- Description:   
-- 
-- VHDL Test Bench Created by ISE for module: TimingComponent
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
 
ENTITY TB_snot IS
END TB_snot;
 
ARCHITECTURE behavior OF TB_snot IS 
 
    -- Component Declaration for the Unit Under Test (UUT)
 
    COMPONENT TimingComponent
    PORT(
         SSNot : IN  std_logic;
         Clk : IN  std_logic;
         Reset : IN  std_logic;
         DataReady : OUT  std_logic
        );
    END COMPONENT;
    

   --Inputs
   signal SSNot : std_logic := '0';
   signal SClk : std_logic := '0';
   signal Clk : std_logic := '0';
   signal Reset : std_logic := '0';

 	--Outputs
   signal DataReady : std_logic;

   -- Clock period definitions
   constant Clk_period : time := 10 ns;
 
BEGIN
 
	-- Instantiate the Unit Under Test (UUT)
   uut: TimingComponent PORT MAP (
          SSNot => SSNot,
          Clk => Clk,
          Reset => Reset,
          DataReady => DataReady
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
		
		
		SSnot <= '1';
		
		wait for 5*Clk_period; 
		Reset <= '1'; 
		
		wait for 5*Clk_period; 
		
		Reset <= '0';

		wait for 5*Clk_period;

		SSnot <= '0'; 


		wait for 3*Clk_period; 
		
		SSnot <= '1';
		
		wait for 5*Clk_period; 

      wait;
   end process;

END;
