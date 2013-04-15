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
* File Name    : fsl_user_ram_functions.c
* Version      : 1.0
* Device(s)    : R5F104PJ
* Tool-Chain   : IAR Systems iccrl78
* Description  : This file implements the user modules to be used with FSL lib
* Creation Date: 18.12.2012
***********************************************************************************************************************/
#include "BL_r_cg_macrodriver.h"
#include "BL_r_cg_userdefine.h"

#include "fsl.h"
#include "fsl_user.h"


// define interrupt routine from ram
// interrupt routine needs to catch everything, and cannot access flash !!!!
// interrupts need to be quitted explicitly within this ISR
static volatile uint8_t numKeyPressRam = 0;
FSL_INT_RAM_CODE void FSL_userIsrInRam(void) {
      
    // interrupt from INTP0  
    if(1u == PIF0) {
      
        PIF0 = 0; // have to clear this explicitly
        keyPress = 1;
        numKeyPress++;
        numKeyPressRam++;
    };

    // interrupt from interval timer
    if(1u == ITIF) {

        ITIF = 0; // have to clear this explicitly
        
        hundredMsec++;
        if(hundredMsec >= 9) {
            hundredMsec = 0;
            P6_bit.no2 ^= 1U;
      };
    }    
  
}



USER_RAM_CODE fsl_u08 eraseFromRam(uint16_t startBlockNum, uint16_t endBlockNum) {

    fsl_u08 fslStatus;
    uint16_t i;

    // erase blocks
    for(i=startBlockNum;i<=endBlockNum;i++) {
        
      fslStatus = FSL_Erase(i);
      while(FSL_BUSY == fslStatus) {        
        fslStatus = FSL_StatusCheck(); 
      };
      
      if(FSL_OK != fslStatus) while(1);
      
      fslStatus = FSL_BlankCheck(i);
      while(FSL_BUSY == fslStatus) {        
        fslStatus = FSL_StatusCheck(); 
      };
      
      if(FSL_OK != fslStatus) while(1);  
    
    }
    
    return(FSL_OK);
}

USER_RAM_CODE fsl_u08 writeFromRam(uint16_t numBlocks, __near fsl_write_t* fslWriteStrPtr) {

    fsl_u08 fslStatus;
    uint16_t i;
    
    // write new data
    for(i=0;i<numBlocks;i++) {
        
        fslStatus = FSL_Write(fslWriteStrPtr);
        while(FSL_BUSY == fslStatus) {        
            fslStatus = FSL_StatusCheck(); 
        };
        if(FSL_OK != fslStatus) while(1);    
        
        fslWriteStrPtr->fsl_destination_address_u32 += WORK_BUFFER_SIZE;
    }  
    
    return(FSL_OK);
}

USER_RAM_CODE uint8_t verifyFromRam(uint16_t startBlockNum, uint16_t endBlockNum) {

    fsl_u08 fslStatus;
    uint16_t i;
    
    // verify retention
    for(i=startBlockNum;i<=endBlockNum;i++) {
        
        fslStatus = FSL_IVerify(i);
        while(FSL_BUSY == fslStatus) {        
         fslStatus = FSL_StatusCheck(); 
        }
    
        if(FSL_OK != fslStatus) while(1);         
    };
    
    return(FSL_OK);  
}





