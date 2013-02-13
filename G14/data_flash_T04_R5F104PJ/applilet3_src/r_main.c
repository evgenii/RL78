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
* File Name    : r_main.c
* Version      : Applilet3 for RL78/G14 V1.01.01 [11 Oct 2011]
* Device(s)    : R5F104LE
* Tool-Chain   : IAR Systems iccrl78
* Description  : This file implements main function.
* Creation Date: 04.02.2013
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_cgc.h"
#include "r_cg_port.h"
#include "r_cg_intc.h"
#include "r_cg_it.h"
/* Start user code for include. Do not edit comment generated here */

#include "pfdl.h"

/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Set option bytes */
#pragma location = "OPTBYTE"
__root const uint8_t opbyte0 = 0xEFU;
#pragma location = "OPTBYTE"
__root const uint8_t opbyte1 = 0xFFU;
#pragma location = "OPTBYTE"
__root const uint8_t opbyte2 = 0xE8U;
#pragma location = "OPTBYTE"
__root const uint8_t opbyte3 = 0x84U;

/* Set security ID */
#pragma location = "SECUID"
__root const uint8_t secuid[10] = 
    {0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U};
/* Start user code for global. Do not edit comment generated here */

char libVersion[24];
unsigned char  __far * version;
pfdl_status_t dataFlashStatus;
pfdl_request_t dataFlashRequest;
uint8_t flashData[8];

/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: main
* Description  : This function implements main function.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void  main(void)
{
    /* Start user code. Do not edit comment generated here */
  
	uint32_t i;
	pfdl_descriptor_t descriptor;

    R_IT_Start();
    R_INTC0_Start(); 

	// this depends on the system settings!
	// fast mode @ 32 MHz in this case
	descriptor.fx_MHz_u08 = 32;
	descriptor.wide_voltage_mode_u08 = 0;
	dataFlashStatus =  PFDL_Open(&descriptor);
	
    // just copy the version string for info
	version = PFDL_GetVersionString();
	i = 0;
	do{ 
	  	libVersion[i++] = *version++; 
		if(23==i) break;
	}
	while((*version) != 0);
	
	// prepare some data
	for(i=0;i<8;i++) flashData[i] = i;
	
	// erase block 0	
	dataFlashRequest.index_u16 = 0;
	dataFlashRequest.data_pu08 = 0;
	dataFlashRequest.bytecount_u16 = 0;
	dataFlashRequest.command_enu = PFDL_CMD_ERASE_BLOCK;	  
	dataFlashStatus = PFDL_Execute(&dataFlashRequest);
	
	while(PFDL_BUSY == dataFlashStatus) {
	  dataFlashStatus = PFDL_Handler(); 	
	};	
	
	// in case of error, lit LED 2 and stay there
	if(dataFlashStatus != PFDL_OK) {	 
	  P7_bit.no6 = 0;
      while(1);
	}
	
	// check block is erased
	dataFlashRequest.index_u16 = 0;
	dataFlashRequest.data_pu08 = 0;
	dataFlashRequest.bytecount_u16 = 8;
	dataFlashRequest.command_enu = PFDL_CMD_BLANKCHECK_BYTES;	  
	dataFlashStatus = PFDL_Execute(&dataFlashRequest);
	while(PFDL_BUSY == dataFlashStatus) {
	  dataFlashStatus = PFDL_Handler(); 
	};
	
	if(dataFlashStatus != PFDL_OK) {	 
	    P7_bit.no6 = 0;
        while(1);
	}
	
	// write bytes
	dataFlashRequest.index_u16 = 0;
	dataFlashRequest.data_pu08 = &flashData[0];
	dataFlashRequest.bytecount_u16 = 8;
	dataFlashRequest.command_enu = PFDL_CMD_WRITE_BYTES;	  
	dataFlashStatus = PFDL_Execute(&dataFlashRequest);
	while(PFDL_BUSY == dataFlashStatus) {
	  dataFlashStatus = PFDL_Handler(); 	
	};
	
	if(dataFlashStatus != PFDL_OK) {	    
        P7_bit.no6 = 0;
        while(1);
	}
	
	// verify cells
	dataFlashRequest.index_u16 = 0;
	dataFlashRequest.data_pu08 = 0;
	dataFlashRequest.bytecount_u16 = 8;
	dataFlashRequest.command_enu = PFDL_CMD_IVERIFY_BYTES;	  
	dataFlashStatus =  PFDL_Execute(&dataFlashRequest);
	while(PFDL_BUSY == dataFlashStatus) {
	  dataFlashStatus = PFDL_Handler(); 	
	}
	
	if(dataFlashStatus != PFDL_OK) {	 
	    P7_bit.no6 = 0;
        while(1);
	}
	
	// destroy original data and read back from data flash
	for(i=0;i<8;i++) flashData[i] = 0xAA;	
	dataFlashRequest.index_u16 = 0;
	dataFlashRequest.data_pu08 = &flashData[0];
	dataFlashRequest.bytecount_u16 = 8;
	dataFlashRequest.command_enu = PFDL_CMD_READ_BYTES;	  
	// this execute immediately returns OK, as it does not use the sequencer
	dataFlashStatus = PFDL_Execute(&dataFlashRequest);
	// a call to the Handler will return "idle" status
	while(PFDL_BUSY == dataFlashStatus) {
	  dataFlashStatus = PFDL_Handler(); 	
	};
	
	if(dataFlashStatus != PFDL_OK) {	 
	    P7_bit.no6 = 0;
        while(1);
	}

	// now an endless loop
	while(1) {	  
	  
	  /* some fancy toggling on success */
	  P7_bit.no6 = ~ P7_bit.no6;
	  for(i=0;i<100000;i++);
	  P7_bit.no6 = ~ P7_bit.no6;
	  for(i=0;i<100000;i++);
	  P7_bit.no6 = ~ P7_bit.no6;
	  for(i=0;i<100000;i++);
	  P7_bit.no6 = ~ P7_bit.no6;
	  for(i=0;i<100000;i++);			  
    }

    /* End user code. Do not edit comment generated here */
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
