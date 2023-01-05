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
* File Name    : r_cg_ad.h
* Version      : 1.0.0
* Device(s)    : R5F12068xSP
* Description  : General header file for ADC peripheral.
* Creation Date: 
***********************************************************************************************************************/

#ifndef ADC_H
#define ADC_H

/***********************************************************************************************************************
Macro definitions (Register bit)
***********************************************************************************************************************/
/*
    Peripheral Enable Register 0 (PER0)
*/
/* Control of AD converter input clock (ADCEN) */
#define _00_AD_CLOCK_STOP                      (0x00U)    /* stop supply of input clock */
#define _20_AD_CLOCK_SUPPLY                    (0x20U)    /* supply input clock */

/*
    AD Converter Mode Register 0 (ADM0)
*/
/* AD conversion operation control (ADCS) */
#define _80_AD_CONVERSION_ENABLE               (0x80U)    /* enable AD conversion operation control */
#define _00_AD_CONVERSION_DISABLE              (0x00U)    /* disable AD conversion operation control */
/* AD conversion clock selection (FR1 - FR0) */
#define _00_AD_CONVERSION_CLOCK_8              (0x00U)    /* fCLK/8 */
#define _08_AD_CONVERSION_CLOCK_4              (0x08U)    /* fCLK/4 */
#define _10_AD_CONVERSION_CLOCK_2              (0x10U)    /* fCLK/2 */
#define _18_AD_CONVERSION_CLOCK_1              (0x18U)    /* fCLK/1 */
/* Specification AD conversion time mode(LV0) */
#define _00_AD_TIME_MODE_NORMAL_1              (0x00U)    /* normal 1 mode */
#define _02_AD_TIME_MODE_NORMAL_2              (0x02U)    /* normal 2 mode */
/* AD comparator operation control (ADCE) */
#define _01_AD_COMPARATOR_ENABLE               (0x01U)    /* enable comparator operation control */
#define _00_AD_COMPARATOR_DISABLE              (0x00U)    /* disable comparator operation control */

/*
    Analog Input Channel Specification Register(ADS)
*/
/* Specification of analog input channel(ADS3 - ADS0) */
#define _00_AD_INPUT_CHANNEL_0                 (0x00U)    /* ANI0 */
#define _01_AD_INPUT_CHANNEL_1                 (0x01U)    /* ANI1 */
#define _02_AD_INPUT_CHANNEL_2                 (0x02U)    /* ANI2 */
#define _03_AD_INPUT_CHANNEL_3                 (0x03U)    /* ANI3 */
#define _04_AD_INPUT_CHANNEL_4                 (0x04U)    /* ANI4 */
#define _05_AD_INPUT_CHANNEL_5                 (0x05U)    /* ANI5 */
#define _06_AD_INPUT_CHANNEL_6                 (0x06U)    /* ANI6 */
#define _07_AD_INPUT_CHANNEL_7                 (0x07U)    /* ANI7 */
#define _08_AD_INPUT_CHANNEL_8                 (0x08U)    /* ANI8 */
#define _09_AD_INPUT_CHANNEL_9                 (0x09U)    /* ANI9 */
#define _0A_AD_INPUT_CHANNEL_10                (0x0AU)    /* ANI10 */
#define _0D_AD_INPUT_INTERREFVOLT              (0x0DU)    /* internal reference voltage output is the input channel */

/*
    AD Converter Mode Register 2 (ADM2)
*/
/* AD resolution selection (ADTYP) */
#define _00_AD_RESOLUTION_10BIT                (0x00U)    /* 10 bits */
#define _01_AD_RESOLUTION_8BIT                 (0x01U)    /* 8 bits */

/*
    AD Test Function Register (ADTES)
*/
/* AD test mode signal (ADTES1)*/
#define _00_AD_NORMAL_INPUT                    (0x00U)    /* normal mode */
#define _02_AD_TEST_VSS                        (0x02U)    /* use VSS as test signal */

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
/* End user code. Do not edit comment generated here */
#endif

