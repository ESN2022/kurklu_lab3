library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;


entity kurklu_lab3 is
	port(
		clk : in std_logic :='0';
		reset_n : in std_logic :='0';
		scl : inout std_logic := 'X';
		sda : inout std_logic := 'X';
		cs_n : out std_logic := '1');
end entity kurklu_lab3;


architecture rit of kurklu_lab3 is

    component kurklu_lab3_sys is
        port (
            clk_clk       : in std_logic := 'X'; -- clk
            reset_reset_n : in std_logic := 'X';  -- reset_n
				opencores_i2c_0_export_0_scl_pad_io : inout std_logic := 'X'; -- scl_pad_io
            opencores_i2c_0_export_0_sda_pad_io : inout std_logic := 'X'  -- sda_pad_io
        );
    end component kurklu_lab3_sys;
	 
begin

    u0 : component kurklu_lab3_sys
        port map (
            clk_clk       => clk,       --   clk.clk
            reset_reset_n => reset_n,  -- reset.reset_n
				opencores_i2c_0_export_0_scl_pad_io => scl, -- opencores_i2c_0_export_0.scl_pad_io
            opencores_i2c_0_export_0_sda_pad_io => sda  --                         .sda_pad_io
        );


end architecture;