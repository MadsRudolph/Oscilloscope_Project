
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity std_1bit_reg is
    Port ( reset : in  STD_LOGIC;
           clk : in  STD_LOGIC;
           enable : in  STD_LOGIC;
           data_in : in  STD_LOGIC;
           data_out : out  STD_LOGIC);
end std_1bit_reg;

architecture Behavioral of std_1bit_reg is
begin
    process (reset, clk)
    begin
        if reset = '1' then
            data_out <= '0' ;  -- Reset the register to 0
        elsif rising_edge(clk) then
            if enable = '1' then
                data_out <= data_in;  -- Load data_in into data_out on clock edge
            end if;
        end if;
    end process;
end Behavioral;