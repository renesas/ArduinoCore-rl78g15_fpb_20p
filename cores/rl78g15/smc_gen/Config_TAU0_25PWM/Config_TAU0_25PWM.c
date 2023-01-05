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
* File Name    : Config_TAU0_2.c
* Version      : 1.1.0
* Device(s)    : R5F12068xSP
* Description  : This file implements device driver for Config_TAU0_2.
* Creation Date: 
***********************************************************************************************************************/

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "Config_TAU0_25PWM.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_Config_TAU0_2_Create
* Description  : This function initializes the TAU0 channel2 module.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_TAU0_25PWM_Create(void)
{
    TPS0 &= _FFF0_TAU_CKM0_CLEAR;
    TPS0 |= _0001_TAU_CKM0_FCLK_1;
    TT0 |= (_0020_TAU_CH5_STOP_TRG_ON | _0004_TAU_CH2_STOP_TRG_ON);
    TMMK02 = 1U;    /* disable INTTM02 interrupt */
    TMIF02 = 0U;    /* clear INTTM02 interrupt flag */
    TMMK05 = 1U;    /* disable INTTM05 interrupt */
    TMIF05 = 0U;    /* clear INTTM05 interrupt flag */
    /* Channel 2 is used as master channel for PWM output function */
    TMR02 = _0000_TAU_CLOCK_SELECT_CKM0 | _0000_TAU_CLOCK_MODE_CKS | _0800_TAU_COMBINATION_MASTER | 
            _0000_TAU_TRIGGER_SOFTWARE | _0001_TAU_MODE_PWM_MASTER;
//    TDR02 = _18FF_TAU_TDR02_VALUE;
    TDR02 = 0x7cff;

    TOM0 &= (uint16_t)~_0004_TAU_CH2_SLAVE_OUTPUT;
    TOL0 &= (uint16_t)~_0004_TAU_CH2_OUTPUT_LEVEL_L;
    TO0 &= (uint16_t)~_0004_TAU_CH2_OUTPUT_VALUE_1;
    TOE0 &= (uint16_t)~_0004_TAU_CH2_OUTPUT_ENABLE;
    /* Channel 5 is used as slave channel for PWM output function */
    TMR05 = _0000_TAU_CLOCK_SELECT_CKM0 | _0000_TAU_CLOCK_MODE_CKS | _0000_TAU_COMBINATION_SLAVE | 
            _0400_TAU_TRIGGER_MASTER_INT | _0009_TAU_MODE_PWM_SLAVE;
    TDR05 = _0C80_TAU_TDR05_VALUE;
    TOM0 |= _0020_TAU_CH5_SLAVE_OUTPUT;
    TOL0 &= (uint16_t)~_0020_TAU_CH5_OUTPUT_LEVEL_L;
    TO0 &= (uint16_t)~_0020_TAU_CH5_OUTPUT_VALUE_1;
    TOE0 |= _0020_TAU_CH5_OUTPUT_ENABLE;
    /* Set TO05 pin */
    P12 &= 0xFBU;
    PM12 &= 0xFBU;

    R_Config_TAU0_25PWM_Create_UserInit();
}

/***********************************************************************************************************************
* Function Name: R_Config_TAU0_2_Start
* Description  : This function starts the TAU0 channel2 counter.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_TAU0_25PWM_Start(void)
{
    TOE0 |= _0020_TAU_CH5_OUTPUT_ENABLE;
    TS0 |= (_0020_TAU_CH5_START_TRG_ON | _0004_TAU_CH2_START_TRG_ON);
}

/***********************************************************************************************************************
* Function Name: R_Config_TAU0_2_Stop
* Description  : This function stops the TAU0 channel2 counter.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_TAU0_25PWM_Stop(void)
{
    TT0 |= (_0020_TAU_CH5_STOP_TRG_ON | _0004_TAU_CH2_STOP_TRG_ON);
    TOE0 &= (uint16_t)~_0020_TAU_CH5_OUTPUT_ENABLE;
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

