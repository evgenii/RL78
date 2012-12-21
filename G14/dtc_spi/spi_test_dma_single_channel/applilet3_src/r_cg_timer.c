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
* File Name    : r_cg_timer.c
* Version      : Applilet3 for RL78/G14 V1.01.01 [11 Oct 2011]
* Device(s)    : R5F104LE
* Tool-Chain   : IAR Systems iccrl78
* Description  : This file implements device driver for TAU module.
* Creation Date: 16.11.2012
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_timer.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_TMR_RD0_Create
* Description  : This function initializes the TMRD0 module.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_TMR_RD0_Create(void)
{
    TRD0EN = 1U;    /* enable input clock supply */ 
    TRDSTR &= (uint8_t)~_01_TMRD_TRD0_COUNT_START;  /* disable TMRD0 operation */
    TRDMK0 = 1U;    /* disable TMRD0 interrupt */
    TRDIF0 = 0U;    /* clear TMRD0 interrupt flag */
    /* Set INTTRD0 priority 2 */
    TRDPR10 = 1U;
    TRDPR00 = 0U;   
    TRDOER1 &= _F0_TMRD_CHANNEL0_OUTPUT_DEFAULT;
    TRDOER1 |= _00_TMRD_TRDIOA0_OUTPUT_ENABLE | _04_TMRD_TRDIOC0_OUTPUT_DISABLE | _08_TMRD_TRDIOD0_OUTPUT_DISABLE;
    TRDOCR |= _01_TMRD_TRDIOA0_INITIAL_OUTPUT_H;
    TRDCR0 |= _00_TMRD_INETNAL_CLOCK_F1_FIH | _A0_TMRD_COUNTER_CLEAR_TRDGRC;
    TRDIER0 = _00_TMRD_IMIA_DISABLE | _02_TMRD_IMIB_ENABLE | _00_TMRD_IMIC_DISABLE | _08_TMRD_IMID_ENABLE |
              _00_TMRD_OVIE_DISABLE;
    TRDIORA0 = _02_TMRD_TRDGRA_COMPARE_OUTPUT_HIGH;
    TRDIORC0 = _01_TMRD_TRDGRC_COMPARE_OUTPUT_LOW | _10_TMRD_TRDGRD_COMPARE_OUTPUT_LOW |
               _00_TMRD_TRDGRC_OUTPUT_REGISTER | _00_TMRD_TRDGRD_OUTPUT_REGISTER;
    TRDGRA0 = _02BF_TMRD_TRDGRA0_VALUE;
    TRDGRB0 = _003F_TMRD_TRDGRB0_VALUE;
    TRDGRC0 = _02FF_TMRD_TRDGRC0_VALUE;
    TRDGRD0 = _017F_TMRD_TRDGRD0_VALUE;
    /* Set TRDIOA0 pin */
    P1 &= 0x7FU;
    PM1 &= 0x7FU;
}

/***********************************************************************************************************************
* Function Name: R_TMR_RD0_Start
* Description  : This function starts TMRD0 counter.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_TMR_RD0_Start(void)
{
    // TRDSR0 = _E0_TMRD_TRDSR0_DEFAULT_VALUR; /* clear TRD0 each interrupt request */
    /* GP modified, shall write all zeros to the register, not 0xE0U */
		TRDSR0 = 0x0; /* clear TRD0 each interrupt request */
		
		TRDIF0 = 0U;    /* clear TMRD0 interrupt flag */
    TRDMK0 = 0U;    /* enable TMRD0 interrupt */
    TRDSTR |= _01_TMRD_TRD0_COUNT_START;    /* start TMRD0 counter */
}

/***********************************************************************************************************************
* Function Name: R_TMR_RD0_Stop
* Description  : This function stops TMRD0 counter.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_TMR_RD0_Stop(void)
{
    TRDSTR &= (uint8_t)~_01_TMRD_TRD0_COUNT_START;  /* stop TMRD0 counter */
    TRDMK0 = 1U;    /* disable TMRD0 interrupt */
    TRDIF0 = 0U;    /* clear TMRD0 interrupt flag */
    TRDSR0 = _E0_TMRD_TRDSR0_DEFAULT_VALUR; /* clear TRD0 each interrupt request */     
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
