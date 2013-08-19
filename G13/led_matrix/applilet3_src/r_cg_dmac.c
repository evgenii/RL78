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
* File Name    : r_cg_dmac.c
* Version      : Applilet3 for RL78/G13 V2.00.00.08 [12 Apr 2013]
* Device(s)    : R5F100SL
* Tool-Chain   : IAR Systems iccrl78
* Description  : This file implements device driver for DMAC module.
* Creation Date: 17/07/2013
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_dmac.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_DMAC0_Create
* Description  : This function initializes the DMA0 transfer.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_DMAC0_Create(void)
{
    DRC0 = _80_DMA_OPERATION_ENABLE;
    NOP();
    NOP();
    DMAMK0 = 1U; /* disable INTDMA0 interrupt */
    DMAIF0 = 0U; /* clear INTDMA0 interrupt flag */
    /* Set INTDMA0 high priority */
    DMAPR10 = 0U;
    DMAPR00 = 0U;
    DMC0 = _40_DMA_TRANSFER_DIR_RAM2SFR | _20_DMA_DATA_SIZE_16 | _05_DMA_TRIGGER_TM03;
    DSA0 = _18_DMA0_SFR_ADDRESS;
    DRA0 = _7F00_DMA0_RAM_ADDRESS;
    DBC0 = _0040_DMA0_BYTE_COUNT;
    DEN0 = 0U; /* disable DMA0 operation */
}

/***********************************************************************************************************************
* Function Name: R_DMAC0_Start
* Description  : This function enables DMA0 transfer.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_DMAC0_Start(void)
{
    DMAIF0 = 0U; /* clear INTDMA0 interrupt flag */
    DMAMK0 = 0U; /* enable INTDMA0 interrupt */
    DEN0 = 1U;
    DST0 = 1U;
}

/***********************************************************************************************************************
* Function Name: R_DMAC0_Stop
* Description  : This function disables DMA0 transfer.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_DMAC0_Stop(void)
{
    if (DST0 != 0U)
    {
        DST0 = 0U;
    }
    
    NOP();
    NOP();
    DEN0 = 0U; /* disable DMA0 operation */
    DMAMK0 = 1U; /* disable INTDMA0 interrupt */
    DMAIF0 = 0U; /* clear INTDMA0 interrupt flag */
}

/***********************************************************************************************************************
* Function Name: R_DMAC1_Create
* Description  : This function initializes the DMA1 transfer.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_DMAC1_Create(void)
{
    DRC1 = _80_DMA_OPERATION_ENABLE;
    NOP();
    NOP();
    DMAMK1 = 1U; /* disable INTDMA1 interrupt */
    DMAIF1 = 0U; /* clear INTDMA1 interrupt flag */
    /* Set INTDMA1 level 1 priority */
    DMAPR11 = 0U;
    DMAPR01 = 1U;
    DMC1 = _40_DMA_TRANSFER_DIR_RAM2SFR | _00_DMA_DATA_SIZE_8 | _05_DMA_TRIGGER_TM03;
    DSA1 = _01_DMA1_SFR_ADDRESS;
    DRA1 = _7F00_DMA1_RAM_ADDRESS;
    DBC1 = _0200_DMA1_BYTE_COUNT;
    DEN1 = 0U; /* disable DMA1 operation */
}

/***********************************************************************************************************************
* Function Name: R_DMAC1_Start
* Description  : This function enables DMA1 transfer.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_DMAC1_Start(void)
{
    DMAIF1 = 0U; /* clear INTDMA1 interrupt flag */
    DMAMK1 = 0U; /* enable INTDMA1 interrupt */
    DEN1 = 1U;
    DST1 = 1U;
}

