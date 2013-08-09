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
* File Name    : r_cg_timer.h
* Version      : Applilet3 for RL78/I1A V2.00.00.05 [12 Apr 2013]
* Device(s)    : R5F107DE
* Tool-Chain   : IAR Systems iccrl78
* Description  : This file implements device driver for TAU module.
* Creation Date: 31.07.2013
***********************************************************************************************************************/

#ifndef TAU_H
#define TAU_H

/***********************************************************************************************************************
Macro definitions (Register bit)
***********************************************************************************************************************/
/*
    Peripheral Enable Register 0 (PER0)
*/
/* Control of timer array unit 0 input clock (TAU0EN) */
#define _00_TAU0_CLOCK_STOP                 (0x00U)       /* stops supply of input clock */
#define _01_TAU0_CLOCK_SUPPLY               (0x01U)       /* supplies input clock */

/*
    Timer Clock Select Register m (TPS0)
*/
/* Operating mode and clear mode selection (PRS003 - PRS000) */
#define _0000_TAU_CKM0_FCLK_0               (0x0000U)     /* ckm0 - fCLK */
#define _0001_TAU_CKM0_FCLK_1               (0x0001U)     /* ckm0 - fCLK/2^1 */
#define _0002_TAU_CKM0_FCLK_2               (0x0002U)     /* ckm0 - fCLK/2^2 */
#define _0003_TAU_CKM0_FCLK_3               (0x0003U)     /* ckm0 - fCLK/2^3 */
#define _0004_TAU_CKM0_FCLK_4               (0x0004U)     /* ckm0 - fCLK/2^4 */
#define _0005_TAU_CKM0_FCLK_5               (0x0005U)     /* ckm0 - fCLK/2^5 */
#define _0006_TAU_CKM0_FCLK_6               (0x0006U)     /* ckm0 - fCLK/2^6 */
#define _0007_TAU_CKM0_FCLK_7               (0x0007U)     /* ckm0 - fCLK/2^7 */
#define _0008_TAU_CKM0_FCLK_8               (0x0008U)     /* ckm0 - fCLK/2^8 */
#define _0009_TAU_CKM0_FCLK_9               (0x0009U)     /* ckm0 - fCLK/2^9 */
#define _000A_TAU_CKM0_FCLK_10              (0x000AU)     /* ckm0 - fCLK/2^10 */
#define _000B_TAU_CKM0_FCLK_11              (0x000BU)     /* ckm0 - fCLK/2^11 */
#define _000C_TAU_CKM0_FCLK_12              (0x000CU)     /* ckm0 - fCLK/2^12 */
#define _000D_TAU_CKM0_FCLK_13              (0x000DU)     /* ckm0 - fCLK/2^13 */
#define _000E_TAU_CKM0_FCLK_14              (0x000EU)     /* ckm0 - fCLK/2^14 */
#define _000F_TAU_CKM0_FCLK_15              (0x000FU)     /* ckm0 - fCLK/2^15 */
/* Operating mode and clear mode selection (PRS013 - PRS010) */
#define _0000_TAU_CKM1_FCLK_0               (0x0000U)     /* ckm1 - fCLK */
#define _0010_TAU_CKM1_FCLK_1               (0x0010U)     /* ckm1 - fCLK/2^1 */
#define _0020_TAU_CKM1_FCLK_2               (0x0020U)     /* ckm1 - fCLK/2^2 */
#define _0030_TAU_CKM1_FCLK_3               (0x0030U)     /* ckm1 - fCLK/2^3 */
#define _0040_TAU_CKM1_FCLK_4               (0x0040U)     /* ckm1 - fCLK/2^4 */
#define _0050_TAU_CKM1_FCLK_5               (0x0050U)     /* ckm1 - fCLK/2^5 */
#define _0060_TAU_CKM1_FCLK_6               (0x0060U)     /* ckm1 - fCLK/2^6 */
#define _0070_TAU_CKM1_FCLK_7               (0x0070U)     /* ckm1 - fCLK/2^7 */
#define _0080_TAU_CKM1_FCLK_8               (0x0080U)     /* ckm1 - fCLK/2^8 */
#define _0090_TAU_CKM1_FCLK_9               (0x0090U)     /* ckm1 - fCLK/2^9 */
#define _00A0_TAU_CKM1_FCLK_10              (0x00A0U)     /* ckm1 - fCLK/2^10 */
#define _00B0_TAU_CKM1_FCLK_11              (0x00B0U)     /* ckm1 - fCLK/2^11 */
#define _00C0_TAU_CKM1_FCLK_12              (0x00C0U)     /* ckm1 - fCLK/2^12 */
#define _00D0_TAU_CKM1_FCLK_13              (0x00D0U)     /* ckm1 - fCLK/2^13 */
#define _00E0_TAU_CKM1_FCLK_14              (0x00E0U)     /* ckm1 - fCLK/2^14 */
#define _00F0_TAU_CKM1_FCLK_15              (0x00F0U)     /* ckm1 - fCLK/2^15 */
/* Operating mode and clear mode selection (PRS021 - PRS020) */
#define _0000_TAU_CKM2_FCLK_1               (0x0000U)     /* ckm2 - fCLK/2^1 */
#define _0100_TAU_CKM2_FCLK_2               (0x0100U)     /* ckm2 - fCLK/2^2 */
#define _0200_TAU_CKM2_FCLK_4               (0x0200U)     /* ckm2 - fCLK/2^4 */
#define _0300_TAU_CKM2_FCLK_6               (0x0300U)     /* ckm2 - fCLK/2^6 */
/* Operating mode and clear mode selection (PRS031 - PRS030) */
#define _0000_TAU_CKM3_FCLK_8               (0x0000U)     /* ckm2 - fCLK/2^8 */
#define _1000_TAU_CKM3_FCLK_10              (0x1000U)     /* ckm2 - fCLK/2^10 */
#define _2000_TAU_CKM3_FCLK_12              (0x2000U)     /* ckm2 - fCLK/2^12 */
#define _3000_TAU_CKM3_FCLK_14              (0x3000U)     /* ckm2 - fCLK/2^14 */

