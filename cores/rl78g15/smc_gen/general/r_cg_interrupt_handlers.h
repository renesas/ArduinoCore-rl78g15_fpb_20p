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
* File Name    : r_cg_interrupt_handlers.h
* Version      : 1.0.0
* Device(s)    : R5F12068xSP
* Description  : None
* Creation Date: 
***********************************************************************************************************************/

#include "main.h"

#ifndef INTERRUPT_HANDLER_H
#define INTERRUPT_HANDLER_H
/*
 * INT_WDTI (0x4)
 */
void r_Config_WDT_interrupt(void) __attribute__ ((interrupt));

/*
 * INT_P0 (0x6)
 */
void r_Config_INTC_intp0_interrupt(void) __attribute__ ((interrupt));

/*
 * INT_P1 (0x8)
 */
void INT_P1(void) __attribute__ ((interrupt));

/*
 * INT_P2 (0xA)
 */
 void INT_P2(void) __attribute__ ((interrupt));
//void r_Config_INTC_intp2_interrupt(void) __attribute__ ((interrupt));

/*
 * INT_P3 (0xC)
 */
// void INT_P3(void) __attribute__ ((interrupt));
void r_Config_INTC_intp3_interrupt(void) __attribute__ ((interrupt));

/*
 * INT_P4 (0xE)
 */
//void INT_P4(void) __attribute__ ((interrupt));
void r_Config_INTC_intp4_interrupt(void) __attribute__ ((interrupt));

/*
 * INT_P5 (0x10)
 */
void INT_P5(void) __attribute__ ((interrupt));

/*
 * INT_CSI00/INT_IIC00/INT_ST0 (0x12)
 */
#if defined(USE_UART0) && USE_UART0 == 1
void r_Config_UART0_interrupt_send(void) __attribute__ ((interrupt));
#endif // defined(USE_UART0) && USE_UART0 == 1
/*
 * INT_CSI01/INT_IIC01/INT_SR0 (0x14)
 */
#if defined(USE_UART0) && USE_UART0 == 1
void r_Config_UART0_interrupt_receive(void) __attribute__ ((interrupt));
#endif // defined(USE_UART0) && USE_UART0 == 1

/*
 * INT_SRE0 (0x16)
 */
void r_Config_UART0_interrupt_error(void) __attribute__ ((interrupt));

/*
 * INT_TM01H (0x18)
 */
void INT_TM01H(void) __attribute__ ((interrupt));

/*
 * INT_TM00 (0x1A)
 */
void INT_TM00(void) __attribute__ ((interrupt));
void r_Config_TAU0_0_Measure_Signal_interrupt(void) __attribute__ ((interrupt));
/*
 * INT_TM01 (0x1C)
 */
void r_Config_TAU0_1_Square_Wave_interrupt(void) __attribute__ ((interrupt));
void INT_TM01(void) __attribute__ ((interrupt));

/*
 * INT_AD (0x1E)
 */
//void INT_AD(void) __attribute__ ((interrupt));
void r_Config_ADC_interrupt(void) __attribute__ ((interrupt));

/*
 * INT_P6 (0x20)
 */
void INT_P6(void) __attribute__ ((interrupt));

/*
 * INT_P7 (0x22)
 */
void INT_P7(void) __attribute__ ((interrupt));

/*
 * INT_TM03H (0x24)
 */
void INT_TM03H(void) __attribute__ ((interrupt));

/*
 * INT_IICA0 (0x26)
 */
void r_Config_IICA0_interrupt(void) __attribute__ ((interrupt));

/*
 * INT_TM02 (0x28)
 */
// void r_Config_TAU0_2_channel2_interrupt(void) __attribute__ ((interrupt));
void INT_TM02(void) __attribute__ ((interrupt));
void r_Config_TAU0_2_Square_Wave_interrupt(void) __attribute__ ((interrupt));


/*
 * INT_TM03 (0x2A)
 */
// void r_Config_TAU0_2_channel3_interrupt(void) __attribute__ ((interrupt));
void INT_TM03(void) __attribute__ ((interrupt));
void r_Config_TAU0_3_Measure_Signal_interrupt(void) __attribute__ ((interrupt));
void r_Config_TAU0_3_Square_Wave_interrupt(void) __attribute__ ((interrupt));


/*
 * INT_IT (0x2C)
 */
void r_Config_IT_interrupt(void) __attribute__ ((interrupt));

/*
 * INT_TM04 (0x2E)
 */
void INT_TM04(void) __attribute__ ((interrupt));

/*
 * INT_TM05 (0x30)
 */
void INT_TM05(void) __attribute__ ((interrupt));

/*
 * INT_TM06 (0x32)
 */
//void INT_TM06(void) __attribute__ ((interrupt));
void r_Config_TAU0_6_Micros_interrupt(void) __attribute__ ((interrupt));
/*
 * INT_TM07 (0x34)
 */
void INT_TM07(void) __attribute__ ((interrupt));

/*
 * INT_CMP0 (0x36)
 */
void INT_CMP0(void) __attribute__ ((interrupt));

/*
 * INT_CMP1 (0x38)
 */
void INT_CMP1(void) __attribute__ ((interrupt));
/*
 * INT_BRK_I (0x7E)
 */
void INT_BRK_I(void) __attribute__ ((interrupt));

//Hardware Vectors
//PowerON_Reset (0x0)
void PowerON_Reset(void) __attribute__ ((interrupt));

#endif
