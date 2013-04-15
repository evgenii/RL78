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
* File Name    : interrupts.c
* Version      : v.1
* Device(s)    : R5F100LE
* Tool-Chain   : IAR Systems iccrl78
* Description  : This file implements the common skeleton for the interrupts
* Creation Date: 09.04.2013
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#ifdef APPLICATION

#include "r_cg_macrodriver.h"
#include "r_cg_intc.h"
#include "r_cg_userdefine.h"

#endif

#ifdef BOOTLOADER

#include "BL_r_cg_macrodriver.h"
#include "BL_r_cg_intc.h"

#include "BL_r_cg_userdefine.h"
#endif

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */

/* End user code. Do not edit comment generated here */
/***********************************************************************************************************************
* Function Name: r_it_interrupt
* Description  : This function is INTIT interrupt service routine skeleton.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
/* this pointer is used to read the content of the reset vector for the application */
__no_init void (**pAPP_START)(void);

/* location of the interrupt vectors in ram */
__no_init void (*pISR_INTIT)(void) @ 0xFF30A;
__no_init void (*pISR_INTP0)(void) @ 0xFF30C;


#pragma vector = INTIT_vect
__interrupt static void isr_INTIT_skeleton(void)
{
    (*pISR_INTIT)();	
}

/***********************************************************************************************************************
* Function Name: isr_INTP0_skeleton
* Description  : This function is INTP0 interrupt service routine skeleton.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
__no_init void (*pISR_INTP0)(void);

#pragma vector = INTP0_vect
__interrupt static void isr_INTP0_skeleton(void)
{
    (*pISR_INTP0)();	
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
