/*******************************************************************************
* Library       : EEPROM Emulation Library (T02)
*
* File Name     : $Source: eel_descriptor.c $
* Lib. Version  : $RL78_EEL_LIB_VERSION_T02: V1.00 $
* Mod. Revision : $Revision: 1.4 $
* Mod. Date     : $Date: 2012/10/25 17:59:28MESZ $
* Device(s)     : RL78
* Description   : contains the user defined EEL-variable descriptor
*******************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only
* intended for use with Renesas products. No other uses are authorized. This
* software is owned by Renesas Electronics Corporation and is protected under
* all applicable laws, including copyright laws.
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT
* LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
* AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.
* TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS
* ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE
* FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR
* ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE
* BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software
* and to discontinue the availability of this software. By using this software,
* you agree to the additional terms and conditions found by accessing the
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2012 Renesas Electronics Corporation. All rights reserved.
*******************************************************************************/



/*==============================================================================================*/
/* compiler settings                                                                            */
/*==============================================================================================*/
#pragma language = extended


/*==============================================================================================*/
/* include files list                                                                           */
/*==============================================================================================*/
#define  __EEL_DESCRIPTOR_C
  #include  "eel_types.h"
  #include  "eel_descriptor.h"
#undef   __EEL_DESCRIPTOR_C

#include  "fdl_types.h"


/* definition of variable types registered at EEL */
#include  "EEL_user_types.h"


/*==============================================================================================*/
/* import list                                                                                  */
/*==============================================================================================*/
/* empty */


/*==============================================================================================*/
/* data definition                                                                              */
/*==============================================================================================*/
/* empty */


  
/*********************************************************************************************************/
/*******                                                                                           *******/
/*******      B E G I N    O F    C U S T O M I Z A B L E    D E C L A R A T I O N    A R E A      *******/
/*******                                                                                           *******/
/*********************************************************************************************************/

#pragma location="EEL_CNST"
#pragma data_alignment=2

__far const eel_u08 eel_descriptor[EEL_VAR_NO+2] =
{
  (eel_u08)(EEL_VAR_NO),      /* variable count   */  \
  (eel_u08)(sizeof(type_A)),  /* id=1             */  \
  (eel_u08)(sizeof(type_B)),  /* id=2             */  \
  (eel_u08)(sizeof(type_C)),  /* id=3             */  \
  (eel_u08)(sizeof(type_D)),  /* id=4             */  \
  (eel_u08)(sizeof(type_E)),  /* id=5             */  \
  (eel_u08)(sizeof(type_F)),  /* id=6             */  \
  (eel_u08)(sizeof(type_X)),  /* id=7             */  \
  (eel_u08)(sizeof(type_Z)),  /* id=8             */  \
  (eel_u08)(0x00),            /* zero terminator  */  \
};

/*********************************************************************************************************/
/*******                                                                                           *******/
/*******      E N D    O F    C U S T O M I Z A B L E    D E C L A R A T I O N    A R E A          *******/
/*******                                                                                           *******/
/*********************************************************************************************************/




/*********************************************************************************************************/
/*******                                                                                           *******/
/*******      B E G I N    O F    U N T O U C H A B L E     D E C L A R A T I O N    A R E A       *******/
/*******                                                                                           *******/
/*********************************************************************************************************/

#pragma location="EEL_CNST"
#pragma data_alignment=2

__far const eel_u08   eel_internal_cfg_cau08[]     = {0x40};

/*********************************************************************************************************/
/*******                                                                                           *******/
/*******      E N D    O F    U N T O U C H A B L E     D E C L A R A T I O N    A R E A           *******/
/*******                                                                                           *******/
/*********************************************************************************************************/

