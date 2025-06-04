
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity SPI_test is
    Port ( sck : in  STD_LOGIC;
           MOSI : in  STD_LOGIC;
           Reset : in  STD_LOGIC;
           Clk : in  STD_LOGIC;
           LED : out  STD_LOGIC_VECTOR (7 downto 0));
end SPI_test;

Q: signal STD_LOGIC_VECTOR (7 downto 0); 

architecture Behavioral of SPI_test is

begin

shift: process (sck, Reset) 
variable ShiftVal: STD_LOGIC_VECTOR(7 downto 0);

begin

if reset = '1' then
ShiftVal := "00000000";


elsif sck'event and sck ='1' then


end Behavioral;

