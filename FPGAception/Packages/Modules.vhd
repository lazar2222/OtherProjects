library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use ieee.math_real.all;
use work.Parameters.all;
use work.Functions.all;

package Modules is
	
	constant ActualInterconnectInputs: integer := CalcInterconnectInputs(InterconnectInputs);
	constant InterconnectSelects: integer := integer(ceil(log2(real(ActualInterconnectInputs))));
	constant LogicBanks: integer := OutputBanks*OutputsPerBank/LSLICEPerBank;
	constant HybridMemoryBanks: integer := HybridBanks*HybridsPerBank/MSLICEPerBank;
	constant MemoryLogicBanks: integer := MemoryBanks*MemoryBitsPerBank/MSLICEPerBank;
	constant ProgPerLogicBank: integer := LSLICEPerBank*LUTCount(LUTInputs,LSLICELayers);
	constant InputPerLogicBank: integer := LSLICEPerBank*LUTInputs**LSLICELayers;
	constant ProgPerMemoryBank: integer := MSLICEPerBank*LUTCount(LUTInputs,MSLICELayers);
	constant InputPerMemoryBank: integer := MSLICEPerBank*LUTInputs**MSLICELayers;
	constant InterconnectOutputs: integer := (InputPerLogicBank*LogicBanks)+(InputPerMemoryBank*MemoryLogicBanks)+(InputPerMemoryBank*HybridMemoryBanks);
	constant InterconnectBanks: integer := InterconnectOutputs/(InterconnectBlocksPerBank*InterconnectsPerBlock);
	constant ProgSize: integer := outputBanks*2+InputBanks*3+HybridBanks*3+(LogicBanks*ProgPerLogicBank)+(HybridBanks*(ProgPerMemoryBank+1))+(MemoryLogicBanks*(ProgPerMemoryBank+1))+InterconnectBanks*InterconnectBlocksPerBank;
	constant OSend: integer := outputBanks*2;
	constant ISend: integer := InputBanks*3+OSend;
	constant HSend: integer := HybridBanks*3+ISend;
	constant LSend: integer := (LogicBanks*ProgPerLogicBank)+HSend;
	constant HMSend: integer := (HybridBanks*(ProgPerMemoryBank+1))+LSend;
	constant MSend: integer := (MemoryLogicBanks*(ProgPerMemoryBank+1))+HMSend;
	constant ProgammerAddressSize: integer := integer(ceil(log2(real(ProgSize))));
	
	type Program is array (0 to ProgSize-1) of std_logic_vector(ProgrammerArchitecture-1 downto 0);
	--type Program is array (0 to 533-1) of std_logic_vector(8-1 downto 0);
	
	component GenericMUX is
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
	end component;
	
	component GenericDEMUX is
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
	end component;
	
	component RisingEdge is
		port(
			I: in std_logic;
			clk: in std_logic;
			O: out std_logic
		);
	end component;
	
	component LUT is
		port(
			I: in std_logic_vector(LUTInputs-1 downto 0);
			L: in std_logic_vector((2**LUTInputs)-1 downto 0);
			prog: in std_logic;
			clk: in std_logic;
			O: out std_logic
		);
	end component;
	
	component MLU is
		port(
			I: in std_logic_vector(LUTInputs-1 downto 0);
			L: in std_logic_vector((2**LUTInputs)-1 downto 0);
			prog: in std_logic;
			memL: in std_logic;
			memProg: in std_logic;
			clk: in std_logic;
			O: out std_logic
		);
	end component;
	
	component LLayer is
		generic(
			size: integer := 4
		);
		port(
			I: in std_logic_vector((size*LUTInputs)-1 downto 0);
			L: in std_logic_vector((2**LUTInputs)-1 downto 0);
			prog: in std_logic_vector(size-1 downto 0);
			clk: in std_logic;
			O: out std_logic_vector(size-1 downto 0)
		);
	end component;
	
	component LSLICE is
		port(
			I: in std_logic_vector((LUTInputs**LSLICELayers)-1 downto 0);
			L: in std_logic_vector((2**LUTInputs)-1 downto 0);
			prog: in std_logic_vector(LUTCount(LUTInputs,LSLICELayers)-1 downto 0);
			clk: in std_logic;
			O: out std_logic
		);
	end component;
	
	component MSLICE is
		port(
			I: in std_logic_vector((LUTInputs**MSLICELayers)-1 downto 0);
			L: in std_logic_vector((2**LUTInputs)-1 downto 0);
			prog: in std_logic_vector(LUTCount(LUTInputs,MSLICELayers)-1 downto 0);
			memL: in std_logic;
			memProg: in std_logic;
			clk: in std_logic;
			O: out std_logic
		);
	end component;
	
	component LBank is
		port(
			I: in std_logic_vector(((LUTInputs**LSLICELayers)*LSLICEPerBank)-1 downto 0);
			L: in std_logic_vector((2**LUTInputs)-1 downto 0);
			prog: in std_logic_vector((LSLICEPerBank*LUTCount(LUTInputs,LSLICELayers)-1) downto 0);
			clk: in std_logic;
			O: out std_logic_vector(LSLICEPerBank-1 downto 0)
		);
	end component;
	
	component MBank is
		port(
			I: in std_logic_vector(((LUTInputs**MSLICELayers)*MSLICEPerBank)-1 downto 0);
			L: in std_logic_vector((2**LUTInputs)-1 downto 0);
			prog: in std_logic_vector((MSLICEPerBank*LUTCount(LUTInputs,MSLICELayers))-1 downto 0);
			memL: in std_logic_vector(MSLICEPerBank-1 downto 0);
			memProg: in std_logic;
			clk: in std_logic;
			O: out std_logic_vector(MSLICEPerBank-1 downto 0)
		);
	end component;
	
	component InputSelector is
		port(
			I: in std_logic_vector(1 downto 0);
			L: in std_logic;
			prog: in std_logic;
			clk: in std_logic;
			O: out std_logic
		);
	end component;
	
	component InputConditioner is
		port(
			I: in std_logic;
			L: in std_logic;
			prog: in std_logic_vector (1 downto 0);
			clk: in std_logic;
			O: out std_logic
		);
	end component;
	
	component InputBank is
		port(
			I: in std_logic_vector((InputsPerBank*2)-1 downto 0);
			L: in std_logic_vector(InputsPerBank-1 downto 0);
			conditionerL: in std_logic_vector(InputsPerBank-1 downto 0);
			prog: in std_logic;
			conditionerProg: in std_logic_vector(1 downto 0);
			clk: in std_logic;
			O: out std_logic_vector(InputsPerBank-1 downto 0)
		);
	end component;
	
	component OutputSelector is
		port(
			I: in std_logic;
			L: in std_logic;
			prog: in std_logic;
			clk: in std_logic;
			O: out std_logic_vector(1 downto 0)
		);
	end component;
	
	component OutputConditioner is
		port(
			I: in std_logic;
			L: in std_logic;
			prog: in std_logic;
			clk: in std_logic;
			O: out std_logic
		);
	end component;
	
	component OutputBank is
		port(
			I: in std_logic_vector(OutputsPerBank-1 downto 0);
			L: in std_logic_vector(OutputsPerBank-1 downto 0);
			conditionerL: in std_logic_vector(OutputsPerBank-1 downto 0);
			prog: in std_logic;
			conditionerProg: in std_logic;
			clk: in std_logic;
			O: out std_logic_vector((OutputsPerBank*2)-1 downto 0)
		);
	end component;
	
	component InterconnectUnit is
		port(
			I: in std_logic_vector(ActualInterconnectInputs-1 downto 0);
			L: in std_logic_vector(InterconnectSelects-1 downto 0);
			prog: in std_logic;
			clk: in std_logic;
			O: out std_logic
		);
	end component;
	
	component InterconnectBlock is
		port(
			I: in std_logic_vector(ActualInterconnectInputs-1 downto 0);
			L: in std_logic_vector((InterconnectsPerBlock*InterconnectSelects)-1 downto 0);
			prog: in std_logic;
			clk: in std_logic;
			O: out std_logic_vector(InterconnectsPerBlock-1 downto 0)
		);
	end component;
	
	component InterconnectBank is
		port(
			I: in std_logic_vector(ActualInterconnectInputs-1 downto 0);
			L: in std_logic_vector((InterconnectsPerBlock*InterconnectSelects)-1 downto 0);
			prog: in std_logic_vector(InterconnectBlocksPerBank-1 downto 0);
			clk: in std_logic;
			O: out std_logic_vector((InterconnectsPerBlock*InterconnectBlocksPerBank)-1 downto 0)
		);
	end component;
	
	component OutputSection is
		port(
			I: in std_logic_vector((OutputsPerBank*OutputBanks)-1 downto 0);
			L: in std_logic_vector(OutputsPerBank-1 downto 0);
			Fprog: in std_logic_vector(outputBanks*2-1 downto 0);
			clk: in std_logic;
			O: out std_logic_vector((OutputsPerBank*OutputBanks*2)-1 downto 0)
		);
	end component;
	
	component InputSection is
		port(
			I: in std_logic_vector((InputsPerBank*InputBanks*2)-1 downto 0);
			L: in std_logic_vector(InputsPerBank-1 downto 0);
			Fprog: in std_logic_vector(InputBanks*3-1 downto 0);
			clk: in std_logic;
			O: out std_logic_vector((InputsPerBank*InputBanks)-1 downto 0)
		);
	end component;
	
	component HybridSection is
		port(
			I: in std_logic_vector((HybridsPerBank*HybridBanks)-1 downto 0);
			M: in std_logic_vector((HybridsPerBank*HybridBanks)-1 downto 0);
			L: in std_logic_vector(HybridsPerBank-1 downto 0);
			Fprog: in std_logic_vector(HybridBanks*3-1 downto 0);
			clk: in std_logic;
			O: out std_logic_vector((HybridsPerBank*HybridBanks)-1 downto 0)
		);
	end component;
	
	component LogicSection is
		port(
			I: in std_logic_vector((LogicBanks*InputPerLogicBank)-1 downto 0);
			L: in std_logic_vector((2**LUTInputs)-1 downto 0);
			prog: in std_logic_vector((LogicBanks*ProgPerLogicBank)-1 downto 0);
			clk: in std_logic;
			O: out std_logic_vector((LSLICEPerBank*LogicBanks)-1 downto 0)
		);
	end component;
	
	component HybridMemorySection is
		port(
			I: in std_logic_vector((HybridBanks*InputPerMemoryBank)-1 downto 0);
			L: in std_logic_vector((2**LUTInputs)-1 downto 0);
			Fprog: in std_logic_vector((HybridBanks*(ProgPerMemoryBank+1))-1 downto 0);
			clk: in std_logic;
			O: out std_logic_vector((MSLICEPerBank*HybridMemoryBanks)-1 downto 0)
		);
	end component;
	
	component MemorySection is
		port(
			I: in std_logic_vector((MemoryLogicBanks*InputPerMemoryBank)-1 downto 0);
			L: in std_logic_vector((2**LUTInputs)-1 downto 0);
			Fprog: in std_logic_vector((MemoryLogicBanks*(ProgPerMemoryBank+1))-1 downto 0);
			clk: in std_logic;
			O: out std_logic_vector((MSLICEPerBank*MemoryLogicBanks)-1 downto 0)
		);
	end component;
	
	component FullInterconnect is
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
	end component;
	
	component FPGALogic is
		port(
			I: in std_logic_vector(((InputsPerBank*InputBanks*2)+(HybridsPerBank*HybridBanks))-1 downto 0);
			L: in std_logic_vector(ProgrammerArchitecture-1 downto 0);
			prog: in std_logic_vector(ProgSize-1 downto 0);
			clk: in std_logic;
			O: out std_logic_vector((OutputsPerBank*OutputBanks*2)-1 downto 0)
		);
	end component;
	
	component FPGAProgrammingInterface is
		port(
			Addr: in std_logic_vector(ProgammerAddressSize-1 downto 0);
			Data: in std_logic_vector(ProgrammerArchitecture-1 downto 0);
			Load: in std_logic;
			L: out std_logic_vector(ProgrammerArchitecture-1 downto 0);
			prog: out std_logic_vector(ProgSize-1 downto 0)
		);
	end component;
	
	component FPGAProgrammer is
		port(
			Prog: in Program;
			clk: in std_logic;
			Addr: out std_logic_vector(ProgammerAddressSize-1 downto 0);
			Data: out std_logic_vector(ProgrammerArchitecture-1 downto 0);
			Load: out std_logic
		);
	end component;
	
	component FPGAProgram is
		port(
			O: out Program
		);
	end component;
	
end Modules;