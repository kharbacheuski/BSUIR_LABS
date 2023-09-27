entity and2 is
	port(
		x1,x2: in BIT;
		y: out Bit
	);
end and2;

architecture func of and2 is
	begin
		y <= x1 and x2;
end func;
		
