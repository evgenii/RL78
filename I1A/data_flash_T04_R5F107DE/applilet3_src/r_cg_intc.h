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
* File Name    : r_cg_intc.h
* Version      : Applilet3 for RL78/I1A V1.01.01 [05 Oct 2011]
* Device(s)    : R5F107DE
* Tool-Chain   : IAR Systems iccrl78
* Description  : This file implements device driver for INTC module.
* Creation Date: 14.02.2013
***********************************************************************************************************************/

#ifndef INTC_H
#define INTC_H

/***********************************************************************************************************************
Macro definitions (Register bit)
***********************************************************************************************************************/

/*
    External Interrupt Rising Edge Enable Register 0 (EGP0)
*/
/* INTPn pin valid edge selection (EGPn) */
#define _01_INTP0_EDGE_RISING_SEL           (0x01U)    /* rising edge selected for INTP0 pin */
#define _00_INTP0_EDGE_RISING_UNSEL         (0x00U)    /* rising edge not selected for INTP0 pin */
#define _08_INTP3_EDGE_RISING_SEL           (0x08U)    /* rising edge selected for INTP3 pin */
#define _00_INTP3_EDGE_RISING_UNSEL         (0x00U)    /* rising edge not selected for INTP3 pin */
#define _10_INTP4_EDGE_RISING_SEL           (0x10U)    /* rising edge selected for INTP4 pin */
#define _00_INTP4_EDGE_RISING_UNSEL         (0x00U)    /* rising edge not selected for INTP4 pin */

/*
    External Interrupt Falling Edge Enable Register 0 (EGN0)
*/
/* INTPn pin valid edge selection (EGNn) */
#define _01_INTP0_EDGE_FALLING_SEL          (0x01U)    /* falling edge selected for INTP0 pin */
#define _00_INTP0_EDGE_FALLING_UNSEL        (0x00U)    /* falling edge not selected for INTP0 pin */
#define _08_INTP3_EDGE_FALLING_SEL          (0x08U)    /* falling edge selected for INTP3 pin */
#define _00_INTP3_EDGE_FALLING_UNSEL        (0x00U)    /* falling edge not selected for INTP3 pin */
#define _10_INTP4_EDGE_FALLING_SEL          (0x10U)    /* falling edge selected for INTP4 pin */
#define _00_INTP4_EDGE_FALLING_UNSEL        (0x00U)    /* falling edge not selected for INTP4 pin */

/*
    External Interrupt Rising Edge Enable Register 1 (EGP1)
*/
/* INTPn pin valid edge selection (EGPn) */
#define _02_INTP9_EDGE_RISING_SEL           (0x02U)    /* rising edge selected for INTP9 pin */
#define _00_INTP9_EDGE_RISING_UNSEL         (0x00U)    /* rising edge not selected for INTP9 pin */
#define _04_INTP10_EDGE_RISING_SEL          (0x04U)    /* rising edge selected for INTP10 pin */
#define _00_INTP10_EDGE_RISING_UNSEL        (0x00U)    /* rising edge not selected for INTP10 pin */
#define _08_INTP11_EDGE_RISING_SEL          (0x08U)    /* rising edge selected for INTP11 pin */
#define _00_INTP11_EDGE_RISING_UNSEL        (0x00U)    /* rising edge not selected for INTP11 pin */

/*
    External Interrupt Falling Edge Enable Register 1 (EGN1)
*/
/* INTPn pin valid edge selection (EGNn) */
#define _02_INTP9_EDGE_FALLING_SEL          (0x02U)    /* falling edge selected for INTP9 pin */
#define _00_INTP9_EDGE_FALLING_UNSEL        (0x00U)    /* falling edge not selected for INTP9 pin */
#define _04_INTP10_EDGE_FALLING_SEL         (0x04U)    /* falling edge selected for INTP10 pin */
#define _00_INTP10_EDGE_FALLING_UNSEL       (0x00U)    /* falling edge not selected for INTP10 pin */
#define _08_INTP11_EDGE_FALLING_SEL         (0x08U)    /* falling edge selected for INTP11 pin */
#define _00_INTP11_EDGE_FALLING_UNSEL       (0x00U)    /* falling edge not selected for INTP11 pin */

