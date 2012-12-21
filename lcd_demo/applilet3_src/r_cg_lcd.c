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
* File Name    : r_cg_lcd.c
* Version      : Applilet3 for RL78/L12 V1.00.00 [23 Mar 2012]
* Device(s)    : R5F10RLC
* Tool-Chain   : IAR Systems iccrl78
* Description  : This file implements device driver for LCD module.
* Creation Date: 15.10.2012
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_lcd.h"
/* Start user code for include. Do not edit comment generated here */
#include "r_cg_it.h"
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
void waitMs(uint8_t time);
#define wait500Ms() do {\
waitMs(125);\
waitMs(125);\
waitMs(125);\
waitMs(125);\
} while(0);

/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_LCD_Create
* Description  : This function initializes the LCD module.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
#if(PLATFORM == RSKRL78L12)
void R_LCD_Create(void)
{
    volatile uint32_t wt_count;
    
    RTCEN = 1U;    /* supply LCD clock */
    LCDON = 0U;    /* disable LCD clock operation */
    LCMK0 = 1U;    /* disable INTLCD0 interrupt */
    LCIF0 = 0U;    /* clear INTLCD0 interrupt flag */
    LCDM1 |= _01_LCD_VOLTAGE_LOW;
    LCDM0 = _00_LCD_DISPLAY_WAVEFORM_A | _0D_LCD_DISPLAY_MODE1;
    LCDM0 |= _40_LCD_VOLTAGE_MODE_INTERNAL;
    /* Set CAPL and CAPH pins */
    ISCLCD &= (uint8_t)~_01_LCD_CAPLH_BUFFER_VALID;
    P12 &= 0x3FU;
    PM12 |= 0xC0U;
    /* Set segment pins */
    PFSEG0 |= 0xC0U;
    PFSEG1 |= 0xFFU;
    PFSEG2 |= 0xF9U;
    PFSEG3 |= 0x9FU;
    PFSEG4 |= 0x7EU;
    PMC1 &= 0xF7U;
    P1 &= 0x76U;
    PM1 &= 0x76U;
    P3 &= 0xFEU;
    PM3 &= 0xFEU;
    PMC4 &= 0xFDU;
    P4 &= 0xF1U;
    PM4 &= 0xF1U;
    P5 &= 0xE0U;
    PM5 &= 0xE0U;
    P6 &= 0xFCU;
    PM6 &= 0xFCU;
    P7 &= 0xE0U;
    PM7 &= 0xE0U;
    PMC12 &= 0xFEU;
    P12 &= 0xFEU;
    PM12 &= 0xFEU;
    PMC14 &= 0xC3U;
    P14 &= 0x00U;
    PM14 &= 0x00U;
    LCDM1 |= _00_LCD_DISPLAY_PATTERN_A;
    LCDC0 = _00_LCD_SOURCE_CLOCK_FSUB | _05_LCD_CLOCK_FLCD_64;
    VLCD = _0C_LCD_BOOST_VOLTAGE_140V;

    /* Change the waiting time according to the system */
	  waitMs(5);
// 	 for (wt_count = 0U; wt_count <= LCD_REFVOLTAGE_WAITTIME; wt_count++)
//    {
//        NOP();
//    }
}
#endif

