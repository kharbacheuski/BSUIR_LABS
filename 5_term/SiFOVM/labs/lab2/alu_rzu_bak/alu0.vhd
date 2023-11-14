library ieee;
USE ieee.std_logic_1164.all;
USE ieee.std_logic_signed.all;
USE ieee.std_logic_arith.all;

entity alu0 is
port (ctrl: in std_logic_vector(2 downto 0);
    r, s: in std_logic_vector (3 downto 0);
      c0: in std_logic;
    f_out: out std_logic_vector(3 downto 0);
    c4, ovr, z, f3: out std_logic);
end alu0;

architecture alu of alu0 is
signal tmp: std_logic_vector (4 downto 0);
signal ri, si: std_logic_vector (4 downto 0);


begin
calc: process
begin
ri(4) <= '0';
si(4) <= '0';
ri(3 downto 0) <= r;
si (3 downto 0) <= s;
if ctrl = "000" then tmp <= ri+si+c0;
elsif ctrl = "001" then tmp <= si-ri-1+c0;
elsif ctrl = "010" then tmp <= ri-si-1+c0;
elsif ctrl = "011" then tmp <= ri or si;
elsif ctrl = "100" then tmp <= ri and si;
elsif ctrl = "101" then tmp <= (not ri) and si;
elsif ctrl = "110" then tmp <= ri xor si;
elsif ctrl = "111" then tmp <= not (ri xor si);
end if;

f_out <= tmp (3 downto 0);
end process calc;

f3_p: process(tmp)
begin
f3 <= tmp(3);
end process;

ovr_p: process(tmp)
begin
ovr <= tmp(3) xor tmp(2);
end process;

c4_p: process(tmp)
begin
c4 <= tmp(4);
end process;

z_p: process(tmp)
begin
z <= (not tmp(0) and not tmp(1) and not tmp(2) and not tmp(3)); 
end process;
end alu;
