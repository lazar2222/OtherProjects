library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use ieee.math_real.all;
use work.Modules.all;
use work.Parameters.all;
use work.Functions.all;

entity FPGAProgram is
	port(
		O: out Program
	);
end entity;

architecture rtl of FPGAProgram is
	constant Z: std_logic_vector(ProgrammerArchitecture-1 downto 0) := (others=>'0');
	signal Prog: program := (others=>Z);
begin

	--program starts here
	Prog(2)<=   x"7F";
	Prog(6)<=   x"03";
	Prog(7)<=   x"FF";
	Prog(8)<=   x"03";
	Prog(10)<=  x"F0";
	Prog(13)<=  x"ED";
	Prog(14)<=  x"F0";
	Prog(17)<=  x"9F";
	Prog(18)<=  x"F0";
	Prog(21)<=  x"FB";
	Prog(22)<=  x"F0";
	Prog(25)<=  x"6D";
	Prog(26)<=  x"F0";
	Prog(29)<=  x"45";
	Prog(30)<=  x"F0";
	Prog(33)<=  x"71";
	Prog(34)<=  x"F0";
	Prog(37)<=  x"7C";
	Prog(74)<=  x"F0";
	Prog(77)<=  x"F0";
	Prog(78)<=  x"F0";
	Prog(81)<=  x"F0";
	Prog(82)<=  x"F0";
	Prog(85)<=  x"F8";
	Prog(86)<=  x"F0";
	Prog(89)<=  x"F8";
	Prog(107)<= x"AC";
	Prog(108)<= x"E4";
	Prog(109)<= x"8A";
	Prog(110)<= x"0C";
	Prog(111)<= x"AC";
	Prog(112)<= x"71";
	Prog(113)<= x"8A";
	Prog(114)<= x"0C";
	Prog(115)<= x"AC";
	Prog(116)<= x"5C";
	Prog(117)<= x"8A";
	Prog(118)<= x"0C";
	Prog(119)<= x"AC";
	Prog(120)<= x"E4";
	Prog(121)<= x"8A";
	Prog(122)<= x"0C";
	Prog(123)<= x"AC";
	Prog(124)<= x"71";
	Prog(125)<= x"8A";
	Prog(126)<= x"0C";
	Prog(127)<= x"AC";
	Prog(128)<= x"5C";
	Prog(129)<= x"8A";
	Prog(130)<= x"0C";
	Prog(171)<= x"07";
	Prog(179)<= x"13";
	Prog(180)<= x"14";
	Prog(181)<= x"15";
	Prog(188)<= x"13";
	Prog(189)<= x"14";
	Prog(190)<= x"15";
	Prog(197)<= x"13";
	Prog(198)<= x"14";
	Prog(199)<= x"15";
	Prog(206)<= x"13";
	Prog(207)<= x"14";
	Prog(208)<= x"15";
	Prog(215)<= x"13";
	Prog(216)<= x"14";
	Prog(217)<= x"15";
	Prog(224)<= x"13";
	Prog(225)<= x"14";
	Prog(226)<= x"15";
	Prog(233)<= x"13";
	Prog(234)<= x"14";
	Prog(235)<= x"15";
	Prog(334)<= x"01";
	Prog(342)<= x"01";
	Prog(343)<= x"08";
	Prog(351)<= x"01";
	Prog(352)<= x"09";
	Prog(389)<= x"10";
	Prog(390)<= x"11";
	Prog(391)<= x"12";
	Prog(392)<= x"10";
	Prog(393)<= x"0B";
	Prog(394)<= x"0A";
	Prog(395)<= x"1F";
	Prog(396)<= x"0B";
	Prog(397)<= x"0A";
	Prog(398)<= x"10";
	Prog(399)<= x"11";
	Prog(400)<= x"12";
	Prog(401)<= x"11";
	Prog(402)<= x"0B";
	Prog(403)<= x"0A";
	Prog(404)<= x"1F";
	Prog(405)<= x"0B";
	Prog(406)<= x"0A";
	Prog(407)<= x"10";
	Prog(408)<= x"11";
	Prog(409)<= x"12";
	Prog(410)<= x"12";
	Prog(411)<= x"0B";
	Prog(412)<= x"0A";
	Prog(413)<= x"1F";
	Prog(414)<= x"0B";
	Prog(415)<= x"0A";
	Prog(416)<= x"10";
	Prog(417)<= x"11";
	Prog(418)<= x"12";
	Prog(419)<= x"10";
	Prog(420)<= x"0B";
	Prog(421)<= x"0A";
	Prog(422)<= x"1F";
	Prog(423)<= x"0B";
	Prog(424)<= x"0A";
	Prog(425)<= x"10";
	Prog(426)<= x"11";
	Prog(427)<= x"12";
	Prog(428)<= x"11";
	Prog(429)<= x"0B";
	Prog(430)<= x"0A";
	Prog(431)<= x"1F";
	Prog(432)<= x"0B";
	Prog(433)<= x"0A";
	Prog(434)<= x"10";
	Prog(435)<= x"11";
	Prog(436)<= x"12";
	Prog(437)<= x"12";
	Prog(438)<= x"0B";
	Prog(439)<= x"0A";
	Prog(440)<= x"1F";
	Prog(441)<= x"0B";
	Prog(442)<= x"0A";
	--program ends here

	O<=Prog;
end rtl;