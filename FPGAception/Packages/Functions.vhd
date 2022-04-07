library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use ieee.math_real.all;
use work.Parameters.all;

package Functions is
	
	function LUTCount(Inputs: integer; Layers: integer) return integer;
	function CalcInterconnectInputs(Inputs: integer) return integer;
	
end Functions;

package body Functions is
		function LUTCount(Inputs: integer; Layers: integer) return integer is
			variable res: integer := 0;
			variable cnt: integer := 1;
		begin
			for i in 1 to Layers loop
				res := res+cnt;
				cnt:= cnt*Inputs;
			end loop;
			return res;
		end LUTCount;
		
		function CalcInterconnectInputs(Inputs: integer) return integer is
		begin
			if Inputs /= 0 then
				return Inputs;
			else
				return (InputsPerBank*InputBanks)+(HybridsPerBank*HybridBanks)+(MemoryBitsPerBank*MemoryBanks);
			end if;
		end CalcInterconnectInputs;
end Functions;