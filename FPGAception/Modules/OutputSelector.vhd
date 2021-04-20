library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use ieee.math_real.all;
use work.Modules.all;
use work.Parameters.all;
use work.Functions.all;

entity OutputSelector is
	port(
		I: in std_logic;
		L: in std_logic;
		prog: in std_logic;
		clk: in std_logic;
		O: out std_logic_vector(1 downto 0)
	);
end entity;

architecture rtl of OutputSelector is
	signal S: std_logic_vector(0 downto 0); 
begin
	dmux: GenericDEMUX generic map(1) port map(I,S,O);
process(clk)
begin
	if rising_edge(clk) and prog='1' then
		S(0) <= L;
	end if;
end process;
end rtl;