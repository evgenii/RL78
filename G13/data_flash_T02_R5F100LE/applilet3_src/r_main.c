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
* File Name    : r_main.c
* Version      : Applilet3 for RL78/G13 V2.01.00.01 [26 Jul 2013]
* Device(s)    : R5F100LE
* Tool-Chain   : IAR Systems iccrl78
* Description  : This file implements main function.
* Creation Date: 19.11.2013
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

#include "fdl.h"
#include "fdl_descriptor.h"

#include "eel.h"
#include "eel_descriptor.h"
#include "eel_user_types.h"

/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */

char libVersion[24];
unsigned char  __far * version;
fdl_status_t dataFlashStatus;
#pragma data_alignment=2
fdl_request_t dataFlashRequest;
uint8_t flashData[8];

eel_status_t eepromStatus;
eel_driver_status_t eelDriverStatus;

#pragma data_alignment=2
eel_request_t eepromRequest;
uint8_t eepromData[8];

// data variable examples
type_A arrayA;
type_B arrayB;
type_C arrayC;
type_D arrayD;
type_E arrayE;
type_F arrayF;
type_X arrayX;
type_Z arrayZ;

eel_u16 eelFreeSpace;

// On RL78/G13
#define NUM_DATAFLASH_BLOCKS    4
#define BLOCK_SIZE_BYTES    0x400

#if((EEL_POOL_BLOCKS + FDL_POOL_BLOCKS)!= NUM_DATAFLASH_BLOCKS)
#error "check the block allocation between FDL and EEL Pool, check fsl_descriptor.h"
#endif
#if(EEL_POOL_BLOCKS < 2)
#error "Minimum number of blocks for EEL is 2, check 'fsl_descriptor.h'"
#endif

/* End user code. Do not edit comment generated here */

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

void R_MAIN_UserInit(void);

