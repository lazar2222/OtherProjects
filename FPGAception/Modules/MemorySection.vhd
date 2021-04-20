library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use ieee.math_real.all;
use work.Modules.all;
use work.Parameters.all;
use work.Functions.all;

entity MemorySection is
	port(
		I: in std_logic_vector((MemoryLogicBanks*InputPerMemoryBank)-1 downto 0);
		L: in std_logic_vector((2**LUTInputs)-1 downto 0);
		Fprog: in std_logic_vector((MemoryLogicBanks*(ProgPerMemoryBank+1))-1 downto 0);
		clk: in std_logic;
		O: out std_logic_vector((MSLICEPerBank*MemoryLogicBanks)-1 downto 0)
	);
end entity;

architecture rtl of MemorySection is
	signal prog: std_logic_vector((MemoryLogicBanks*ProgPerMemoryBank)-1 downto 0);
	signal memProg: std_logic_vector(MemoryLogicBanks-1 downto 0);
begin
	genMB:for n in 0 to MemoryLogicBanks-1 generate
		MBX: MBank port map(
			I(((n+1)*InputPerMemoryBank)-1 downto n*InputPerMemoryBank),
			L,
			prog(((n+1)*ProgPerMemoryBank)-1 downto n*ProgPerMemoryBank),
			L(7 downto 0),
			memProg(n),
			clk,
			O((n+1)*MSLICEPerBank-1 downto n*MSLICEPerBank)
		);
	end generate;
		prog<=Fprog((MemoryLogicBanks*ProgPerMemoryBank)-1 downto 0);
	memProg<=Fprog((MemoryLogicBanks*(ProgPerMemoryBank+1))-1 downto MemoryLogicBanks*ProgPerMemoryBank);
end rtl;