/***********************************************************************************************************************
* Function Name: R_DMAC1_Stop
* Description  : This function disables DMA1 transfer.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_DMAC1_Stop(void)
{
    if (DST1 != 0U)
    {
        DST1 = 0U;
    }
    
    NOP();
    NOP();
    DEN1 = 0U; /* disable DMA1 operation */
    DMAMK1 = 1U; /* disable INTDMA1 interrupt */
    DMAIF1 = 0U; /* clear INTDMA1 interrupt flag */
}

/***********************************************************************************************************************
* Function Name: R_DMAC2_Create
* Description  : This function initializes the DMA2 transfer.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_DMAC2_Create(void)
{
    DRC2 = _80_DMA_OPERATION_ENABLE;
    NOP();
    NOP();
    DMAMK2 = 1U; /* disable INTDMA2 interrupt */
    DMAIF2 = 0U; /* clear INTDMA2 interrupt flag */
    /* Set INTDMA2 level 1 priority */
    DMAPR12 = 0U;
    DMAPR02 = 1U;
    DMC2 = _40_DMA_TRANSFER_DIR_RAM2SFR | _00_DMA_DATA_SIZE_8 | _02_DMA_TRIGGER_TM10;
    DSA2 = _02_DMA2_SFR_ADDRESS;
    DRA2 = _7F00_DMA2_RAM_ADDRESS;
    DBC2 = _0200_DMA2_BYTE_COUNT;
    DEN2 = 0U; /* disable DMA2 operation */
}

/***********************************************************************************************************************
* Function Name: R_DMAC2_Start
* Description  : This function enables DMA2 transfer.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_DMAC2_Start(void)
{
    DMAIF2 = 0U; /* clear INTDMA2 interrupt flag */
    DMAMK2 = 0U; /* enable INTDMA2 interrupt */
    DEN2 = 1U;
    DST2 = 1U;
}

/***********************************************************************************************************************
* Function Name: R_DMAC2_Stop
* Description  : This function disables DMA2 transfer.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_DMAC2_Stop(void)
{
    if (DST2 != 0U)
    {
        DST2 = 0U;
    }
    
    NOP();
    NOP();
    DEN2 = 0U; /* disable DMA2 operation */
    DMAMK2 = 1U; /* disable INTDMA2 interrupt */
    DMAIF2 = 0U; /* clear INTDMA2 interrupt flag */
}

/***********************************************************************************************************************
* Function Name: R_DMAC3_Create
* Description  : This function initializes the DMA3 transfer.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_DMAC3_Create(void)
{
    DRC3 = _80_DMA_OPERATION_ENABLE;
    NOP();
    NOP();
    DMAMK3 = 1U; /* disable INTDMA3 interrupt */
    DMAIF3 = 0U; /* clear INTDMA3 interrupt flag */
    /* Set INTDMA3 level 1 priority */
    DMAPR13 = 0U;
    DMAPR03 = 1U;
    DMC3 = _40_DMA_TRANSFER_DIR_RAM2SFR | _00_DMA_DATA_SIZE_8 | _02_DMA_TRIGGER_TM10;
    DSA3 = _05_DMA3_SFR_ADDRESS;
    DRA3 = _7F00_DMA3_RAM_ADDRESS;
    DBC3 = _0200_DMA3_BYTE_COUNT;
    DEN3 = 0U; /* disable DMA3 operation */
}

/***********************************************************************************************************************
* Function Name: R_DMAC3_Start
* Description  : This function enables DMA3 transfer.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_DMAC3_Start(void)
{
    DMAIF3 = 0U; /* clear INTDMA3 interrupt flag */
    DMAMK3 = 0U; /* enable INTDMA3 interrupt */
    DEN3 = 1U;
    DST3 = 1U;
}

/***********************************************************************************************************************
* Function Name: R_DMAC3_Stop
* Description  : This function disables DMA3 transfer.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_DMAC3_Stop(void)
{
    if (DST3 != 0U)
    {
        DST3 = 0U;
    }
    
    NOP();
    NOP();
    DEN3 = 0U; /* disable DMA3 operation */
    DMAMK3 = 1U; /* disable INTDMA3 interrupt */
    DMAIF3 = 0U; /* clear INTDMA3 interrupt flag */
}

