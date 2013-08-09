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
* Copyright (C) 2010, 2013 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name    : r_cg_timer.c
* Version      : Applilet3 for RL78/I1A V2.00.00.05 [12 Apr 2013]
* Device(s)    : R5F107DE
* Tool-Chain   : IAR Systems iccrl78
* Description  : This file implements device driver for TAU module.
* Creation Date: 31.07.2013
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
* Function Name: R_TMR_KB_Create
* Description  : This function initializes the TMKB module.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_TMR_KB_Create(void)
{
    TKB0EN = 1U;    /* supplies input clock for timer KB0*/
    TKB1EN = 1U;    /* supplies input clock for timer KB1*/
    TKB2EN = 1U;    /* supplies input clock for timer KB2*/
    TPS2 = _00_TMKB_CK20_FCLK_0;
    PFSEL0 |= _00_TMKB_KB0_TRIGGER_SOURCE;
    /* Mask TMKB0 interrupt */
    TMKBMK0 = 1U;   /* disable INTTMKB0 interrupt */
    TMKBIF0 = 0U;   /* clear INTTMKB0 interrupt flag */
    /* Set INTTMKB0 low priority */
    TMKBPR10 = 1U;
    TMKBPR00 = 1U;
    /* TMKB0 used as standalone mode */
    TKBCTL01 = _00_TMKB_OPERATION_DISABLED | _00_TMKB_CK20_SELECTED | _00_TMKB_TKBCKSn_SELECTED |
               _00_TMKB_STANDALONE_MASTER;
    TKBCTL00 = _0400_TMKB_OUTPUT_GATE0_ENABLE | _0000_TMKB_OUTPUT_GATE1_DISABLE | _0000_TMKB_SMOOTH_START0_DISABLE |
               _0000_TMKB_SMOOTH_START1_DISABLE | _0000_TMKB_DITHERING0_DISABLE | _0000_TMKB_DITHERING1_DISABLE |
               _0000_TMKB_MAXFREQ_DISABLE | _0000_TMKB_BATCH_OVERWRITE_DISABLE | _0000_TMKB_TRIGGER_DISABLED;
    TKBIOC00 = _00_TMKB_OUTPUT0_ACTIVE_HIGH | _00_TMKB_OUTPUT0_DEFAULT_LOW;
    TKBCR00 = _0C7F_TMKB_CYCLE00_VALUE;
    TKBCR01 = _0640_TMKB_DUTY01_VALUE;
    /* Set TKBO00 pin */
    PM20 &= 0xFEU;
}

/***********************************************************************************************************************
* Function Name: R_TMR_KB0_Start
* Description  : This function starts TMKB0 counter.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_TMR_KB0_Start(void)
{
    TMKBIF0 = 0U;   /* clear INTMKB0 interrupt flag */
    TMKBMK0 = 0U;   /* enable INTMKB0 interrupt */
    TKBCE0 = 1U;    /* enable timer count operation */
    TKBIOC01 = _01_TMKB_PIN0_OUTPUT_ENABLED;
}

/***********************************************************************************************************************
* Function Name: R_TMR_KB0_Stop
* Description  : This function stops TMKB0 counter.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_TMR_KB0_Stop(void)
{
    /* Mask channel 0 interrupt */
    TMKBMK0 = 1U;   /* disable INTMKB0 interrupt */
    TMKBIF0 = 0U;   /* clear INTMKB0 interrupt flag */
    TKBCE0 = 0U;    /* disable timer count operation */
    TKBIOC01 = _00_TMKB_PIN0_OUTPUT_DISABLED;
}

/***********************************************************************************************************************
* Function Name: R_TMR_KC0_Create
* Description  : This function initializes the TMKCn module.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_TMR_KC0_Create(void)
{
    TKC0EN = 1U;    /* supplies input clock */
    TPS2 |= _00_TMKC_CK21_FCLK_0;
    /* disable all timer output */
    TKCIOC01 = _00_TMKC_TIMER_OUTPUT0_DISABLED | _00_TMKC_TIMER_OUTPUT1_DISABLED | _00_TMKC_TIMER_OUTPUT2_DISABLED |
               _00_TMKC_TIMER_OUTPUT3_DISABLED | _00_TMKC_TIMER_OUTPUT4_DISABLED | _00_TMKC_TIMER_OUTPUT5_DISABLED;
    /* Mask TMKC0 interrupt */
    TMKCMK0 = 1U;   /* disable INTMKC0 interrupt */
    TMKCIF0 = 0U;   /* clear INTMKC0 interrupt flag */
    /* Set INTTMKC0 low priority */
    TMKCPR10 = 1U;
    TMKCPR00 = 1U;
    /* TMKC0 used as synchronous start/clear mode */
    TKCCTL0 = _00_TMKC_OPERATION_DISABLED | _10_TMKC_CK21_SELECTED | _01_TMKC_SYNC_START_SLAVE;
    TKCIOC00 = _0001_TMKC_OUTPUT0_DEFAULT_LOW | _0000_TMKC_OUTPUT0_ACTIVE_HIGH;
    TKCCR0 = _7CFF_TMKC_CYCLE0_VALUE;
    TKCDUTY00 = _3E80_TMKC_DUTY0_VALUE;
    /* Set TKCO00 pin */
    PM1 &= 0xFEU;
}

/***********************************************************************************************************************
* Function Name: R_TMR_KC0_Start
* Description  : This function starts TMKC channel 0 counter.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_TMR_KC0_Start(void)
{
    TMKCIF0 = 0U;   /* clear INTMKC0 interrupt flag */
    TMKCMK0 = 0U;   /* enable INTMKC0 interrupt */
    TKCCE0 = 1U;    /* enables timer count operation */
    TKCIOC01 = _01_TMKC_TIMER_OUTPUT0_ENABLED;
}

/***********************************************************************************************************************
* Function Name: R_TMR_KC0_Stop
* Description  : This function stops TMKC channel 0 counter.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_TMR_KC0_Stop(void)
{
    TKCCE0 = 0U;    /* stops timer operation */
    TKCIOC01 = _00_TMKC_TIMER_OUTPUT0_DISABLED;
    TMKCMK0 = 1U;   /* disable INTMKC0 interrupt */
    TMKCIF0 = 0U;   /* clear INTMKC0 interrupt flag */
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
