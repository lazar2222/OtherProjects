library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use ieee.math_real.all;
use work.Modules.all;
use work.Parameters.all;
use work.Functions.all;

entity InterconnectUnit is
	port(
		I: in std_logic_vector(ActualInterconnectInputs-1 downto 0);
		L: in std_logic_vector(InterconnectSelects-1 downto 0);
		prog: in std_logic;
		clk: in std_logic;
		O: out std_logic
	);
end entity;

architecture rtl of InterconnectUnit is
	signal S: std_logic_vector(InterconnectSelects-1 downto 0); 
	signal FI: std_logic_vector((2**InterconnectSelects)-1 downto 0):=(others=>'0');
begin
	FI(ActualInterconnectInputs-1 downto 0)<=I;
	mux: GenericMUX generic map(InterconnectSelects) port map(FI,S,O);
process(clk)
begin
	if rising_edge(clk) and prog='1' then
		S <= L;
	end if;
end process;
end rtl;