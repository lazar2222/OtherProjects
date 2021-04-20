library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use ieee.math_real.all;
use work.Modules.all;
use work.Parameters.all;
use work.Functions.all;

entity OutputConditioner is
	port(
		I: in std_logic;
		L: in std_logic;
		prog: in std_logic;
		clk: in std_logic;
		O: out std_logic
	);
end entity;

architecture rtl of OutputConditioner is
	signal S: std_logic; 
begin
process(clk)
begin
	if rising_edge(clk) and prog='1' then
		S <= L;
	end if;
end process;

process(I,S)
begin
	if S='1' then
		O<= not I;
	else
		O<= I;
	end if;
end process;
end rtl;