/*
    External Interrupt Rising Edge Enable Register 2 (EGP2)
*/
/* INTPn pin valid edge selection (EGPn) */
#define _01_INTP20_EDGE_RISING_SEL          (0x01U)    /* rising edge selected for INTP20 pin */
#define _00_INTP20_EDGE_RISING_UNSEL        (0x00U)    /* rising edge not selected for INTP20 pin */
#define _02_INTP21_EDGE_RISING_SEL          (0x02U)    /* rising edge selected for INTP21 pin */
#define _00_INTP21_EDGE_RISING_UNSEL        (0x00U)    /* rising edge not selected for INTP21 pin */
#define _04_INTP22_EDGE_RISING_SEL          (0x04U)    /* rising edge selected for INTP22 pin */
#define _00_INTP22_EDGE_RISING_UNSEL        (0x00U)    /* rising edge not selected for INTP22 pin */
#define _08_INTP23_EDGE_RISING_SEL          (0x08U)    /* rising edge selected for INTP23 pin */
#define _00_INTP23_EDGE_RISING_UNSEL        (0x00U)    /* rising edge not selected for INTP23 pin */

/*
    External Interrupt Falling Edge Enable Register 2 (EGN2)
*/
/* INTPn pin valid edge selection (EGNn) */
#define _01_INTP20_EDGE_FALLING_SEL         (0x01U)    /* falling edge selected for INTP20 pin */
#define _00_INTP20_EDGE_FALLING_UNSEL       (0x00U)    /* falling edge not selected for INTP20 pin */
#define _02_INTP21_EDGE_FALLING_SEL         (0x02U)    /* falling edge selected for INTP21 pin */
#define _00_INTP21_EDGE_FALLING_UNSEL       (0x00U)    /* falling edge not selected for INTP21 pin */
#define _04_INTP22_EDGE_FALLING_SEL         (0x04U)    /* falling edge selected for INTP22 pin */
#define _00_INTP22_EDGE_FALLING_UNSEL       (0x00U)    /* falling edge not selected for INTP22 pin */
#define _08_INTP23_EDGE_FALLING_SEL         (0x08U)    /* falling edge selected for INTP23 pin */
#define _00_INTP23_EDGE_FALLING_UNSEL       (0x00U)    /* falling edge not selected for INTP23 pin */

/*
    Peripheral function switch register 0 (PFSEL0)
*/
/* Use/Do not use external interrupt INTP20 noise filter (PNFEN) */
#define _00_INTP20_NOISE_FILTER_ENABLED     (0x00U)
#define _10_INTP20_NOISE_FILTER_DISABLED    (0x10U)
/* Use selection for external interrupt INTP21 (TMRSTEN1) */
#define _00_INTP21_CLEAR_STOP               (0x00U)
#define _02_INTP21_TIMER_RESTART            (0x02U)
/* Use selection for external interrupt INTP20 (TMRSTEN0) */
#define _00_INTP20_CLEAR_STOP               (0x00U)
#define _01_INTP20_TIMER_RESTART            (0x01U)

/*
    External Interrupt Control Register (INTPCTL)
*/
/* Inverted output setting of INTP21 signal */
#define _00_INTP21_OUTPUT_NORMAL            (0x00U)
#define _02_INTP21_OUTPUT_INVERTED          (0x02U)
/* Inverted output setting of INTP20 signal */
#define _00_INTP20_OUTPUT_NORMAL            (0x00U)
#define _01_INTP20_OUTPUT_INVERTED          (0x01U)

/*
    Comparator rising edge enable register 0 (CMPEGP0)
*/
/* INTP20 pin valid edge selection */
#define _40_INTP20_CMP_EDGE_RISING_SEL      (0x40U)    /* rising edge selected for INTP20 pin */
#define _00_INTP20_CMP_EDGE_RISING_UNSEL    (0x00U)    /* rising edge not selected for INTP20 pin */
/* INTP21 pin valid edge selection */
#define _80_INTP21_CMP_EDGE_RISING_SEL      (0x80U)    /* rising edge selected for INTP21 pin */
#define _00_INTP21_CMP_EDGE_RISING_UNSEL    (0x00U)    /* rising edge not selected for INTP21 pin */

/*
    Comparator Falling Edge Enable Register 0 (CMPEGN0)
*/
/* INTP20 pin valid edge selection */
#define _40_INTP20_CMP_EDGE_FALLING_SEL     (0x40U)    /* falling edge selected for INTP20 pin */
#define _00_INTP20_CMP_EDGE_FALLING_UNSEL   (0x00U)    /* falling edge not selected for INTP20 pin */
/* INTP21 pin valid edge selection */
#define _80_INTP21_CMP_EDGE_FALLING_SEL     (0x80U)    /* falling edge selected for INTP21 pin */
#define _00_INTP21_CMP_EDGE_FALLING_UNSEL   (0x00U)    /* falling edge not selected for INTP21 pin */


/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Global functions
***********************************************************************************************************************/
void R_INTC_Create(void);
void R_INTC0_Start(void);
void R_INTC0_Stop(void);

#endif
