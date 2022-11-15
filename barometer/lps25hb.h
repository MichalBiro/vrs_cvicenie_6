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


#define 	LPS25HB_DEVICE_ADDRESS_0				0xB8
#define 	LPS25HB_DEVICE_ADDRESS_1				0xBB

#define 	LPS25HB_WHO_AM_I_VALUE					0xBD
#define 	LPS25HB_WHO_AM_I_ADDRES					0x0F

#define 	LPS25HB_ADDRESS_CTRL1					0x20

/*  Tieto bude treba zmenit na potrebne adresy pre data z mojho senzora  */
#define 	LPS25HB_ADDRESS_PRESS					0x28   // XL


#define 	LPS25HB_ADDRESS_TEMP_L					0x20

uint8_t lps25hb_init(void);
uint8_t lps25hb_read_byte(uint8_t reg_addr);
void lps25hb_write_byte(uint8_t reg_addr, uint8_t value);

/* doplnit funcie zadefinovane v lps25hb.c subore   */


#endif /* LPS25HB_H_ */
