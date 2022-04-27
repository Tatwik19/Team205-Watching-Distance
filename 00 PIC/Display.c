#include <builtins.h>
#include "mcc_generated_files/mcc.h"
#include "Display.h"

void Display_Init(){
    int digit;
    I2C1_Write1ByteRegister(Display, 0x0C,0x01);

  // Default global intensity is minimal. Set to 50 %.
  I2C1_Write1ByteRegister(Display, 0x0A, 0x0f);

  // Set scan limit to display all digits.
  I2C1_Write1ByteRegister(Display, 0x0B, 0x07);

  // Set all digits to "no decode".
  I2C1_Write1ByteRegister(Display, 0x09, 0x00);

  for(digit=0; digit<=7; digit++) {
    I2C1_Write1ByteRegister(Display, digit+1, 0x60);   // turn all segments ON
    //__delay_ms(1000);
    
  // Set all digits to font decode.
  I2C1_Write1ByteRegister(Display, 0x09, 0xFF);
  }
}
void Display_Write1Digit(int Digit,int Number){
      I2C1_Write1ByteRegister(Display, Digit, Number);
}
void Display_Digits(int Number){
    int Num4;
    int Num3;
    int Num2;
    int Num1;
    int Temporary;
    //print digit 4
    Num4 = Number/1000;
    Temporary = Number %1000;
    Display_Write1Digit(1,Num4);
    //print digit 3
    Num3 = Temporary/100;
    Temporary = Temporary %100;
    Display_Write1Digit(2,Num3);
    //print digit 2
        Num2 = Temporary/10;
    Temporary = Temporary %10;
    Display_Write1Digit(3,Num2);
    //print digit 1
        Num1 = Temporary/1;
    Display_Write1Digit(4,Num1);
    
}


void Display_Help()
{
    Display_Write1Digit(1,12);
    Display_Write1Digit(2,11);
    Display_Write1Digit(3,13);
    Display_Write1Digit(4,14);
}

void Display_Blank()
{
    Display_Write1Digit(1,10);
    Display_Write1Digit(2,10);
    Display_Write1Digit(3,10);
    Display_Write1Digit(4,10);
}

void Display_Off()
{
    I2C1_Write1ByteRegister(Display, 0x0C,0x80);
}

void Display_On()
{
    I2C1_Write1ByteRegister(Display, 0x0C,0x01);
}