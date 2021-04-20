library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use ieee.math_real.all;
use work.Modules.all;
use work.Parameters.all;
use work.Functions.all;

entity MSLICE is
	port(
		I: in std_logic_vector((LUTInputs**MSLICELayers)-1 downto 0);
		L: in std_logic_vector((2**LUTInputs)-1 downto 0);
		prog: in std_logic_vector(LUTCount(LUTInputs,MSLICELayers)-1 downto 0);
		memL: in std_logic;
		memProg: in std_logic;
		clk: in std_logic;
		O: out std_logic
	);
end entity;

architecture rtl of MSLICE is
	type net is array (0 to MSLICELayers-1) of std_logic_vector((LUTInputs**MSLICELayers)-1 downto 0);
	signal local: net;
begin
	genLayer: for n in 1 to MSLICELayers-1 generate
		constant CLayer: integer := LUTInputs**n;
	begin
		LLayerX: LLayer generic map(Clayer) port map(local(n)((Clayer*LUTInputs)-1 downto 0),L,prog(LUTCount(LUTInputs,n+1)-1 downto LUTCount(LUTInputs,n)),clk,local(n-1)(Clayer-1 downto 0));
	end generate;
	local(MSLICELayers-1)<=I;
	lut0: MLU port map(local(0)(LUTInputs-1 downto 0),L,prog(0),memL,memProg,clk,O);
end rtl;