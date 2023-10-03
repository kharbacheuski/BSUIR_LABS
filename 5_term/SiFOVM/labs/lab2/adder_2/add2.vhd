entity add2 is
  port (c1, a2, b2 : in  bit;
        c2, s2     : out bit);
end add2;

architecture struct_1 of add2 is
begin
  s2 <= ((not c1) and (not a2) and b2) or
        ((not c1) and a2 and (not b2)) or
        (c1 and (not a2) and (not b2)) or
        (a2 and b2 and c1);
  c2 <= (a2 and c1) or (b2 and c1) or (a2 and b2);
end struct_1;
