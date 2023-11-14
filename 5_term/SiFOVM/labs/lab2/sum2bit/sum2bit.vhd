entity sum2bit is
port (b1,b2: in BIT;
s, c: out BIT);
end sum2bit;
architecture func of sum2bit is
begin
s <= b1 xor b2;
c <= b1 and b2;
end func;
