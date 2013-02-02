/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only 
* intended for use with Renesas products. No other uses are authorized. This 
* software is owned by Renesas Electronics Corporation and is protected under 
* all applicable laws, including copyright laws.
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING 
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT 
* LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE 
* AND NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.
* TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS 
* ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE 
* FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR 
* ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE 
* BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software 
* and to discontinue the availability of this software.  By using this software, 
* you agree to the additional terms and conditions found by accessing the 
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2012 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name    : r_main.c
* Version      : Applilet3 for RL78/L12 V1.00.00 [23 Mar 2012]
* Device(s)    : R5F10RLC
* Tool-Chain   : IAR Systems iccrl78
* Description  : This file implements main function.
* Creation Date: 30.11.2012
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_cgc.h"
#include "r_cg_serial.h"
#include "r_cg_adc.h"
#include "r_cg_rtc.h"
#include "r_cg_it.h"
#include "r_cg_lcd_RPB.h"
/* Start user code for include. Do not edit comment generated here */

/* include the board specific package definitions */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
#define BUFFER_SIZE 40
char buffer[BUFFER_SIZE];

extern volatile uint8_t uartReady;
extern volatile uint8_t sendString;
extern volatile uint8_t adcResultReady;
extern volatile uint8_t rtcInterrupt;

uint16_t count = 0;
uint16_t adcResultValue = 0;
uint16_t voltage = 0;

void welcomeMessage(void);

#define REF_VOLTAGE 5
typedef struct Voltage {
    uint16_t  integerValue;
    uint8_t   fractionalValue;
} Voltage;

Voltage displayVoltage;

void adcToVolts(uint16_t adcValue, Voltage* result);


rtc_counter_value_t time_data = { 0, 0x58, 0, 0, 0, 0, 0x12 };


void testLCD(void);

/* End user code. Do not edit comment generated here */

/* Set option bytes */
#pragma constseg = __far "OPTBYTE"
__root const uint8_t opbyte0 = 0xEFU;
__root const uint8_t opbyte1 = 0xFFU;
__root const uint8_t opbyte2 = 0xE0U;
__root const uint8_t opbyte3 = 0x85U;
#pragma constseg = default

/* Set security ID */
#pragma constseg = __far "SECUID"
__root const uint8_t secuid[10] = 
	{0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U};
#pragma constseg = default

void R_MAIN_UserInit(void);

/***********************************************************************************************************************
* Function Name: main
* Description  : This function implements main function.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void main(void)
{
    R_MAIN_UserInit();
    /* Start user code. Do not edit comment generated here */

#if 0
    /* test the display with different patterns */
    LCD_selfTest();
#endif
    
    LCD_initDisplay();
    welcomeMessage();
    
    while (1U)
    {
      if(1 == rtcInterrupt) {
        rtcInterrupt = 0;
        LCD_blinkHourColumn();
        R_RTC_Get_CounterValue(&time_data);
        LCD_displayTime(&time_data);
      }
      
      if(1 == adcResultReady) {
          
        adcResultReady = 0;
        R_ADC_Get_Result(&adcResultValue);
        adcToVolts(adcResultValue, &displayVoltage);
        LCD_displayValue(PLUS,displayVoltage.integerValue,displayVoltage.fractionalValue);
        
        if(1 == uartReady) {
          
          /* copy new result */
          snprintf(buffer, BUFFER_SIZE, "[Sample %d : %d]   \r", count++, adcResultValue);
          uartReady = 0;
          R_UART0_Send((uint8_t *)buffer, strlen(buffer));
          
          /* Don't go in STOP immediately at this point 
          while UART might be still sending the first char */
          while(!uartReady) HALT();
        }
        
      }          
      
      STOP();
    };
    /* End user code. Do not edit comment generated here */
}


/***********************************************************************************************************************
* Function Name: R_MAIN_UserInit
* Description  : This function adds user code before implementing main function.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_MAIN_UserInit(void)
{
    /* Start user code. Do not edit comment generated here */
    
	/* Just for debug to check CPU frequency */
	/* remember to configure for PLCBUZ0 instead of SEG27 */
	// R_PCLBUZ0_Start();

    R_LCD_Set_VoltageOn();
    R_LCD_Start();
    
    R_ADC_Set_OperationOn();
    
    R_UART0_Start();

    R_IT_Start();    
    
    /* RTC start */   
    R_RTC_Start();                      
    
    EI();
    
    /* End user code. Do not edit comment generated here */
}

/* Start user code for adding. Do not edit comment generated here */

void welcomeMessage(void) {
  
    snprintf ( buffer, BUFFER_SIZE, "\n\n\r**********************\n\r");
    uartReady = 0;
    R_UART0_Send((uint8_t *)buffer, strlen(buffer));
    while(!uartReady);

    snprintf ( buffer, BUFFER_SIZE, "*  Renesas RL78-L12  *\n\r");

    uartReady = 0;
    R_UART0_Send((uint8_t *)buffer, strlen(buffer));
    while(!uartReady);
                
    snprintf ( buffer, BUFFER_SIZE, "**********************\n\n\r");
    uartReady = 0;
    R_UART0_Send((uint8_t *)buffer, strlen(buffer));
    while(!uartReady);

}


void adcToVolts(uint16_t adcValue, Voltage* result) {
  
  div_t scaledResult = div(adcValue, (1024/REF_VOLTAGE));
  
  result->integerValue = scaledResult.quot;
  result->fractionalValue = (scaledResult.rem * REF_VOLTAGE)/100;
}

/* End user code. Do not edit comment generated here */
