library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use ieee.math_real.all;
use work.Modules.all;
use work.Parameters.all;
use work.Functions.all;

entity LLayer is
	generic(
		size: integer := 4
	);
	port(
		I: in std_logic_vector((size*LUTInputs)-1 downto 0);
		L: in std_logic_vector((2**LUTInputs)-1 downto 0);
		prog: in std_logic_vector(size-1 downto 0);
		clk: in std_logic;
		O: out std_logic_vector(size-1 downto 0)
	);
end entity;

architecture rtl of LLayer is
begin
	genLUT: for n in 0 to size-1 generate
		lutX: LUT port map(I(((n+1)*LUTInputs)-1 downto n*LUTInputs),L,prog(n),clk,O(n));
	end generate;
end rtl;