/*
    Timer Mode Register 0n (TMR0n)
*/
/* Selection of macro clock (MCK) of channel n (CKS0n1 - CKS0n0) */
#define _0000_TAU_CLOCK_SELECT_CKM0         (0x0000U)     /* operation clock CK0 set by PRS register */
#define _8000_TAU_CLOCK_SELECT_CKM1         (0x8000U)     /* operation clock CK1 set by PRS register */
#define _4000_TAU_CLOCK_SELECT_CKM2         (0x4000U)     /* operation clock CK2 set by PRS register */
#define _C000_TAU_CLOCK_SELECT_CKM3         (0xC000U)     /* operation clock CK3 set by PRS register */
/* Selection of count clock (CCK) of channel n (CCS0n) */
#define _0000_TAU_CLOCK_MODE_CKS            (0x0000U)     /* macro clock MCK specified by CKS0n bit */
#define _1000_TAU_CLOCK_MODE_TIMN           (0x1000U)     /* valid edge of input signal input from TI0n pin */
/* Selection of slave/master of channel n (MASTER0n) */
#define _0000_TAU_COMBINATION_SLAVE         (0x0000U)     /* slave channel with combination operation function */
#define _0800_TAU_COMBINATION_MASTER        (0x0800U)     /* master channel with combination operation function */
/* Operation explanation of channel 1 or 3 (SPLIT) */
#define _0000_TAU_16BITS_MODE               (0x0000U)     /* operates as 16 bits timer */
#define _0800_TAU_8BITS_MODE                (0x0800U)     /* operates as 8 bits timer */
/* Setting of start trigger or capture trigger of channel n (STS0n2 - STS0n0) */
#define _0000_TAU_TRIGGER_SOFTWARE          (0x0000U)     /* only software trigger start is valid */
#define _0100_TAU_TRIGGER_TIMN_VALID        (0x0100U)     /* valid edge of TI0n pin input is used as both the start */
                                                          /* trigger and capture trigger */
#define _0200_TAU_TRIGGER_TIMN_BOTH         (0x0200U)     /* both the edges of TI0n pin input are used as a start */
                                                          /* trigger and a capture trigger */
#define _0400_TAU_TRIGGER_MASTER_INT        (0x0400U)     /* interrupt signal of the master channel is used */
/* Selection of TI0n pin input valid edge (CIS0n1 - CIS0n0) */
#define _0000_TAU_TIMN_EDGE_FALLING         (0x0000U)     /* falling edge */
#define _0040_TAU_TIMN_EDGE_RISING          (0x0040U)     /* rising edge */
#define _0080_TAU_TIMN_EDGE_BOTH_LOW        (0x0080U)     /* both edges (when low-level width is measured) */
#define _00C0_TAU_TIMN_EDGE_BOTH_HIGH       (0x00C0U)     /* both edges (when high-level width is measured) */
/* Operation mode of channel n (MD0n3 - MD0n0) */
#define _0000_TAU_MODE_INTERVAL_TIMER       (0x0000U)     /* interval timer mode */
#define _0004_TAU_MODE_CAPTURE              (0x0004U)     /* capture mode */
#define _0006_TAU_MODE_EVENT_COUNT          (0x0006U)     /* event counter mode */
#define _0008_TAU_MODE_ONE_COUNT            (0x0008U)     /* one count mode */
#define _000C_TAU_MODE_HIGHLOW_MEASURE      (0x000CU)     /* high-/low-level width measurement mode */
#define _0001_TAU_MODE_PWM_MASTER           (0x0001U)     /* PWM Function (Master Channel) mode */
#define _0009_TAU_MODE_PWM_SLAVE            (0x0009U)     /* PWM Function (Slave Channel) mode */
#define _0008_TAU_MODE_ONESHOT              (0x0008U)     /* one-shot pulse output mode */
/* Setting of starting counting and interrupt (MD0n0) */
#define _0000_TAU_START_INT_UNUSED          (0x0000U)     /* timer interrupt is not generated when counting starts */
                                                          /* (timer output does not change, either) */
#define _0001_TAU_START_INT_USED            (0x0001U)     /* timer interrupt is generated when counting starts */
                                                          /* (timer output also changes) */

/*
    Timer Status Register 0n (TSR0n)
*/
/* Counter overflow status of channel n (OVF) */
#define _0000_TAU_OVERFLOW_NOT_OCCURS       (0x0000U)     /* overflow does not occur */
#define _0001_TAU_OVERFLOW_OCCURS           (0x0001U)     /* overflow occurs */

