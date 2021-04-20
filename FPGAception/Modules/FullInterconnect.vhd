library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use ieee.math_real.all;
use work.Modules.all;
use work.Parameters.all;
use work.Functions.all;

entity FullInterconnect is
	port(
		I: in std_logic_vector((InputsPerBank*InputBanks)-1 downto 0);
		H: in std_logic_vector((HybridsPerBank*HybridBanks)-1 downto 0);
		M: in std_logic_vector((MemoryBitsPerBank*MemoryBanks)-1 downto 0);
		L: in std_logic_vector((InterconnectsPerBlock*InterconnectSelects)-1 downto 0);
		prog: in std_logic_vector(InterconnectBanks*InterconnectBlocksPerBank-1 downto 0);
		clk: in std_logic;
		OL: out std_logic_vector((InputPerLogicBank*LogicBanks)-1 downto 0);
		OH: out std_logic_vector((InputPerMemoryBank*HybridMemoryBanks)-1 downto 0);
		OM: out std_logic_vector((InputPerMemoryBank*MemoryLogicBanks)-1 downto 0)
	);
end entity;

architecture rtl of FullInterconnect is
	signal InterconnectInBus: std_logic_vector(ActualInterconnectInputs-1 downto 0);
	signal InterconnectOutBus: std_logic_vector(InterconnectOutputs-1 downto 0);
begin
	genICB:for n in 0 to InterconnectBanks-1 generate
		ICBX: InterconnectBank port map(
			InterconnectInBus,
			L,
			prog(((n+1)*InterconnectBlocksPerBank)-1 downto n*InterconnectBlocksPerBank),
			clk,
			InterconnectOutBus(((n+1)*(InterconnectBlocksPerBank*InterconnectsPerBlock))-1 downto n*(InterconnectBlocksPerBank*InterconnectsPerBlock))
		);
	end generate;
	
	InterconnectInBus<=M&H&I;
	OL<=InterconnectOutBus((InputPerLogicBank*LogicBanks)-1 downto 0);
	OH<=InterconnectOutBus((InputPerLogicBank*LogicBanks)+(InputPerMemoryBank*HybridMemoryBanks)-1 downto (InputPerLogicBank*LogicBanks));
	OM<=InterconnectOutBus((InputPerLogicBank*LogicBanks)+(InputPerMemoryBank*HybridMemoryBanks)+(InputPerMemoryBank*MemoryLogicBanks)-1 downto (InputPerLogicBank*LogicBanks)+(InputPerMemoryBank*HybridMemoryBanks));
end rtl;