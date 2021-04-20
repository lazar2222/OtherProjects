library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use ieee.math_real.all;
use work.Modules.all;
use work.Parameters.all;
use work.Functions.all;

entity FPGAProgrammer is
	port(
		Prog: in Program;
		clk: in std_logic;
		Addr: out std_logic_vector(ProgammerAddressSize-1 downto 0);
		Data: out std_logic_vector(ProgrammerArchitecture-1 downto 0);
		Load: out std_logic
	);
end entity;

architecture rtl of FPGAProgrammer is
	signal cnt: integer :=0;
begin
	process(clk)
	begin
		if cnt < ProgSize then
			Load<='1';
			if rising_edge(clk) then
				Addr<=std_logic_vector(to_unsigned(cnt, ProgammerAddressSize));
				Data<=Prog(cnt);
				cnt<=cnt+1;
			end if;
		elsif cnt <=Progsize then
			Load<='1';
			cnt<=cnt+1;
		else
			Load<='0';
		end if;
	end process;
end rtl;