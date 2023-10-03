entity add1 is
  port (a1, b1 : in  bit;
        c1, s1 : out bit);
end add1;
 
architecture struct_1 of add1 is
begin
  s1 <= ((a1 and (not b1)) or ((not a1) and b1));
  c1 <= a1 and b1;
end struct_1;
