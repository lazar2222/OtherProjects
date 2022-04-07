library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use ieee.math_real.all;

package Parameters is
	
	constant InputsPerBank: integer :=8;
	constant InputBanks: integer :=1;
	constant InputConditioning: integer :=1;
	
	constant HybridsPerBank: integer :=8;
	constant HybridBanks: integer :=1;
	constant HybridConditioning: integer :=1;
	
	constant MemoryBitsPerBank: integer :=8;
	constant MemoryBanks: integer :=2;
	
	constant OutputsPerBank: integer :=8;
	constant OutputBanks: integer :=2;
	constant OutputConditioning: integer :=1;
	
	constant LUTInputs: integer :=3;
	constant LSLICELayers: integer :=2;
	constant MSLICELayers: integer :=2;
	
	constant InterconnectInputs: integer := 0; --Zero for automatic
	constant InterconnectsPerBlock: integer :=1;
	constant InterconnectBlocksPerBank: integer :=8;
	
	constant LSLICEPerBank: integer := 8;
	constant MSLICEPerBank: integer := 8;
	
	constant ProgrammerArchitecture: integer := 8;
	
end Parameters;