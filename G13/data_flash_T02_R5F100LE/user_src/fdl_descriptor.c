/*******************************************************************************
* Library       : Data Flash Access Library T02
*
* File Name     : $Source: fdl_descriptor.c $
* Lib. Version  : $RL78_FDL_LIB_VERSION_T02_IAR: V1.01 $
* Mod. Revision : $Revision: 1.10 $
* Mod. Date     : $Date: 2013/06/25 15:44:23MESZ $
* Device(s)     : RL78
* Description   : Physical allocation of the FDL descriptor.
*                 Please do NOT change this file !!!!
*******************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only
* intended for use with Renesas products. No other uses are authorized. This
* software is owned by Renesas Electronics Corporation and is protected under
* all applicable laws, including copyright laws.
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT
* LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
* AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.
* TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS
* ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE
* FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR
* ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE
* BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software
* and to discontinue the availability of this software. By using this software,
* you agree to the additional terms and conditions found by accessing the
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2011-2013 Renesas Electronics Corporation. All rights reserved.
*******************************************************************************/




/*==============================================================================================*/
/* compiler settings                                                                            */
/*==============================================================================================*/
#pragma language = extended

/*==============================================================================================*/
/* include files list                                                                           */
/*==============================================================================================*/
#include "fdl_types.h"
#include "fdl_descriptor.h"

/* ----------------------------------------------------------------------------------------------------- */
/* ------                                                                                          ----- */
/* ------     B E G I N    O F    U N T O U C H A B L E     D E C L A R A T I O N    A R E A       ----- */
/* ------                                                                                          ----- */
/* ----------------------------------------------------------------------------------------------------- */

/* constant segment definition */
#pragma location="FDL_CNST"


/* physical data flash specification: start address and block-size in bytes */
#define     DATA_FLASH_BLOCK_SIZE         (1*1024)


#if (EEL_POOL_BLOCKS>0)
    #define   EEL_POOL_BYTES                (DATA_FLASH_BLOCK_SIZE*EEL_POOL_BLOCKS)
#else
    #define   EEL_POOL_BYTES                0
#endif

#if (FDL_POOL_BLOCKS>0)
    #define   FDL_POOL_BYTES                (DATA_FLASH_BLOCK_SIZE*FDL_POOL_BLOCKS)
#else
    #define   FDL_POOL_BYTES                0
#endif


/* calculate f_MHz = round-up(FDL_SYSTEM_FREQUENCY)   */
#define FDL_FX_MHZ                      ((FDL_SYSTEM_FREQUENCY+999999)/1000000)

/* calculate 10us delay as a function f(fx)           */
#define FDL_DELAY                       ((10*FDL_FX_MHZ)/6)

#ifdef FDL_WIDE_VOLTAGE_MODE
    #define FDL_VOLTAGE_MODE  0x01
#else
    #define FDL_VOLTAGE_MODE  0x00
#endif

__far const fdl_descriptor_t  fdl_descriptor_str =  {                                   \
                                                      (fdl_u16)EEL_POOL_BYTES,          \
                                                      (fdl_u16)FDL_POOL_BYTES,          \

                                                      (fdl_u16)FDL_DELAY,               \

                                                      (fdl_u08)EEL_POOL_BLOCKS,         \
                                                      (fdl_u08)FDL_POOL_BLOCKS,         \

                                                      (fdl_u08)FDL_FX_MHZ,              \
                                                      (fdl_u08)FDL_VOLTAGE_MODE         \
                                                    };

/* ----------------------------------------------------------------------------------------------------- */
/* ------                                                                                          ----- */
/* ------     E N D    O F    U N T O U C H A B L E     D E C L A R A T I O N    A R E A           ----- */
/* ------                                                                                          ----- */
/* ----------------------------------------------------------------------------------------------------- */
