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
* File Name    : r_cg_port.h
* Version      : 1.0.0
* Device(s)    : R5F12068xSP
* Description  : General header file for PORT peripheral.
* Creation Date: 
***********************************************************************************************************************/

#ifndef PORT_H
#define PORT_H

/***********************************************************************************************************************
Macro definitions (Register bit)
***********************************************************************************************************************/
/*
    Port Mode Registers (PMn)
*/
/* Pn7 pin I/O mode selection (PMn7) */
#define _00_PMn7_MODE_OUTPUT                    (0x00U)    /* use Pn7 as output mode */
#define _80_PMn7_MODE_INPUT                     (0x80U)    /* use Pn7 as input mode */
#define _80_PMn7_NOT_USE                        (0x80U)    /* not use Pn7 as digital I/O */
/* Pn6 pin I/O mode selection (PMn6) */
#define _00_PMn6_MODE_OUTPUT                    (0x00U)    /* use Pn6 as output mode */
#define _40_PMn6_MODE_INPUT                     (0x40U)    /* use Pn6 as input mode */
#define _40_PMn6_NOT_USE                        (0x40U)    /* not use Pn6 as digital I/O */
/* Pn5 pin I/O mode selection (PMn5) */
#define _00_PMn5_MODE_OUTPUT                    (0x00U)    /* use Pn5 as output mode */
#define _20_PMn5_MODE_INPUT                     (0x20U)    /* use Pn5 as input mode */
#define _20_PMn5_NOT_USE                        (0x20U)    /* not use Pn5 as digital I/O */
/* Pn4 pin I/O mode selection (PMn4) */
#define _00_PMn4_MODE_OUTPUT                    (0x00U)    /* use Pn4 as output mode */
#define _10_PMn4_MODE_INPUT                     (0x10U)    /* use Pn4 as input mode */
#define _10_PMn4_NOT_USE                        (0x10U)    /* not use Pn4 as digital I/O */
/* Pn3 pin I/O mode selection (PMn3) */
#define _00_PMn3_MODE_OUTPUT                    (0x00U)    /* use Pn3 as output mode */
#define _08_PMn3_MODE_INPUT                     (0x08U)    /* use Pn3 as input mode */
#define _08_PMn3_NOT_USE                        (0x08U)    /* not use Pn3 as digital I/O */
/* Pn2 pin I/O mode selection (PMn2) */
#define _00_PMn2_MODE_OUTPUT                    (0x00U)    /* use Pn2 as output mode */
#define _04_PMn2_MODE_INPUT                     (0x04U)    /* use Pn2 as input mode */
#define _04_PMn2_NOT_USE                        (0x04U)    /* not use Pn2 as digital I/O */
/* Pn1 pin I/O mode selection (PMn1) */
#define _00_PMn1_MODE_OUTPUT                    (0x00U)    /* use Pn1 as output mode */
#define _02_PMn1_MODE_INPUT                     (0x02U)    /* use Pn1 as input mode */
#define _02_PMn1_NOT_USE                        (0x02U)    /* not use Pn1 as digital I/O */
/* Pn0 pin I/O mode selection (PMn0) */
#define _00_PMn0_MODE_OUTPUT                    (0x00U)    /* use Pn0 as output mode */
#define _01_PMn0_MODE_INPUT                     (0x01U)    /* use Pn0 as input mode */
#define _01_PMn0_NOT_USE                        (0x01U)    /* not use Pn0 as digital I/O */

