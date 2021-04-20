library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use ieee.math_real.all;
use work.Modules.all;
use work.Parameters.all;
use work.Functions.all;

entity LBank is
	port(
		I: in std_logic_vector(InputPerLogicBank-1 downto 0);
		L: in std_logic_vector((2**LUTInputs)-1 downto 0);
		prog: in std_logic_vector(ProgPerLogicBank-1 downto 0);
		clk: in std_logic;
		O: out std_logic_vector(LSLICEPerBank-1 downto 0)
	);
end entity;

architecture rtl of LBank is
begin
	genLS: for n in 0 to LSLICEPerBank-1 generate
		LSX: LSLICE port map(
			I(((LUTInputs**LSLICELayers)*(n+1))-1 downto (LUTInputs**LSLICELayers)*n),
			L,
			prog((LUTCount(LUTInputs,LSLICELayers)*(n+1))-1 downto LUTCount(LUTInputs,LSLICELayers)*n),
			clk,
			O(n)
		);
	end generate;
end rtl;