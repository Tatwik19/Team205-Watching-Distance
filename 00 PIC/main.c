/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.7
        Device            :  PIC18F27Q43
        Driver Version    :  2.00
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#include "mcc_generated_files/mcc.h"
#include "mcc_generated_files/examples/i2c1_master_example.h"
#include "mcc_generated_files/i2c1_master.h"
#include "MPU.h"
#include "Display.h"

/*
                         Main application
 */

void MPU_Setup()
{
    i2c1_address_t a = 0x68;
    I2C1_Write1ByteRegister(a,SMPLRT_DIV,0x07);
    __delay_ms(1);
    I2C1_Write1ByteRegister(a,PWR_MGMT_1,0x01);
    __delay_ms(1);
    I2C1_Write1ByteRegister(a,CONFIG,0x00);
    __delay_ms(1);
    I2C1_Write1ByteRegister(a,ACCEL_CONFIG,0x00);
    __delay_ms(1);
    I2C1_Write1ByteRegister(a,GYRO_CONFIG,0x18);
    __delay_ms(1);
    I2C1_Write1ByteRegister(a,INT_ENABLE,0x01);
    __delay_ms(1);
}
float MPU_Read()
{
    i2c1_address_t ad = 0x68;
    char buffer[40];
    int Ax,AxL,Ay,AyL,Az,AzL,TL,TH,Gx,Gy,Gz;
    float AX, AY,AYL, AZ,AZL, tl,th, GX, GY, GZ,AXL;
    float accD = 16384.0;
    //I2C1_Write1ByteRegister(ad, ACCEL_XOUT_H);

    //Acceleration
    Ax = (int)I2C1_Read1ByteRegister(ad, ACCEL_XOUT_H);
    AxL = (int) I2C1_Read1ByteRegister(ad, ACCEL_XOUT_L);
    Ay = (int)I2C1_Read1ByteRegister(ad, ACCEL_YOUT_H);
    AyL = (int) I2C1_Read1ByteRegister(ad, ACCEL_YOUT_L);
    Az = (int)I2C1_Read1ByteRegister(ad, ACCEL_ZOUT_H);
    AzL = (int) I2C1_Read1ByteRegister(ad, ACCEL_ZOUT_L);
    AX = (float)Ax/accD;
    AXL = (float)AxL/accD;
//    printf("AX_H: %f",AX);
//    printf("     AX_L: %f \n\r",AXL);
//    printf("AY_H: %f",AY);
//    printf("     AY_L: %f \n\r",AYL);
//    printf("AZ_H: %f",AZ);
//    printf("     AZ_L: %f \n\r",AZL);

    //Temp
    TL = (int) I2C1_Read1ByteRegister(ad, TEMP_OUT_L);
    TH = (int) I2C1_Read1ByteRegister(ad, TEMP_OUT_H);
    tl = (float) (TL/340.00)+36.53;
    th = (float) (TH/340.00)+36.53;
   // printf("T_H: %f",th);
    //printf("     T_L: %f \n\r",tl);

    //Gyro
    Gx = (int)I2C1_Read1ByteRegister(ad, GYRO_XOUT_H);
    Gy = (int)I2C1_Read1ByteRegister(ad, GYRO_YOUT_H);
    Gz = (int)I2C1_Read1ByteRegister(ad, GYRO_ZOUT_H);
    GX = (float)Gx/131.0;
    GY = (float)Gy/131.0;
    GZ = (float)Gz/131.0;
    printf("GX: %f \n\r",GX);
    //printf("GY: %f \n\r",GY);
    //printf("GZ: %f \n\r",GZ);
    
    return GX;
}


float Conversion(float x)
{
    float y =  (float) (0.0066575727*(x*x) + -0.5089235578*x + 9.856333104);
    return y*100;
}

float ADC_Read()
{
    float a,b,c,d; //float values to read ADC,D is avg
    adcc_channel_t c1, c2, c3; //used to read ADC
    __delay_ms(5);
    c1 = ADCC_GetSingleConversion(channel_ANA6);
    a = (float) c1 - 33;
    __delay_ms(5);
    c2 = ADCC_GetSingleConversion(channel_ANA6);
    b = (float) c2 - 33;
    __delay_ms(5);
    c3 = ADCC_GetSingleConversion(channel_ANA6);
    c = (float) c3 - 33;
        
    d = (a+b+c)/3; //find AVG
    return d;
}

uint8_t rxData = 'D';
void Data_Eusart(void)
{
       UART1_Receive_ISR();
    
if(UART1_is_rx_ready())
        {
            rxData = (uint8_t) UART1_Read();
        }   
LED_W_Toggle();
    
}
void main(void)
{
    // Initialize the device
    SYSTEM_Initialize();
    MPU_Setup();
    Display_Init();
    INTERRUPT_GlobalInterruptEnable();
//    INTERRUPT_PeripheralInterruptEnable();
    UART1_SetRxInterruptHandler(Data_Eusart);
        
   // printf("hi2 \n\r");
    i2c1_address_t address = 0x68;
    uint8_t GYROX = 0x41;
    
    // Enable the Global Interrupts
    //INTERRUPT_GlobalInterruptEnable();
    
    // Enable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptEnable();
    
    
    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global Interrupts
    // Use the following macros to:

    // Enable the Global Interrupts
    //INTERRUPT_GlobalInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();
    
    
    adcc_channel_t conv;
    float j;
    int k;
    float value = 0;
    uint8_t b = 0;
    I2C1_Open(address);
    float GYROTHINGGY;
    
    

    while (1)
    { 
        GYROTHINGGY = MPU_Read();
        //__delay_ms(10);
        if(GYROTHINGGY < 1)
        {
            LED_Y_SetHigh();
            Display_Blank();
            __delay_ms(1000);
        }
        else
        {
            LED_Y_SetLow();
            j = ADC_Read();
            printf("ADC: %3.2f",j);
            __delay_ms(1);
            if(j>39)
            {
                j = 40;
            }
            k = (int) Conversion(j);

            if(k<500)
            {
                LED_G_SetHigh();
            }
            else
            {
                LED_G_SetLow();
            }
            printf("      Adjusted: %d",k);
            printf("      RX: %c\n\r",rxData);


            if(rxData == 'D')
            {
                Display_Digits(k);
            }
            else
            {
                Display_Help();
                __delay_ms(1000);
                rxData = 'D';
            }
            __delay_ms(500);
        }
    }

    
    
}





/**
 End of File
*/