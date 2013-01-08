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
* File Name    : r_cg_elc.h
* Version      : Applilet3 for RL78/G14 V1.01.01 [11 Oct 2011]
* Device(s)    : R5F104LE
* Tool-Chain   : IAR Systems iccrl78
* Description  : This file implements device driver for ELC module.
* Creation Date: 05.12.2012
***********************************************************************************************************************/

#ifndef ELC_H
#define ELC_H

/***********************************************************************************************************************
Macro definitions (Register bit)
***********************************************************************************************************************/

/*
    Event Output Destination Selection Register n (ELSELRn)
*/
/* Event link selection (ELSELn3 - ELSELn0) */
#define _00_ELC_EVENT_LINK_OFF      (0x00U) /* prohibit event link */
#define _01_ELC_EVENT_LINK_AD       (0x01U) /* link destination AD */
#define _02_ELC_EVENT_LINK_TAU00    (0x02U) /* link destination TAU00 */
#define _03_ELC_EVENT_LINK_TAU01    (0x03U) /* link destination TAU01 */
#define _04_ELC_EVENT_LINK_RJ0      (0x04U) /* link destination RJ0 */
#define _05_ELC_EVENT_LINK_RG       (0x05U) /* link destination RG */
#define _06_ELC_EVENT_LINK_RD0      (0x06U) /* link destination RD0 */
#define _07_ELC_EVENT_LINK_RD1      (0x07U) /* link destination RD1 */

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
#define ELC_DESTINATION_COUNT       (20U) 

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Global functions
***********************************************************************************************************************/
void R_ELC_Create(void);
void R_ELC_Stop(uint32_t event);

/* Start user code for function. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#endif
