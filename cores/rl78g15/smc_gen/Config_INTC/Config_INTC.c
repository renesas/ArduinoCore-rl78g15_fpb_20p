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
* File Name    : Config_INTC.c
* Version      : 1.1.0
* Device(s)    : R5F12068xSP
* Description  : This file implements device driver for Config_INTC.
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
#include "Config_INTC.h"
/* Start user code for include. Do not edit comment generated here */
#include "wiring_variant.h"
#include "wiring_private.h"
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
typedef struct {
    uint8_t intNum;
    uint8_t pinNum;
    int modeNum;
} Num;
Num value;
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_Config_INTC_Create
* Description  : This function initializes the INTC module.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_INTC_Create(void)
{
    PMK0 = 1U;    /* disable INTP0 operation */
    PIF0 = 0U;    /* clear INTP0 interrupt flag */
    PMK3 = 1U;    /* disable INTP3 operation */
    PIF3 = 0U;    /* clear INTP3 interrupt flag */
    PMK4 = 1U;    /* disable INTP4 operation */
    PIF4 = 0U;    /* clear INTP4 interrupt flag */
    /* Set INTP0 low priority */
    PPR10 = 1U;
    PPR00 = 1U;
    /* Set INTP3 low priority */
    PPR13 = 1U;
    PPR03 = 1U;
    /* Set INTP4 low priority */
    PPR14 = 1U;
    PPR04 = 1U;

    R_Config_INTC_Create_UserInit();
}

/***********************************************************************************************************************
* Function Name: R_Config_INTC_INTP0_Start
* Description  : This function clears INTP0 interrupt flag and enables interrupt.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_INTC_INTP0_Start(void)
{
    PIF0 = 0U;    /* clear INTP0 interrupt flag */
    PMK0 = 0U;    /* enable INTP0 interrupt */
}

/***********************************************************************************************************************
* Function Name: R_Config_INTC_INTP0_Stop
* Description  : This function disables INTP0 interrupt and clears interrupt flag.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_INTC_INTP0_Stop(void)
{
    PMK0 = 1U;    /* disable INTP0 interrupt */
    PIF0 = 0U;    /* clear INTP0 interrupt flag */
}

/***********************************************************************************************************************
* Function Name: R_Config_INTC_INTP3_Start
* Description  : This function clears INTP3 interrupt flag and enables interrupt.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_INTC_INTP3_Start(void)
{
    PIF3 = 0U;    /* clear INTP3 interrupt flag */
    PMK3 = 0U;    /* enable INTP3 interrupt */
}

/***********************************************************************************************************************
* Function Name: R_Config_INTC_INTP3_Stop
* Description  : This function disables INTP3 interrupt and clears interrupt flag.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_INTC_INTP3_Stop(void)
{
    PMK3 = 1U;    /* disable INTP3 interrupt */
    PIF3 = 0U;    /* clear INTP3 interrupt flag */
}


/***********************************************************************************************************************
* Function Name: R_Config_INTC_INTP4_Start
* Description  : This function clears INTP2 interrupt flag and enables interrupt.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_INTC_INTP4_Start(void)
{
    PIF4 = 0U;    /* clear INTP4 interrupt flag */
    PMK4 = 0U;    /* enable INTP4 interrupt */
}

/***********************************************************************************************************************
* Function Name: R_Config_INTC_INTP4_Stop
* Description  : This function disables INTP2 interrupt and clears interrupt flag.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_INTC_INTP4_Stop(void)
{
    PMK4 = 1U;    /* disable INTP2 interrupt */
    PIF4 = 0U;    /* clear INTP2 interrupt flag */
}

/* Start user code for adding. Do not edit comment generated here */
void R_Config_INTC_Create_Mode(uint8_t interruptNum, int mode)
{
    switch (interruptNum) {
    case 0:  // INTP3
        value.intNum = interruptNum;
        value.pinNum = EXTERNAL_INTERRUPT_0;
        value.modeNum = mode;
        if (value.modeNum == FALLING) {
            EGN0_bit.no3 = 1U;
            EGP0_bit.no3 = 0U;
        }
        else if (value.modeNum == RISING) {
            EGN0_bit.no3 = 0U;
            EGP0_bit.no3 = 1U;
        }
        else if (value.modeNum == CHANGE){
            EGN0_bit.no3 = 1U;
            EGP0_bit.no3 = 1U;
        }
        else{
            EGN0_bit.no3 = 0U;
            EGP0_bit.no3 = 0U;
        }
        break;
    case 1:  // INTP0
        value.intNum = interruptNum;
        value.pinNum = EXTERNAL_INTERRUPT_1;
        value.modeNum = mode;
        if (value.modeNum == FALLING) {
            EGN0_bit.no0 = 1U;
            EGP0_bit.no0 = 0U;
        }
        else if (value.modeNum == RISING) {
            EGN0_bit.no0 = 0U;
            EGP0_bit.no0 = 1U;
        }
        else if (value.modeNum == CHANGE){
            EGN0_bit.no0 = 1U;
            EGP0_bit.no0 = 1U;
        }
        else{
            EGN0_bit.no0 = 0U;
            EGP0_bit.no0 = 0U;
        }
        break;
    case 2:  // INTP4
        value.intNum = interruptNum;
        value.pinNum = EXTERNAL_INTERRUPT_2;
        value.modeNum = mode;
        if (value.modeNum == FALLING) {
            EGN0_bit.no4 = 1U;
            EGP0_bit.no4 = 0U;
        }
        else if (value.modeNum == RISING) {
            EGN0_bit.no4 = 0U;
            EGP0_bit.no4 = 1U;
        }
        else if (value.modeNum == CHANGE){
            EGN0_bit.no4 = 1U;
            EGP0_bit.no4 = 1U;
        }
        else{
            EGN0_bit.no4 = 0U;
            EGP0_bit.no4 = 0U;
        }
        break;
    }
}

void R_Config_INTC_INTP_Start(void){
    if(value.pinNum == EXTERNAL_INTERRUPT_0){
        R_Config_INTC_INTP3_Start();
    }
    else if (value.pinNum == EXTERNAL_INTERRUPT_1){
        R_Config_INTC_INTP0_Start();
    }
    else if (value.pinNum == EXTERNAL_INTERRUPT_2){
        R_Config_INTC_INTP4_Start();
    }
}

void R_Config_INTC_INTP_Stop(uint8_t interruptNum){
    switch (interruptNum) {
        case 0:
            R_Config_INTC_INTP3_Stop();
            break;
        case 1:
            R_Config_INTC_INTP0_Stop();
            break;
        case 2:
            R_Config_INTC_INTP4_Stop();
            break;

    }
}

/* End user code. Do not edit comment generated here */
