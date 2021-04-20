library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use ieee.math_real.all;
use work.Modules.all;
use work.Parameters.all;
use work.Functions.all;

entity Main is
end Main;

architecture Main of Main is

signal S: std_logic_vector(3 downto 0) := (others => '0');
signal Pat: std_logic_vector(15 downto 0) := (others => '0');
signal prog: std_logic := '0';
signal memPat: std_logic := '0';
signal memProg: std_logic := '0';
signal clk: std_logic := '0';
signal O: std_logic := '0';

constant clk_period : time := 10 ns;

begin

l:MLU port map(S,Pat,prog,memPat,memProg,clk,O);

process
begin
	  clk <= '0';
	  wait for clk_period/2; 
	  clk <= '1';
	  wait for clk_period/2;
end process;

process
begin
wait for 5 ns;

Pat<="01010101010101010";
prog<='1';
wait for clk_period;
prog<='0';
for i in 0 to 15 loop
   	S<=std_logic_vector(to_unsigned(i,4));
	wait for 10 ns;
end loop;

Pat<="10101010110101010";
prog<='1';
wait for clk_period;
prog<='0';
for i in 0 to 15 loop
   	S<=std_logic_vector(to_unsigned(i,4));
	wait for 10 ns;
end loop;

Pat<="11011111100000010";
prog<='1';
wait for clk_period;
prog<='0';
for i in 0 to 15 loop
   	S<=std_logic_vector(to_unsigned(i,4));
	wait for 10 ns;
end loop;

wait;
end process;

end Main;