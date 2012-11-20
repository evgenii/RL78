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
* Creation Date: 16.11.2012
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_cgc.h"
#include "r_cg_port.h"
#include "r_cg_intc.h"
#include "r_cg_serial.h"
#include "r_cg_timer.h"
#include "r_cg_it.h"
#include "r_cg_dtc.h"
/* Start user code for include. Do not edit comment generated here */
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

/* alignment is mandatory for the DMA repeat mode */
#pragma data_alignment = 256
uint8_t commandBuffer[BURST_SIZE];

/* alignment to 256 bytes is important for the DMA repeat mode */
#pragma data_alignment = 256
uint8_t addressBuffer[BURST_SIZE];

#pragma data_alignment = 256
uint8_t slaveResponse_L[BURST_SIZE];

#pragma data_alignment = 256
uint8_t slaveResponse_H[BURST_SIZE+1];


/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: main
* Description  : This function implements main function.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void main(void)
{
    /* Start user code. Do not edit comment generated here */

#if(RPB_BOARD == 1) 

	/* run the demo on the RPBRL78G14 promotion board
	*
	* layout: 
	* CS: 	P17 - TRDIOA0
	* MISO: P14 - SI20
	* MOSI: P13 - SO20
	* CLK:	P15 - SCK20
	*
	* serial unit 1 - channel 0 (S20) is used 
	* timer RD0 is used to activate the dma transfers
	* 
	* CSI_Init() gets called once at the beginning
	*
	* CSI_Send() is called to start the transmission. In the demo is called every 
	* 10 msec from the repetitive interrupt timer
    *
    * In the demo for the RPB board, the data is sent from the serial output SO20
    * and looped back into SI20 via an external wire. This for the purpose to test
    * if the communication is successful.
    *
    * The led keeps blinking every second, in case of errors the led blink stops.
    *
    * Switches S1 & S2 are used to trigger interrupt routines which set or clear the
    * led (just for the sake of having some interrupts in between). 
	*
	* commandBuffer contents are sent within the first byte of the master transmitted word
	* addressBuffer holds the remaining byte of the master word
	*
    * command (8 bit) + address (8 bit) form a 16 bit frame
	*
	* after every frame, the chip select signal is toggled
	*
	* one full burst holds BURST_SIZE frames, configurable in r_cg_userdefine.h 
	* 
	* The slave response is divided into two buffers, slaveResponse_L and
	* slaveResponse_H, which are received in this order
	* 
	* Note: the value in slaveResponse_H[0] is not valid for the
	* last received burst, the valid BURST_SIZE values are stored in the range
	* slaveResponse_H[1]...slaveResponse_H[BURST_SIZE]. 
	*
    * the timer values are calculated for the following match timings:
	* B0: 2  usec
	* D0: 12 usec
	* A0: 22 usec
	* C0: 24 usec
    *
	* Timer pin output A0 is used to generate the (active low) chip select
	* waveform. The timer is started via the cpu at the beginning of the transmission
    *
    * The DCT configuration uses two channels, each of them is configured in chain mode
    * Channel 0 is linked to the timer B0 match event, and linked with channel 1
    * Channel 2 is linked to the timer D0 match event, and linked with channel 3
    * For each timer event, the DCT performs one read operation from the serial line
    * register, chained with a write to the same register.
    * In this way the previously received data is saved to the receive buffer, and the 
    * next command / address is sent.
    * 
    * Since channel 0 transfers the data related to the first half of each frame, 
    * at the beginning of the last frame its job is finished and an end of transfer 
    * interrupt is issued to the cpu. Within this interrupt routine, the RD timer is 
    * configured to automatically stop and generate an interrupt in occurrence of 
    * the next A0 match, which in this case happens at the end of the last transferred 
    * frame, i.e. at the end of the whole burst transfer.
    *
    * This interrupt is very important to make sure the timer stops, so it is 
    * issued by a dedicated dma channel which fires at the beginning of the 
    * last frame. This should ensure that the interrupt routine has a sufficient
    * time margin to set the timer to stop mode before the last frame finishes      
	*/
	
	/* run the main application */
	demoRpbRl78();

#endif

    /* otherwise */
    while(1);
    
    /* End user code. Do not edit comment generated here */
}




/* Start user code for adding. Do not edit comment generated here */

void CSI_Init(void)
{		
	
		/* activate the dma channels */
		R_DTCD0_Start();	
		R_DTCD2_Start();
		
		/* activate the serial line
		 * nothing happens yet, is triggered by the first write
		*/ 
		R_CSI20_Start_noInt();
}

	
void CSI_Send(void)
{
		TRDSR0 = 0U;
		
		/* (re)activate the dma channels */
		R_DTCD0_Start();	
		R_DTCD2_Start();
		
		/* 'force' output to low for the timer output match A
		 * Defines the chip select start, active low
		 * Then start the timer
		*/
		TRDOCR &= ~_01_TMRD_TRDIOA0_INITIAL_OUTPUT_H;
		R_TMR_RD0_Start();
	
}

#if(RPB_BOARD == 1)

/* compare the received contents with the items sent */
void checkBuffer(void) {

	unsigned int i;

	for(i=0;i<BURST_SIZE;i++) {
		if(slaveResponse_L[i] != commandBuffer[i]) error = 1;
		if(slaveResponse_H[i+1] != addressBuffer[i]) error = 1;
	}
}

/* prepare the buffers with a known pattern */
void prepareBuffer(void) {

		unsigned int i;
	
		for(i=0;i<BURST_SIZE;i++) {
			commandBuffer[i] = (i+1)*2;
			addressBuffer[i] = (i+1)*2 + 1;
			slaveResponse_L[i] = 0;
			slaveResponse_H[i] = 0;
		}
		slaveResponse_H[BURST_SIZE] = 0;	
}

/*
 * This is the main demo program
*/
void demoRpbRl78(void) {

		volatile uint16_t numBursts = 0;

		/*
		 * Connect internal pull-ups on switch pins P3_1 and P7_6 
		 * as there is no external pullup and switch goes to gnd
		 * just needed for the user switches on the RPB board
		*/
		PU3_bit.no1 = 1U;
		PU7_bit.no6 = 1U;
		P7_bit.no7 = 1;
		
		/* just for fun, for having some user interrupts in between */
		R_INTC4_Start();
		R_INTC10_Start();		

		/* call this first */
		CSI_Init();		

		/* start the 10 msec timer */
		R_IT_Start();

		while (1U)
    {

			if(burstDone) {
		
				/* count the bursts... */
				numBursts++;

				/* check the received contents */
				checkBuffer();
				
				/* process the data, here we just clear the buffer if successful */
				/* keep the received one in case there was an error, for inspection */
				if(error == 0) {
					
					/* clear the buffer */
					prepareBuffer();
				
					/* reset flag */
					burstDone = 0;				
					
				};
			};

			/* just some led toggling on the RPB board */
			if(sw1_keyPressed) {
				sw1_keyPressed = 0;
				P7_bit.no7 = 1u; /* clear led */
				R_INTC10_Start();
			};

			if(sw2_keyPressed) {
				sw2_keyPressed = 0;
				P7_bit.no7 = 0; /* set led */
				R_INTC4_Start();
			};

			
    };	
}

#endif

/* End user code. Do not edit comment generated here */
