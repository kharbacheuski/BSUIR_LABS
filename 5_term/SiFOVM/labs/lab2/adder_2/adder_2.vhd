entity adder_2 is
  port (a1, b1, a2, b2 : in  bit;
        c2, s2, s1     : out bit);
end adder_2;
 
architecture structure of adder_2 is

  component add1
    port (a1, b1 : in  bit;
          c1, s1 : out bit);
  end component;

  component add2
    port(c1, a2, b2 : in  bit;
         c2, s2     : out bit);
  end component;

  signal c1 : bit;
begin
  circ1 : add1
    port map (a1, b1, c1, s1);
  circ2 : add2
    port map (c1, a2, b2, c2, s2);
end structure;