/* Start user code for adding. Do not edit comment generated here */
void DMAC0_Create(void)
{
    DRC0 = _80_DMA_OPERATION_ENABLE;
    NOP();
    NOP();
    DMAMK0 = 1U; /* disable INTDMA0 interrupt */
    DMAIF0 = 0U; /* clear INTDMA0 interrupt flag */
    /* Set INTDMA0 high priority */
    DMAPR10 = 0U;
    DMAPR00 = 0U;
    DMC0 = _40_DMA_TRANSFER_DIR_RAM2SFR | _20_DMA_DATA_SIZE_16 | _02_DMA_TRIGGER_TM00;
    DSA0 = _18_DMA0_SFR_ADDRESS;
    DRA0 = (uint16_t) &timerPeriod[1];
    DBC0 = DIM_STEPS-1; // _0040_DMA0_BYTE_COUNT;
    DEN0 = 0U; /* disable DMA0 operation */
}

void DMAC1_Create(void)
{
    DRC1 = _80_DMA_OPERATION_ENABLE;
    NOP();
    NOP();
    DMAMK1 = 1U; /* disable INTDMA1 interrupt */
    DMAIF1 = 0U; /* clear INTDMA1 interrupt flag */
    /* Set INTDMA1 level 1 priority */
    DMAPR11 = 0U;
    DMAPR01 = 1U;
    DMC1 = _40_DMA_TRANSFER_DIR_RAM2SFR | _00_DMA_DATA_SIZE_8 | _05_DMA_TRIGGER_TM03;
    DSA1 = _01_DMA1_SFR_ADDRESS;
    DRA1 = (uint16_t) &com;
    DBC1 = NUM_COM; // count 8 elements before the com lines repeat the patten _0200_DMA1_BYTE_COUNT;
                // the trigger comes from the timer, 64 times
    DEN1 = 0U; /* disable DMA1 operation */
}

void DMAC2_Create(void)
{
    DRC2 = _80_DMA_OPERATION_ENABLE;
    NOP();
    NOP();
    DMAMK2 = 1U; /* disable INTDMA2 interrupt */
    DMAIF2 = 0U; /* clear INTDMA2 interrupt flag */
    /* Set INTDMA2 level 1 priority */
    DMAPR12 = 0U;
    DMAPR02 = 1U;
    DMC2 = _40_DMA_TRANSFER_DIR_RAM2SFR | _00_DMA_DATA_SIZE_8 | _02_DMA_TRIGGER_TM10;
    DSA2 = _02_DMA2_SFR_ADDRESS;
    DRA2 = (uint16_t) &(ledArray_A.segmentBuffer);
    DBC2 = DIM_STEPS*NUM_COM; // _0200_DMA2_BYTE_COUNT;
    DEN2 = 0U; /* disable DMA2 operation */
}

void DMAC3_Create(void)
{
    DRC3 = _80_DMA_OPERATION_ENABLE;
    NOP();
    NOP();
    DMAMK3 = 1U; /* disable INTDMA3 interrupt */
    DMAIF3 = 0U; /* clear INTDMA3 interrupt flag */
    /* Set INTDMA3 level 1 priority */
    DMAPR13 = 0U;
    DMAPR03 = 1U;
    DMC3 = _40_DMA_TRANSFER_DIR_RAM2SFR | _00_DMA_DATA_SIZE_8 | _02_DMA_TRIGGER_TM10;
    DSA3 = _05_DMA3_SFR_ADDRESS;
    DRA3 = (uint16_t) &(ledArray_B.segmentBuffer);
    DBC3 = DIM_STEPS*NUM_COM; // _0200_DMA3_BYTE_COUNT;
    DEN3 = 0U; /* disable DMA3 operation */
}

/* End user code. Do not edit comment generated here */
