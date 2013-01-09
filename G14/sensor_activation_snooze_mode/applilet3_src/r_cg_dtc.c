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
* File Name    : r_cg_dtc.c
* Version      : Applilet3 for RL78/G14 V1.01.01 [11 Oct 2011]
* Device(s)    : R5F104LE
* Tool-Chain   : IAR Systems iccrl78
* Description  : This file implements device driver for DTC module.
* Creation Date: 08.01.2013
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_dtc.h"
/* Start user code for include. Do not edit comment generated here */
#include "r_cg_adc.h"
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
#pragma location = 0xFFD00U
__no_init uint8_t dtc_vectortable[40];

#pragma location = 0xFFD40U
__no_init st_dtc_data dtc_controldata_0;

#pragma location = 0xFFD48U
__no_init st_dtc_data dtc_controldata_1;

/* Start user code for global. Do not edit comment generated here */

#pragma location = 0xFFD50U
__no_init st_dtc_data dtc_controldata_2;

#pragma location = 0xFFD58U
__no_init st_dtc_data dtc_controldata_3;

// keep alignment to 256 bytes for the DMA repeat mode
#pragma data_alignment = 256
uint16_t RJ_timing[2] = { SENSOR_ON_TIME, 0xFFFF/*0x1D4B*/ };

#pragma data_alignment = 256
uint16_t IT_timing[2] = { (0x8000 | IT_TRIGGER_TIME), 0x0 }; 

#pragma data_alignment = 256
uint16_t IT_stop[2] = { 0x0, 0x0 }; 

//#pragma data_alignment = 256
//uint8_t ADC_power[2] = { _18_AD_CONVERSION_CLOCK_8 | _00_AD_TIME_MODE_NORMAL_1 | _00_AD_OPERMODE_SELECT | _01_AD_COMPARATOR_ENABLE,
//                            0x0 };

void DTC_Create(void);

/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_DTC_Create
* Description  : This function initializes the DTC module.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_DTC_Create(void)
{
//    /* Enable input clock supply */
//    DTCEN = 1U;
//    /* Disable all DTC channels operation */
//    DTCEN0 = 0x00U;
//    DTCEN1 = 0x00U;
//    DTCEN2 = 0x00U;
//    DTCEN3 = 0x00U;
//    DTCEN4 = 0x00U;
//    /* Set base address */
//    DTCBAR = 0xFDU;
//    /* Set DTCD0 */
//    dtc_vectortable[37] = 0x40U;
//    dtc_controldata_0.dtccr = _01_DTC_TRANSFER_MODE_REPEAT | _02_DTC_REPEAT_AREA_SOURCE | _00_DTC_SOURCE_ADDR_FIXED |
//                              _00_DTC_DEST_ADDR_FIXED | _10_DTC_CHAIN_TRANSFER_ENABLE | _00_DTC_REPEAT_INT_DISABLE;
//    dtc_controldata_0.dtbls = _01_DTCD0_TRANSFER_BLOCKSIZE;
//    dtc_controldata_0.dtcct = _02_DTCD0_TRANSFER_BYTE;
//    dtc_controldata_0.dtrld = _02_DTCD0_TRANSFER_BYTE;
//    dtc_controldata_0.dtsar = _0000_DTCD0_SRC_ADDRESS;
//    dtc_controldata_0.dtdar = _0240_DTCD0_DEST_ADDRESS;
//    /* Set DTCD1 */
//    dtc_controldata_1.dtccr = _01_DTC_TRANSFER_MODE_REPEAT | _02_DTC_REPEAT_AREA_SOURCE |
//                              _04_DTC_SOURCE_ADDR_INCREMENTED | _00_DTC_DEST_ADDR_FIXED |
//                              _00_DTC_CHAIN_TRANSFER_DISABLE | _00_DTC_REPEAT_INT_DISABLE;
//    dtc_controldata_1.dtbls = _01_DTCD1_TRANSFER_BLOCKSIZE;
//    dtc_controldata_1.dtcct = _02_DTCD1_TRANSFER_BYTE;
//    dtc_controldata_1.dtrld = _02_DTCD1_TRANSFER_BYTE;
//    dtc_controldata_1.dtsar = _0000_DTCD1_SRC_ADDRESS;
//    dtc_controldata_1.dtdar = _0500_DTCD1_DEST_ADDRESS;
}

