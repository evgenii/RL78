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
* File Name    : fsl_user.h
* Version      : 1.0
* Device(s)    : R5F104PJ
* Tool-Chain   : IAR Systems iccrl78
* Description  : This file implements some user helper modules to be used with FSL lib
* Creation Date: 18.12.2012
***********************************************************************************************************************/
#ifndef __FSL_USER_H
#define __FSL_USER_H

// declaration of segment used to determine the flash boundaries within the application
#pragma segment="APPLICATION_FLASH" __far
#define PROG_FLASH _Pragma("location=\"APPLICATION_FLASH\"")
#define PROG_FLASH_PTR uint8_t __far*

// declaration of segments where the FSL interrupt routine is located
#pragma segment="FSL_INT_ROM_CODE" __far
#define FSL_ROM_CODE_PTR uint8_t __far*
#define FSL_INT_ROM_CODE _Pragma("location=\"FSL_INT_ROM_CODE\"") __interrupt 

#pragma segment="FSL_INT_RAM_CODE" __far
#define FSL_RAM_CODE_PTR uint8_t __far*
#define FSL_INT_RAM_CODE _Pragma("location=\"FSL_INT_RAM_CODE\"") __interrupt 


// declaration of segments where the application code is located
// load region is rom, execution region is ram
#pragma segment="USER_ROM_CODE" __far
#define USER_ROM_CODE_PTR uint8_t __far*
#define USER_ROM_CODE _Pragma("location=\"USER_ROM_CODE\"") __far_func

#pragma segment="USER_RAM_CODE" __far
#define USER_RAM_CODE_PTR uint8_t __far*
#define USER_RAM_CODE _Pragma("location=\"USER_RAM_CODE\"") __far_func


#define WORK_BUFFER_SIZE    256     // in bytes
#define WORK_BUFFER_WDSIZE  (256/4) // in 4 byte words


// copy routine for the ram interrupt setup
void FSL_userCopyInterruptToRam(void);

// copy routine for the ram executed application code
void FSL_userCopyApplicationCodeToRam(void);

// function to determine the block ranges to be checked or erased
void FSL_userGetFlashBlockRanges(uint16_t* startBlock, uint16_t* endBlock);

// function to determine the start of the flash range to be programmed
uint32_t FSL_userGetFlashStartAddress(void);

// function to determine the end of the flash range to be programmed
uint32_t FSL_userGetFlashEndAddress(void);

// prototype of the RAM interrupt routine
FSL_INT_RAM_CODE void FSL_userIsrInRam(void);

#endif

