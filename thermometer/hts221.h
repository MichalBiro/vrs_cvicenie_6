/*
 * hts221.h
 *
 *  Created on: 14. 11. 2022
 *      Author: micha
 */

#ifndef HTS221_H_
#define HTS221_H_

#include "main.h"
#include "i2c.h"


#define 	HTS221_DEVICE_ADDRESS_0				0xBE   //write
#define 	HTS221_DEVICE_ADDRESS_1				0xBE   //rezervana - asi netreba

#define 	HTS221_WHO_AM_I_VALUE					0xBC
#define 	HTS221_WHO_AM_I_ADDRES					0x0F

#define 	HTS221_ADDRESS_CTRL1					0x20
#define 	H0_RH_X2	  							0x30
#define 	H0_T0_OUT  								0x36
#define 	T1T0_MSB    							0x3A

/*  Tieto bude treba zmenit na potrebne adresy pre data z mojho senzora  */
#define 	HTS221_ADDRESS_HUM					0x28   //LSB address
#define 	HTS221_ADDRESS_TEMP					0x2A   //LSB address




uint8_t hts221_init(void);
uint8_t hts221_read_byte(uint8_t reg_addr);
void hts221_write_byte(uint8_t reg_addr, uint8_t value);
float hts221_get_temp();
float hts221_get_humid();

/* doplnit funcie zadefinovane v hts221.c subore   */


#endif /* HTS221_H_ */

