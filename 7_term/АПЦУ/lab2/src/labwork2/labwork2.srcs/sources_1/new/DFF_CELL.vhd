----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 20.09.2024 16:23:21
-- Design Name: 
-- Module Name: DFF_CELL - Behavioral
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

entity DFF_CELL is
    Port ( CLK : in STD_LOGIC;
           CLR : in STD_LOGIC;
           SER : in STD_LOGIC;
           SH : in STD_LOGIC;
           ENTRY : in STD_LOGIC;
           Q_out : out STD_LOGIC);
end DFF_CELL;

architecture Behavioral of DFF_CELL is

  signal D : std_logic;
  signal C : std_logic;
  signal R : std_logic;
  signal Q : std_logic;
  
  component DFF
  port(
      D : in std_logic;
      C : in std_logic;
      R : in std_logic;
      Q : out std_logic
  );
  end component;

begin

    C <= CLK;
    R <= CLR;
    
  dff_inst: DFF port map (
      D => D,
      C => C,
      R => R,
      Q => Q
    );
    
    D <= (((SER) and (SH)) or ((not SH) and (ENTRY)));
        
    Q_out <= Q;

end Behavioral;
