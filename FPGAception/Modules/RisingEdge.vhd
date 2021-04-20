library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use ieee.math_real.all;
use work.Modules.all;
use work.Parameters.all;
use work.Functions.all;

entity RisingEdge is
	port(
		I: in std_logic;
		clk: in std_logic;
		O: out std_logic
	);
end entity;

architecture rtl of RisingEdge is
	signal P: std_logic;
	signal Q: std_logic;
begin
process(clk)
begin
	if rising_edge(clk) then
		Q<=P;
		P<=I;
	end if;
end process;

O<= ((not Q) and P);

end rtl;