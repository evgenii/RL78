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
* File Name    : r_cg_cgc.h
* Version      : Applilet3 for RL78/G13 V2.00.00.08 [12 Apr 2013]
* Device(s)    : R5F100SL
* Tool-Chain   : IAR Systems iccrl78
* Description  : This file implements device driver for CGC module.
* Creation Date: 07.08.2013
***********************************************************************************************************************/

#ifndef CGC_H
#define CGC_H

/***********************************************************************************************************************
Macro definitions (Register bit)
***********************************************************************************************************************/
/*
    Clock operation mode control register (CMC)
*/
/* High-speed system clock pin operation mode (EXCLK, OSCSEL) */
#define _C0_CGC_HISYS_PIN           (0xC0U)
#define _00_CGC_HISYS_PORT          (0x00U) /* X1, X2 as I/O port */
#define _40_CGC_HISYS_OSC           (0x40U) /* X1, X2 as crystal/ceramic resonator connection */
#define _80_CGC_HISYS_PORT1         (0x80U) /* X1, X2 as I/O port */
#define _C0_CGC_HISYS_EXT           (0xC0U) /* X1 as I/O port, X2 as external clock input */
/* Subsystem clock pin operation mode (EXCLKS, OSCSELS) */
#define _30_CGC_SUB_PIN             (0x30U)
#define _00_CGC_SUB_PORT            (0x00U) /* XT1, XT2 as I/O port */
#define _10_CGC_SUB_OSC             (0x10U) /* XT1, XT2 as crystal connection */
#define _20_CGC_SUB_PORT1           (0x20U) /* XT1, XT2 as I/O port */
#define _30_CGC_SUB_EXT             (0x30U) /* XT1 as I/O port, XT2 as external clock input */
/* XT1 oscillator oscillation mode selection (AMPHS1, AMPHS0) */
#define _00_CGC_SUBMODE_DEFAULT     (0x00U)
#define _00_CGC_SUBMODE_LOW         (0x00U) /* low power consumption oscillation */
#define _02_CGC_SUBMODE_NORMAL      (0x02U) /* normal oscillation */
#define _04_CGC_SUBMODE_ULOW        (0x04U) /* ultra-low power consumption oscillation */
/* Control of X1 high-speed system clock oscillation frequency (AMPH) */
#define _00_CGC_SYSOSC_DEFAULT      (0x00U)
#define _00_CGC_SYSOSC_UNDER10M     (0x00U) /* fX <= 10MHz */
#define _01_CGC_SYSOSC_OVER10M      (0x01U) /* fX > 10MHz */

/*
    Clock operation status control register (CSC)
*/
/* Control of high-speed system clock operation (MSTOP) */
#define _00_CGC_HISYS_OPER          (0x00U) /* X1 oscillator/external clock operating */
#define _80_CGC_HISYS_STOP          (0x80U) /* X1 oscillator/external clock stopped */
/* Subsystem clock operation (XTSTOP) */
#define _00_CGC_SUB_OPER            (0x00U) /* XT1 oscillator operating */
#define _40_CGC_SUB_STOP            (0x40U) /* XT1 oscillator stopped */
/* High-speed OCO operation (HIOSTOP) */
#define _00_CGC_HIO_OPER            (0x00U) /* high-speed OCO operating */
#define _01_CGC_HIO_STOP            (0x01U) /* high-speed OCO stopped */

/*
    Oscillation stabilization time counter status register (OSTC)
*/
/* Oscillation stabilization time status (MOST18 - MOST8) */
#define _00_CGC_OSCSTAB_STA0        (0x00U) /* < 2^8/fX */
#define _80_CGC_OSCSTAB_STA8        (0x80U) /* 2^8/fX */
#define _C0_CGC_OSCSTAB_STA9        (0xC0U) /* 2^9/fX */
#define _E0_CGC_OSCSTAB_STA10       (0xE0U) /* 2^10/fX */
#define _F0_CGC_OSCSTAB_STA11       (0xF0U) /* 2^11/fX */
#define _F8_CGC_OSCSTAB_STA13       (0xF8U) /* 2^13/fX */
#define _FC_CGC_OSCSTAB_STA15       (0xFCU) /* 2^15/fX */
#define _FE_CGC_OSCSTAB_STA17       (0xFEU) /* 2^17/fX */
#define _FF_CGC_OSCSTAB_STA18       (0xFFU) /* 2^18/fX */