/*
    Timer Channel Enable Status Register 0 (TE0)
*/
/* Indication of operation enable/stop status of channel 0 (TE00) */
#define _0000_TAU_CH0_OPERATION_STOP        (0x0000U)     /* operation is stopped */
#define _0001_TAU_CH0_OPERATION_ENABLE      (0x0001U)     /* operation is enabled */
/* Indication of operation enable/stop status of channel 1 (TE01) */
#define _0000_TAU_CH1_OPERATION_STOP        (0x0000U)     /* operation is stopped */
#define _0002_TAU_CH1_OPERATION_ENABLE      (0x0002U)     /* operation is enabled */
/* Indication of operation enable/stop status of channel 2 (TE02) */
#define _0000_TAU_CH2_OPERATION_STOP        (0x0000U)     /* operation is stopped */
#define _0004_TAU_CH2_OPERATION_ENABLE      (0x0004U)     /* operation is enabled */
/* Indication of operation enable/stop status of channel 3 (TE03) */
#define _0000_TAU_CH3_OPERATION_STOP        (0x0000U)     /* operation is stopped */
#define _0008_TAU_CH3_OPERATION_ENABLE      (0x0008U)     /* operation is enabled */
/* Indication of operation enable/stop status of channel 4 (TE04) */
#define _0000_TAU_CH4_OPERATION_STOP        (0x0000U)     /* operation is stopped */
#define _0010_TAU_CH4_OPERATION_ENABLE      (0x0010U)     /* operation is enabled */
/* Indication of operation enable/stop status of channel 5 (TE05) */
#define _0000_TAU_CH5_OPERATION_STOP        (0x0000U)     /* operation is stopped */
#define _0020_TAU_CH5_OPERATION_ENABLE      (0x0020U)     /* operation is enabled */
/* Indication of operation enable/stop status of channel 6 (TE06) */
#define _0000_TAU_CH6_OPERATION_STOP        (0x0000U)     /* operation is stopped */
#define _0040_TAU_CH6_OPERATION_ENABLE      (0x0040U)     /* operation is enabled */
/* Indication of operation enable/stop status of channel 7 (TE07) */
#define _0000_TAU_CH7_OPERATION_STOP        (0x0000U)     /* operation is stopped */
#define _0080_TAU_CH7_OPERATION_ENABLE      (0x0080U)     /* operation is enabled */
/* Indication of operation enable/stop status of channel 1 higher 8 bits (TEHm1) */
#define _0000_TAU_CH1_H8_OPERATION_STOP     (0x0000U)     /* operation is stopped */
#define _0200_TAU_CH1_H8_OPERATION_ENABLE   (0x0200U)     /* operation is enabled */
/* Indication of operation enable/stop status of channel 3 higher 8 bits (TEHm3) */
#define _0000_TAU_CH3_H8_OPERATION_STOP     (0x0000U)     /* operation is stopped */
#define _0800_TAU_CH3_H8_OPERATION_ENABLE   (0x0800U)     /* operation is enabled */

/*
    Timer Channel Start Register 0(TS0)
*/
/* Operation enable (start) trigger of channel 0 (TS00) */
#define _0000_TAU_CH0_START_TRG_OFF         (0x0000U)     /* no trigger operation */
#define _0001_TAU_CH0_START_TRG_ON          (0x0001U)     /* operation is enabled (start software trigger generated) */
/* Operation enable (start) trigger of channel 1 (TS01) */
#define _0000_TAU_CH1_START_TRG_OFF         (0x0000U)     /* no trigger operation */
#define _0002_TAU_CH1_START_TRG_ON          (0x0002U)     /* operation is enabled (start software trigger generated) */
/* Operation enable (start) trigger of channel 2 (TS02) */
#define _0000_TAU_CH2_START_TRG_OFF         (0x0000U)     /* no trigger operation */
#define _0004_TAU_CH2_START_TRG_ON          (0x0004U)     /* operation is enabled (start software trigger generated) */
/* Operation enable (start) trigger of channel 3 (TS03) */
#define _0000_TAU_CH3_START_TRG_OFF         (0x0000U)     /* no trigger operation */
#define _0008_TAU_CH3_START_TRG_ON          (0x0008U)     /* operation is enabled (start software trigger generated) */
/* Operation enable (start) trigger of channel 4 (TS04) */
#define _0000_TAU_CH4_START_TRG_OFF         (0x0000U)     /* no trigger operation */
#define _0010_TAU_CH4_START_TRG_ON          (0x0010U)     /* operation is enabled (start software trigger generated) */
/* Operation enable (start) trigger of channel 5 (TS05) */
#define _0000_TAU_CH5_START_TRG_OFF         (0x0000U)     /* no trigger operation */
#define _0020_TAU_CH5_START_TRG_ON          (0x0020U)     /* operation is enabled (start software trigger generated) */
/* Operation enable (start) trigger of channel 6 (TS06) */
#define _0000_TAU_CH6_START_TRG_OFF         (0x0000U)     /* no trigger operation */
#define _0040_TAU_CH6_START_TRG_ON          (0x0040U)     /* operation is enabled (start software trigger generated) */
/* Operation enable (start) trigger of channel 7 (TS07) */
#define _0000_TAU_CH7_START_TRG_OFF         (0x0000U)     /* no trigger operation */
#define _0080_TAU_CH7_START_TRG_ON          (0x0080U)     /* operation is enabled (start software trigger generated) */
/* Operation enable (start) trigger of channel 1 higher 8 bits (TSH01) */
#define _0000_TAU_CH1_H8_START_TRG_OFF      (0x0000U)     /* no trigger operation */
#define _0200_TAU_CH1_H8_START_TRG_ON       (0x0200U)     /* operation is enabled (start software trigger generated) */
/* Operation enable (start) trigger of channel 3 higher 8 bits (TSH03) */
#define _0000_TAU_CH3_H8_START_TRG_OFF      (0x0000U)     /* no trigger operation */
#define _0800_TAU_CH3_H8_START_TRG_ON       (0x0800U)     /* operation is enabled (start software trigger generated) */

