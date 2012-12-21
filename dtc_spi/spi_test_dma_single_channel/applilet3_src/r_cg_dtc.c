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
* Creation Date: 16.11.2012
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_dtc.h"
/* Start user code for include. Do not edit comment generated here */
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

#pragma location = 0xFFD50U
__no_init st_dtc_data dtc_controldata_2;

#pragma location = 0xFFD58U
__no_init st_dtc_data dtc_controldata_3;

/* Start user code for global. Do not edit comment generated here */
extern uint8_t commandBuffer[];
extern uint8_t addressBuffer[];
extern uint8_t slaveResponse_L[];
extern uint8_t slaveResponse_H[];

/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_DTC_Create
* Description  : This function initializes the DTC module.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_DTC_Create(void)
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
    dtc_vectortable[28] = 0x40U;
    dtc_controldata_0.dtccr = _01_DTC_TRANSFER_MODE_REPEAT | _20_DTC_REPEAT_INT_ENABLE | _00_DTC_DATA_SIZE_8BITS | _00_DTC_SOURCE_ADDR_FIXED |
                              _08_DTC_DEST_ADDR_INCREMENTED | _10_DTC_CHAIN_TRANSFER_ENABLE | _00_DTC_REPEAT_AREA_DEST;
    dtc_controldata_0.dtbls = _01_DTCD0_TRANSFER_BLOCKSIZE;
    dtc_controldata_0.dtcct = BURST_SIZE;
    dtc_controldata_0.dtrld = BURST_SIZE; 
		dtc_controldata_0.dtsar = 0xFF48; /* address of SDR10 - CSI20 */
    dtc_controldata_0.dtdar = (uint16_t) &slaveResponse_H[0];
    
		/* Set DTCD1 */
    dtc_controldata_1.dtccr = _01_DTC_TRANSFER_MODE_REPEAT | _00_DTC_REPEAT_INT_DISABLE | _00_DTC_DATA_SIZE_8BITS | _04_DTC_SOURCE_ADDR_INCREMENTED |
                              _00_DTC_DEST_ADDR_FIXED | _00_DTC_CHAIN_TRANSFER_DISABLE | _02_DTC_REPEAT_AREA_SOURCE;
    dtc_controldata_1.dtbls = _01_DTCD1_TRANSFER_BLOCKSIZE;
    dtc_controldata_1.dtcct = BURST_SIZE;
    dtc_controldata_1.dtrld = BURST_SIZE; 
		dtc_controldata_1.dtsar = (uint16_t) &commandBuffer[0];    
		dtc_controldata_1.dtdar = 0xFF48; /* address of SDR10 - CSI20 */
		
    /* Set DTCD2 */
    /* 
    * The second dma channel does not need to issue an interrupt. 
    * In the interrupt issued by dma channel 0 the timer gets stopped so 
    * that there are no transfers anymore after a full frame, thus also DTC2 stops 
    */
    dtc_vectortable[30] = 0x50U;
    dtc_controldata_2.dtccr = _01_DTC_TRANSFER_MODE_REPEAT | _00_DTC_REPEAT_INT_DISABLE | _00_DTC_DATA_SIZE_8BITS | _00_DTC_SOURCE_ADDR_FIXED |
                              _08_DTC_DEST_ADDR_INCREMENTED | _10_DTC_CHAIN_TRANSFER_ENABLE | _00_DTC_REPEAT_AREA_DEST;
    dtc_controldata_2.dtbls = _01_DTCD2_TRANSFER_BLOCKSIZE;
    dtc_controldata_2.dtcct = BURST_SIZE;
    dtc_controldata_2.dtrld = BURST_SIZE; 
    dtc_controldata_2.dtsar = 0xFF48; /* address of SDR10 - CSI20 */
    dtc_controldata_2.dtdar =  (uint16_t) &slaveResponse_L[0];
    
		/* Set DTCD3 */
    dtc_controldata_3.dtccr = _01_DTC_TRANSFER_MODE_REPEAT | _00_DTC_REPEAT_INT_DISABLE | _00_DTC_DATA_SIZE_8BITS | _04_DTC_SOURCE_ADDR_INCREMENTED |
                              _00_DTC_DEST_ADDR_FIXED | _00_DTC_CHAIN_TRANSFER_DISABLE | _02_DTC_REPEAT_AREA_SOURCE;
    dtc_controldata_3.dtbls = _01_DTCD3_TRANSFER_BLOCKSIZE;
    dtc_controldata_3.dtcct = BURST_SIZE;
    dtc_controldata_3.dtrld = BURST_SIZE; 
    dtc_controldata_3.dtsar = (uint16_t) &addressBuffer[0];
    dtc_controldata_3.dtdar = 0xFF48; /* address of SDR10 - CSI20 */
}

/***********************************************************************************************************************
* Function Name: R_DTCD0_Start
* Description  : This function enables DTCD0 module operation.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_DTCD0_Start(void)
{
  /* GP modified: single bit access */
	DTCEN3_bit.no3 = 1U;
}

/***********************************************************************************************************************
* Function Name: R_DTCD0_Stop
* Description  : This function disables DTCD0 module operation.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_DTCD0_Stop(void)
{
  /* GP modified: single bit access */
		DTCEN3_bit.no3 = 0U;
}

/***********************************************************************************************************************
* Function Name: R_DTCD2_Start
* Description  : This function enables DTCD2 module operation.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_DTCD2_Start(void)
{
	/* GP modified: single bit access */
	DTCEN3_bit.no1 = 1U;
}

/***********************************************************************************************************************
* Function Name: R_DTCD2_Stop
* Description  : This function disables DTCD2 module operation.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_DTCD2_Stop(void)
{
  /* GP modified: single bit access */
		DTCEN3_bit.no1 = 0U;
}

/* Start user code for adding. Do not edit comment generated here */

/* End user code. Do not edit comment generated here */
