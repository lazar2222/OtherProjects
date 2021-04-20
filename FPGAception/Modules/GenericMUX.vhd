library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use ieee.math_real.all;
use work.Modules.all;
use work.Parameters.all;
use work.Functions.all;

entity GenericMUX is
	generic
	(
		size: integer := 2
	);
	port
	(
		I:in std_logic_vector((2**size)-1 downto 0);
		S:in std_logic_vector(size-1 downto 0);
		O:out std_logic
	);
end entity;

architecture rtl of GenericMUX is
begin
	process(I,S)
	begin
		O<=I(to_integer(unsigned(S)));
	end process;
end rtl;