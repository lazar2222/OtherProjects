library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use ieee.math_real.all;
use work.Modules.all;
use work.Parameters.all;
use work.Functions.all;

entity InputConditioner is
	port(
		I: in std_logic;
		L: in std_logic;
		prog: in std_logic_vector (1 downto 0);
		clk: in std_logic;
		O: out std_logic
	);
end entity;

architecture rtl of InputConditioner is
	signal S: std_logic_vector(1 downto 0);
	signal R: std_logic;
	signal REout: std_logic;
begin
	re: RisingEdge port map(R,clk,REout);
process(clk)
begin
	if rising_edge(clk) then
		if prog(0) = '1' then
			S(0) <= L;
		end if;
		if prog(1) = '1' then
			S(1) <= L;
		end if;
	end if;
end process;

process(I,S,REout,R)
begin
	if S(1)='1' then
		R<= not I;
	else
		R<= I;
	end if;
	if S(0)='1' then
		O<=REout;
	else
		O<=R;
	end if;
end process;
end rtl;