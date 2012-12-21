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
* Copyright (C) 2012 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name    : fsl_user.c
* Version      : 1.0
* Device(s)    : R5F104PJ
* Tool-Chain   : IAR Systems iccrl78
* Description  : This file implements some user helper modules to be used with FSL lib
* Creation Date: 18.12.2012
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_userdefine.h"

#include "fsl.h"
#include "fsl_user.h"

// copy the interrupt function to the ram area
void FSL_userCopyInterruptToRam(void) {
     
    FSL_ROM_CODE_PTR romcode_start; // base of rom code section
    FSL_ROM_CODE_PTR romcode_end;   // base of rom code section    
    FSL_RAM_CODE_PTR ramcode_start; // base of ram code section

    // get hold of the rom contents
    romcode_start = (FSL_ROM_CODE_PTR) __segment_begin("FSL_INT_ROM_CODE");
    romcode_end = (FSL_ROM_CODE_PTR) __segment_end("FSL_INT_ROM_CODE");    
    
    // get the ram pointer
    ramcode_start = (FSL_RAM_CODE_PTR) __segment_begin("FSL_INT_RAM_CODE");    
    
    // copy in a loop - the end pointer is the next location past the segment
    while(romcode_start < romcode_end) {
      
      *ramcode_start++ = *romcode_start++;
    }
    
}

// copy the interrupt function to the ram area
void FSL_userCopyApplicationCodeToRam(void) {
     
    USER_ROM_CODE_PTR romcode_start; // base of rom code section
    USER_ROM_CODE_PTR romcode_end;   // base of rom code section    
    USER_RAM_CODE_PTR ramcode_start; // base of ram code section

    // get hold of the rom contents
    romcode_start = (USER_ROM_CODE_PTR) __segment_begin("USER_ROM_CODE");
    romcode_end = (USER_ROM_CODE_PTR) __segment_end("USER_ROM_CODE");    
    
    // get the ram pointer
    ramcode_start = (USER_RAM_CODE_PTR) __segment_begin("USER_RAM_CODE");    
    
    // copy in a loop - the end pointer is the next location past the segment
    while(romcode_start < romcode_end) {
      
      *ramcode_start++ = *romcode_start++;
    }
    
}

// block number is in 1K chunks so ignore the last 10 bit
#define BLOCK_NUM(address) (((uint32_t)address) >> 10)

// retrieve the block numbers used for the flash memory to be reprogrammed
void FSL_userGetFlashBlockRanges(uint16_t* startBlock, uint16_t* endBlock) {

    PROG_FLASH_PTR prog_flash_start;    // base of flash block
    PROG_FLASH_PTR prog_flash_end;      // end of flash block

    prog_flash_start = (PROG_FLASH_PTR) __segment_begin("APPLICATION_FLASH");
    prog_flash_end = (PROG_FLASH_PTR) __segment_end("APPLICATION_FLASH");
  
    // determine the block ranges
    *startBlock = BLOCK_NUM(prog_flash_start);
    *endBlock = BLOCK_NUM(prog_flash_end);   
}

// function to determine the start of the flash range to be programmed
uint32_t FSL_userGetFlashStartAddress(void) {
  
    uint32_t prog_flash_start;    // base of flash block

    prog_flash_start = (uint32_t) __segment_begin("APPLICATION_FLASH");

    return(prog_flash_start);
}

// function to determine the end of the flash range to be programmed
uint32_t FSL_userGetFlashEndAddress(void) {

    uint32_t prog_flash_end;      // end of flash block

    prog_flash_end = (uint32_t) __segment_end("APPLICATION_FLASH");  

    return(prog_flash_end);
}


