library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use ieee.math_real.all;
use work.Modules.all;
use work.Parameters.all;
use work.Functions.all;

entity InterconnectBlock is
	port(
		I: in std_logic_vector(ActualInterconnectInputs-1 downto 0);
		L: in std_logic_vector((InterconnectsPerBlock*InterconnectSelects)-1 downto 0);
		prog: in std_logic;
		clk: in std_logic;
		O: out std_logic_vector(InterconnectsPerBlock-1 downto 0)
	);
end entity;

architecture rtl of InterconnectBlock is
begin
	genIU: for n in 0 to InterconnectsPerBlock-1 generate
		IUX: InterconnectUnit port map(I,L(((n+1)*InterconnectSelects)-1 downto n*InterconnectSelects),prog,clk,O(n));
	end generate;
end rtl;