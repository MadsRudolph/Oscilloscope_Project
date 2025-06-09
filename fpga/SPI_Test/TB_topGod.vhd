--------------------------------------------------------------------------------
-- Company: 
-- Engineer:
--
-- Create Date:   15:27:23 06/09/2025
-- Design Name:   
-- Module Name:   C:/Users/s240324/Oscilloscope_Project/fpga/SPI_Test/TB_topGod.vhd
-- Project Name:  SPI_Test
-- Target Device:  
-- Tool versions:  
-- Description:   
-- 
-- VHDL Test Bench Created by ISE for module: SigGenSPIControl
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
 
ENTITY TB_topGod IS
END TB_topGod;
 
ARCHITECTURE behavior OF TB_topGod IS 
 
    -- Component Declaration for the Unit Under Test (UUT)
 
    COMPONENT SigGenSPIControl
    PORT(
         CLK : IN  std_logic;
         Reset : IN  std_logic;
         SCK : IN  std_logic;
         MOSI : IN  std_logic;
         SSnot : IN  std_logic;
         Shape : OUT  std_logic_vector(7 downto 0);
         Amp : OUT  std_logic_vector(7 downto 0);
         Freq : OUT  std_logic_vector(7 downto 0);
         SigEN : OUT  std_logic
        );
    END COMPONENT;
    

   --Inputs
   signal CLK : std_logic := '0';
   signal Reset : std_logic := '0';
   signal SCK : std_logic := '0';
   signal MOSI : std_logic := '0';
   signal SSnot : std_logic := '0';

 	--Outputs
   signal Shape : std_logic_vector(7 downto 0);
   signal Amp : std_logic_vector(7 downto 0);
   signal Freq : std_logic_vector(7 downto 0);
   signal SigEN : std_logic;

   -- Clock period definitions
   constant CLK_period : time := 10 ns;
 
BEGIN
 
	-- Instantiate the Unit Under Test (UUT)
   uut: SigGenSPIControl PORT MAP (
          CLK => CLK,
          Reset => Reset,
          SCK => SCK,
          MOSI => MOSI,
          SSnot => SSnot,
          Shape => Shape,
          Amp => Amp,
          Freq => Freq,
          SigEN => SigEN
        );

   -- Clock process definitions
   CLK_process :process
   begin
		CLK <= '0';
		wait for CLK_period/2;
		CLK <= '1';
		wait for CLK_period/2;
   end process;
 

   -- Stimulus process
   stim_proc: process
   begin		
      -- hold reset state for 100 ns.
      wait for 100 ns;	

      wait for CLK_period*10;

      -- insert stimulus here 

      wait;
   end process;

END;
