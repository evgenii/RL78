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
* File Name    : r_cg_dmac_user.c
* Version      : Applilet3 for RL78/G13 V2.00.00.08 [12 Apr 2013]
* Device(s)    : R5F100SL
* Tool-Chain   : IAR Systems iccrl78
* Description  : This file implements device driver for DMAC module.
* Creation Date: 17/07/2013
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_dmac.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
volatile int dmac0Ints = 0 ;
volatile int dmac1Ints = 0 ;
volatile int dmac2Ints = 0 ;
volatile int dmac3Ints = 0 ;
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: r_dmac0_interrupt
* Description  : This function is INTDMA0 interrupt service routine.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
#pragma bank=1
#pragma vector = INTDMA0_vect
__interrupt static void r_dmac0_interrupt(void)
{
    /* Start user code. Do not edit comment generated here */
    TDR03 = DIM_STEPS-1;
    dmac0Ints++;
    DRA0 = (uint16_t) &timerPeriod;
    DBC0 = DIM_STEPS; // _0040_DMA0_BYTE_COUNT;
    DST0 = 1U;
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: r_dmac1_interrupt
* Description  : This function is INTDMA1 interrupt service routine.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
#pragma vector = INTDMA1_vect
__interrupt static void r_dmac1_interrupt(void)
{
    /* Start user code. Do not edit comment generated here */
    dmac1Ints++;
    DRA1 = (uint16_t) &com;
    DBC1 = NUM_COM; // count 8 com periods _0200_DMA1_BYTE_COUNT;
    DST1 = 1U;
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: r_dmac2_interrupt
* Description  : This function is INTDMA2 interrupt service routine.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
#pragma bank = 2
#pragma vector = INTDMA2_vect
__interrupt static void r_dmac2_interrupt(void)
{
    /* Start user code. Do not edit comment generated here */
    dmac2Ints++;
    DRA2 = (uint16_t) &(ledArray_A.segmentBuffer);
    DBC2 = DIM_STEPS*NUM_COM; // _0200_DMA2_BYTE_COUNT;
    DST2 = 1U;
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: r_dmac3_interrupt
* Description  : This function is INTDMA3 interrupt service routine.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
#pragma bank = 3
#pragma vector = INTDMA3_vect
__interrupt static void r_dmac3_interrupt(void)
{
    /* Start user code. Do not edit comment generated here */
    dmac3Ints++;
    DRA3 = (uint16_t) &(ledArray_B.segmentBuffer);
    DBC3 = DIM_STEPS*NUM_COM; //_0200_DMA3_BYTE_COUNT;
    DST3 = 1U;
    /* End user code. Do not edit comment generated here */
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
