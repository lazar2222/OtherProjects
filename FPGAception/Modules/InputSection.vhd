library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use ieee.math_real.all;
use work.Modules.all;
use work.Parameters.all;
use work.Functions.all;

entity InputSection is
	port(
		I: in std_logic_vector((InputsPerBank*InputBanks*2)-1 downto 0);
		L: in std_logic_vector(InputsPerBank-1 downto 0);
		Fprog: in std_logic_vector(InputBanks*3-1 downto 0);
		clk: in std_logic;
		O: out std_logic_vector((InputsPerBank*InputBanks)-1 downto 0)
	);
end entity;

architecture rtl of InputSection is
	signal prog: std_logic_vector(InputBanks-1 downto 0);
	signal conditionerProg: std_logic_vector((InputBanks*2)-1 downto 0);
begin
	genIB:for n in 0 to InputBanks-1 generate
		IBX: InputBank port map(
			I(((n+1)*2*InputsPerBank)-1 downto n*2*InputsPerBank),
			L,
			L,
			prog(n),
			conditionerProg((2*n)+1 downto 2*n),
			clk,
			O(((n+1)*InputsPerBank)-1 downto n*InputsPerBank)
		);
	end generate;
	prog<=Fprog(InputBanks-1 downto 0);
	conditionerProg<=Fprog(InputBanks*3-1 downto InputBanks);
end rtl;