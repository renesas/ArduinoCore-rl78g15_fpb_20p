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
* File Name    : r_smc_entry.h
* Version      : 1.0.0
* Device(s)    : R5F12068xSP
* Description  : SMC platform header file..
* Creation Date: 
***********************************************************************************************************************/

#ifndef SMC_ENTRY_H
#define SMC_ENTRY_H

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "Config_UART0.h"
#include "r_cg_it_common.h"
#include "r_cg_macrodriver.h"
#include "r_cg_sau_common.h"
#include "r_cg_userdefine.h"
#include "Config_INTC.h"

/***********************************************************************************************************************
Macro definitions (Register bit)
***********************************************************************************************************************/

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Global functions
***********************************************************************************************************************/
/* Start user code for function. Do not edit comment generated here */
#include "Config_TAU0_1_Square_Wave.h"
#include "Config_TAU0_2_Square_Wave.h"
#include "Config_TAU0_3_Square_Wave.h"
#include "Config_TAU0_0_Measure_Signal.h"
#include "Config_TAU0_3_Measure_Signal.h"
#include "Config_TAU0_6_Micros.h"
#include "Config_TAU0_2.h"
#include "Config_TAU0_25PWM.h"
#include "Config_ADC.h"
/* End user code. Do not edit comment generated here */
#endif

