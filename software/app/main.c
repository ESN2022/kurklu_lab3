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
#define DATA_FORMAT 0x31

#define X0 0x32
#define X1 0x33
#define Y0 0x34
#define Y1 0x35
#define Z0 0x36
#define Z1 0x37



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
	alt_printf("Ecriture POWER_CTL\n\n");
	ecriture_i2c(OPENCORES_I2C_0_BASE,POWER_CTL,0x8);
	usleep(100000);
	
	//Lecture POWER_CTL
	alt_printf("Lecture POWER_CTL\n");
	data = lecture_i2c(OPENCORES_I2C_0_BASE,POWER_CTL);
	alt_printf("POWER_CTL = %x\n",data);
	
	
	//Lecture DATA_FORMAT
	alt_printf("Lecture DATA_FORMAT\n");
	data = lecture_i2c(OPENCORES_I2C_0_BASE,DATA_FORMAT);
	alt_printf("DATA_FORMAT = %x\n",data);
	
	//D1=1 et D0=1 -> +-16g 
	//Ecriture DATA_FORMAT
	alt_printf("Ecriture DATA_FORMAT\n\n");
	ecriture_i2c(OPENCORES_I2C_0_BASE,DATA_FORMAT,0x7);
	usleep(100000);
	
	//Lecture DATA_FORMAT
	alt_printf("Lecture DATA_FORMAT\n");
	data = lecture_i2c(OPENCORES_I2C_0_BASE,DATA_FORMAT);
	alt_printf("DATA_FORMAT = %x\n",data);
	
	/*
	//Lecture Z0
	alt_printf("Lecture Z0\n");
	data = lecture_i2c(OPENCORES_I2C_0_BASE,0x36);
	alt_printf("Z0 = %x\n",data);
	//Lecture Z1
	alt_printf("Lecture Z1\n");
	data = lecture_i2c(OPENCORES_I2C_0_BASE,0x37);
	alt_printf("Z1 = %x\n",data);*/
	
	int x1,x0,y1,y0,z1,z0;
	while(1){
		
		//Lecture X0 Lecture X1
		x0 = lecture_i2c(OPENCORES_I2C_0_BASE,X0);
		x1 = lecture_i2c(OPENCORES_I2C_0_BASE,X1);
		//Lecture Y0 Lecture Y1
		y0 = lecture_i2c(OPENCORES_I2C_0_BASE,Y0);
		y1 = lecture_i2c(OPENCORES_I2C_0_BASE,Y1);
		//Lecture Z0 Lecture Z1
		z0 = lecture_i2c(OPENCORES_I2C_0_BASE,Z0);
		z1 = lecture_i2c(OPENCORES_I2C_0_BASE,Z1);
		
		alt_printf("X= %x, Y= %x, Z= %x\n",(x1<<8)|x0,(y1<<8)|y0,(z1<<8)|z0  );
		alt_printf("--------------------\n");
		
		
		
		usleep(1000000);
	}
}