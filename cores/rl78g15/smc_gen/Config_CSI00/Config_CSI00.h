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
* File Name    : Config_CSI00.h
* Version      : 1.1.0
* Device(s)    : R5F12068xSP
* Description  : This file implements device driver for Config_CSI00.
* Creation Date: 
***********************************************************************************************************************/

#ifndef CFG_Config_CSI00_H
#define CFG_Config_CSI00_H

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_sau.h"

/***********************************************************************************************************************
Macro definitions (Register bit)
***********************************************************************************************************************/

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
#define _0600_SAU0_CH0_BAUDRATE_DIVISOR    (0x0600U)    /* transfer clock set by dividing the operating clock */

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Global functions
***********************************************************************************************************************/
void R_Config_CSI00_Create (void);
void R_Config_CSI00_Start (void);
void R_Config_CSI00_Stop (void);
MD_STATUS R_Config_CSI00_Send_Receive (uint8_t * const tx_buf, uint16_t tx_num, uint8_t * const rx_buf);
void R_Config_CSI00_Create_UserInit (void);
/* Start user code for function. Do not edit comment generated here */
void R_Config_CSI00_ClearStatus(void);
uint8_t R_Config_CSI00_GetBitOrder(void);
void R_Config_CSI00_SetBitOrder(uint8_t bitOrder);
void R_Config_CSI00_SetDataMode(uint8_t dataMode);
void R_Config_CSI00_SetClockDivider(uint16_t clockDiv);
void R_Config_CSI00_SetClock(uint32_t clock);
static void r_Config_CSI00_callback_receiveend(void);
static void r_Config_CSI00_callback_error(uint8_t err_type);
void r_Config_CSI00_interrupt(void);

/* End user code. Do not edit comment generated here */
#endif
