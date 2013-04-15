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
* File Name    : r_main_internal_mode.c
* Version      : Applilet3 for RL78/G13 V1.03.01 [11 Oct 2011]
* Device(s)    : R5F100LE
* Tool-Chain   : IAR Systems iccrl78
* Description  : This file implements main function.
* Creation Date: 21.12.2012
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "BL_r_cg_macrodriver.h"
#include "BL_r_cg_cgc.h"
#include "BL_r_cg_port.h"
#include "BL_r_cg_intc.h"
#include "BL_r_cg_it.h"
/* Start user code for include. Do not edit comment generated here */

#include "fsl.h"
#include "fsl_user.h"

/* End user code. Do not edit comment generated here */
#include "BL_r_cg_userdefine.h"

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
__root const uint8_t opbyte3 = 0x04U;

/* Set security ID */
#pragma location = "SECUID"
__root const uint8_t secuid[10] = 
    {0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U};
/* Start user code for global. Do not edit comment generated here */


// variables for checking the FSL status
fsl_u08 fslStatus;
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


/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: main
* Description  : This function implements main function.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void BL_main(void)
{
    /* Start user code. Do not edit comment generated here */
    
    uint16_t i, startBlockNum, endBlockNum;

      
    fslDescriptor.fsl_flash_voltage_u08 = 0x0;      // full speed mode
    fslDescriptor.fsl_frequency_u08 = 32;           // 32 MHz frequency, round up
    fslDescriptor.fsl_auto_status_check_u08 = 0x1;  // status check internal mode

    // retrieve the flash block numbers for checking
    FSL_userGetFlashBlockRanges(&startBlockNum, &endBlockNum);
      
    // always do this sequence first
    fslStatus = FSL_Init(&fslDescriptor);
    FSL_Open();
    FSL_PrepareFunctions();
    FSL_PrepareExtFunctions();         
               
    // prepare the interrupt vector table in ram before the timer starts
    FSL_userCopyInterruptToRam();
    
    // get the flash status
    fslVersionString = FSL_GetVersionString();            
    fslStatus = FSL_GetSecurityFlags(&fslSecurityFlags);
    fslStatus = FSL_GetBootFlag(&fslBootFlag);
    fslStatus = FSL_GetSwapState(&fslSwapState);        
    fslStatus = FSL_GetFlashShieldWindow(&fslFlashShieldWindow);        

    BL_R_INTC0_Start();
    BL_R_IT_Start();
    
    // repeat in a loop to wait for interrupt (keypress)
    while(1) {    
      
      
      if(keyPress) {
              
        keyPress = 0;
        
        // activate the interrupt table in ram for the FSL library
        FSL_ChangeInterruptTable((fsl_u16)&FSL_userIsrInRam);
        
        // erase blocks
        for(i=startBlockNum;i<=endBlockNum;i++) {
        
            fslStatus = FSL_Erase(i);
            if(FSL_OK != fslStatus) while(1);
        
            fslStatus = FSL_BlankCheck(i);
            if(FSL_OK != fslStatus) while(1);       
        }
      
        // demonstrate interrupt servicing in background
        FSL_RestoreInterruptTable();
      
        // prepare buffer data
        for(i=0;i<WORK_BUFFER_SIZE;i++) {
            workingBuffer[i] = i;
        }
      
        fslWriteStr.fsl_data_buffer_p_u08 = &workingBuffer[0];
        fslWriteStr.fsl_word_count_u08 = WORK_BUFFER_WDSIZE;
        fslWriteStr.fsl_destination_address_u32 = FSL_userGetFlashStartAddress();     
      
        FSL_ChangeInterruptTable((fsl_u16)&FSL_userIsrInRam);
      
        // write new data
        for(i=0;i<NUM_DATA_BLOCKS;i++) {
        
            fslStatus = FSL_Write(&fslWriteStr);
            if(FSL_OK != fslStatus) while(1);
        
            fslWriteStr.fsl_destination_address_u32 += WORK_BUFFER_SIZE;
        }
      
        // verify retention
        for(i=startBlockNum;i<=endBlockNum;i++) {
        
            fslStatus = FSL_IVerify(i);
            if(FSL_OK != fslStatus) while(1);    
        }
      
        FSL_RestoreInterruptTable();      
        
        DI();
        
        BL_R_INTC0_Stop();
        BL_R_IT_Stop();
        

        /* get the location of the reset vector for the application */
        pAPP_START = (void (**)(void))(APPLICATION_RESET_VECTOR);
        (*pAPP_START)();        // jump to the application
        
      };            
      
      STOP();
    };  
    
    /* End user code. Do not edit comment generated here */
}

/* Start user code for adding. Do not edit comment generated here */


/* End user code. Do not edit comment generated here */
