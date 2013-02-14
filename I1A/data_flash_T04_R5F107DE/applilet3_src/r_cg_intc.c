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
* Copyright (C) 2010, 2011 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name    : r_cg_intc.c
* Version      : Applilet3 for RL78/I1A V1.01.01 [05 Oct 2011]
* Device(s)    : R5F107DE
* Tool-Chain   : IAR Systems iccrl78
* Description  : This file implements device driver for INTC module.
* Creation Date: 14.02.2013
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_intc.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_INTC_Create
* Description  : This function initializes INTP module.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_INTC_Create(void)
{
    PMK0 = 1U;        /* disable INTP0 operation */
    PIF0 = 0U;        /* clear INTP0 interrupt flag */
    PMK3 = 1U;        /* disable INTP3 operation */
    PIF3 = 0U;        /* clear INTP3 interrupt flag */
    PMK4 = 1U;        /* disable INTP4 operation */
    PIF4 = 0U;        /* clear INTP4 interrupt flag */
    PMK9 = 1U;        /* disable INTP9 operation */
    PIF9 = 0U;        /* clear INTP9 interrupt flag */
    PMK10 = 1U;        /* disable INTP10 operation */
    PIF10 = 0U;        /* clear INTP10 interrupt flag */
    PMK11 = 1U;        /* disable INTP11 operation */
    PIF11 = 0U;        /* clear INTP11 interrupt flag */
    PMK20 = 1U;        /* disable INTP20 operation */
    PIF20 = 0U;        /* clear INTP20 interrupt flag */
    PMK21 = 1U;        /* disable INTP21 operation */
    PIF21 = 0U;        /* clear INTP21 interrupt flag */
    PMK22 = 1U;        /* disable INTP22 operation */
    PIF22 = 0U;        /* clear INTP22 interrupt flag */
    PMK23 = 1U;        /* disable INTP23 operation */
    PIF23 = 0U;        /* clear INTP23 interrupt flag */
    /* Set INTP0 low priority */
    PPR10 = 1U;
    PPR00 = 1U;
    EGN0 = _01_INTP0_EDGE_FALLING_SEL;
}

/***********************************************************************************************************************
* Function Name: R_INTC0_Start
* Description  : This function clears INTP0 interrupt flag and enables interrupt.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_INTC0_Start(void)
{
    PIF0 = 0U;        /* clear INTP0 interrupt flag */
    PMK0 = 0U;        /* enable INTP0 interrupt */
}

/***********************************************************************************************************************
* Function Name: R_INTC0_Stop
* Description  : This function disables INTP0 interrupt and clears interrupt flag.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_INTC0_Stop(void)
{
    PMK0 = 1U;        /* disable INTP0 interrupt */
    PIF0 = 0U;        /* clear INTP0 interrupt flag */
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
