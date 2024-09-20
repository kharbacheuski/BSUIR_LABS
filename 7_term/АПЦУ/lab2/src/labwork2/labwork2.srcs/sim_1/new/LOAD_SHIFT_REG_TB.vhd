
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity LOAD_SHIFT_REG_TB is
--  Port ( );
end LOAD_SHIFT_REG_TB;

architecture Behavioral of LOAD_SHIFT_REG_TB is

  component LOAD_SHIFT_REG
        port ( 
             SH_in : in STD_LOGIC;
             SER_in : in STD_LOGIC;
             CLK_in : in STD_LOGIC;
             CLK_INH : in STD_LOGIC;
             CLR_in : in STD_LOGIC;
             ENTRY_VEC : in STD_LOGIC_VECTOR (7 downto 0);
             Q_H : out STD_LOGIC
        );
  end component;
  
  signal SH_in : std_logic;
  signal SER_in : std_logic;
  signal CLK_in : std_logic;
  signal CLK_INH : std_logic;
  signal CLR_in : std_logic;
  signal ENTRY_VEC : STD_LOGIC_VECTOR (7 downto 0);
  signal Q_H : std_logic;

begin

  mapping: LOAD_SHIFT_REG port map (
    SH_in => SH_in,
    SER_in => SER_in,
    CLK_in => CLK_in,
    CLK_INH => CLK_INH,
    CLR_in => CLR_in,
    ENTRY_VEC => ENTRY_VEC,
    Q_H => Q_H
  );

test_case: process
begin
    for SH_in_i in std_logic range '0' to '1' loop
        for SER_in_i in std_logic range '0' to '1' loop
            for CLK_in_i in std_logic range '0' to '1' loop
                for CLK_INH_i in std_logic range '0' to '1' loop
                    for CLR_in_i in std_logic range '0' to '1' loop
                        for i in 0 to 7 loop  -- Перебор индексов битов ENTRY_VEC
                            -- Присваиваем отдельные биты вектора ENTRY_VEC значениями 0 и 1
                            ENTRY_VEC(i) <= '0';
                            wait for 10 ns;
                            ENTRY_VEC(i) <= '1';
                            wait for 10 ns;
                        end loop;

                        -- Присваиваем входные сигналы
                        SH_in <= SH_in_i;
                        SER_in <= SER_in_i;
                        CLK_in <= CLK_in_i;
                        CLK_INH <= CLK_INH_i;
                        CLR_in <= CLR_in_i;

                        wait for 10 ns;
                    end loop;
                end loop;
            end loop;
        end loop;
    end loop;
end process;


end Behavioral;
