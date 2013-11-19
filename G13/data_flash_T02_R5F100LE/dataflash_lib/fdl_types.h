/*******************************************************************************
* Library       : Data Flash Access Library T02
*
* File Name     : $Source: fdl_types.h $
* Lib. Version  : $RL78_FDL_LIB_VERSION_T02_IAR: V1.01 $
* Mod. Revision : $Revision: 1.16 $
* Mod. Date     : $Date: 2013/06/25 15:44:26MESZ $
* Device(s)     : RL78
* Description   : Type definitions used by the library
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


#ifndef __FDL_TYPES_H_INCLUDED
#define __FDL_TYPES_H_INCLUDED


/*==============================================================================================*/
/* unsigned type definitions                                                                    */
/*==============================================================================================*/
typedef unsigned char                       fdl_u08;
typedef unsigned int                        fdl_u16;
typedef unsigned long int                   fdl_u32;


/*==============================================================================================*/
/* global constant definitions                                                                  */
/*==============================================================================================*/



/*==============================================================================================*/
/* global type definitions                                                                      */
/*==============================================================================================*/


/* FDL command code set */
typedef enum
{                                                         /* ---------------------------------------------- */
            FDL_CMD_READ_BYTES          = (0x00),         /* 0x00, reads data from flash memory             */
            FDL_CMD_IVERIFY_BYTES       = (0x01),         /* 0x01, verifies data if flash content is stable */
            FDL_CMD_BLANKCHECK_BYTES    = (0x02),         /* 0x02, checks if flash content is blank         */
            FDL_CMD_WRITE_BYTES         = (0x03),         /* 0x03, writes data into flash memory            */
            FDL_CMD_ERASE_BLOCK         = (0x04)          /* 0x04, erases one flash block                   */
} fdl_command_t;                                          /* ---------------------------------------------- */



/* FDL error code set */
typedef enum
{
            /* operation related status               */  /* ---------------------------------------------- */
            FDL_OK                      = (0x00),         /* 0x00, command finished without problems        */
            FDL_BUSY                    = (0xFF),         /* 0xFF, command is being processed               */
            FDL_ERR_INITIALIZATION      = (0x02),         /* 0x02, FDL_Init()/FDL_Open() missing            */
            FDL_ERR_REJECTED            = (0x03),         /* 0x03, request could not be accepted            */
            FDL_ERR_ABORTED             = (0x04),         /* 0x04, block oriented command has been aborted  */
            FDL_ERR_PARAMETER           = (0x05),         /* 0x05, parameter error                          */
            FDL_ERR_STANDBY             = (0x06),         /* 0x06, FDL_WakeUp missing                       */
            /* flash access related status            */  /* ---------------------------------------------- */
            FDL_ERR_ERASE               = (0x1A),         /* 0x1A, erase error                              */
            FDL_ERR_BLANK_VERIFY        = (0x1B),         /* 0x1B, blank(MRG12)-, verify(MRG01/MRG12)-error */
            FDL_ERR_WRITE               = (0x1C),         /* 0x1C, write error                              */
            /* configuration error related status     */  /* ---------------------------------------------- */
            FDL_ERR_CONFIGURATION       = (0x01)          /* 0x01, pool or frequency configuration wrong    */
} fdl_status_t;                                           /* ---------------------------------------------- */


/* FDL request type (base type for any FDL access) */
typedef struct
{                                                         /* ---------------------------------------------- */
            fdl_u16         index_u16;                    /* 2, W, virt. byte/block index inside FDL-pool   */
    __near  fdl_u08*        data_pu08;                    /* 2, W, pointer to the 1'st byte of data buffer  */
            fdl_u16         bytecount_u16;                /* 2, W, number of bytes to be transferred        */
            fdl_command_t   command_enu;                  /* 1, W, command code                             */
            fdl_status_t    status_enu;                   /* 1, R, status code                              */
} fdl_request_t;                                          /*------------------------------------------------*/
                                                          /* 8 bytes in total                               */
                                                          /*------------------------------------------------*/


/* FDL descriptor type */
typedef struct
{                                                         /* ---------------------------------------------- */
            fdl_u16         eel_pool_bytes_u16;           /* 2, EEL-pool, size expressed in bytes           */
            fdl_u16         fdl_pool_bytes_u16;           /* 2, FDL-pool, size expressed in bytes           */
            fdl_u16         fdl_delay_u16;                /* 2, delay based on configured frequency         */
            fdl_u08         eel_pool_blocks_u08;          /* 1, EEL-pool, size expressed in blocks          */
            fdl_u08         fdl_pool_blocks_u08;          /* 1, FDL-pool, size expressed in blocks          */
            fdl_u08         fx_MHz_u08;                   /* 1, system frequency expressed in MHz           */
            fdl_u08         wide_voltage_mode_u08;        /* 1, programming voltage mode ( full/wide )      */
} fdl_descriptor_t;                                       /*------------------------------------------------*/
                                                          /* 10 bytes in total                              */


/*==============================================================================================*/
/* type definition plausibility check                                                           */
/*==============================================================================================*/

/* The following checks are implemented in order to check the correct size of the FDL type      */
/* definitions at compile time. In case of a compilation error in the following lines, please   */
/* check your compiler options for enumeration types and structures and contact your local      */
/* support, if necessary.                                                                       */

#define R_FDLT02_ASSERT_CONCAT_(a, b) a##b
#define R_FDLT02_ASSERT_CONCAT(a, b) R_FDLT02_ASSERT_CONCAT_(a, b)
#define R_FDLT02_STATIC_ASSERT(e) enum { R_FDLT02_ASSERT_CONCAT(R_FDLT02_ASSERT_LINE_, __LINE__) = 1/(!!(e)) }


/* assertion if unsigned data type size is not correct, please evaluate compiler settings for integer types */
R_FDLT02_STATIC_ASSERT(sizeof(fdl_u08)==1);
R_FDLT02_STATIC_ASSERT(sizeof(fdl_u16)==2);
R_FDLT02_STATIC_ASSERT(sizeof(fdl_u32)==4);

/* assertion if enumeration type size is not correct, please evaluate compiler settings for enumeration types */
R_FDLT02_STATIC_ASSERT(sizeof(fdl_command_t)==1);
R_FDLT02_STATIC_ASSERT(sizeof(fdl_status_t)==1);

/* assertion if structure type size is not correct, please evaluate compiler settings for structure types */
R_FDLT02_STATIC_ASSERT(sizeof(fdl_request_t)==8);
R_FDLT02_STATIC_ASSERT(sizeof(fdl_descriptor_t)==10);



#endif
