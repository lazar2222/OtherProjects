library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use ieee.math_real.all;
use work.Modules.all;
use work.Parameters.all;
use work.Functions.all;

entity GenericDEMUX is
	generic
	(
		size: integer := 1
	);
	port
	(
		I:in std_logic;
		S:in std_logic_vector(size-1 downto 0);
		O:out std_logic_vector((2**size)-1 downto 0)
	);
end entity;

architecture rtl of GenericDEMUX is
begin
	process(I,S)
	begin
		O<=(others=>'0');
		O(to_integer(unsigned(S)))<=I;
	end process;
end rtl;