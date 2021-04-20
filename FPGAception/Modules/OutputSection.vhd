library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use ieee.math_real.all;
use work.Modules.all;
use work.Parameters.all;
use work.Functions.all;

entity OutputSection is
	port(
		I: in std_logic_vector((OutputsPerBank*OutputBanks)-1 downto 0);
		L: in std_logic_vector(OutputsPerBank-1 downto 0);
		Fprog: in std_logic_vector(outputBanks*2-1 downto 0);
		clk: in std_logic;
		O: out std_logic_vector((OutputsPerBank*OutputBanks*2)-1 downto 0)
	);
end entity;

architecture rtl of OutputSection is
		signal prog: std_logic_vector(outputBanks-1 downto 0);
		signal conditionerProg: std_logic_vector(outputBanks-1 downto 0);
begin
	genOB:for n in 0 to outputBanks-1 generate
		OBX: OutputBank port map(
			I(((n+1)*OutputsPerBank)-1 downto n*OutputsPerBank),
			L,
			L,
			prog(n),
			conditionerProg(n),
			clk,
			O(((n+1)*2*OutputsPerBank)-1 downto n*2*OutputsPerBank)
		);
	end generate;
	prog<=Fprog(outputBanks-1 downto 0);
	conditionerProg<=Fprog(outputBanks*2-1 downto outputBanks);
end rtl;