/*
    Oscillation stabilization time select register (OSTS)
*/
/* Oscillation stabilization time selection (OSTS2 - OSTS0) */
#define _00_CGC_OSCSTAB_SEL8        (0x00U) /* 2^8/fX */
#define _01_CGC_OSCSTAB_SEL9        (0x01U) /* 2^9/fX */
#define _02_CGC_OSCSTAB_SEL10       (0x02U) /* 2^10/fX */
#define _03_CGC_OSCSTAB_SEL11       (0x03U) /* 2^11/fX */
#define _04_CGC_OSCSTAB_SEL13       (0x04U) /* 2^13/fX */
#define _05_CGC_OSCSTAB_SEL15       (0x05U) /* 2^15/fX */
#define _06_CGC_OSCSTAB_SEL17       (0x06U) /* 2^17/fX */
#define _07_CGC_OSCSTAB_SEL18       (0x07U) /* 2^18/fX */

/*
    System clock control register (CKC)
*/
/* Status of CPU/peripheral hardware clock fCLK (CLS) */
#define _00_CGC_CPUCLK_MAIN         (0x00U) /* main system clock (fMAIN) */
#define _80_CGC_CPUCLK_SUB          (0x80U) /* subsystem clock (fSUB) */
/* Selection of CPU/peripheral hardware clock fCLK (CSS) */
#define _00_CGC_CPUCLK_SELMAIN      (0x00U) /* main system clock (fMAIN) */
#define _40_CGC_CPUCLK_SELSUB       (0x40U) /* subsystem clock (fSUB) */
/* Status of Main system clock fMAIN (MCS) */
#define _00_CGC_MAINCLK_HIO         (0x00U) /* high-speed OCO clock (fIH) */
#define _20_CGC_MAINCLK_HISYS       (0x20U) /* high-speed system clock (fMX) */
/* Selection of Main system clock fMAIN (MCM0) */
#define _00_CGC_MAINCLK_SELHIO      (0x00U) /* high-speed OCO clock (fIH) */
#define _10_CGC_MAINCLK_SELHISYS    (0x10U) /* high-speed system clock (fMX) */

/*
    Operation speed mode control register (OSMC)
*/
/* Setting in subsystem clock HALT mode (RTCLPC) */
#define _00_CGC_SUBINHALT_ON        (0x00U) /* enables supply of subsystem clock to peripheral functions */
#define _80_CGC_SUBINHALT_OFF       (0x80U) /* stops supply to peripheral functions other than RTC and interval timer */
/* RTC macro operation clock (WUTMMCK0) */
#define _00_CGC_RTC_CLK_FSUB        (0x00U) /* use fSUB clock */
#define _10_CGC_RTC_CLK_FIL         (0x10U) /* use fIL clcok */

