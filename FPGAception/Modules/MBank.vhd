library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use ieee.math_real.all;
use work.Modules.all;
use work.Parameters.all;
use work.Functions.all;

entity MBank is
	port(
		I: in std_logic_vector(((LUTInputs**MSLICELayers)*MSLICEPerBank)-1 downto 0);
		L: in std_logic_vector((2**LUTInputs)-1 downto 0);
		prog: in std_logic_vector((MSLICEPerBank*LUTCount(LUTInputs,MSLICELayers))-1 downto 0);
		memL: in std_logic_vector(MSLICEPerBank-1 downto 0);
		memProg: in std_logic;
		clk: in std_logic;
		O: out std_logic_vector(MSLICEPerBank-1 downto 0)
	);
end entity;

architecture rtl of MBank is
begin
	genLS: for n in 0 to MSLICEPerBank-1 generate
		LSX: MSLICE port map(
			I(((LUTInputs**MSLICELayers)*(n+1))-1 downto (LUTInputs**MSLICELayers)*n),
			L,
			prog((LUTCount(LUTInputs,MSLICELayers)*(n+1))-1 downto LUTCount(LUTInputs,MSLICELayers)*n),
			memL(n),
			memProg,
			clk,
			O(n)
		);
	end generate;
end rtl;