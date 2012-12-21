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
* File Name    : r_cg_timer_user.c
* Version      : Applilet3 for RL78/G14 V1.01.01 [11 Oct 2011]
* Device(s)    : R5F104LE
* Tool-Chain   : IAR Systems iccrl78
* Description  : This file implements device driver for TAU module.
* Creation Date: 16.11.2012
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_timer.h"
/* Start user code for include. Do not edit comment generated here */
#include "r_cg_dtc.h"
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
volatile uint8_t burstDone = 0;

#pragma inline = forced
static void stopTimerSync(void);

extern uint8_t slaveResponse_H[];
extern uint8_t commandBuffer[];

/* set this to watch interrupt timing on the last frame */
#define DEBUG_RPB_BOARD 0

/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: r_tmr_rd0_interrupt
* Description  : This function is INTTRD0 interrupt service routine.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
#pragma vector = INTTRD0_vect
__interrupt static void r_tmr_rd0_interrupt(void)
{
    /* Start user code. Do not edit comment generated here */
		
		/* interrupt from match B - DMA transfer 1 finished
		 *
		*/
		if(TRDSR0 & 0x02) {
			
			/* clear bit for match flag B !! and flag A !!
			 * flag A is going to be activated in the last step below
			*/
			TRDSR0 = 0xFC;
			
#if((RPB_BOARD == 1) && (DEBUG_RPB_BOARD == 1))
			/* for debug */
			P7_bit.no7 = 0;
#endif
			
			/* we are in middle of last frame, need to stop timer at next RD0 A0 match */
			/* when the last frame is done */
			stopTimerSync();

			/* enable TMRD0 interrupt also for the last A0 match */
			TRDIER0_bit.no0 = 1U;
	    
		};
		
		/* interrupt from match A - end of frame interrupt - finished */
		if(TRDSR0 & 0x01) {
			
#if((RPB_BOARD == 1) && (DEBUG_RPB_BOARD == 1))
			/* for debug */
			P7_bit.no7 = 0;
#endif
			
			/* timer is now stopped */
			/* read out the very last byte received */
			slaveResponse_H[BURST_SIZE] = SIO20;
						
			/* eventually restore here the configuration for the timer */
			TRDSTR = 0xC;
			TRDOCR = 0x1;
			TRD0 = 0; 
			TRDSR0 = 0;

	        TRDIER0 = _00_TMRD_IMIA_DISABLE | _02_TMRD_IMIB_ENABLE | _00_TMRD_IMIC_DISABLE | _08_TMRD_IMID_ENABLE |
              _00_TMRD_OVIE_DISABLE;
		
			/* update the tx flag */
			burstDone = 1;
		};
		
		/* End user code. Do not edit comment generated here */
}

/* Start user code for adding. Do not edit comment generated here */
#pragma inline = forced
static void stopTimerSync(void) {
	
	/* stop the timer at the next MRA match */
	TRDSTR &= ~_04_TMRD_TRD0_COUNT_CONTINUES;

}
/* End user code. Do not edit comment generated here */
