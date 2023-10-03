library ieee;
USE ieee.std_logic_1164.all;
USE ieee.std_logic_signed.all;
USE ieee.std_logic_arith.all;

entity add1 is --name of object
port (b1, b2 : in BIT;
	  c1, s1 : out BIT);
end add1;

architecture func of add1 is
begin
s1<=((b1 and (not b2)) or ((not b1) and b2));
c1<= b1 and b2;
end func;
