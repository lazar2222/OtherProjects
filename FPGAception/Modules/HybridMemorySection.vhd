library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use ieee.math_real.all;
use work.Modules.all;
use work.Parameters.all;
use work.Functions.all;

entity HybridMemorySection is
	port(
		I: in std_logic_vector((HybridBanks*InputPerMemoryBank)-1 downto 0);
		L: in std_logic_vector((2**LUTInputs)-1 downto 0);
		Fprog: in std_logic_vector((HybridBanks*(ProgPerMemoryBank+1))-1 downto 0);
		clk: in std_logic;
		O: out std_logic_vector((MSLICEPerBank*HybridMemoryBanks)-1 downto 0)
	);
end entity;

architecture rtl of HybridMemorySection is
		signal prog: std_logic_vector((HybridBanks*ProgPerMemoryBank)-1 downto 0);
		signal memProg: std_logic_vector(HybridBanks-1 downto 0);
begin
	genHB:for n in 0 to HybridMemoryBanks-1 generate
		HBX: MBank port map(
			I(((n+1)*InputPerMemoryBank)-1 downto n*InputPerMemoryBank),
			L,
			prog(((n+1)*ProgPerMemoryBank)-1 downto n*ProgPerMemoryBank),
			L(7 downto 0),
			memProg(n),
			clk,
			O((n+1)*MSLICEPerBank-1 downto n*MSLICEPerBank)
		);
	end generate;
	prog<=Fprog((HybridBanks*ProgPerMemoryBank)-1 downto 0);
	memProg<=Fprog((HybridBanks*(ProgPerMemoryBank+1))-1 downto HybridBanks*ProgPerMemoryBank);
end rtl;