/*
    Timer Channel Stop Register 0 (TT0)
*/
/* Operation stop trigger of channel 0 (TT00) */
#define _0000_TAU_CH0_STOP_TRG_OFF          (0x0000U)     /* no trigger operation */
#define _0001_TAU_CH0_STOP_TRG_ON           (0x0001U)     /* operation is stopped (stop trigger generated) */
/* Operation stop trigger of channel 1 (TT01) */
#define _0000_TAU_CH1_STOP_TRG_OFF          (0x0000U)     /* no trigger operation */
#define _0002_TAU_CH1_STOP_TRG_ON           (0x0002U)     /* operation is stopped (stop trigger generated) */
/* Operation stop trigger of channel 2 (TT02) */
#define _0000_TAU_CH2_STOP_TRG_OFF          (0x0000U)     /* no trigger operation */
#define _0004_TAU_CH2_STOP_TRG_ON           (0x0004U)     /* operation is stopped (stop trigger generated) */
/* Operation stop trigger of channel 3 (TT03) */
#define _0000_TAU_CH3_STOP_TRG_OFF          (0x0000U)     /* no trigger operation */
#define _0008_TAU_CH3_STOP_TRG_ON           (0x0008U)     /* operation is stopped (stop trigger generated) */
/* Operation stop trigger of channel 4 (TT04) */
#define _0000_TAU_CH4_STOP_TRG_OFF          (0x0000U)     /* no trigger operation */
#define _0010_TAU_CH4_STOP_TRG_ON           (0x0010U)     /* operation is stopped (stop trigger generated) */
/* Operation stop trigger of channel 5 (TT05) */
#define _0000_TAU_CH5_STOP_TRG_OFF          (0x0000U)     /* no trigger operation */
#define _0020_TAU_CH5_STOP_TRG_ON           (0x0020U)     /* operation is stopped (stop trigger generated) */
/* Operation stop trigger of channel 6 (TT06) */
#define _0000_TAU_CH6_STOP_TRG_OFF          (0x0000U)     /* no trigger operation */
#define _0040_TAU_CH6_STOP_TRG_ON           (0x0040U)     /* operation is stopped (stop trigger generated) */
/* Operation stop trigger of channel 7 (TT07) */
#define _0000_TAU_CH7_STOP_TRG_OFF          (0x0000U)     /* no trigger operation */
#define _0080_TAU_CH7_STOP_TRG_ON           (0x0080U)     /* operation is stopped (stop trigger generated) */
/* Operation stop trigger of channel 1 higher 8 bits (TTH01) */
#define _0000_TAU_CH1_H8_STOP_TRG_OFF       (0x0000U)     /* no trigger operation */
#define _0200_TAU_CH1_H8_STOP_TRG_ON        (0x0200U)     /* operation is stopped (stop trigger generated) */
/* Operation stop trigger of channel 3 higher 8 bits (TTH03) */
#define _0000_TAU_CH3_H8_STOP_TRG_OFF       (0x0000U)     /* no trigger operation */
#define _0800_TAU_CH3_H8_STOP_TRG_ON        (0x0800U)     /* operation is stopped (stop trigger generated) */

/*
    Timer Input Select Register 0 (TIS0)
*/
/* Selection of timer input used with channel 5 (TIS02 - TIS00) */
#define _00_TAU_CH5_INPUT_TI05              (0x00U)       /* input signal of timer input pin (TI05) */
#define _01_TAU_CH5_INPUT_TI05              (0x01U)       /* input signal of timer input pin (TI05) */
#define _02_TAU_CH5_INPUT_TI05              (0x02U)       /* input signal of timer input pin (TI05) */
#define _03_TAU_CH5_INPUT_TI05              (0x03U)       /* input signal of timer input pin (TI05) */
#define _04_TAU_CH5_INPUT_FIL               (0x04U)       /* internal low speed oscillation colock (fIL) */
#define _05_TAU_CH5_INPUT_FSUB              (0x05U)       /* sub colock (fSUB) */

/*
    Timer Output Enable Register 0 (TOE0)
*/
/* Timer output enable/disable of channel 3 (TOE03) */
#define _0008_TAU_CH3_OUTPUT_ENABLE         (0x0008U)     /* TOE03 operation enabled by count operation */
#define _0000_TAU_CH3_OUTPUT_DISABLE        (0x0000U)     /* TOE03 operation stopped by count operation */
/* Timer output enable/disable of channel 5 (TOE05) */
#define _0020_TAU_CH5_OUTPUT_ENABLE         (0x0020U)     /* TOE05 operation enabled by count operation */
#define _0000_TAU_CH5_OUTPUT_DISABLE        (0x0000U)     /* TOE05 operation stopped by count operation */
/* Timer output enable/disable of channel 6 (TOE06) */
#define _0040_TAU_CH6_OUTPUT_ENABLE         (0x0040U)     /* TOE06 operation enabled by count operation */
#define _0000_TAU_CH6_OUTPUT_DISABLE        (0x0000U)     /* TOE06 operation stopped by count operation */

/*
    Timer Output Register 0 (TO0)
*/
/* Timer output of channel 3 (TO03) */
#define _0000_TAU_CH3_OUTPUT_VALUE_0        (0x0000U)     /* timer output value is "0" */
#define _0008_TAU_CH3_OUTPUT_VALUE_1        (0x0008U)     /* timer output value is "1" */
/* Timer output of channel 5 (TO05) */
#define _0000_TAU_CH5_OUTPUT_VALUE_0        (0x0000U)     /* timer output value is "0" */
#define _0020_TAU_CH5_OUTPUT_VALUE_1        (0x0020U)     /* timer output value is "1" */
/* Timer output of channel 6 (TO06) */
#define _0000_TAU_CH6_OUTPUT_VALUE_0        (0x0000U)     /* timer output value is "0" */
#define _0040_TAU_CH6_OUTPUT_VALUE_1        (0x0040U)     /* timer output value is "1" */

