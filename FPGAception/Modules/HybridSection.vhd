library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use ieee.math_real.all;
use work.Modules.all;
use work.Parameters.all;
use work.Functions.all;

entity HybridSection is
	port(
		I: in std_logic_vector((HybridsPerBank*HybridBanks)-1 downto 0);
		M: in std_logic_vector((HybridsPerBank*HybridBanks)-1 downto 0);
		L: in std_logic_vector(HybridsPerBank-1 downto 0);
		Fprog: in std_logic_vector(HybridBanks*3-1 downto 0);
		clk: in std_logic;
		O: out std_logic_vector((HybridsPerBank*HybridBanks)-1 downto 0)
	);
end entity;

architecture rtl of HybridSection is
	signal HybridIInBus: std_logic_vector((HybridsPerBank*HybridBanks*2)-1 downto 0);
	signal prog: std_logic_vector(HybridBanks-1 downto 0);
	signal conditionerProg: std_logic_vector((HybridBanks*2)-1 downto 0);
begin
	genHIIB:for n in 0 to(HybridsPerBank*HybridBanks)-1 generate
		HybridIInBus(2*n)<=I(n);
		HybridIInBus((2*n)+1)<=M(n);
	end generate;
	
	genHBI:for n in 0 to HybridBanks-1 generate
		HBIX: InputBank port map(
			HybridIInBus(((n+1)*2*HybridsPerBank)-1 downto n*2*HybridsPerBank),
			L,
			L,
			prog(n),
			conditionerProg((2*n)+1 downto 2*n),
			clk,
			O(((n+1)*HybridsPerBank)-1 downto n*HybridsPerBank)
		);
	end generate;
	prog<=Fprog(HybridBanks-1 downto 0);
	conditionerProg<=Fprog(HybridBanks*3-1 downto HybridBanks);
end rtl;