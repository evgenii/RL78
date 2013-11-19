/*******************************************************************************
* Library       : EEPROM Emulation Library (T02)
*
* File Name     : $Source: eel_user_types.h $
* Lib. Version  : $RL78_EEL_LIB_VERSION_T02: V1.00 $
* Mod. Revision : $Revision: 1.3 $
* Mod. Date     : $Date: 2012/10/25 17:59:29MESZ $
* Device(s)     : RL78
* Description   : user configurable types
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


#ifndef __EEL_USER_TYPES_H_INCLUDED
#define __EEL_USER_TYPES_H_INCLUDED

/* include files list   */
/* -------------------  */
#include "eel_types.h"

/* type definitions     */
/* ----------------     */
typedef   eel_u08   type_A[2];
typedef   eel_u08   type_B[3];
typedef   eel_u08   type_C[4];
typedef   eel_u08   type_D[5];
typedef   eel_u08   type_E[6];
typedef   eel_u08   type_F[10];
typedef   eel_u08   type_X[20];
typedef   eel_u08   type_Z[255];


#endif