/*
    Timer Output Level Register 0 (TOL0)
*/
/* Control of timer output level of channel 3 (TOL03) */
#define _0000_TAU_CH3_OUTPUT_LEVEL_H        (0x0000U)     /* positive logic output (active-high) */
#define _0008_TAU_CH3_OUTPUT_LEVEL_L        (0x0008U)     /* inverted output (active-low) */
/* Control of timer output level of channel 5 (TOL05) */
#define _0000_TAU_CH5_OUTPUT_LEVEL_H        (0x0000U)     /* positive logic output (active-high) */
#define _0020_TAU_CH5_OUTPUT_LEVEL_L        (0x0020U)     /* inverted output (active-low) */
/* Control of timer output level of channel 6 (TOL06) */
#define _0000_TAU_CH6_OUTPUT_LEVEL_H        (0x0000U)     /* positive logic output (active-high) */
#define _0040_TAU_CH6_OUTPUT_LEVEL_L        (0x0040U)     /* inverted output (active-low) */

/*
    Timer Output Mode Register 0 (TOM0)
*/
/* Control of timer output mode of channel 3 (TOM03) */
#define _0000_TAU_CH3_OUTPUT_TOGGLE         (0x0000U)      /* toggle operation mode */
#define _0008_TAU_CH3_OUTPUT_COMBIN         (0x0008U)      /* combination operation mode */
/* Control of timer output mode of channel 5 (TOM05) */
#define _0000_TAU_CH5_OUTPUT_TOGGLE         (0x0000U)      /* toggle operation mode */
#define _0020_TAU_CH5_OUTPUT_COMBIN         (0x0020U)      /* combination operation mode */
/* Control of timer output mode of channel 6 (TOM06) */
#define _0000_TAU_CH6_OUTPUT_TOGGLE         (0x0000U)      /* toggle operation mode */
#define _0040_TAU_CH6_OUTPUT_COMBIN         (0x0040U)      /* combination operation mode */

/*
    Input Switch Control Register (ISC)
*/
/* Switching channel 7 input of timer array unit (ISC1) */
#define _00_TAU_CH7_NO_INPUT                (0x00U)       /* timer input is not used */
#define _02_TAU_CH7_RXD0_INPUT              (0x02U)       /* input signal of RxD0 pin is used as timer input */
/* Switching external interrupt INTP0 input (ISC0) */
#define _00_TAU_EXTERNAL_INTP0_INPUT        (0x00U)       /* input signal of INTP0 pin is used as external interrupt */
#define _01_TAU_EXTERNAL_RXD0_INPUT         (0x01U)       /* input signal of RxD0 pin is used as external interrupt */

/*
    Noise Filter Enable Register 1 (NFEN1)
*/
/* Enable/disable using noise filter of TI07 pin input signal (TNFEN07) */
#define _00_TAU_CH7_NOISE_OFF               (0x00U)       /* noise filter OFF */
#define _80_TAU_CH7_NOISE_ON                (0x80U)       /* noise filter ON */
/* Enable/disable using noise filter of TI06 pin input signal (TNFEN06) */
#define _00_TAU_CH6_NOISE_OFF               (0x00U)       /* noise filter OFF */
#define _40_TAU_CH6_NOISE_ON                (0x40U)       /* noise filter ON */
/* Enable/disable using noise filter of TI05 pin input signal (TNFEN05) */
#define _00_TAU_CH5_NOISE_OFF               (0x00U)       /* noise filter OFF */
#define _20_TAU_CH5_NOISE_ON                (0x20U)       /* noise filter ON */
/* Enable/disable using noise filter of TI03 pin input signal (TNFEN03) */
#define _00_TAU_CH3_NOISE_OFF               (0x00U)       /* noise filter OFF */
#define _08_TAU_CH3_NOISE_ON                (0x08U)       /* noise filter ON */

/*
    Peripheral Enable Register 2 (PER2)
*/
/* Control of timer array unit input clock (TKB0EN) */
#define _00_TMKB0_CLOCK_STOP                            (0x00U)    /* stops supply of input clock */
#define _01_TMKB0_CLOCK_SUPPLY                          (0x01U)    /* supplies input clock */
/* Control of timer array unit input clock (TKB1EN) */
#define _00_TMKB1_CLOCK_STOP                            (0x00U)    /* stops supply of input clock */
#define _02_TMKB1_CLOCK_SUPPLY                          (0x02U)    /* supplies input clock */
/* Control of timer array unit input clock (TKB2EN) */
#define _00_TMKB2_CLOCK_STOP                            (0x00U)    /* stops supply of input clock */
#define _04_TMKB2_CLOCK_SUPPLY                          (0x04U)    /* supplies input clock */

/*
    Timer Clock Select Register 2 (TPS2)
*/
/* Operating clock for CK20 (TPS202 - TPS200) */
#define _00_TMKB_CK20_FCLK_0                            (0x00U)    /* fclk */
#define _01_TMKB_CK20_FCLK_1                            (0x01U)    /* fclk/2^1 */
#define _02_TMKB_CK20_FCLK_2                            (0x02U)    /* fclk/2^2 */
#define _03_TMKB_CK20_FCLK_3                            (0x03U)    /* fclk/2^3 */
#define _04_TMKB_CK20_FCLK_4                            (0x04U)    /* fclk/2^4 */
#define _05_TMKB_CK20_FCLK_5                            (0x05U)    /* fclk/2^5 */
/* Operating clock for CK21 (TPS212 - TPS210) */
#define _00_TMKB_CK21_FCLK_0                            (0x00U)    /* fclk */
#define _10_TMKB_CK21_FCLK_1                            (0x10U)    /* fclk/2^1 */
#define _20_TMKB_CK21_FCLK_2                            (0x20U)    /* fclk/2^2 */
#define _30_TMKB_CK21_FCLK_3                            (0x30U)    /* fclk/2^3 */
#define _40_TMKB_CK21_FCLK_4                            (0x40U)    /* fclk/2^4 */
#define _50_TMKB_CK21_FCLK_5                            (0x50U)    /* fclk/2^5 */

