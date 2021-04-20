library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use ieee.math_real.all;
use work.Modules.all;
use work.Parameters.all;
use work.Functions.all;

entity FPGAProgrammingInterface is
	port(
		Addr: in std_logic_vector(ProgammerAddressSize-1 downto 0);
		Data: in std_logic_vector(ProgrammerArchitecture-1 downto 0);
		Load: in std_logic;
		L: out std_logic_vector(ProgrammerArchitecture-1 downto 0);
		prog: out std_logic_vector(ProgSize-1 downto 0)
	);
end entity;

architecture rtl of FPGAProgrammingInterface is
	
begin
	L<=Data;
	process(Addr,Load)
	begin
		prog<=(others=>'0');
		prog(to_integer(unsigned(Addr)))<=Load;
	end process;
end rtl;