library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use ieee.math_real.all;
use work.Modules.all;
use work.Parameters.all;
use work.Functions.all;

entity LogicSection is
	port(
		I: in std_logic_vector((LogicBanks*InputPerLogicBank)-1 downto 0);
		L: in std_logic_vector((2**LUTInputs)-1 downto 0);
		prog: in std_logic_vector((LogicBanks*ProgPerLogicBank)-1 downto 0);
		clk: in std_logic;
		O: out std_logic_vector((LSLICEPerBank*LogicBanks)-1 downto 0)
	);
end entity;

architecture rtl of LogicSection is
	
begin
	genLB:for n in 0 to LogicBanks-1 generate
		LBX: LBank port map(
			I(((n+1)*InputPerLogicBank)-1 downto n*InputPerLogicBank),
			L,
			prog(((n+1)*ProgPerLogicBank)-1 downto n*ProgPerLogicBank),
			clk,
			O((n+1)*LSLICEPerBank-1 downto n*LSLICEPerBank)
		);
	end generate;
end rtl;