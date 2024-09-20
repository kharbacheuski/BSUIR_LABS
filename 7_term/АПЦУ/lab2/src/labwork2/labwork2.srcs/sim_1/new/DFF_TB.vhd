----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 06.09.2024 22:27:16
-- Design Name: 
-- Module Name: DFF_TB - Behavioral
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

entity DFF_TB is
--  Port ( );
end DFF_TB;

architecture Behavioral of DFF_TB is

  component DFF
    port(
        D : in std_logic;
        C : in std_logic;
        R : in std_logic;
        Q : out std_logic
    );
  end component;

  signal D : std_logic;
  signal C : std_logic;
  signal R : std_logic;
  signal Q : std_logic;

begin

  mapping: DFF port map (
    D => D,
    C => C,
    R => R,
    Q => Q
  );

  test_case: process
  
  begin
  
    for R_i in std_logic range '0' to '1' loop
        for D_i in std_logic range '0' to '1' loop
            for C_i in std_logic range '0' to '1' loop
                
                C <= C_i;
                D <= D_i;
                R <= R_i;
                
                wait for 10 ns;
            end loop;
        end loop;
    end loop;
  end process;

end Behavioral;
