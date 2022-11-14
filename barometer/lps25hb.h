/*
 * lps25hb.h
 *
 *  Created on: 14. 11. 2022
 *      Author: micha
 */

#ifndef LPS25HB_H_
#define LPS25HB_H_

#include "main.h"
#include "i2c.h"


#define 	LPS25HB_DEVICE_ADDRESS_0				0xD4
#define 	LPS25HB_DEVICE_ADDRESS_1				0xD6

#define 	LPS25HB_WHO_AM_I_VALUE					0x68
#define 	LPS25HB_WHO_AM_I_ADDRES					0x0F

#define 	LPS25HB_ADDRESS_CTRL1					0x10

/*  Tieto bude treba zmenit na potrebne adresy pre data z mojho senzora  */
#define 	LPS25HB_ADDRESS_ACCX					0x28
#define 	LPS25HB_ADDRESS_ACCY					0x2A
#define 	LPS25HB_ADDRESS_ACCZ					0x2C

#define 	LPS25HB_ADDRESS_TEMP_L					0x20

uint8_t lps25hb_init(void);
uint8_t lps25hb_read_byte(uint8_t reg_addr);
void lps25hb_write_byte(uint8_t reg_addr, uint8_t value);

/* doplnit funcie zadefinovane v lps25hb.c subore   */


#endif /* LPS25HB_H_ */
