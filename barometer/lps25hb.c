/*
 * lps25hb.c
 *
 *  Created on: 14. 11. 2022
 *      Author: micha
 */

#include "lps25hb.h"

uint8_t addresLps = LPS25HB_DEVICE_ADDRESS_0;

uint8_t lps25hb_read_byte(uint8_t reg_addr)
{
	uint8_t data = 0;
	return *(i2c_master_read(&data, 1, reg_addr, addresLps, 0));
}


void lps25hb_write_byte(uint8_t reg_addr, uint8_t value)
{
	i2c_master_write(value, reg_addr, addresLps, 0);
}


// ---  priestor na funkcie ----
void lps25hb_readArray(uint8_t * data, uint8_t reg, uint8_t length)
{
	i2c_master_read(data, length, reg, addresLps, 1);
}

// ---  priestor na funkcie ----
/*
void lps25hb_get_press(float* press)
{
	uint8_t data[2];
	uint16_t pressure;





	lps25hb_readArray(data, LPS25HB_ADDRESS_PRESS, 2);

	pressure = ((uint16_t)data[1]) << 8 | data[0];
	*press = pressure/1000.0f;

//return data;
}
*/
/*
float lps25hb_get_press(void)
{

	float pressure;





	lps25hb_readArray(data, LPS25HB_ADDRESS_PRESS, 2);

	pressure = ((uint16_t)data[1]) << 8 | data[0];


   return pressure;
}
*/

float lps25hb_get_temp()
{
	uint8_t data[2];
	int16_t temperature;

	lps25hb_readArray(data, LPS25HB_ADDRESS_TEMP, 2);

	temperature = ((int16_t)((data[1] << 8) | data[0]));

    return (42.5 + (temperature/480));
}


float lps25hb_get_pressure()
{
	uint8_t data[3];

	uint32_t pressure;
    uint8_t pressOut_XL, pressOut_L, pressOut_H;


	lps25hb_readArray(data, LPS25HB_ADDRESS_PRESS, 3);

	pressOut_XL = data[0];
	pressOut_L = data[1];
    pressOut_H = data[2];
	pressure = (uint32_t)pressOut_L << 8 | pressOut_XL;
	pressure = (uint32_t)pressOut_H << 16 | pressure;

	return (pressure/4096.0);
}

float lps25hb_get_pressure_calibration() //CHECK
{
	int i;
	float p, sum=0;

	for (i = 0; i < 1000; i++) {
		p=lps25hb_get_pressure();
		sum=sum+p;
		//printf("%d\n", i);
}

	return (sum/1000.);
}

uint8_t lps25hb_init(void)
{

	uint8_t status = 1;

	//LIS3MDL_ACC_ON;

	LL_mDelay(100);

	uint8_t val = lps25hb_read_byte(LPS25HB_WHO_AM_I_ADDRES);

	if(val == LPS25HB_WHO_AM_I_VALUE)
	{
		status = 1;
	}
	else			//if the device is not found on one address, try another one
	{
		addresLps = LPS25HB_DEVICE_ADDRESS_1;
		val = lps25hb_read_byte(LPS25HB_WHO_AM_I_ADDRES);
		if(val == LPS25HB_WHO_AM_I_VALUE)
		{
			status = 1;
		}
		else
		{
			status = 0;
			//return status;
		}
	}

	//acc device init

	uint8_t ctrl1 = 0b11000000;
	lps25hb_write_byte(LPS25HB_ADDRESS_CTRL1, ctrl1);
	return status;
}
