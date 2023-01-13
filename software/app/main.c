#include "system.h"
#include "sys/alt_stdio.h"
#include "alt_types.h"
#include "io.h"
#include "unistd.h"
#include "sys/alt_sys_init.h"
#include "opencores_i2c.h"
#include "opencores_i2c_regs.h"

#define ALT_ADDR 0x1d
#define SPEED 100000



int main(){
	alt_printf("Hello World\n");
	
	//Initialisation de l'i2c
	I2C_init(OPENCORES_I2C_0_BASE,ALT_CPU_FREQ,SPEED);

	
	if(I2C_start(OPENCORES_I2C_0_BASE,ALT_ADDR, 1)== 0){
		alt_printf("Start ok\n");
	}
	
	while(1){
		
		
	}
}