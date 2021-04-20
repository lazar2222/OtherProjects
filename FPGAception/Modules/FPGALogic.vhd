library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use ieee.math_real.all;
use work.Modules.all;
use work.Parameters.all;
use work.Functions.all;

entity FPGALogic is
	port(
		I: in std_logic_vector(((InputsPerBank*InputBanks*2)+(HybridsPerBank*HybridBanks))-1 downto 0);
		L: in std_logic_vector(ProgrammerArchitecture-1 downto 0);
		prog: in std_logic_vector(ProgSize-1 downto 0);
		clk: in std_logic;
		O: out std_logic_vector((OutputsPerBank*OutputBanks*2)-1 downto 0)
	);
end entity;

architecture rtl of FPGALogic is
	signal OutputBus: std_logic_vector((OutputsPerBank*OutputBanks)-1 downto 0);
	signal LogicBus: std_logic_vector((LogicBanks*InputPerLogicBank)-1 downto 0);
	
	signal MemoryOutBus: std_logic_vector((MemoryBitsPerBank*MemoryBanks)-1 downto 0);
	signal MemoryInBus: std_logic_vector((MemoryLogicBanks*InputPerMemoryBank)-1 downto 0);
	
	signal HybridMOutBus: std_logic_vector((HybridsPerBank*HybridBanks)-1 downto 0);
	signal HybridMInBus: std_logic_vector((HybridBanks*InputPerMemoryBank)-1 downto 0);
	signal HybridIOutBus: std_logic_vector((HybridsPerBank*HybridBanks)-1 downto 0);	
	signal InputBus: std_logic_vector((InputsPerBank*InputBanks)-1 downto 0);
	
	signal InterconnectInBus: std_logic_vector((MemoryBitsPerBank*MemoryBanks)+(InputsPerBank*InputBanks)+(HybridsPerBank*HybridBanks)-1 downto 0);
	signal InterconnectOutBus: std_logic_vector((OutputsPerBank*OutputBanks*LUTInputs**LSLICELayers)+(MemoryBitsPerBank*MemoryBanks*LUTInputs**MSLICELayers)+(HybridsPerBank*HybridBanks*LUTInputs**MSLICELayers)-1 downto 0);
	
	signal OSprog: std_logic_vector(outputBanks*2-1 downto 0);
	signal ISprog: std_logic_vector(InputBanks*3-1 downto 0);
	signal HSprog: std_logic_vector(HybridBanks*3-1 downto 0);
	signal LSprog: std_logic_vector((LogicBanks*ProgPerLogicBank)-1 downto 0);
	signal HMSprog: std_logic_vector((HybridBanks*(ProgPerMemoryBank+1))-1 downto 0);
	signal MSprog: std_logic_vector((MemoryLogicBanks*(ProgPerMemoryBank+1))-1 downto 0);
	signal FIprog: std_logic_vector(InterconnectBanks*InterconnectBlocksPerBank-1 downto 0);
begin
	OS: OutputSection port map
	(
		OutputBus,
		L,
		OSprog,
		clk,
		O
	);
	
	LS: LogicSection port map
	(
		LogicBus,
		L,
		LSprog,
		clk,
		OutputBus
	);
	
	HMS: HybridMemorySection port map
	(
		HybridMInBus,
		L,
		HMSprog,
		clk,
		HybridMOutBus
	);
	
	MS: MemorySection port map
	(
		MemoryInBus,
		L,
		MSprog,
		clk,
		MemoryOutBus
	);
	
	FI: FullInterconnect port map
	(
		InputBus,
		HybridIOutBus,
		MemoryOutBus,
		L((InterconnectsPerBlock*InterconnectSelects)-1 downto 0),
		FIprog,
		clk,
		LogicBus,
		HybridMInBus,
		MemoryInBus
	);
	
	InS: InputSection port map
	(
		I((InputsPerBank*InputBanks*2)-1 downto 0),
		L,
		ISprog,
		clk,
		InputBus
	);
	
	HS: HybridSection port map
	(
		I(((InputsPerBank*InputBanks*2)+(HybridsPerBank*HybridBanks))-1 downto (InputsPerBank*InputBanks*2)),
		HybridMOutBus,
		L,
		HSprog,
		clk,
		HybridIOutBus
	);
	
	OSprog<=prog(OSend-1 downto 0);
	ISprog<=prog(ISend-1 downto OSend);
	HSprog<=prog(HSend-1 downto ISend);
	LSprog<=prog(LSend-1 downto HSend);
	HMSprog<=prog(HMSend-1 downto LSend);
	MSprog<=prog(MSend-1 downto HMSend);
	FIprog<=prog(ProgSize-1 downto MSend);
end rtl;