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
* Copyright (C) 2011 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name    : r_main.c
* Version      : Applilet3 for RL78/G14 V1.01.01 [11 Oct 2011]
* Device(s)    : R5F104LE
* Tool-Chain   : IAR Systems iccrl78
* Description  : This file implements main function.
* Creation Date: 08.01.2013
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_cgc.h"
#include "r_cg_port.h"
#include "r_cg_adc.h"
#include "r_cg_timer.h"
#include "r_cg_it.h"
#include "r_cg_dtc.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Set option bytes */
#pragma location = "OPTBYTE"
__root const uint8_t opbyte0 = 0xEFU;
#pragma location = "OPTBYTE"
__root const uint8_t opbyte1 = 0xFFU;
#pragma location = "OPTBYTE"
__root const uint8_t opbyte2 = 0xE8U;
#pragma location = "OPTBYTE"
__root const uint8_t opbyte3 = 0x84U;

/* Set security ID */
#pragma location = "SECUID"
__root const uint8_t secuid[10] = 
    {0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U};
/* Start user code for global. Do not edit comment generated here */

extern volatile uint16_t adcResult;

void setupChain(void);
extern uint16_t RJ_timing[2];

/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: main
* Description  : This function implements main function.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void  main(void)
{
    /* Start user code. Do not edit comment generated here */
    
    uint16_t j;        
    
    DTC_Create(); // initialize with modified versions
    ADC_Create();
    TMR_RJ0_Create();
    
    while(1) {
              
      setupChain(); 
      
      STOP();
        
      // within the ADC interrupt, output is set low
      // allow for some delay to trigger on the pulse with the scope, for debug
      // will also flash the LED on the Promo board
      for(j=0;j<65535;j++);
      P7_bit.no7 = 1;
      for(j=0;j<65535;j++);
      for(j=0;j<65535;j++);
      for(j=0;j<65535;j++);
    };   
   

    /* End user code. Do not edit comment generated here */
}

/* Start user code for adding. Do not edit comment generated here */
void ADC_setupAdmRegister(void) {

    /* disable / enable comparators */
    ADCE = 0U;
    ADCE = 1U;
    
//    ADM0 = 0x0;
//    ADM0 = _18_AD_CONVERSION_CLOCK_8 | _00_AD_TIME_MODE_NORMAL_1 | _00_AD_OPERMODE_SELECT | _01_AD_COMPARATOR_ENABLE;
}

void setupChain(void) {
      
    /* force IT to stop just in case */
    ITMC = 0x0;     
    
    // reinit the DTC
    DTC_Reload(); 
    R_DTCD0_Start();
  
    // rewrite the ADM register, required for proper ADC start 
    ADC_setupAdmRegister();
    
    /* the TRJ match (0x800) is first set to a shorter value than IT (0xFFF) */
    /* the first DTC reprogramming will occur before the interval timer expires */
    /* i.e. the first "sleep cycle" is shorter than the successives */
    /* this is required since IT needs to be started BEFORE going to stop mode */
    TRJCR0 = 0;
    TRJ0 = 0x800;
      
    TMR_RJ0_Start();    
    while(TRJCR0_bit.no0 != 1U); // wait for start flag    
    
    /* enable IT operation with max timeout for beginning */
    /* need to start interval timer before going into stop mode */
    ITMC = 0x8FFF;   
    while((ITMC & 0x8000) == 0); // wait for start before going asleep !

    ADMK = 0U; // enable adc interrupt    
}

/* End user code. Do not edit comment generated here */