/***********************************************************************************************************************
* Function Name: main
* Description  : This function implements main function.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void main(void)
{
    R_MAIN_UserInit();
    /* Start user code. Do not edit comment generated here */
  
	uint32_t i,j;
	// fdl_descriptor_t descriptor;

    R_IT_Start();
    R_INTC0_Start(); 
    
    /* Block 0,1 are reserved for EEL 
     * Physical Block 2,3 are used by FDL 
     * These are mapped to logical blocks 0,1
     * Configuration is done within fdl_descriptor.h    
     */   
	dataFlashStatus =  FDL_Init(&fdl_descriptor_str);
	
    // in case of error, lit LED 2 and stay there
	if(dataFlashStatus != FDL_OK) {	 
	  P6_bit.no3 = 0;
      while(1);
	}
	
    FDL_Open();
    
    // just copy the version string for info
	version = FDL_GetVersionString();
	i = 0;
	do{ 
	  	libVersion[i++] = *version++; 
		if(23==i) break;
	}
	while((*version) != 0);
	
	// prepare some data
	for(j=0;j<8;j++) flashData[j] = j+1;
	
	
    for(i=0;i<FDL_POOL_BLOCKS;i++) {
      
      // erase block 0
      dataFlashRequest.index_u16 = i;
      dataFlashRequest.data_pu08 = 0;
      dataFlashRequest.bytecount_u16 = 0;
	  dataFlashRequest.command_enu = FDL_CMD_ERASE_BLOCK;	  
	
      /* command initiation */ 
      do  { 
        FDL_Execute(&dataFlashRequest); 
        FDL_Handler(); /* proceed background process */ 
      }      
      while (dataFlashRequest.status_enu == FDL_ERR_REJECTED); 
      
      /* command execution */ 
      do  { 
        FDL_Handler(); 
      }  
      while (dataFlashRequest.status_enu == FDL_BUSY);     
      
      
      if(dataFlashRequest.status_enu != FDL_OK) {	 
        P6_bit.no3 = 0;
        while(1);
      }
      
      // check block is erased
      dataFlashRequest.index_u16 = i;
      dataFlashRequest.data_pu08 = 0;
      dataFlashRequest.bytecount_u16 = 8;
      dataFlashRequest.command_enu = FDL_CMD_BLANKCHECK_BYTES;	  
      
      /* command initiation */ 
      do  { 
        FDL_Execute(&dataFlashRequest); 
        FDL_Handler(); /* proceed background process */ 
      }      
      while (dataFlashRequest.status_enu == FDL_ERR_REJECTED); 
      
      /* command execution */ 
      do  { 
        FDL_Handler(); 
      }  
      while (dataFlashRequest.status_enu == FDL_BUSY);     
      
      
      if(dataFlashRequest.status_enu != FDL_OK) {	 
        P6_bit.no3 = 0;
        while(1);
      }
	
    };

   for(i=0;i<FDL_POOL_BLOCKS;i++) {
     
     // write bytes
     dataFlashRequest.index_u16 = i*BLOCK_SIZE_BYTES;
     dataFlashRequest.data_pu08 = &flashData[0];
     dataFlashRequest.bytecount_u16 = 8;
     dataFlashRequest.command_enu = FDL_CMD_WRITE_BYTES;	  
     
     /* command initiation */ 
     do  { 
       FDL_Execute(&dataFlashRequest); 
       FDL_Handler(); /* proceed background process */ 
     }      
     while (dataFlashRequest.status_enu == FDL_ERR_REJECTED); 
     
     /* command execution */ 
     do  { 
       FDL_Handler(); 
     }  
     while (dataFlashRequest.status_enu == FDL_BUSY);     
     
     
     if(dataFlashRequest.status_enu != FDL_OK) {	 
       P6_bit.no3 = 0;
       while(1);
     }
     
     // verify cells
     dataFlashRequest.index_u16 = i*BLOCK_SIZE_BYTES;
     dataFlashRequest.data_pu08 = 0;
     dataFlashRequest.bytecount_u16 = 8;
     dataFlashRequest.command_enu = FDL_CMD_IVERIFY_BYTES;	  
     
     /* command initiation */ 
     do  { 
       FDL_Execute(&dataFlashRequest); 
       FDL_Handler(); /* proceed background process */ 
     }      
     while (dataFlashRequest.status_enu == FDL_ERR_REJECTED); 
     
     /* command execution */ 
     do  { 
       FDL_Handler(); 
     }  
     while (dataFlashRequest.status_enu == FDL_BUSY);     
     
     
     if(dataFlashRequest.status_enu != FDL_OK) {	 
       P6_bit.no3 = 0;
       while(1);
     }
     
     // destroy original data and read back from data flash
     for(j=0;j<8;j++) flashData[j] = 0xAA;	
     
     dataFlashRequest.index_u16 = i*BLOCK_SIZE_BYTES;
     dataFlashRequest.data_pu08 = &flashData[0];
     dataFlashRequest.bytecount_u16 = 8;
     dataFlashRequest.command_enu = FDL_CMD_READ_BYTES;	  
     
     /* command initiation */ 
     do  { 
       FDL_Execute(&dataFlashRequest); 
       FDL_Handler(); /* proceed background process */ 
     }      
     while (dataFlashRequest.status_enu == FDL_ERR_REJECTED); 
     
     /* command execution */ 
     // a call to the Handler will return "idle" status
     do  { 
       FDL_Handler(); 
     }  
     while (dataFlashRequest.status_enu == FDL_BUSY);     
     
     
     if(dataFlashRequest.status_enu != FDL_OK) {	 
       P6_bit.no3 = 0;
       while(1);
     } 
       
   } 
	
   
   
   // now test the eeprom emulation
   eepromStatus = EEL_Init();
   if(eepromStatus != EEL_OK) {	 
       P6_bit.no3 = 0;
       while(1);
     } 
   
   // check the status, should return EEL_DRIVER_PASSIVE
   EEL_GetDriverStatus(&eelDriverStatus);
   
   // open logically the eeprom
   EEL_Open();

    // just copy the version string for info
	version = EEL_GetVersionString();
	i = 0;
	do{ 
	  	libVersion[i++] = *version++; 
		if(23==i) break;
	}
	while((*version) != 0);
    
   // check the status, should return EEL_DRIVER_PASSIVE
   EEL_GetDriverStatus(&eelDriverStatus);     
   
   eepromRequest.address_pu08 = 0;
   eepromRequest.identifier_u08 = 0;
   eepromRequest.command_enu = EEL_CMD_FORMAT;

   /* command initiation - FORMAT */       
   do  { 
     EEL_Execute(&eepromRequest); 
     EEL_Handler(); /* proceed background process */ 
   }      
   while (eepromRequest.status_enu == EEL_ERR_REJECTED); 
   
   /* command execution */ 
   // a call to the Handler will return "idle" status
   do  { 
     EEL_Handler(); 
   }  
   while (eepromRequest.status_enu == EEL_BUSY);     
   
   
   if(eepromRequest.status_enu != EEL_OK) {	 
     P6_bit.no3 = 0;
     while(1);
   } 

   // check the status, should return EEL_DRIVER_PASSIVE
   EEL_GetDriverStatus(&eelDriverStatus);   
   
   eepromRequest.address_pu08 = 0;
   eepromRequest.identifier_u08 = 0;
   eepromRequest.command_enu = EEL_CMD_STARTUP;

   /* command initiation - STARTUP */ 
   do  { 
     EEL_Execute(&eepromRequest); 
     EEL_Handler(); /* proceed background process */ 
   }      
   while (eepromRequest.status_enu == EEL_ERR_REJECTED); 
   
   /* command execution */ 
   // a call to the Handler will return "idle" status
   do  { 
     EEL_Handler(); 
   }  
   while (eepromRequest.status_enu == EEL_BUSY);     
   
   if(eepromRequest.status_enu != EEL_OK) {	 
     P6_bit.no3 = 0;
     while(1);
   }  

   // check the status, should return EEL_DRIVER_IDLE
   EEL_GetDriverStatus(&eelDriverStatus); 
   
   // now try to write some data
   i = 0;
   for(j=0;j<sizeof(type_A);j++) arrayA[j] = i;
   for(j=0;j<sizeof(type_B);j++) arrayB[j] = i;
   for(j=0;j<sizeof(type_E);j++) arrayE[j] = i;
   for(j=0;j<sizeof(type_F);j++) arrayF[j] = i;
   for(j=0;j<sizeof(type_Z);j++) arrayZ[j] = i;   
   
   // write A
   eepromRequest.address_pu08 = &arrayA[0];
   eepromRequest.identifier_u08 = 1;
   eepromRequest.command_enu = EEL_CMD_WRITE;

   /* command initiation - WRITE */ 
   do  { 
     EEL_Execute(&eepromRequest); 
     EEL_Handler(); /* proceed background process */ 
   }      
   while (eepromRequest.status_enu == EEL_ERR_REJECTED); 
   
   /* command execution */ 
   // a call to the Handler will return "idle" status
   do  { 
     EEL_Handler(); 
   }  
   while (eepromRequest.status_enu == EEL_BUSY);     
   
   if(eepromRequest.status_enu != EEL_OK) {	 
     P6_bit.no3 = 0;
     while(1);
   }  


   // write B
   eepromRequest.address_pu08 = &arrayB[0];
   eepromRequest.identifier_u08 = 2;
   eepromRequest.command_enu = EEL_CMD_WRITE;

   /* command initiation - WRITE */ 
   do  { 
     EEL_Execute(&eepromRequest); 
     EEL_Handler(); /* proceed background process */ 
   }      
   while (eepromRequest.status_enu == EEL_ERR_REJECTED); 
   
   /* command execution */ 
   // a call to the Handler will return "idle" status
   do  { 
     EEL_Handler(); 
   }  
   while (eepromRequest.status_enu == EEL_BUSY);     
   
   if(eepromRequest.status_enu != EEL_OK) {	 
     P6_bit.no3 = 0;
     while(1);
   }
   
   // check the status, should return EEL_DRIVER_IDLE
   EEL_GetDriverStatus(&eelDriverStatus);    
   
   // write E
   eepromRequest.address_pu08 = &arrayE[0];
   eepromRequest.identifier_u08 = 5;
   eepromRequest.command_enu = EEL_CMD_WRITE;

   /* command initiation - WRITE */ 
   do  { 
     EEL_Execute(&eepromRequest); 
     EEL_Handler(); /* proceed background process */ 
   }      
   while (eepromRequest.status_enu == EEL_ERR_REJECTED); 
   
   /* command execution */ 
   // a call to the Handler will return "idle" status
   do  { 
     EEL_Handler(); 
   }  
   while (eepromRequest.status_enu == EEL_BUSY);     
   
   if(eepromRequest.status_enu != EEL_OK) {	 
     P6_bit.no3 = 0;
     while(1);
   }
   
   // check the status, should return EEL_DRIVER_IDLE
   EEL_GetDriverStatus(&eelDriverStatus);   
   
   // write F
   eepromRequest.address_pu08 = &arrayF[0];
   eepromRequest.identifier_u08 = 6;
   eepromRequest.command_enu = EEL_CMD_WRITE;

   /* command initiation - WRITE */ 
   do  { 
     EEL_Execute(&eepromRequest); 
     EEL_Handler(); /* proceed background process */ 
   }      
   while (eepromRequest.status_enu == EEL_ERR_REJECTED); 
   
   /* command execution */ 
   // a call to the Handler will return "idle" status
   do  { 
     EEL_Handler(); 
   }  
   while (eepromRequest.status_enu == EEL_BUSY);     
   
   if(eepromRequest.status_enu != EEL_OK) {	 
     P6_bit.no3 = 0;
     while(1);
   }
   
   // check the status, should return EEL_DRIVER_IDLE
   EEL_GetDriverStatus(&eelDriverStatus);   
   
   // write Z
   eepromRequest.address_pu08 = &arrayZ[0];
   eepromRequest.identifier_u08 = 8;
   eepromRequest.command_enu = EEL_CMD_WRITE;

   /* command initiation - WRITE */ 
   do  { 
     EEL_Execute(&eepromRequest); 
     EEL_Handler(); /* proceed background process */ 
   }      
   while (eepromRequest.status_enu == EEL_ERR_REJECTED); 
   
   /* command execution */ 
   // a call to the Handler will return "idle" status
   do  { 
     EEL_Handler(); 
   }  
   while (eepromRequest.status_enu == EEL_BUSY);     
   
   if(eepromRequest.status_enu != EEL_OK) {	 
     P6_bit.no3 = 0;
     while(1);
   }
   
   // check the status, should return EEL_DRIVER_IDLE
   EEL_GetDriverStatus(&eelDriverStatus);    

   eepromRequest.address_pu08 = 0;
   eepromRequest.identifier_u08 = 0;
   eepromRequest.command_enu = EEL_CMD_VERIFY;
   
   /* command initiation - VERIFY */ 
   do  { 
     EEL_Execute(&eepromRequest); 
     EEL_Handler(); /* proceed background process */ 
   }      
   while (eepromRequest.status_enu == EEL_ERR_REJECTED); 
   
   /* command execution */ 
   // a call to the Handler will return "idle" status
   do  { 
     EEL_Handler(); 
   }  
   while (eepromRequest.status_enu == EEL_BUSY);     
   
   if(eepromRequest.status_enu != EEL_OK) {	 
     P6_bit.no3 = 0;
     while(1);
   }
   
   // check the status, should return EEL_DRIVER_IDLE
   EEL_GetDriverStatus(&eelDriverStatus);    

   // check the status, should return EEL_DRIVER_IDLE
   eepromStatus = EEL_GetSpace(&eelFreeSpace);    

   // now an endless loop
	while(1) {	  
	  
	  /* some fancy toggling on success */
	  P6_bit.no3 = ~ P6_bit.no3;
	  for(i=0;i<100000;i++);
	  P6_bit.no3 = ~ P6_bit.no3;
	  for(i=0;i<100000;i++);
	  P6_bit.no3 = ~ P6_bit.no3;
	  for(i=0;i<100000;i++);
	  P6_bit.no3 = ~ P6_bit.no3;
	  for(i=0;i<100000;i++);			  
    }
    
    /* End user code. Do not edit comment generated here */
}


/***********************************************************************************************************************
* Function Name: R_MAIN_UserInit
* Description  : This function adds user code before implementing main function.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_MAIN_UserInit(void)
{
    /* Start user code. Do not edit comment generated here */
    EI();
    /* End user code. Do not edit comment generated here */
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