/*
    Port Registers (Pn)
*/
/* Pn7 pin output latch selection (Pn7) */
#define _00_Pn7_OUTPUT_0                        (0x00U)    /* Pn7 output 0 */
#define _80_Pn7_OUTPUT_1                        (0x80U)    /* Pn7 output 1 */
/* Pn6 pin output latch selection (Pn6) */
#define _00_Pn6_OUTPUT_0                        (0x00U)    /* Pn6 output 0 */
#define _40_Pn6_OUTPUT_1                        (0x40U)    /* Pn6 output 1 */
/* Pn5 pin output latch selection (Pn5) */
#define _00_Pn5_OUTPUT_0                        (0x00U)    /* Pn5 output 0 */
#define _20_Pn5_OUTPUT_1                        (0x20U)    /* Pn5 output 1 */
/* Pn4 pin output latch selection (Pn4) */
#define _00_Pn4_OUTPUT_0                        (0x00U)    /* Pn4 output 0 */
#define _10_Pn4_OUTPUT_1                        (0x10U)    /* Pn4 output 1 */
/* Pn3 pin output latch selection (Pn3) */
#define _00_Pn3_OUTPUT_0                        (0x00U)    /* Pn3 output 0 */
#define _08_Pn3_OUTPUT_1                        (0x08U)    /* Pn3 output 1 */
/* Pn2 pin output latch selection (Pn2) */
#define _00_Pn2_OUTPUT_0                        (0x00U)    /* Pn2 output 0 */
#define _04_Pn2_OUTPUT_1                        (0x04U)    /* Pn2 output 1 */
/* Pn1 pin output latch selection (Pn1) */
#define _00_Pn1_OUTPUT_0                        (0x00U)    /* Pn1 output 0 */
#define _02_Pn1_OUTPUT_1                        (0x02U)    /* Pn1 output 1 */
/* Pn0 pin output latch selection (Pn0) */
#define _00_Pn0_OUTPUT_0                        (0x00U)    /* Pn0 output 0 */
#define _01_Pn0_OUTPUT_1                        (0x01U)    /* Pn0 output 1 */

/*
    Pull-up Resistor Option Registers (PUn)
*/
/* Pn7 pin on-chip pull-up resistor selection (PUn7) */
#define _00_PUn7_PULLUP_OFF                     (0x00U)    /* Pn7 pull-up resistor not connected */
#define _80_PUn7_PULLUP_ON                      (0x80U)    /* Pn7 pull-up resistor connected */
/* Pn6 pin on-chip pull-up resistor selection (PUn6) */
#define _00_PUn6_PULLUP_OFF                     (0x00U)    /* Pn6 pull-up resistor not connected */
#define _40_PUn6_PULLUP_ON                      (0x40U)    /* Pn6 pull-up resistor connected */
/* Pn5 pin on-chip pull-up resistor selection (PUn5) */
#define _00_PUn5_PULLUP_OFF                     (0x00U)    /* Pn5 pull-up resistor not connected */
#define _20_PUn5_PULLUP_ON                      (0x20U)    /* Pn5 pull-up resistor connected */
/* Pn4 pin on-chip pull-up resistor selection (PUn4) */
#define _00_PUn4_PULLUP_OFF                     (0x00U)    /* Pn4 pull-up resistor not connected */
#define _10_PUn4_PULLUP_ON                      (0x10U)    /* Pn4 pull-up resistor connected */
/* Pn3 pin on-chip pull-up resistor selection (PUn3) */
#define _00_PUn3_PULLUP_OFF                     (0x00U)    /* Pn3 pull-up resistor not connected */
#define _08_PUn3_PULLUP_ON                      (0x08U)    /* Pn3 pull-up resistor connected */
/* Pn2 pin on-chip pull-up resistor selection (PUn2) */
#define _00_PUn2_PULLUP_OFF                     (0x00U)    /* Pn2 Pull-up resistor not connected */
#define _04_PUn2_PULLUP_ON                      (0x04U)    /* Pn2 pull-up resistor connected */
/* Pn1 pin on-chip pull-up resistor selection (PUn1) */
#define _00_PUn1_PULLUP_OFF                     (0x00U)    /* Pn1 pull-up resistor not connected */
#define _02_PUn1_PULLUP_ON                      (0x02U)    /* Pn1 pull-up resistor connected */
/* Pn0 pin on-chip pull-up resistor selection (PUn0) */
#define _00_PUn0_PULLUP_OFF                     (0x00U)    /* Pn0 pull-up resistor not connected */
#define _01_PUn0_PULLUP_ON                      (0x01U)    /* Pn0 pull-up resistor connected */

