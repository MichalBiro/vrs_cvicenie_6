/*
 * hts221.c
 *
 *  Created on: 14. 11. 2022
 *      Author: micha
 */

#include "hts221.h"

uint8_t addresHts = HTS221_DEVICE_ADDRESS_0;



uint8_t hts221_read_byte(uint8_t reg_addr)
{
	uint8_t data = 0;
	return *(i2c_master_read(&data, 1, reg_addr, addresHts, 0));
}


void hts221_write_byte(uint8_t reg_addr, uint8_t value)
{
	i2c_master_write(value, reg_addr, addresHts, 0);
}

void hts221_readArray(uint8_t * data, uint8_t reg, uint8_t length)
{
	i2c_master_read(data, length, reg, addresHts, 1);
}

// ---  priestor na funkcie ----
/*
void hts221_get_temp(float* temp)
{
	uint8_t data[2];
	uint16_t temperature;

	uint8_t k;
	//get current scale and use it for final calculation
	    k = hts221_read_byte(HTS221_ADDRESS_CTRL1);

	    k = k >> 2;
	    k &= 0x03;			//full scale bits exctracted

	hts221_readArray(data, HTS221_ADDRESS_TEMP, 2);

	temperature = ((uint16_t)data[1]) << 8 | data[0];
	*temp = temperature/1000.0f;

//return data;
}
*/
/*
void hts221_get_temp(float* temp)
{
    uint8_t data[2];
    int16_t temparature;

    hts221_readArray(data, HTS221_ADDRESS_TEMP, 2);

    temparature = (((((int16_t)temp[1] << 8) | (int16_t)temp[0])) >> 3)  + 25;
    *temp = temparature*1.0f;
}
*/

float hts221_get_temp()
{
	int16_t T0_out, T1_out, T_out, T0_degC_x8_u16, T1_degC_x8_u16, T0_degC, T1_degC;
	uint8_t buffer[4], tmp;
	float value;

	hts221_readArray(buffer, 0x32, 2);

	tmp = hts221_read_byte(0x35);

	T0_degC_x8_u16 = (((uint16_t)(tmp & 0x03)) << 8) | ((uint16_t)buffer[0]);
	T1_degC_x8_u16 = (((uint16_t)(tmp & 0x0C)) << 6) | ((uint16_t)buffer[1]);
	T0_degC = T0_degC_x8_u16>>3;
	T1_degC = T1_degC_x8_u16>>3;

	hts221_readArray(buffer, 0x3C, 4);

	T0_out = (((uint16_t)buffer[1])<<8) | (uint16_t)buffer[0];
	T1_out = (((uint16_t)buffer[3])<<8) | (uint16_t)buffer[2];

	hts221_readArray(buffer, 0x2A, 2);
	T_out = (((uint16_t)buffer[1])<<8) | (uint16_t)buffer[0];

	value = (float)((((int32_t)(T_out - T0_out)) * ((int32_t)(T1_degC - T0_degC)*10)) /(T1_out - T0_out) + T0_degC*10)*0.10000f;

	if(value>=100)
	{
		value=99.9f;
	}
	else if(value<=-100)
	{
		value=-99.9f;
	}

	return value;
}

float hts221_get_humid()
{
	int16_t H0_T0_out, H1_T0_out, H_T_out, H0_rh, H1_rh;;
	uint8_t buffer[2];

	float value = 0;

	hts221_readArray(buffer, H0_RH_X2, 2);     //   H0_RH_X2  0x30
	H0_rh = buffer[0]>>1;
	H1_rh = buffer[1]>>1;

	hts221_readArray(buffer, H0_T0_OUT, 2); //H0_T0_OUT  0x36
	H0_T0_out = (((uint16_t)buffer[1])<<8) | (uint16_t)buffer[0];

	hts221_readArray(buffer, T1T0_MSB, 2); // T1T0_MSB    0x3A
	H1_T0_out = (((uint16_t)buffer[1])<<8) | (uint16_t)buffer[0];

	hts221_readArray(buffer, HTS221_ADDRESS_HUM, 2);

	H_T_out = (((uint16_t)buffer[1])<<8) | (uint16_t)buffer[0];

	value = ((((int32_t)(H_T_out - H0_T0_out)) * ((int32_t)(H1_rh - H0_rh)*10))/(H1_T0_out - H0_T0_out) + H0_rh*10);

	if(value>1000)
	{
		value = 1000;
	}

	return (value * 0.1);
}


uint8_t hts221_init(void)
{

	uint8_t status = 1;

	//LIS3MDL_ACC_ON;

	LL_mDelay(100);

	uint8_t val = hts221_read_byte(HTS221_WHO_AM_I_ADDRES);

	if(val == HTS221_WHO_AM_I_VALUE)
	{
		status = 1;
	}
	else			//if the device is not found on one address, try another one
	{
		addresHts = HTS221_DEVICE_ADDRESS_1;
		val = hts221_read_byte(HTS221_WHO_AM_I_ADDRES);
		if(val == HTS221_WHO_AM_I_VALUE)
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

	uint8_t ctrl1 = 0b10000111;
	hts221_write_byte(HTS221_ADDRESS_CTRL1, ctrl1);

	return status;
}
