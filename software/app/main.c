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

#define ACT_INACT_CTL 0X27
#define POWER_CTL 0x2D


//Fonction pour lire avec l'I2C
int lecture_i2c(int base,int addr){
	
	int data = 0;
	I2C_start(base, ALT_ADDR, 0);
	I2C_write(base,addr,0);
	
	I2C_start(base,ALT_ADDR,1);
	data = I2C_read(base,1);
	
	return data;
}

void ecriture_i2c(int base,int addr,int value){
	I2C_start(base, ALT_ADDR, 0);
	I2C_write(base,addr,0);
	I2C_write(base,value,1);
}



int main(){
	alt_printf("\n\n\n\nDans le main\n\n");
	int data =0;
	
	//Initialisation de l'i2c
	alt_printf("Initialisation I2C\n");
	I2C_init(OPENCORES_I2C_0_BASE, ALT_CPU_FREQ, SPEED);
	if(I2C_start(OPENCORES_I2C_0_BASE, ALT_ADDR, 0)== 0){
		
		alt_printf("Start ok\n");
	}
	
	//Lecture ACT_INACT_CTL
	alt_printf("Lecture ACT_INACT_CTL\n");
	data = lecture_i2c(OPENCORES_I2C_0_BASE,ACT_INACT_CTL);
	alt_printf("ACT_INACT_CTL = %x\n",data);
	
	//Lecture POWER_CTL
	alt_printf("Lecture POWER_CTL\n");
	data = lecture_i2c(OPENCORES_I2C_0_BASE,POWER_CTL);
	alt_printf("POWER_CTL = %x\n",data);
		
	//Ecriture POWER_CTL
	alt_printf("Ecriture POWER_CTL\n");
	ecriture_i2c(OPENCORES_I2C_0_BASE,POWER_CTL,0x8);
	usleep(100000);
	
	//Lecture POWER_CTL
	alt_printf("Lecture POWER_CTL\n");
	data = lecture_i2c(OPENCORES_I2C_0_BASE,POWER_CTL);
	alt_printf("POWER_CTL = %x\n",data);
	
	
	//Lecture Z0
	alt_printf("Lecture Z0\n");
	data = lecture_i2c(OPENCORES_I2C_0_BASE,0x36);
	alt_printf("Z0 = %x\n",data);
	//Lecture Z1
	alt_printf("Lecture Z1\n");
	data = lecture_i2c(OPENCORES_I2C_0_BASE,0x37);
	alt_printf("Z1 = %x\n",data);
	
	while(1){
		
	}
}