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
* Copyright (C) 2011, 2013 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name    : r_main.c
* Version      : Applilet3 for RL78/G13 V2.00.00.08 [12 Apr 2013]
* Device(s)    : R5F100SL
* Tool-Chain   : IAR Systems iccrl78
* Description  : This file implements main function.
* Creation Date: 17/07/2013
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_cgc.h"
#include "r_cg_port.h"
#include "r_cg_intc.h"
#include "r_cg_timer.h"
#include "r_cg_dmac.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */


// dimmedLedRow_t ledArray_A[NUM_COM];
void lightUp(const COM_t com, const ROW_t row, DIM_LEVEL_t level) {
  
  switch(row) {
    
      case ROW0:
        ledArray_A.ledArray[com].dimmedLed[level].led.no0 = 1U;
        break;
        
      case ROW1:
        ledArray_A.ledArray[com].dimmedLed[level].led.no1 = 1U;
        break;
        
      case ROW2:
        ledArray_A.ledArray[com].dimmedLed[level].led.no2 = 1U;
        break;
        
      case ROW3:
        ledArray_A.ledArray[com].dimmedLed[level].led.no3 = 1U;
        break;
        
      case ROW4:
        ledArray_A.ledArray[com].dimmedLed[level].led.no4 = 1U;
        break;
        
      case ROW5:
        ledArray_A.ledArray[com].dimmedLed[level].led.no5 = 1U;
        break;
        
      case ROW6:
        ledArray_A.ledArray[com].dimmedLed[level].led.no6 = 1U;
        break;
        
      case ROW7:
        ledArray_A.ledArray[com].dimmedLed[level].led.no7 = 1U;
        break;
    
    
  };
  
}

void lightDown(const COM_t com, const ROW_t row, DIM_LEVEL_t level) {
  
  switch(row) {
    
      case ROW0:
        ledArray_A.ledArray[com].dimmedLed[level].led.no0 = 0U;
        break;
        
      case ROW1:
        ledArray_A.ledArray[com].dimmedLed[level].led.no1 = 0U;
        break;
        
      case ROW2:
        ledArray_A.ledArray[com].dimmedLed[level].led.no2 = 0U;
        break;
        
      case ROW3:
        ledArray_A.ledArray[com].dimmedLed[level].led.no3 = 0U;
        break;
        
      case ROW4:
        ledArray_A.ledArray[com].dimmedLed[level].led.no4 = 0U;
        break;
        
      case ROW5:
        ledArray_A.ledArray[com].dimmedLed[level].led.no5 = 0U;
        break;
        
      case ROW6:
        ledArray_A.ledArray[com].dimmedLed[level].led.no6 = 0U;
        break;
        
      case ROW7:
        ledArray_A.ledArray[com].dimmedLed[level].led.no7 = 0U;
        break;
    
    
  };
  
}



ledArray_t ledArray_A;
ledArray_t ledArray_B;

uint8_t com[NUM_COM] = { 0x1, 0x2, 0x4, 0x8, 0x10, 0x20, 0x40, 0x80 };


// logarithmic curve DALI-like
// target is to have ~100 Hz refresh for each COM segment
uint16_t timerPeriod[DIM_STEPS] = { 
50, // dead time
34,
35,
35,
35,
36,
37,
37,
38,
39,
40,
41,
42,
43,
44,
46,
47,
49,
51,
54,
56,
59,
63,
66,
70,
75,
80,
86,
92,
99,
107,
116,
126,
136,
149,
162,
177,
194,
213,
234,
257,
284,
313,
345,
381,
422,
467,
517,
573,
636,
706,
784,
871,
968,
1076,
1196,
1331,
1481,
1648,
1835,
2043,
2275,
2534,
2823,
3145,
50      // dead time
};



DIM_LEVEL_t dimLevel = LEVEL_1;
uint8_t up = 1;

/* End user code. Do not edit comment generated here */

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
    int i;
    
    // wait for the user to press the button once to start the demo
    while(!trigger);
    
    trigger = 0;
    
    R_TAU0_Channel3_Start();
    R_TAU1_Channel0_Start();
    R_TAU0_Channel0_Start();  
    
    // set one LED from OFF to maximum brightness and backwards, cyclically
    // each button press makes one step on the processor
    while (1U)
    {
      if(trigger) {
        
        trigger = 0;
        if(up) {
          
            lightUp(COM0,ROW7, dimLevel);
            dimLevel++;
            if(dimLevel == NUM_DIM_LEVELS) {
                dimLevel--;
                up = 0;
            }
        }
        else {
            
            lightDown(COM0,ROW7,dimLevel);
            dimLevel--;
            if(dimLevel == LEVEL_1) {
                up = 1;
            } 
        }
          
      }
      
      HALT();   
        
    }
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
  
    R_DMAC0_Start();
    R_DMAC1_Start();
    R_DMAC2_Start();
    R_DMAC3_Start();
      
    R_INTC0_Start();
    
    EI();
    /* End user code. Do not edit comment generated here */
}

/* Start user code for adding. Do not edit comment generated here */




/* End user code. Do not edit comment generated here */
