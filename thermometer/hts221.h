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


#define 	HTS221_DEVICE_ADDRESS_0				0xD4
#define 	HTS221_DEVICE_ADDRESS_1				0xD6

#define 	HTS221_WHO_AM_I_VALUE					0x68
#define 	HTS221_WHO_AM_I_ADDRES					0x0F

#define 	HTS221_ADDRESS_CTRL1					0x10

/*  Tieto bude treba zmenit na potrebne adresy pre data z mojho senzora  */
#define 	HTS221_ADDRESS_ACCX					0x28
#define 	HTS221_ADDRESS_ACCY					0x2A
#define 	HTS221_ADDRESS_ACCZ					0x2C

#define 	HTS221_ADDRESS_TEMP_L					0x20

uint8_t hts221_init(void);
uint8_t hts221_read_byte(uint8_t reg_addr);
void hts221_write_byte(uint8_t reg_addr, uint8_t value);

/* doplnit funcie zadefinovane v hts221.c subore   */


#endif /* HTS221_H_ */

