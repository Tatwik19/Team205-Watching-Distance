/* 
 * File:   Display.h
 * Author: User
 *
 * Created on April 20, 2022, 1:26 PM
 */

#ifndef DISPLAY_H
#define	DISPLAY_H

#include "mcc_generated_files/i2c1_master.h"
#include "mcc_generated_files/examples/i2c1_master_example.h"

i2c1_address_t Display = 0x00;

#ifdef	__cplusplus
extern "C" {
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* DISPLAY_H */

#define one 


void Display_Init(void);
void Display_Write1Digit(int Digit,int Number);
void Display_Digits(int Numbers);
void Display_Help(void);
void Display_Blank(void);
void Display_Off(void);
void Display_On(void);