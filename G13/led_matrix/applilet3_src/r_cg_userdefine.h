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
* File Name    : r_cg_userdefine.h
* Version      : Applilet3 for RL78/G13 V2.00.00.08 [12 Apr 2013]
* Device(s)    : R5F100SL
* Tool-Chain   : IAR Systems iccrl78
* Description  : This file includes user definition.
* Creation Date: 17/07/2013
***********************************************************************************************************************/

#ifndef _USER_DEF_H
#define _USER_DEF_H

/***********************************************************************************************************************
User definitions
***********************************************************************************************************************/

/* Start user code for function. Do not edit comment generated here */

#define NUM_COM             8

typedef enum COM_t {
  
  COM0 = 0,
  COM1,
  COM2,
  COM3,
  COM4,
  COM5,
  COM6,
  COM7
    
} COM_t;

typedef enum ROW_t {
  
  ROW0 = 0,
  ROW1,
  ROW2,
  ROW3,
  ROW4,
  ROW5,
  ROW6,
  ROW7
    
} ROW_t;

typedef enum DIM_LEVEL_t {

    
    LEVEL_1 = 0, LEVEL_2, LEVEL_3, LEVEL_4, LEVEL_5, LEVEL_6, LEVEL_7, LEVEL_8, 
    LEVEL_9, LEVEL_10, LEVEL_11, LEVEL_12, LEVEL_13, LEVEL_14, LEVEL_15, LEVEL_16,  
    LEVEL_17, LEVEL_18, LEVEL_19, LEVEL_20, LEVEL_21, LEVEL_22, LEVEL_23, LEVEL_24,
    LEVEL_25, LEVEL_26, LEVEL_27, LEVEL_28, LEVEL_29, LEVEL_30, LEVEL_31, LEVEL_32,
    LEVEL_33, LEVEL_34, LEVEL_35, LEVEL_36, LEVEL_37, LEVEL_38, LEVEL_39, LEVEL_40,
    LEVEL_41, LEVEL_42, LEVEL_43, LEVEL_44, LEVEL_45, LEVEL_46, LEVEL_47, LEVEL_48,
    LEVEL_49, LEVEL_50, LEVEL_51, LEVEL_52, LEVEL_53, LEVEL_54, LEVEL_55, LEVEL_56,
    LEVEL_57, LEVEL_58, LEVEL_59, LEVEL_60, LEVEL_61, LEVEL_62, LEVEL_63, LEVEL_64,
    NUM_DIM_LEVELS
      
} DIM_LEVEL_t;

typedef enum LIGHT_DIR_t {

    UP = 0,
    DOWN
      
} LIGHT_DIR_t;



#define DIM_STEPS           (NUM_DIM_LEVELS+2) // 2 are for the dead band insertion




typedef struct ledRow {
  union {
    uint8_t row;
    __BITS8 led; 
  };
} ledRow_t;
  

typedef struct dimmedLedRow {
  
  uint8_t  rowBeginDeadTime;
  ledRow_t dimmedLed[DIM_STEPS];
  uint8_t  rowEndDeadTime;
  
} dimmedLedRow_t;

typedef struct ledArray {
  
  union {
    
    dimmedLedRow_t ledArray[NUM_COM];
    uint8_t segmentBuffer[NUM_COM*DIM_STEPS];
  };
  
} ledArray_t;



extern ledArray_t ledArray_A;
extern ledArray_t ledArray_B;
extern uint8_t com[NUM_COM];
extern uint16_t timerPeriod[DIM_STEPS];


void DMAC0_Create(void);
void DMAC1_Create(void);
void DMAC2_Create(void);
void DMAC3_Create(void);

void initSeg(void);
void initCom(void);


extern volatile uint8_t trigger;

/* End user code. Do not edit comment generated here */
#endif