/*
    Operation Control Register n0 (TKBCTLn0)
*/
/* Control of TKBOnp output gate function by timer KC0 output (TKBGTEnp)*/
#define _0000_TMKB_OUTPUT_GATE0_DISABLE                 (0x0000U)
#define _0400_TMKB_OUTPUT_GATE0_ENABLE                  (0x0400U)
#define _0000_TMKB_OUTPUT_GATE1_DISABLE                 (0x0000U)
#define _4000_TMKB_OUTPUT_GATE1_ENABLE                  (0x4000U)
/* Control of TKBOnp PWM output smooth start function (TKBSSEnp) */
#define _0000_TMKB_SMOOTH_START0_DISABLE                (0x0000U)
#define _0200_TMKB_SMOOTH_START0_ENABLE                 (0x0200U)
#define _0000_TMKB_SMOOTH_START1_DISABLE                (0x0000U)
#define _2000_TMKB_SMOOTH_START1_ENABLE                 (0x2000U)
/* Control of TKBOnp PWM output dithering function (TKBDIEnp) */
#define _0000_TMKB_DITHERING0_DISABLE                   (0x0000U)
#define _0100_TMKB_DITHERING0_ENABLE                    (0x0100U)
#define _0000_TMKB_DITHERING1_DISABLE                   (0x0000U)
#define _1000_TMKB_DITHERING1_ENABLE                    (0x1000U)
/* Control of TKBOn0 and TKBOn1 maximum frequency limit function (TKBMFEn) */
#define _0000_TMKB_MAXFREQ_DISABLE                      (0x0000U)
#define _0080_TMKB_MAXFREQ_ENABLE                       (0x0080U)
/* TKBOn1 judgment range setting for interleave PFC output mode (TKBISRn1 - TKBISRn0) */
#define _0000_TMKB_RANGE_T64                            (0x0000U)
#define _0010_TMKB_RANGE_T32                            (0x0010U)
#define _0020_TMKB_RANGE_T16                            (0x0020U)
#define _0030_TMKB_RANGE_T8                             (0x0030U)
/* Control of compare register batch overwrite function set by external trigger (TKBTSEn) */
#define _0000_TMKB_BATCH_OVERWRITE_DISABLE              (0x0000U)
#define _0004_TMKB_BATCH_OVERWRITE_ENABLE               (0x0004U)
/* Selection of timer KBn count start trigger (TKBSTSn1 - TKBSTSn0) */
#define _0000_TMKB_TRIGGER_DISABLED                     (0x0000U)
#define _0001_TMKB_TRIGGER_INTP20                       (0x0001U)
#define _0002_TMKB_TRIGGER_INTP21                       (0x0002U)
#define _0003_TMKB_TRIGGER_COMPARATOR                   (0x0003U)

/*
    Operation Control Register n1 (TKBCTLn1)
*/
/* Timer KBn operation control (TKBCEn) */
#define _00_TMKB_OPERATION_DISABLED                     (0x00U)
#define _80_TMKB_OPERATION_ENABLED                      (0x80U)
/* Timer KBn clock selection (TKBCKSn) */
#define _00_TMKB_CK20_SELECTED                          (0x00U)
#define _10_TMKB_CK21_SELECTED                          (0x10U)
/* Timer KBn operation control (TKBSCMn) */
#define _00_TMKB_TKBCKSn_SELECTED                       (0x00U)
#define _08_TMKB_CK20_CK21_SYNC                         (0x08U)
/* Timer KBn operation mode selection (TKBMDn1 - TKBMDn0) */
#define _00_TMKB_STANDALONE_MASTER                      (0x00U)
#define _01_TMKB_SYNC_START_SLAVE                       (0x01U)
#define _02_TMKB_SYNC_CLEAR_SLAVE                       (0x02U)
#define _03_TMKB_SYNC_PFC_OUTPUT                        (0x03U)

/*
    Output Control Register n0 (TKBIOCn0)
*/
/* Active level setting of timer output TKBOnp (TKBTOLn0) */
#define _00_TMKB_OUTPUT0_ACTIVE_HIGH                    (0x00U)
#define _08_TMKB_OUTPUT0_ACTIVE_LOW                     (0x08U)
#define _00_TMKB_OUTPUT1_ACTIVE_HIGH                    (0x00U)
#define _04_TMKB_OUTPUT1_ACTIVE_LOW                     (0x04U)
/* Default level setting of timer output TKBOnp (TKBTODnp) */
#define _00_TMKB_OUTPUT0_DEFAULT_LOW                    (0x00U)
#define _01_TMKB_OUTPUT0_DEFAULT_HIGH                   (0x01U)
#define _00_TMKB_OUTPUT1_DEFAULT_LOW                    (0x00U)
#define _02_TMKB_OUTPUT1_DEFAULT_HIGH                   (0x02U)

/*
    Output Control Register n1 (TKBIOCn1)
*/
/* Timer output TKBOnp output enable/disable (TKBTOEnp) */
#define _00_TMKB_PIN0_OUTPUT_DISABLED                   (0x00U)
#define _01_TMKB_PIN0_OUTPUT_ENABLED                    (0x01U)
#define _00_TMKB_PIN1_OUTPUT_DISABLED                   (0x00U)
#define _02_TMKB_PIN1_OUTPUT_ENABLED                    (0x02U)

