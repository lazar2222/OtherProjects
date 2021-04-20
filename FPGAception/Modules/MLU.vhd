library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use ieee.math_real.all;
use work.Modules.all;
use work.Parameters.all;
use work.Functions.all;

entity MLU is
	port(
		I: in std_logic_vector(LUTInputs-1 downto 0);
		L: in std_logic_vector((2**LUTInputs)-1 downto 0);
		prog: in std_logic;
		memL: in std_logic;
		memProg: in std_logic;
		clk: in std_logic;
		O: out std_logic
	);
end entity;

architecture rtl of MLU is
	signal MF:std_logic;
	signal S:std_logic;
	signal LI:std_logic_vector(LUTInputs-1 downto 0);
	signal LO:std_logic;
begin
	lut0: LUT port map(LI,L,prog,clk,LO);
process(clk)
begin
	if rising_edge(clk) then
		if memProg = '1' then
			MF <= memL;
		end if;
		S<=LO;
	end if;
end process;

process(I,S,MF,LO)
begin 
	if MF='1' then
		--LI<=S&I(LUTInputs-2 downto 0);
		LI<=I;
		O<=S;
	else
		LI<=I;
		O<=LO;
	end if;
end process;
end rtl;