/***********************************************************************************************************************
* Function Name: R_DTCD0_Start
* Description  : This function enables DTCD0 module operation.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_DTCD0_Start(void)
{
    DTCEN4 |= _04_DTC_TMRJ0_ACTIVATION_ENABLE;
}

/***********************************************************************************************************************
* Function Name: R_DTCD0_Stop
* Description  : This function disables DTCD0 module operation.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_DTCD0_Stop(void)
{
    DTCEN4 &= (uint8_t)~_04_DTC_TMRJ0_ACTIVATION_ENABLE;
}

/* Start user code for adding. Do not edit comment generated here */
/* use these modified versions of the driver */
void DTC_Reload(void) {

    dtc_controldata_0.dtccr = _01_DTC_TRANSFER_MODE_REPEAT | _02_DTC_REPEAT_AREA_SOURCE | 
                              _04_DTC_SOURCE_ADDR_INCREMENTED | _00_DTC_DEST_ADDR_FIXED |
                              _10_DTC_CHAIN_TRANSFER_ENABLE | _00_DTC_REPEAT_INT_DISABLE | 
                              _40_DTC_DATA_SIZE_16BITS;
    dtc_controldata_0.dtbls = 0x01;
    dtc_controldata_0.dtcct = 0x02;
    dtc_controldata_0.dtrld = 0x02;
    dtc_controldata_0.dtsar = (uint16_t) &IT_stop[0];
    dtc_controldata_0.dtdar = (uint16_t) &ITMC; 
    
    /* Set DTCD1 */
    dtc_controldata_1.dtccr = _01_DTC_TRANSFER_MODE_REPEAT | _02_DTC_REPEAT_AREA_SOURCE |
                              _04_DTC_SOURCE_ADDR_INCREMENTED | _00_DTC_DEST_ADDR_FIXED |
                              _10_DTC_CHAIN_TRANSFER_ENABLE | _00_DTC_REPEAT_INT_DISABLE |
                              _40_DTC_DATA_SIZE_16BITS;
    dtc_controldata_1.dtbls = 0x01;
    dtc_controldata_1.dtcct = 0x02;
    dtc_controldata_1.dtrld = 0x02;
    dtc_controldata_1.dtsar = (uint16_t) &RJ_timing[0];
    dtc_controldata_1.dtdar = (uint16_t) &TRJ0;

    dtc_controldata_2.dtccr = _01_DTC_TRANSFER_MODE_REPEAT | _02_DTC_REPEAT_AREA_SOURCE | 
                              _04_DTC_SOURCE_ADDR_INCREMENTED | _00_DTC_DEST_ADDR_FIXED |
                              _00_DTC_CHAIN_TRANSFER_DISABLE | _00_DTC_REPEAT_INT_DISABLE | 
                              _40_DTC_DATA_SIZE_16BITS;
    dtc_controldata_2.dtbls = 0x01;
    dtc_controldata_2.dtcct = 0x02;
    dtc_controldata_2.dtrld = 0x02;
    dtc_controldata_2.dtsar = (uint16_t) &IT_timing[0];
    dtc_controldata_2.dtdar = (uint16_t) &ITMC;
    
}

void DTC_Create(void)
{
    /* Enable input clock supply */
    DTCEN = 1U;
    /* Disable all DTC channels operation */
    DTCEN0 = 0x00U;
    DTCEN1 = 0x00U;
    DTCEN2 = 0x00U;
    DTCEN3 = 0x00U;
    DTCEN4 = 0x00U;
    /* Set base address */
    DTCBAR = 0xFDU;
    /* Set DTCD0 */
    dtc_vectortable[37] = 0x40U;
    dtc_controldata_0.dtccr = _01_DTC_TRANSFER_MODE_REPEAT | _02_DTC_REPEAT_AREA_SOURCE | 
                              _04_DTC_SOURCE_ADDR_INCREMENTED | _00_DTC_DEST_ADDR_FIXED |
                              _10_DTC_CHAIN_TRANSFER_ENABLE | _00_DTC_REPEAT_INT_DISABLE | 
                              _40_DTC_DATA_SIZE_16BITS;
    dtc_controldata_0.dtbls = 0x01;
    dtc_controldata_0.dtcct = 0x02;
    dtc_controldata_0.dtrld = 0x02;
    dtc_controldata_0.dtsar = (uint16_t) &IT_stop[0];
    dtc_controldata_0.dtdar = (uint16_t) &ITMC; 
    
    /* Set DTCD1 */
    dtc_controldata_1.dtccr = _01_DTC_TRANSFER_MODE_REPEAT | _02_DTC_REPEAT_AREA_SOURCE |
                              _04_DTC_SOURCE_ADDR_INCREMENTED | _00_DTC_DEST_ADDR_FIXED |
                              _10_DTC_CHAIN_TRANSFER_ENABLE | _00_DTC_REPEAT_INT_DISABLE |
                              _40_DTC_DATA_SIZE_16BITS;
    dtc_controldata_1.dtbls = 0x01;
    dtc_controldata_1.dtcct = 0x02;
    dtc_controldata_1.dtrld = 0x02;
    dtc_controldata_1.dtsar = (uint16_t) &RJ_timing[0];
    dtc_controldata_1.dtdar = (uint16_t) &TRJ0;

    dtc_controldata_2.dtccr = _01_DTC_TRANSFER_MODE_REPEAT | _02_DTC_REPEAT_AREA_SOURCE | 
                              _04_DTC_SOURCE_ADDR_INCREMENTED | _00_DTC_DEST_ADDR_FIXED |
                              _00_DTC_CHAIN_TRANSFER_DISABLE | _00_DTC_REPEAT_INT_DISABLE | 
                              _40_DTC_DATA_SIZE_16BITS;
    dtc_controldata_2.dtbls = 0x01;
    dtc_controldata_2.dtcct = 0x02;
    dtc_controldata_2.dtrld = 0x02;
    dtc_controldata_2.dtsar = (uint16_t) &IT_timing[0];
    dtc_controldata_2.dtdar = (uint16_t) &ITMC;
    
}

/* End user code. Do not edit comment generated here */