#if(PLATFORM == RPBRL78L12)
void R_LCD_Create(void)
{
    volatile uint32_t wt_count;
    
    RTCEN = 1U;    /* supply LCD clock */
    LCDON = 0U;    /* disable LCD clock operation */
    LCMK0 = 1U;    /* disable INTLCD0 interrupt */
    LCIF0 = 0U;    /* clear INTLCD0 interrupt flag */
    LCDM1 |= _01_LCD_VOLTAGE_LOW;
    LCDM0 = _00_LCD_DISPLAY_WAVEFORM_A | _0D_LCD_DISPLAY_MODE1;
    LCDM0 |= _40_LCD_VOLTAGE_MODE_INTERNAL;
    /* Set CAPL and CAPH pins */
    ISCLCD &= (uint8_t)~_01_LCD_CAPLH_BUFFER_VALID;
    P12 &= 0x3FU;
    PM12 |= 0xC0U;
    /* Set segment pins */
    PFSEG0 |= 0xF0U;
    PFSEG1 |= 0xFFU;
    PFSEG2 |= 0xF9U;
    PFSEG3 |= 0x9FU;
    PFSEG4 |= 0x7FU;
    PMC1 &= 0xE7U;
    P1 &= 0x06U;
    PM1 &= 0x06U;
    P3 &= 0xFEU;
    PM3 &= 0xFEU;
    PMC4 &= 0xFDU;
    P4 &= 0xF1U;
    PM4 &= 0xF1U;
    P5 &= 0xE0U;
    PM5 &= 0xE0U;
    P6 &= 0xFCU;
    PM6 &= 0xFCU;
    P7 &= 0xE0U;
    PM7 &= 0xE0U;
    PMC12 &= 0xFEU;
    P12 &= 0xFEU;
    PM12 &= 0xFEU;
    PMC14 &= 0xC3U;
    P14 &= 0x00U;
    PM14 &= 0x00U;
    LCDM1 |= _00_LCD_DISPLAY_PATTERN_A;
    LCDC0 = _00_LCD_SOURCE_CLOCK_FSUB | _05_LCD_CLOCK_FLCD_64;
    VLCD = _0C_LCD_BOOST_VOLTAGE_140V;

    /* Change the waiting time according to the system */
	  waitMs(5);
// 	 for (wt_count = 0U; wt_count <= LCD_REFVOLTAGE_WAITTIME; wt_count++)
//    {
//        NOP();
//    }
}
#endif

/***********************************************************************************************************************
* Function Name: R_LCD_Start
* Description  : This function enables the LCD display.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_LCD_Start(void)
{
    LCDON = 1U;
}

/***********************************************************************************************************************
* Function Name: R_LCD_Stop
* Description  : This function disables the LCD display.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_LCD_Stop(void)
{
    LCDON = 0U;
}

/***********************************************************************************************************************
* Function Name: R_LCD_Set_VoltageOn
* Description  : This function enables voltage boost circuit or capacitor split circuit.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_LCD_Set_VoltageOn(void)
{
    volatile uint32_t wt_count;
    
    VLCON = 1U;

    /* Change the waiting time according to the system */
    wait500Ms();
//	for(wt_count = 0U; wt_count <= LCD_VOLTAGE_WAITTIME; wt_count++)
//    {
//        NOP();
//    }

    SCOC = 1U;
}

/***********************************************************************************************************************
* Function Name: R_LCD_Set_VoltageOff
* Description  : This function disables voltage boost circuit or capacitor split circuit.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_LCD_Set_VoltageOff(void)
{
    SCOC = 0U;
    VLCON = 0U;
    LCDM0 &= (uint8_t)~_C0_LCD_VOLTAGE_MODE_INITIALVALUE;
}

/* Start user code for adding. Do not edit comment generated here */

void waitMs(uint8_t time) {
	
	/* stop the timer if running */
	ITMC = _0000_IT_OPERATION_DISABLE;
	ITMK = 1U;    /* disable INTIT interrupt */
  ITIF = 0U;    /* clear INTIT interrupt flag */

	/* program the new value */
  ITMC = ((time*32768)/1000) - 1; 
  ITMC |= _8000_IT_OPERATION_ENABLE;
  while (!(ITMC & 0x8000));

  while(0U == ITIF); // wait for elapse

  ITIF = 0U;    /* clear INTIT interrupt flag */
  ITMC &= (uint16_t)~(_8000_IT_OPERATION_ENABLE);
  while (ITMC & 0x8000);

  ITMC = _0147_ITMCMP_VALUE; // restore old value
	
}		

/* End user code. Do not edit comment generated here */
