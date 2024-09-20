----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 20.09.2024 16:30:02
-- Design Name: 
-- Module Name: LOAD_SHIFT_REG - Behavioral
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

entity LOAD_SHIFT_REG is
    Port ( SH_in : in STD_LOGIC;
           SER_in : in STD_LOGIC;
           CLK_in : in STD_LOGIC;
           CLK_INH : in STD_LOGIC;
           CLR_in : in STD_LOGIC;
           ENTRY_VEC : in STD_LOGIC_VECTOR (7 downto 0);
           Q_H : out STD_LOGIC);
end LOAD_SHIFT_REG;

architecture Behavioral of LOAD_SHIFT_REG is

  component DFF_CELL
    port(
        CLK : in STD_LOGIC;
        CLR : in STD_LOGIC;
        SER : in STD_LOGIC;
        SH : in STD_LOGIC;
        ENTRY : in STD_LOGIC;
        Q_out : out STD_LOGIC
    );
  end component;

  signal Q_VEC : std_logic_vector(7 downto 0);
  signal CLK_RES : std_logic;
  signal CLR_INV : std_logic;

begin

    CLK_RES <= CLK_in or CLK_INH;
    CLR_INV <= not CLR_in;

    cell_0: DFF_CELL port map (
        CLK => CLK_RES,
        CLR => CLR_INV,
        SER => SER_in,
        SH => SH_in,
        ENTRY => ENTRY_VEC(0),
        Q_out => Q_VEC(0)
    );
    
    cell_1: DFF_CELL port map (
        CLK => CLK_RES,
        CLR => CLR_INV,
        SER => Q_VEC(0),
        SH => SH_in,
        ENTRY => ENTRY_VEC(1),
        Q_out => Q_VEC(1)
    );
    
    cell_2: DFF_CELL port map (
        CLK => CLK_RES,
        CLR => CLR_INV,
        SER => Q_VEC(1),
        SH => SH_in,
        ENTRY => ENTRY_VEC(2),
        Q_out => Q_VEC(2)
    );
    
    cell_3: DFF_CELL port map (
        CLK => CLK_RES,
        CLR => CLR_INV,
        SER => Q_VEC(2),
        SH => SH_in,
        ENTRY => ENTRY_VEC(3),
        Q_out => Q_VEC(3)
    );
    
    cell_4: DFF_CELL port map (
        CLK => CLK_RES,
        CLR => CLR_INV,
        SER => Q_VEC(3),
        SH => SH_in,
        ENTRY => ENTRY_VEC(4),
        Q_out => Q_VEC(4)
    );
    
    cell_5: DFF_CELL port map (
        CLK => CLK_RES,
        CLR => CLR_INV,
        SER => Q_VEC(4),
        SH => SH_in,
        ENTRY => ENTRY_VEC(5),
        Q_out => Q_VEC(5)
    );
    
    cell_6: DFF_CELL port map (
        CLK => CLK_RES,
        CLR => CLR_INV,
        SER => Q_VEC(5),
        SH => SH_in,
        ENTRY => ENTRY_VEC(6),
        Q_out => Q_VEC(6)
    );
    
    cell_7: DFF_CELL port map (
        CLK => CLK_RES,
        CLR => CLR_INV,
        SER => Q_VEC(6),
        SH => SH_in,
        ENTRY => ENTRY_VEC(7),
        Q_out => Q_VEC(7)
    );
    
    Q_H <= Q_VEC(7);

end Behavioral;
