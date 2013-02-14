/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only 
* intended for use with Renesas products. No other uses are authorized. This 
* software is owned by Renesas Electronics Corporation and is protected under 
* all applicable laws, including copyright laws.
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING 
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT 
* LIMITED TO WARRNTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE 
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
* File Name    : r_main.c
* Version      : Applilet3 for RL78/I1A V1.01.01 [05 Oct 2011]
* Device(s)    : R5F107DE
* Tool-Chain   : IAR Systems iccrl78
* Description  : This file implements main function.
* Creation Date: 14.02.2013
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

#include "fsl.h"
#include "fsl_user.h"

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

// variables for checking the FSL status

fsl_u08 fslSecurityFlags;
fsl_u08 fslBootFlag;
fsl_u08 fslSwapState;
fsl_fsw_t fslFlashShieldWindow;
__far fsl_descriptor_t fslDescriptor;
fsl_u08 __far* fslVersionString;


// define 5 arrays in flash, spanning 5 blocks
#define NUM_DATA_BLOCKS 5
#define FLASH_ITEM_SIZE 256

typedef const struct progFlashBlockStr {

    uint8_t const flashData0[FLASH_ITEM_SIZE];
    uint8_t const flashData1[FLASH_ITEM_SIZE];
    uint8_t const flashData2[FLASH_ITEM_SIZE];
    uint8_t const flashData3[FLASH_ITEM_SIZE];
    uint8_t const flashData4[FLASH_ITEM_SIZE];   

} progFlashBlockStr;

/* specify __no init to avoid OCD to re-program the flash while downloading */
PROG_FLASH __root __no_init progFlashBlockStr flashData;


uint8_t workingBuffer[WORK_BUFFER_SIZE];

__near fsl_write_t fslWriteStr;


USER_RAM_CODE fsl_u08 eraseFromRam(uint16_t startBlockNum, uint16_t endBlockNum);
USER_RAM_CODE fsl_u08 writeFromRam(uint16_t numBlocks, __near fsl_write_t* fslWriteStr); 
USER_RAM_CODE fsl_u08 verifyFromRam(uint16_t startBlockNum, uint16_t endBlockNum); 


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
  
    uint16_t i, startBlockNum, endBlockNum;
    fsl_u08 fslStatus;
    
    // prepare the interrupt vector table and user code in ram 
    FSL_userCopyInterruptToRam();
    FSL_userCopyApplicationCodeToRam();
    
    // copy the relevant FSL API sections to ram
    FSL_CopySection();
    
    // prepare the descriptor for initializing the mode
    fslDescriptor.fsl_flash_voltage_u08 = 0x0;      // full speed mode
    fslDescriptor.fsl_frequency_u08 = 32;           // 32 MHz frequency, round up
    fslDescriptor.fsl_auto_status_check_u08 = 0x0;  // status check user mode

    // retrieve the flash block numbers for checking
    FSL_userGetFlashBlockRanges(&startBlockNum, &endBlockNum);
      
    // always do this sequence before using FSL
    fslStatus = FSL_Init(&fslDescriptor);
    FSL_Open();
    FSL_PrepareFunctions();
    FSL_PrepareExtFunctions();                      
    
    // get the flash status
    fslVersionString = FSL_GetVersionString();            
    fslStatus = FSL_GetSecurityFlags(&fslSecurityFlags);
    fslStatus = FSL_GetBootFlag(&fslBootFlag);
    fslStatus = FSL_GetSwapState(&fslSwapState);        
    fslStatus = FSL_GetFlashShieldWindow(&fslFlashShieldWindow);        
    
    // activate the interrupt table in ram
    FSL_ChangeInterruptTable((fsl_u16)&FSL_userIsrInRam);

    R_INTC0_Start();
    R_IT_Start();
    
    // repeat in a loop to demonstrate interrupt servicing in background
    while(1) {
    
      fslStatus = eraseFromRam(startBlockNum, endBlockNum);
      
      FSL_RestoreInterruptTable();
      
      // prepare buffer data
      for(i=0;i<WORK_BUFFER_SIZE;i++) {
        workingBuffer[i] = i;
      }
      
      fslWriteStr.fsl_data_buffer_p_u08 = &workingBuffer[0];
      fslWriteStr.fsl_word_count_u08 = WORK_BUFFER_WDSIZE;
      fslWriteStr.fsl_destination_address_u32 = FSL_userGetFlashStartAddress();     
      
      FSL_ChangeInterruptTable((fsl_u16)&FSL_userIsrInRam);
      
      fslStatus = writeFromRam(NUM_DATA_BLOCKS, &fslWriteStr);

      fslStatus = verifyFromRam(startBlockNum, endBlockNum);
      
      FSL_RestoreInterruptTable();
      
      // toggle the led if requested
      if(keyPress) {
        keyPress = 0;
        P7_bit.no6 ^= 1U;
      };            

      FSL_ChangeInterruptTable((fsl_u16)&FSL_userIsrInRam);
      
    };  

    /* End user code. Do not edit comment generated here */
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
