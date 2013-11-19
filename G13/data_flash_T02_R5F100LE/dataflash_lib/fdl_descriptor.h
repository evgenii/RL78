/*******************************************************************************
* Library       : Data Flash Access Library T02
*
* File Name     : $Source: fdl_descriptor.h $
* Lib. Version  : $RL78_FDL_LIB_VERSION_T02_IAR: V1.01 $
* Mod. Revision : $Revision: 1.11 $
* Mod. Date     : $Date: 2013/06/25 15:44:23MESZ $
* Device(s)     : RL78
* Description   : User specific library configuration parameters
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
* Copyright (C) 2011-2013 Renesas Electronics Corporation. All rights reserved.
*******************************************************************************/



#ifndef __FDL_DESCRIPTOR_H_INCLUDED
#define __FDL_DESCRIPTOR_H_INCLUDED

#include "fdl_types.h"

/* specify the CPU frequency in [Hz]                                                              */
#define   FDL_SYSTEM_FREQUENCY      32000000

/* programming voltage mode                                                                       */
/* #define   FDL_WIDE_VOLTAGE_MODE  */

/* specify the size of the FDL pool expressed in number of blocks                                 */
#define   FDL_POOL_BLOCKS               2

/* specify the size of the EEL pool inside the FDL pool expressed in blocks (min. value is 2)     */
#define   EEL_POOL_BLOCKS               2

/* external reference to descriptor */
extern    __far const fdl_descriptor_t  fdl_descriptor_str;

#endif
