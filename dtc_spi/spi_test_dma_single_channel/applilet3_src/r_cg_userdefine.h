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
* File Name    : r_cg_userdefine.h
* Version      : Applilet3 for RL78/G14 V1.01.01 [11 Oct 2011]
* Device(s)    : R5F104LE
* Tool-Chain   : IAR Systems iccrl78
* Description  : This file includes user definition.
* Creation Date: 16.11.2012
***********************************************************************************************************************/

#ifndef _USER_DEF_H
#define _USER_DEF_H

/***********************************************************************************************************************
User definitions
***********************************************************************************************************************/

/* Start user code for function. Do not edit comment generated here */

/* set this to zero for a custom board */
/* RPB_BOARD is defined for the YRPBRL78G14 promotion board */
#define RPB_BOARD 			1

/* configure the desired burst size */
#define BURST_SIZE 16




/* CSI specific API */
void CSI_Send(void);
void CSI_Init(void);

/* transmission complete flag */
extern volatile uint8_t burstDone;




#if(1 == RPB_BOARD)

extern volatile uint8_t sw1_keyPressed;
extern volatile uint8_t sw2_keyPressed;

/* Utility function */
void prepareBuffer(void);
void checkBuffer(void);
void demoRpbRl78(void);

extern volatile uint8_t error;

#endif

/* End user code. Do not edit comment generated here */
#endif
