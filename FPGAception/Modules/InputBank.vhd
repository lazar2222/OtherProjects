library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use ieee.math_real.all;
use work.Modules.all;
use work.Parameters.all;
use work.Functions.all;

entity InputBank is
	port(
		I: in std_logic_vector((InputsPerBank*2)-1 downto 0);
		L: in std_logic_vector(InputsPerBank-1 downto 0);
		conditionerL: in std_logic_vector(InputsPerBank-1 downto 0);
		prog: in std_logic;
		conditionerProg: in std_logic_vector(1 downto 0);
		clk: in std_logic;
		O: out std_logic_vector(InputsPerBank-1 downto 0)
	);
end entity;

architecture rtl of InputBank is 
	signal CI: std_logic_vector(InputsPerBank-1 downto 0);
begin
	genIN: for C in 0 to InputsPerBank-1 generate
		genCOND: if InputConditioning = 1 generate
			ISX: InputSelector port map(I((2*C)+1 downto (2*C)),L(C),prog,clk,CI(C));
			ICX: InputConditioner port map(CI(C),conditionerL(C),conditionerProg,clk,O(C));
		end generate;
		genNCOND: if InputConditioning = 0 generate
			ISX: InputSelector port map(I((2*C)+1 downto (2*C)),L(C),prog,clk,O(C));
		end generate;
	end generate;
end rtl;