/*
    Peripheral function switch register 0 (PFSEL0)
*/
/* Timer trigger selection for A/D conversion (ADTRG11 - ADTRG10) */
#define _00_TMKB_KB0_TRIGGER_SOURCE                     (0x00U)
#define _04_TMKB_KB1_TRIGGER_SOURCE                     (0x04U)
#define _08_TMKB_KB2_TRIGGER_SOURCE                     (0x08U)

/*
    Forced output stop function control registers n0, n1 (TKBPACTLn0, TKBPACTLn1)
*/
/* Trigger selection for forced output stop function 1 (TKBPAFXSnp3 - 0) */
#define _0000_TMKB_FORCED_FUNCTION2_TRIGGER_DISABLED    (0x0000U)
#define _1000_TMKB_FORCED_FUNCTION2_TRIGGER_ITEM1       (0x1000U)
#define _2000_TMKB_FORCED_FUNCTION2_TRIGGER_ITEM2       (0x2000U)
#define _4000_TMKB_FORCED_FUNCTION2_TRIGGER_ITEM3       (0x4000U)
#define _8000_TMKB_FORCED_FUNCTION2_TRIGGER_ITEM4       (0x8000U)
/* Operation mode selection for forced output stop function 2 (TKBPAFCMnp) */
#define _0000_TMKB_FORCED_FUNCTION2_TYPE1               (0x0000U)
#define _0100_TMKB_FORCED_FUNCTION2_TYPE2               (0x0100U)
/* Trigger selection for forced output stop function 1 (TKBPAHZSnp2 - 0) */
#define _0000_TMKB_FORCED_FUNCTION1_TRIGGER_DISABLED    (0x0000U)
#define _0010_TMKB_FORCED_FUNCTION1_TRIGGER_ITEM1       (0x0010U)
#define _0020_TMKB_FORCED_FUNCTION1_TRIGGER_ITEM2       (0x0020U)
#define _0040_TMKB_FORCED_FUNCTION1_TRIGGER_ITEM3       (0x0040U)
/* Operation mode selection for forced output stop function 1 (TKBPAHCMnp1 - 0) */
#define _0000_TMKB_FORCED_FUNCTION1_TYPE1               (0x0000U)
#define _0040_TMKB_FORCED_FUNCTION1_TYPE2               (0x0040U)
#define _0080_TMKB_FORCED_FUNCTION1_TYPE3               (0x0080U)
#define _00C0_TMKB_FORCED_FUNCTION1_TYPE4               (0x00C0U)
/* Output level selection when executing forced output stop function (TKBPAMDnp1 - 0) */
#define _0000_TMKB_FORCED_HIZ_LOW                       (0x0000U)
#define _0001_TMKB_FORCED_HIZ_HIGH                      (0x0001U)
#define _0002_TMKB_FORCED_LOW_LOW                       (0x0002U)
#define _0003_TMKB_FORCED_HIGH_HIGH                     (0x0003U)

/*
    Forced Output Stop Function Control Register n2 (TKBPACTLn2)
*/
/* Input control of trigger signal used for forced output stop function */
#define _00_TMKB_FORCED_STOP_PIN0_INPUT_DISABLED        (0x00U)
#define _01_TMKB_FORCED_STOP_PIN0_INPUT_ENABLED         (0x01U)
#define _00_TMKB_FORCED_STOP_PIN1_INPUT_DISABLED        (0x00U)
#define _02_TMKB_FORCED_STOP_PIN1_INPUT_ENABLED         (0x02U)

/*
    Forced output stop function start trigger register n (TKBPAHFSn)
*/
/* Start trigger of forced output stop function 1 for TKBOnp output */
#define _01_TMKB_FORCED_STOP_PIN0_START_TRIGGER         (0x01U)
#define _02_TMKB_FORCED_STOP_PIN1_START_TRIGGER         (0x02U)

/*
    Forced output stop function stop trigger register n (TKBPAHFTn)
*/
/* Stop trigger of forced output stop function 1 for TKBOnp output */
#define _01_TMKB_FORCED_STOP_PIN0_CLEAR_TRIGGER         (0x01U)
#define _02_TMKB_FORCED_STOP_PIN1_CLEAR_TRIGGER         (0x02U)

/*
    Peripheral Enable Register 2 (PER2)
*/
/* Control of timer array unit input clock (TKC0EN) */
#define _00_TMKC0_CLOCK_STOP                    (0x00U)    /* stops supply of input clock */
#define _08_TMKC0_CLOCK_SUPPLY                  (0x08U)    /* supplies input clock */

/*
    Timer Clock Select Register 2 (TPS2)
*/
/* Operating clock for CK20 (TPS202 - TPS200) */
#define _00_TMKC_CK20_FCLK_0                    (0x00U)    /* fclk */
#define _01_TMKC_CK20_FCLK_1                    (0x01U)    /* fclk/2^1 */
#define _02_TMKC_CK20_FCLK_2                    (0x02U)    /* fclk/2^2 */
#define _03_TMKC_CK20_FCLK_3                    (0x03U)    /* fclk/2^3 */
#define _04_TMKC_CK20_FCLK_4                    (0x04U)    /* fclk/2^4 */
#define _05_TMKC_CK20_FCLK_5                    (0x05U)    /* fclk/2^5 */
/* Operating clock for CK21 (TPS212 - TPS210) */
#define _00_TMKC_CK21_FCLK_0                    (0x00U)    /* fclk */
#define _10_TMKC_CK21_FCLK_1                    (0x10U)    /* fclk/2^1 */
#define _20_TMKC_CK21_FCLK_2                    (0x20U)    /* fclk/2^2 */
#define _30_TMKC_CK21_FCLK_3                    (0x30U)    /* fclk/2^3 */
#define _40_TMKC_CK21_FCLK_4                    (0x40U)    /* fclk/2^4 */
#define _50_TMKC_CK21_FCLK_5                    (0x50U)    /* fclk/2^5 */

