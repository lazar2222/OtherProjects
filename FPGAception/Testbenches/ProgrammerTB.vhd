library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use ieee.math_real.all;
use work.Modules.all;
use work.Parameters.all;
use work.Functions.all;

entity Programmer is
end Programmer;

architecture Programmer of Programmer is

constant clk_period: time := 10 ns;

signal clk: std_logic;
signal P: Program;
signal Addr: std_logic_vector(ProgammerAddressSize-1 downto 0);
signal Data: std_logic_vector(ProgrammerArchitecture-1 downto 0);
signal Load: std_logic;
signal prog: std_logic_vector(ProgSize-1 downto 0);
signal L: std_logic_vector(ProgrammerArchitecture-1 downto 0);
signal I: std_logic_vector(((InputsPerBank*InputBanks*2)+(HybridsPerBank*HybridBanks))-1 downto 0) := (others => '0');
signal O: std_logic_vector((OutputsPerBank*OutputBanks*2)-1 downto 0);

begin

FP: FPGAProgram port map (P);
FPR: FPGAProgrammer port map (P,clk,Addr,Data,Load);
FPI: FPGAProgrammingInterface port map (Addr,Data,Load,L,prog);
FPL: FPGALogic port map (I,L,prog,clk,O);

process
begin
	  clk <= '0';
	  wait for clk_period/2; 
	  clk <= '1';
	  wait for clk_period/2;
end process;

process
begin

wait;
end process;

end Programmer;