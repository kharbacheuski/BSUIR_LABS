----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 20.09.2024 16:14:39
-- Design Name: 
-- Module Name: DFF - Behavioral
-- Project Name: 
-- Target Devices: 
-- Tool Versions: 
-- Description: 
-- 
-- Dependencies: 
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
-- 
----------------------------------------------------------------------------------


library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity DFF is
    Port ( D : in STD_LOGIC;
           R : in STD_LOGIC;
           C : in STD_LOGIC;
           Q : out STD_LOGIC);
end DFF;

architecture Behavioral of DFF is

begin

    process(C)
    begin
        if(rising_edge(C)) then
            Q <= D;
        end if;
        if(R = '1') then
            Q <= '0';
        end if;
    end process;    

end Behavioral;