/*
    Operation Control Register 0 (TKCCTL0)
*/
/* Timer KC0 operation control (TKCCE0) */
#define _00_TMKC_OPERATION_DISABLED             (0x00U)
#define _80_TMKC_OPERATION_ENABLED              (0x80U)
/* Timer KC0 clock selection (TKCCKS0) */
#define _00_TMKC_CK20_SELECTED                  (0x00U)
#define _10_TMKC_CK21_SELECTED                  (0x10U)
/* Timer KC0 operation mode selection (TKCMD01) */
#define _00_TMKC_STANDALONE_MASTER              (0x00U)
#define _01_TMKC_SYNC_START_SLAVE               (0x01U)

/*
    Output Control Register 00 (TKCIOC00))
*/
/* Active level setting of timer output TKCO0m (TKCTOL0m) */
#define _0000_TMKC_OUTPUT0_ACTIVE_HIGH          (0x0000U)
#define _0100_TMKC_OUTPUT0_ACTIVE_LOW           (0x0100U)
#define _0000_TMKC_OUTPUT1_ACTIVE_HIGH          (0x0000U)
#define _0200_TMKC_OUTPUT1_ACTIVE_LOW           (0x0200U)
#define _0000_TMKC_OUTPUT2_ACTIVE_HIGH          (0x0000U)
#define _0400_TMKC_OUTPUT2_ACTIVE_LOW           (0x0400U)
#define _0000_TMKC_OUTPUT3_ACTIVE_HIGH          (0x0000U)
#define _0800_TMKC_OUTPUT3_ACTIVE_LOW           (0x0800U)
#define _0000_TMKC_OUTPUT4_ACTIVE_HIGH          (0x0000U)
#define _1000_TMKC_OUTPUT4_ACTIVE_LOW           (0x1000U)
#define _0000_TMKC_OUTPUT5_ACTIVE_HIGH          (0x0000U)
#define _2000_TMKC_OUTPUT5_ACTIVE_LOW           (0x2000U)
/* Default level setting of timer output TKCO0m (TKCTOD0m) */
#define _0000_TMKC_OUTPUT0_DEFAULT_HIGH         (0x0000U)
#define _0001_TMKC_OUTPUT0_DEFAULT_LOW          (0x0001U)
#define _0000_TMKC_OUTPUT1_DEFAULT_HIGH         (0x0000U)
#define _0002_TMKC_OUTPUT1_DEFAULT_LOW          (0x0002U)
#define _0000_TMKC_OUTPUT2_DEFAULT_HIGH         (0x0000U)
#define _0004_TMKC_OUTPUT2_DEFAULT_LOW          (0x0004U)
#define _0000_TMKC_OUTPUT3_DEFAULT_HIGH         (0x0000U)
#define _0008_TMKC_OUTPUT3_DEFAULT_LOW          (0x0008U)
#define _0000_TMKC_OUTPUT4_DEFAULT_HIGH         (0x0000U)
#define _0010_TMKC_OUTPUT4_DEFAULT_LOW          (0x0010U)
#define _0000_TMKC_OUTPUT5_DEFAULT_HIGH         (0x0000U)
#define _0020_TMKC_OUTPUT5_DEFAULT_LOW          (0x0020U)

/*
    Output Control Register 01 (TKCIOC01)
*/
/* Timer output TKCO0p output enable/disable (TKCTOE0m) */
#define _00_TMKC_TIMER_OUTPUT0_DISABLED         (0x00U)
#define _01_TMKC_TIMER_OUTPUT0_ENABLED          (0x01U)
#define _00_TMKC_TIMER_OUTPUT1_DISABLED         (0x00U)
#define _02_TMKC_TIMER_OUTPUT1_ENABLED          (0x02U)
#define _00_TMKC_TIMER_OUTPUT2_DISABLED         (0x00U)
#define _04_TMKC_TIMER_OUTPUT2_ENABLED          (0x04U)
#define _00_TMKC_TIMER_OUTPUT3_DISABLED         (0x00U)
#define _08_TMKC_TIMER_OUTPUT3_ENABLED          (0x08U)
#define _00_TMKC_TIMER_OUTPUT4_DISABLED         (0x00U)
#define _10_TMKC_TIMER_OUTPUT4_ENABLED          (0x10U)
#define _00_TMKC_TIMER_OUTPUT5_DISABLED         (0x00U)
#define _20_TMKC_TIMER_OUTPUT5_ENABLED          (0x20U)



/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
/* 16-bit compare register (TKBCR00) */
#define _0C7F_TMKB_CYCLE00_VALUE                (0x0C7FU)
/* 16-bit compare register (TKBCR01) */
#define _0640_TMKB_DUTY01_VALUE                 (0x0640U)
/* 16-bit compare register (TKCCR0) */
#define _7CFF_TMKC_CYCLE0_VALUE                 (0x7CFFU)
/* 16-bit compare register (TKCDUTY0) */
#define _3E80_TMKC_DUTY0_VALUE                  (0x3E80U)

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Global functions
***********************************************************************************************************************/
void R_TMR_KB_Create(void);
void R_TMR_KB0_Start(void);
void R_TMR_KB0_Stop(void);
void R_TMR_KC0_Create(void);
void R_TMR_KC0_Start(void);
void R_TMR_KC0_Stop(void);


/* Start user code for function. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#endif
