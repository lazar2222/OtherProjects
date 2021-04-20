library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use ieee.math_real.all;
use work.Modules.all;
use work.Parameters.all;
use work.Functions.all;

entity InterconnectBank is
	port(
		I: in std_logic_vector(ActualInterconnectInputs-1 downto 0);
		L: in std_logic_vector((InterconnectsPerBlock*InterconnectSelects)-1 downto 0);
		prog: in std_logic_vector(InterconnectBlocksPerBank-1 downto 0);
		clk: in std_logic;
		O: out std_logic_vector((InterconnectsPerBlock*InterconnectBlocksPerBank)-1 downto 0)
	);
end entity;

architecture rtl of InterconnectBank is
begin
	genIB: for n in 0 to InterconnectBlocksPerBank-1 generate
		IBX: InterconnectBlock port map(I,L,prog(n),clk,O(((n+1)*InterconnectsPerBlock)-1 downto n*InterconnectsPerBlock));
	end generate;
end rtl;