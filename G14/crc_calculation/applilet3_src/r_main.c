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
* Version      : Applilet3 for RL78/G14 V2.00.00.08 [12 Apr 2013]
* Device(s)    : R5F104LE
* Tool-Chain   : IAR Systems iccrl78
* Description  : This file implements main function.
* Creation Date: 29.07.2013
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
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */

/******************************************************************************
Typedef definitions
******************************************************************************/

/******************************************************************************
Private global variables and functions
******************************************************************************/

/* End user code. Do not edit comment generated here */

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
	
    uint16_t	result_hs_crc;		/* Program result.(High-Speed) */
	uint16_t	__far *oc_calc_hs_crc;	/* Pointer of OC result.(High-Speed) */
	uint16_t	count;

    
    P6_bit.no3 = 0;
    
    /* High-speed CRC */
	    
    /* Get High-speed CRC calculated result that OC output. */
	oc_calc_hs_crc = (uint16_t __far*)HIGHSPEED_CALC_ADDR;

	result_hs_crc = my_HighSpeedCRCProc();

	/* The results are compared and it outputs it to LED. */
	if (result_hs_crc == *oc_calc_hs_crc)	/* High-speed CRC. */
	{
		P6_bit.no3 = 0;							/* OK = LED Lighting. */
	}
	else
	{
		P6_bit.no3 = 1;							/* NG = LED Turning off. */
	}

    // toggle the second led
    while (1U)
    {

        P6_bit.no2 = 0;
        for( count=0; count<65000; count++ );
        for( count=0; count<65000; count++ );
        P6_bit.no2 = 1;
        for( count=0; count<65000; count++ );
        for( count=0; count<65000; count++ );

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

void (__far_func *fct_ptr)(void);

__root uint8_t	crc_opcode[2+1+10] = {
  
    0x61,		/* HALT(high) */
	0xed,		/* HALT(low) */
	0xD7,		/* RET */
	0x00,		/* NOP */
	0x00,		/* NOP */
	0x00,		/* NOP */
	0x00,		/* NOP */
	0x00,		/* NOP */
	0x00,		/* NOP */
	0x00,		/* NOP */
	0x00,	    /* NOP */
	0x00,	    /* NOP */
	0x00	    /* NOP */
      
};

uint16_t my_HighSpeedCRCProc(void)
{
	uint16_t	result;

	/* Set mask for all interrupt. */
	MK0 = 0xFFFF;
	MK1 = 0xFFFF;
	MK2 = 0xFFFF;

	R_CGC_Set_CRCOn();			/* Enable CRC ALU. */

	PGCRCL = 0;					/* Initialization of result register. */

    
    	/* Execute background CRC calulation by HALT executed from RAM */
    fct_ptr = (void (__far_func*)(void)) &crc_opcode[0];  /* initialize pointer */
    (*fct_ptr)();                                            /* execute HALT */    

	__no_operation();       
    __no_operation();                 /* Wake up delay */
    
    CRC0EN = 0;					/* Disable CRC ALU. */
    result = PGCRCL;			/* Save result. */

	return  result;
}









/* End user code. Do not edit comment generated here */
