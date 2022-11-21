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
#define     LPS25HB_ADDRESS_PRESS                    0x28
#define     LPS25HB_ADDRESS_TEMP                    0x2B




uint8_t lps25hb_init(void);
uint8_t lps25hb_read_byte(uint8_t reg_addr);
void lps25hb_write_byte(uint8_t reg_addr, uint8_t value);
void lps25hb_readArray(uint8_t * data, uint8_t reg, uint8_t length);
//void lps25hb_get_press(float* press);
float lps25hb_get_temp();
float lps25hb_get_pressure();
float lps25hb_get_pressure_calibration();


/* doplnit funcie zadefinovane v lps25hb.c subore   */


#endif /* LPS25HB_H_ */
