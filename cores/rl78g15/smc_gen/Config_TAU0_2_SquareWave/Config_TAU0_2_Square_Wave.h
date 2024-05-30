/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products.
* No other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
* applicable laws, including copyright laws. 
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED
* OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY
* LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE FOR ANY DIRECT,
* INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR
* ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability 
* of this software. By using this software, you agree to the additional terms and conditions found by accessing the 
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2020 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name    : Config_TAU0_2.h
* Version      : 1.1.0
* Device(s)    : R5F12068xSP
* Description  : This file implements device driver for Config_TAU0_2.
* Creation Date: 
***********************************************************************************************************************/

#ifndef Config_TAU0_2_H
#define Config_TAU0_2_H

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_tau.h"

/***********************************************************************************************************************
Macro definitions (Register bit)
***********************************************************************************************************************/

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
#define _063F_TAU_TDR02_VALUE               (0x063FU)    /* 16-bit timer data register 02 (TDR02) */

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Global functions
***********************************************************************************************************************/
void R_Config_TAU0_2_Square_Wave_Create (void);
void R_Config_TAU0_2_Square_Wave_Start (void);
void R_Config_TAU0_2_Square_Wave_Stop (void);
void R_Config_TAU0_2_Square_Wave_Create_UserInit (void);
/* Start user code for function. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#endif
