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
* File Name    : r_cg_vect_table.c
* Version      : 1.0.0
* Device(s)    : R5F12068xSP
* Description  : None
* Creation Date: 
***********************************************************************************************************************/

#include <rl78g15/smc_gen/general/r_cg_macrodriver.h>
#include <rl78g15/smc_gen/general/r_cg_userdefine.h>
#include "main.h"

extern void PowerON_Reset (void);

const unsigned char Option_Bytes[]  __attribute__ ((section (".option_bytes"))) = {
//        0xFFU, 0xE3U, 0xF9U, 0x85U
        0xEFU, 0xF3U, 0xF9U, 0x85U
};

const unsigned char Security_Id[]  __attribute__ ((section (".security_id"))) = {
    0x00U,0x00U,0x00U,0x00U,0x00U,0x00U,0x00U,0x00U,0x00U,0x00U
};

#define VEC          __attribute__ ((section (".vec")))
const void *HardwareVectors[] VEC = {
    // Address 0x0
    PowerON_Reset,
    // Secure for Debugging
    (void*)0xFFFF
};

#define VECT_SECT          __attribute__ ((section (".vects")))
const void *Vectors[] VECT_SECT = {
/*
 * INT_WDTI (0x4)
 */
//    r_Config_WDT_interrupt,
        INT_P5,
/*
 * INT_P0 (0x6)
 */
    r_Config_INTC_intp0_interrupt,

/*
 * INT_P1 (0x8)
 */
    INT_P1,

/*
 * INT_P2 (0xA)
 */
    INT_P2,
//    r_Config_INTC_intp2_interrupt,

/*
 * INT_P3 (0xC)
 */
//    INT_P3,
    r_Config_INTC_intp3_interrupt,

/*
 * INT_P4 (0xE)
 */
//    INT_P4,
    r_Config_INTC_intp4_interrupt,

/*
 * INT_P5 (0x10)
 */
    INT_P5,

/*
 * INT_CSI00/INT_IIC00/INT_ST0 (0x12)
 */
#if defined(USE_UART0) && USE_UART0 == 1
    r_Config_UART0_interrupt_send,
#else // defined(USE_UART0) && USE_UART0 == 1
    INT_P5,
#endif // defined(USE_UART0) && USE_UART0 == 1

/*
 * INT_CSI01/INT_IIC01/INT_SR0 (0x14)
 */
#if defined(USE_UART0) && USE_UART0 == 1
    r_Config_UART0_interrupt_receive,
#else // defined(USE_UART0) && USE_UART0 == 1
    INT_P5,
#endif // defined(USE_UART0) && USE_UART0 == 1

/*
 * INT_SRE0 (0x16)
 */
//    r_Config_UART0_interrupt_error,
    INT_P1,
/*
 * INT_TM01H (0x18)
 */
    INT_TM01H,

/*
 * INT_TM00 (0x1A)
 */
//    INT_TM00,
	r_Config_TAU0_0_Measure_Signal_interrupt,
/*
 * INT_TM01 (0x1C)
 */
    INT_TM01,

/*
 * INT_AD (0x1E)
 */
//    INT_AD,
#if defined(USE_ADC) & (USE_ADC==1)
    r_Config_ADC_interrupt,
#else // defined(USE_ADC) & (USE_ADC==1)
    INT_P5,
#endif // defined(USE_ADC) & (USE_ADC==1)

/*
 * INT_P6 (0x20)
 */
    INT_P6,

/*
 * INT_P7 (0x22)
 */
    INT_P7,

/*
 * INT_TM03H (0x24)
 */
    INT_TM03H,

/*
 * INT_IICA0 (0x26)
 */
#if defined(USE_I2C) && USE_I2C == 1
    r_Config_IICA0_interrupt,
#else
    INT_P5,
#endif  // defined(USE_I2C)

/*
 * INT_TM02 (0x28)
 */
//    r_Config_TAU0_2_channel2_interrupt,
    INT_TM02,

/*
 * INT_TM03 (0x2A)
 */
//    r_Config_TAU0_2_channel3_interrupt,
//    INT_TM03,
	r_Config_TAU0_3_Measure_Signal_interrupt,
/*
 * INT_IT (0x2C)
 */
    r_Config_IT_interrupt,
//    INT_P1,

/*
 * INT_TM04 (0x2E)
 */
    INT_TM04,

/*
 * INT_TM05 (0x30)
 */
    INT_TM05,

/*
 * INT_TM06 (0x32)
 */
//    INT_TM06,
    r_Config_TAU0_6_Micros_interrupt,

/*
 * INT_TM07 (0x34)
 */
    INT_TM07,

/*
 * INT_CMP0 (0x36)
 */
    INT_CMP0,

/*
 * INT_CMP1 (0x38)
 */
    INT_CMP1,

    // Padding
    (void*)0xFFFF,
    // Padding
    (void*)0xFFFF,

/*
 * INT_BRK_I (0x7E)
 */
    INT_BRK_I,
};
