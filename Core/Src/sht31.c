/*
 * SHT31.c
 *
 *  Created on: janvier 2021
 *      Author:
 */
 #include <stdio.h>
 #include <SHT31.h>
#include "usart.h"
#include "main.h"
#include "string.h"
#include "i2c.h"

void sht31_init(uint16_t cmd)
{

	uint8_t data[2];
	data[0]= cmd >> 8 ;
	data[1]= cmd & 0x00FF ;

	HAL_I2C_Master_Transmit(&hi2c1,SHT31_ADDR,data,2,HAL_MAX_DELAY);
}

void sht31_temphum(float *Hum,float *Temp)
{

	uint8_t data[6];
	HAL_I2C_Master_Receive(&hi2c1,SHT31_ADDR, data,6, HAL_MAX_DELAY);

	*Temp= ((uint8_t)data[0]<<8 | (data[1])>>8);
	*Hum = ((uint8_t)data[3]<<8 | (data[4])>>8);
    *Temp *= 175;
    *Temp /= 0xfffe;
	*Temp = -45 + *Temp;

	*Hum *= 100;
	*Hum /= 0xfffe;


}

void afficher_hum(char* data, float Hum)
{
	Hum *= 100;
	sprintf((char*)data, "%u.02u %%", ((unsigned int)Hum/100), ((unsigned int)Hum % 100));
	lcd_position(&hi2c1,0,1);
	lcd_print(&hi2c1, "Hum: ");
	lcd_position(&hi2c1,7,1);
	lcd_print(&hi2c1,data);
}

void afficher_temp(char* data, float Temp)
{
	Temp *= 100;
	sprintf((char*)data, "%u.02u %%", ((unsigned int)Temp/100), ((unsigned int)Temp % 100));
	lcd_position(&hi2c1,0,1);
	lcd_print(&hi2c1, "Temp: ");
	lcd_position(&hi2c1,7,1);
	lcd_print(&hi2c1,data);
}

