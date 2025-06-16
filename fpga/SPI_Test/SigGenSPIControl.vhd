----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    15:35:16 06/06/2025 
-- Design Name: 
-- Module Name:    SigGenSPIControl - Behavioral 
-- Project Name: 
-- Target Devices: 
-- Tool versions: 
-- Description: 
--
-- Dependencies: 
--
-- Revision: 
-- Revision 0.01 - File Created
-- Additional Comments: 
--
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity SigGenSPIControl is
    Port ( CLK : in  STD_LOGIC;
           Reset : in  STD_LOGIC;
           SClk : in  STD_LOGIC;
           MOSI : in  STD_LOGIC;
           SSnot : in  STD_LOGIC;
           Shape : out  STD_LOGIC_VECTOR (1 downto 0);
           Amp : out  STD_LOGIC_VECTOR (7 downto 0);
           Freq : out  STD_LOGIC_VECTOR (7 downto 0);
			  LD: out STD_LOGIC;
           SigEN : inout  STD_LOGIC); -- inout da den bruges som et internt signal også
end SigGenSPIControl;

architecture Behavioral of SigGenSPIControl is

signal SPIdat: STD_LOGIC_VECTOR (7 downto 0);
signal DataReady: STD_LOGIC;


begin

-- Clock Divider to generate display-friendly clock
    ProtokolBlok: entity work.ProtokolBlok 
        port map (
            Reset     => Reset,
            Clk      => Clk,
				Amp		=> Amp,
				Freq		=> Freq,
				Shape 	=> Shape,
				DataReady => DataReady,
				SPIdat => SPIdat,
				SigEN => SigEN,
				LD => LD
        );

    --7-Segment Display Controller
    SkifteReg: entity work.Skifte_reg_til_Parallel 
        port map (
            Reset => Reset,
				SPIdat => SPIdat,
				MOSI => MOSI,
				SClk => SClk
				);
				
		TimingComponent: entity work.TimingComponent 
        port map (
            Reset => Reset,
            Clk => Clk,
				DataReady => DataReady,
				SSnot => SSnot
				);

end Behavioral;

