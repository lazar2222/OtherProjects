library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use ieee.math_real.all;
use work.Modules.all;
use work.Parameters.all;
use work.Functions.all;

entity OutputBank is
	port(
		I: in std_logic_vector(OutputsPerBank-1 downto 0);
		L: in std_logic_vector(OutputsPerBank-1 downto 0);
		conditionerL: in std_logic_vector(OutputsPerBank-1 downto 0);
		prog: in std_logic;
		conditionerProg: in std_logic;
		clk: in std_logic;
		O: out std_logic_vector((OutputsPerBank*2)-1 downto 0)
	);
end entity;

architecture rtl of OutputBank is 
	signal CO: std_logic_vector(OutputsPerBank-1 downto 0);
begin
	genOUT: for C in 0 to OutputsPerBank-1 generate
		genCOND: if OutputConditioning = 1 generate
			OCX: OutputConditioner port map(I(C),conditionerL(C),conditionerProg,clk,CO(C));
			OSX: OutputSelector port map(CO(C),L(C),prog,clk,O((2*C)+1 downto (2*C)));
		end generate;
		genNCOND: if OutputConditioning = 0 generate
			OSX: OutputSelector port map(I(C),L(C),prog,clk,O((2*C)+1 downto (2*C)));
		end generate;
	end generate;
end rtl;