library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use ieee.math_real.all;
use work.Modules.all;
use work.Parameters.all;
use work.Functions.all;

entity RE is
end RE;

architecture RE of RE is

signal I: std_logic := '0';
signal clk: std_logic := '0';
signal O: std_logic := '0';

constant clk_period : time := 10 ns;

begin

l:RisingEdge port map(I,clk,O);

process
begin
	  clk <= '0';
	  wait for clk_period/2; 
	  clk <= '1';
	  wait for clk_period/2;
end process;

process
begin
wait for 103 ns;

I<='1';

wait for 153 ns;

I<='0';

wait for 325 ns;

I<='1';

wait for 18 ns;

I<='0';

wait;
end process;

end RE;