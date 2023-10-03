library ieee;
USE ieee.std_logic_1164.all;
USE ieee.std_logic_signed.all;
USE ieee.std_logic_arith.all;

entity mult_2 is
  port (s1, s0, r1, r0 : in  bit;
        t3, t2, t1, t0 : out bit);
end mult_2;
 
architecture structure of mult_2 is
  component
    add1 port (b1, b2 : in  bit;
               c1, s1 : out bit);
  end component;
 
  signal p1, p2, p3, p4 : bit;
 
begin
  t0 <= r0 and s0;                      
  p2 <= r0 and s1;                      
  p1 <= r1 and s0;                      
  p4 <= r1 and s1;                      
 
  circ1 : add1 port map (p1, p2, p3, t1);
  circ2 : add1 port map (p3, p4, t3, t2);
end structure;