/*
    CRC control register (CRC0CTL)
*/
/* CRC calculation operation (CRC0EN) */
#define _00_CGC_CRC_OPERATION_OFF   (0x00U) /* stops operation */
#define _80_CGC_CRC_OPERATION_ON    (0x80U) /* CRC calculation is performed after enter HALT mode */
/* CRC calculation range (FEA5 - FEA0) */
#define _00_CGC_CRC_AREA0           (0x00U) /* 0 - 3FFBH (16K - 4byte) */
#define _01_CGC_CRC_AREA1           (0x01U) /* 0 - 7FFBH (32K - 4byte) */
#define _02_CGC_CRC_AREA2           (0x02U) /* 0 - BFFBH (48K - 4byte) */
#define _03_CGC_CRC_AREA3           (0x03U) /* 0 - FFFBH (64K - 4byte) */
#define _04_CGC_CRC_AREA4           (0x04U) /* 0 - 13FFBH (80K - 4byte) */
#define _05_CGC_CRC_AREA5           (0x05U) /* 0 - 17FFBH (96K - 4byte) */
#define _06_CGC_CRC_AREA6           (0x06U) /* 0 - 1BFFBH (112K - 4byte) */
#define _07_CGC_CRC_AREA7           (0x07U) /* 0 - 1FFFBH (128K - 4byte) */
#define _08_CGC_CRC_AREA8           (0x08U) /* 0 - 23FFBH (144K - 4byte) */
#define _09_CGC_CRC_AREA9           (0x09U) /* 0 - 27FFBH (160K - 4byte) */
#define _0A_CGC_CRC_AREA10          (0x0AU) /* 0 - 2BFFBH (176K - 4byte) */
#define _0B_CGC_CRC_AREA11          (0x0BU) /* 0 - 2FFFBH (192K - 4byte) */
#define _0C_CGC_CRC_AREA12          (0x0CU) /* 0 - 33FFBH (208K - 4byte) */
#define _0D_CGC_CRC_AREA13          (0x0DU) /* 0 - 37FFBH (224K - 4byte) */
#define _0E_CGC_CRC_AREA14          (0x0EU) /* 0 - 3BFFBH (240K - 4byte) */
#define _0F_CGC_CRC_AREA15          (0x0FU) /* 0 - 3FFFBH (256K - 4byte) */
#define _10_CGC_CRC_AREA16          (0x10U) /* 0 - 43FFBH (272K - 4byte) */
#define _11_CGC_CRC_AREA17          (0x11U) /* 0 - 47FFBH (288K - 4byte) */
#define _12_CGC_CRC_AREA18          (0x12U) /* 0 - 4BFFBH (304K - 4byte) */
#define _13_CGC_CRC_AREA19          (0x13U) /* 0 - 4FFFBH (320K - 4byte) */
#define _14_CGC_CRC_AREA20          (0x14U) /* 0 - 53FFBH (336K - 4byte) */
#define _15_CGC_CRC_AREA21          (0x15U) /* 0 - 57FFBH (352K - 4byte) */
#define _16_CGC_CRC_AREA22          (0x16U) /* 0 - 5BFFBH (368K - 4byte) */
#define _17_CGC_CRC_AREA23          (0x17U) /* 0 - 5FFFBH (384K - 4byte) */
#define _18_CGC_CRC_AREA24          (0x18U) /* 0 - 63FFBH (400K - 4byte) */
#define _19_CGC_CRC_AREA25          (0x19U) /* 0 - 67FFBH (416K - 4byte) */
#define _1A_CGC_CRC_AREA26          (0x1AU) /* 0 - 6BFFBH (432K - 4byte) */
#define _1B_CGC_CRC_AREA27          (0x1BU) /* 0 - 6FFFBH (448K - 4byte) */
#define _1C_CGC_CRC_AREA28          (0x1CU) /* 0 - 73FFBH (464K - 4byte) */
#define _1D_CGC_CRC_AREA29          (0x1DU) /* 0 - 77FFBH (480K - 4byte) */
#define _1E_CGC_CRC_AREA30          (0x1EU) /* 0 - 7BFFBH (496K - 4byte) */
#define _1F_CGC_CRC_AREA31          (0x1FU) /* 0 - 7FFFBH (512K - 4byte) */

/*
    Illegal memory access detection control register (IAWCTL)
*/
/* Illegal memory access detection control (IAWEN) */
#define _00_CGC_ILLEGAL_ACCESS_OFF  (0x00U) /* disables illegal memory access detection */
#define _80_CGC_ILLEGAL_ACCESS_ON   (0x80U) /* enables illegal memory access detection */
/* RAM guard area (GRAM1, GRAM0) */
#define _00_CGC_RAM_GUARD_OFF       (0x00U) /* invalid, it is possible to write RAM */
#define _10_CGC_RAM_GUARD_ARAE0     (0x10U) /* 128 bytes from RAM bottom address */
#define _20_CGC_RAM_GUARD_ARAE1     (0x20U) /* 256 bytes from RAM bottom address */
#define _30_CGC_RAM_GUARD_ARAE2     (0x30U) /* 512 bytes from RAM bottom address */
/* PORT register guard (GPORT) */
#define _00_CGC_PORT_GUARD_OFF      (0x00U) /* invalid, it is possible to write PORT register */
#define _04_CGC_PORT_GUARD_ON       (0x04U) /* valid, it is impossible to write PORT register, but possible for read */
/* Interrupt register guard (GINT) */   
#define _00_CGC_INT_GUARD_OFF       (0x00U) /* invalid, it is possible to write interrupt register */
#define _02_CGC_INT_GUARD_ON        (0x02U) /* valid, impossible to write interrupt register, but possible for read */
/* CSC register guard (GCSC) */         
#define _00_CGC_CSC_GUARD_OFF       (0x00U) /* invalid, it is possible to write CSC register */
#define _01_CGC_CSC_GUARD_ON        (0x01U) /* valid, it is impossible to write CSC register, but possible for read */

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/
typedef enum
{
    HIOCLK, 
    SYSX1CLK, 
    SYSEXTCLK, 
    SUBXT1CLK, 
    SUBEXTCLK
} clock_mode_t;

/***********************************************************************************************************************
Global functions
***********************************************************************************************************************/
void R_CGC_Create(void);
void R_CGC_Set_CRCOn(void);
void R_CGC_Get_ResetSource(void);

/* Start user code for function. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#endif