/*
    Port Output Mode Registers (POMn)
*/
/* Pn7 pin output mode selection (POMn7) */
#define _00_POMn7_NCH_OFF                       (0x00U)    /* Pn7 normal output mode */
#define _80_POMn7_NCH_ON                        (0x80U)    /* Pn7 N-ch open-drain output mode */
/* Pn6 pin output mode selection (POMn6) */
#define _00_POMn6_NCH_OFF                       (0x00U)    /* Pn6 normal output mode */
#define _40_POMn6_NCH_ON                        (0x40U)    /* Pn6 N-ch open-drain output mode */
/* Pn5 pin output mode selection (POMn5) */
#define _00_POMn5_NCH_OFF                       (0x00U)    /* Pn5 normal output mode */
#define _20_POMn5_NCH_ON                        (0x20U)    /* Pn5 N-ch open-drain output mode */
/* Pn4 pin output mode selection (POMn4) */
#define _00_POMn4_NCH_OFF                       (0x00U)    /* Pn4 normal output mode */
#define _10_POMn4_NCH_ON                        (0x10U)    /* Pn4 N-ch open-drain output mode */
/* Pn3 pin output mode selection (POMn3) */
#define _00_POMn3_NCH_OFF                       (0x00U)    /* Pn3 normal output mode */
#define _08_POMn3_NCH_ON                        (0x08U)    /* Pn3 N-ch open-drain output mode */
/* Pn2 pin output mode selection (POMn2) */
#define _00_POMn2_NCH_OFF                       (0x00U)    /* Pn2 normal output mode */
#define _04_POMn2_NCH_ON                        (0x04U)    /* Pn2 N-ch open-drain output mode */
/* Pn1 pin output mode selection (POMn1) */
#define _00_POMn1_NCH_OFF                       (0x00U)    /* Pn1 normal output mode */
#define _02_POMn1_NCH_ON                        (0x02U)    /* Pn1 N-ch open-drain output mode */
/* Pn0 pin output mode selection (POMn0) */
#define _00_POMn0_NCH_OFF                       (0x00U)    /* Pn0 normal output mode */
#define _01_POMn0_NCH_ON                        (0x01U)    /* Pn0 N-ch open-drain output mode */

/*
    Port Mode Control Registers (PMCn)
*/
/* Selection of digital I/O or analog input for Pn7 (PMCn7) */
#define _00_PMCn7_DIGITAL_ON                   (0x00U)    /* digital I/O */
#define _80_PMCn7_NOT_USE                      (0x80U)    /* analog input */
/* Selection of digital I/O or analog input for Pn6 (PMCn6) */
#define _00_PMCn6_DIGITAL_ON                   (0x00U)    /* digital I/O */
#define _40_PMCn6_NOT_USE                      (0x40U)    /* analog input */
/* Selection of digital I/O or analog input for Pn5 (PMCn5) */
#define _00_PMCn5_DIGITAL_ON                   (0x00U)    /* digital I/O */
#define _20_PMCn5_NOT_USE                      (0x20U)    /* analog input */
/* Selection of digital I/O or analog input for Pn4 (PMCn4) */
#define _00_PMCn4_DIGITAL_ON                   (0x00U)    /* digital I/O */
#define _10_PMCn4_NOT_USE                      (0x10U)    /* analog input */
/* Selection of digital I/O or analog input for Pn3 (PMCn3) */
#define _00_PMCn3_DIGITAL_ON                   (0x00U)    /* digital I/O */
#define _08_PMCn3_NOT_USE                      (0x08U)    /* analog input */
/* Selection of digital I/O or analog input for Pn2 (PMCn2) */
#define _00_PMCn2_DIGITAL_ON                   (0x00U)    /* digital I/O */
#define _04_PMCn2_NOT_USE                      (0x04U)    /* analog input */
/* Selection of digital I/O or analog input for Pn1 (PMCn1) */
#define _00_PMCn1_DIGITAL_ON                   (0x00U)    /* digital I/O */
#define _02_PMCn1_NOT_USE                      (0x02U)    /* analog input */
/* Selection of digital I/O or analog input for Pn0 (PMCn0) */
#define _00_PMCn0_DIGITAL_ON                   (0x00U)    /* digital I/O */
#define _01_PMCn0_NOT_USE                      (0x01U)    /* analog input */

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

