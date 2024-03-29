/*
  pins_arduino.h - Pin definition functions for Arduino
  Part of Arduino - http://www.arduino.cc/

  Copyright (c) 2007 David A. Mellis

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General
  Public License along with this library; if not, write to the
  Free Software Foundation, Inc., 59 Temple Place, Suite 330,
  Boston, MA  02111-1307  USA
*/
/*
 * Modified 13 July 2014 by Nozomu Fujita
 * Modified  2 Mar  2017 by Yuuki Okamiya
 * Modified 19 Jul  2022 by Yoshikazu Aono
 */

#ifndef Pins_Arduino_h
#define Pins_Arduino_h

#ifndef __RL78__
#include <rl78g15/avr/pgmspace.h>
#else
#include <stdint.h>
#include <stdlib.h>
#endif

#ifndef __RL78__
#define NUM_DIGITAL_PINS            20
#define NUM_ANALOG_INPUTS           6
#else  //__RL78__
    #ifndef BSP_MCU_GROUP_RL78G15  // old code for G23 but not general
        //#define NUM_DIGITAL_PINS            31
        #define NUM_DIGITAL_PINS            57
        #define NUM_ANALOG_INPUTS           10
        #define NUM_SWPWM_PINS              4
    #else  // BSP_MCU_GROUP_RL78G15 (Yes G15)
        #define NUM_DIGITAL_PINS            20
        #define NUM_ANALOG_INPUTS           3  // 20220831 changed from 4->3
        #define NUM_SWPWM_PINS              2
    #endif  // BSP_MCU_GROUP_RL78G15
#endif  //__RL78__

#define analogInputToDigitalPin(p)  ((p < 6) ? (p) + 14 : -1)

#if defined(__AVR_ATmega8__)
#define digitalPinHasPWM(p)         ((p) == 9 || (p) == 10 || (p) == 11)
#elif defined(__RL78__)
#define digitalPinHasPWM(p)         ((p) == 3 || (p) == 5 || (p) == 6 || (p) == 9 || (p) == 10 || (p) == 11|| (p) == 22|| (p) == 23|| (p) == 24)
#else
#define digitalPinHasPWM(p)         ((p) == 3 || (p) == 5 || (p) == 6 || (p) == 9 || (p) == 10 || (p) == 11)
#endif

#if 0
#define PIN_SPI_SS    (10)
#define PIN_SPI_MOSI  (11)
#define PIN_SPI_MISO  (12)
#define PIN_SPI_SCK   (13)
#ifdef __RL78__
#define PIN_SPI2_SS    (27)
#define PIN_SPI2_MOSI  (28)
#define PIN_SPI2_MISO  (29)
#define PIN_SPI2_SCK   (30)
#endif

static const uint8_t SS   = PIN_SPI_SS;
static const uint8_t MOSI = PIN_SPI_MOSI;
static const uint8_t MISO = PIN_SPI_MISO;
static const uint8_t SCK  = PIN_SPI_SCK;
#ifdef __RL78__
static const uint8_t SS2   = PIN_SPI2_SS;
static const uint8_t MOSI2 = PIN_SPI2_MOSI;
static const uint8_t MISO2 = PIN_SPI2_MISO;
static const uint8_t SCK2  = PIN_SPI2_SCK;
#endif
#endif

#ifdef __RL78__
#define PIN_SPI_SS    (10)
#define PIN_SPI_MOSI  (36)
#define PIN_SPI_MISO  (37)
#define PIN_SPI_SCK   (38)

#define PIN_SPI3_SS    (27)
#define PIN_SPI3_MOSI  (11)
#define PIN_SPI3_MISO  (12)
#define PIN_SPI3_SCK   (13)

#define PIN_SPI4_SS    (27)
#define PIN_SPI4_MOSI  (35)
#define PIN_SPI4_MISO  (34)
#define PIN_SPI4_SCK   (33)

#define PIN_SPI5_SS    (27)
#define PIN_SPI5_MOSI  (21)
#define PIN_SPI5_MISO  (20)
#define PIN_SPI5_SCK   (19)

static const uint8_t SS   = PIN_SPI_SS;
static const uint8_t MOSI = PIN_SPI_MOSI;
static const uint8_t MISO = PIN_SPI_MISO;
static const uint8_t SCK  = PIN_SPI_SCK;

static const uint8_t SS3   = PIN_SPI3_SS;
static const uint8_t MOSI3 = PIN_SPI3_MOSI;
static const uint8_t MISO3 = PIN_SPI3_MISO;
static const uint8_t SCK3  = PIN_SPI3_SCK;

static const uint8_t SS4   = PIN_SPI4_SS;
static const uint8_t MOSI4 = PIN_SPI4_MOSI;
static const uint8_t MISO4 = PIN_SPI4_MISO;
static const uint8_t SCK4  = PIN_SPI4_SCK;

static const uint8_t SS5   = PIN_SPI5_SS;
static const uint8_t MOSI5 = PIN_SPI5_MOSI;
static const uint8_t MISO5 = PIN_SPI5_MISO;
static const uint8_t SCK5  = PIN_SPI5_SCK;

#else
#define PIN_SPI_SS    (10)
#define PIN_SPI_MOSI  (11)
#define PIN_SPI_MISO  (12)
#define PIN_SPI_SCK   (13)

static const uint8_t SS   = PIN_SPI_SS;
static const uint8_t MOSI = PIN_SPI_MOSI;
static const uint8_t MISO = PIN_SPI_MISO;
static const uint8_t SCK  = PIN_SPI_SCK;

#endif


#ifndef __RL78__
#define PIN_WIRE_SDA        (18)
#define PIN_WIRE_SCL        (19)
#else
#define PIN_WIRE_SDA0        (48) // P61
#define PIN_WIRE_SCL0        (47) // P60
#define PIN_WIRE_SDA1        (50) // P63
#define PIN_WIRE_SCL1        (49) // P62

#define PIN_WIRE_SDA0_MASK   0x02 // P61
#define PIN_WIRE_SCL0_MASK   0x01 // P60
#define PIN_WIRE_SDA1_MASK   0x08 // P63
#define PIN_WIRE_SCL1_MASK   0x04 // P62
#endif /*__RL78__*/

static const uint8_t SDA0 = PIN_WIRE_SDA0;
static const uint8_t SCL0 = PIN_WIRE_SCL0;
static const uint8_t SDA1 = PIN_WIRE_SDA1;
static const uint8_t SCL1 = PIN_WIRE_SCL1;

#ifdef GRADZUKI
#define LED_BUILTIN 13
#else
#define LED_BUILTIN 24
#endif

//★逆になっていたので修正
#define BUILTIN_LED1 7
#define BUILTIN_LED2 4

/*
#define PIN_A0   (51)
#define PIN_A1   (52)
#define PIN_A2   (53)
#define PIN_A3   (54)
#define PIN_A4   (55)
#define PIN_A5   (56)
*/
// temporary 2022/09/01
// #define G15_A0 14
// #define G15_A1 15
// #define G15_A2 16

// #define PIN_A0   (51)	/*A0 = ANI2 */
// #define PIN_A1   (52)	/*A1 = ANI3 */
// #define PIN_A2   (53)	/*A2 = ANI4 */
// #define PIN_A3   (54)	/*A3 = ANI5 */
// #define PIN_A4   (55)	/*A4 = ANI6 */
// #define PIN_A5   (56)	/*A5 = ANI7 */

/* add 2021.07.29 */
// #define PIN_A6	(0)		/* ANI16(P03/RxD1) */
// #define PIN_A7	(1)		/* ANI17(P02/TxD1) */
//#define PIN_A8	(29)	/* ANI19(P120) (DIGITAL_PIN_29) */
// #define PIN_A9	(40)	/* ANI18(P147) (DIGITAL_PIN_40) */
/* add 2021.07.29 */

//#define PIN_A6   (20)
//#define PIN_A7   (21)

#define PIN_A0   (14)
#define PIN_A1   (15)
#define PIN_A2   (16)
//#define PIN_A3   (17)
//#define PIN_A4   (18)
//#define PIN_A5   (19)
//#define PIN_A6   (20)
//#define PIN_A7   (21)

static const uint8_t A0 = PIN_A0;
static const uint8_t A1 = PIN_A1;
static const uint8_t A2 = PIN_A2;
// static const uint8_t A3 = PIN_A3;
// static const uint8_t A4 = PIN_A4;
// static const uint8_t A5 = PIN_A5;
/* add 2021.07.29 */
// static const uint8_t A6 = PIN_A6;
// static const uint8_t A7 = PIN_A7;
// static const uint8_t A8 = PIN_A8;
// static const uint8_t A9 = PIN_A9;
/* add 2021.07.29 */

#define digitalPinToPCICR(p)    (((p) >= 0 && (p) <= 21) ? (&PCICR) : ((uint8_t *)0))
#define digitalPinToPCICRbit(p) (((p) <= 7) ? 2 : (((p) <= 13) ? 0 : 1))
#define digitalPinToPCMSK(p)    (((p) <= 7) ? (&PCMSK2) : (((p) <= 13) ? (&PCMSK0) : (((p) <= 21) ? (&PCMSK1) : ((uint8_t *)0))))
#define digitalPinToPCMSKbit(p) (((p) <= 7) ? (p) : (((p) <= 13) ? ((p) - 8) : ((p) - 14)))

#ifndef __RL78__
#define digitalPinToInterrupt(p)  ((p) == 2 ? 0 : ((p) == 3 ? 1 : NOT_AN_INTERRUPT))
#else
// 2022/12/01
// #define digitalPinToInterrupt(p)  ((p) == 2 ? 0 : ((p) == 9 ? 1 : (p) == 10 ? 2 : NOT_AN_INTERRUPT))  // RL78/G15
#define digitalPinToInterrupt(p)  ((p) == 0 ? 0 : ((p) == 2 ? 1 : (p) == 3 ? 2 : NOT_AN_INTERRUPT))  // RL78/G15
#endif

#ifdef __RL78__
/***************************************************************************/
/*    Macro Definitions                                                    */
/***************************************************************************/
#define ADDR_PORT_REG			0xFFFFFF00
#define ADDR_PORT_MODE_REG		0xFFFFFF20
#define ADDR_PORT_PULL_UP_REG	0xFFFF0030
#define	ADDR_PORT_IN_MODE_REG	0xFFFF0040
#define ADDR_PORT_OUT_MODE_REG	0xFFFF0050
#if 0
/* Add for G23 */
#define ADDR_PORT_MODE_CONTROL_A_REG	0xFFFF0060
#define ADDR_PORT_MODE_CONTROL_T_REG	0xFFFF0260
#define ADDR_PORT_MODE_CONTROL_E_REG	0xFFFF0280
#define ADDR_PORT_OUT_CUR_CONTROL_REG	0xFFFF02A8
#define ADDR_PORT_DIG_INPUT_DIS_REG		0xFFFF02B0


/* Add for G23 */
#endif

/* 20220801追加　*/
#define ADDR_PORT_OUT_CUR_CONTROL_REG	0xFFFF02A8
#define ADDR_PORT_DIG_INPUT_DIS_REG		0xFFFF02B0
#define ADDR_PORT_MODE_CONTROL_REG		0xFFFF0060

// 20220831 maintenance for RL78/G15
#define ANALOG_PIN_0		7		// ANI7 (A0 J4-1 DIGITAL_PIN_14)
#define ANALOG_PIN_1		8		// ANI8 (A1 DIGITAL_PIN_15)
#define ANALOG_PIN_2		1		// ANI1 (A2 DIGITAL_PIN_16)
// #define ANALOG_PIN_3		5		// ANI5 (DIGITAL_PIN_54)
// #define ANALOG_PIN_4		6		// ANI6 (DIGITAL_PIN_55)
// #define ANALOG_PIN_5		7		// ANI7 (DIGITAL_PIN_56)
/* add 2021.07.29 */
// #define ANALOG_PIN_6		16		// ANI16(P03/RxD1) (DIGITAL_PIN_0)
// #define ANALOG_PIN_7		17		// ANI17(P02/TxD1) (DIGITAL_PIN_1)
// #define ANALOG_PIN_8		19		// ANI19(P120) (DIGITAL_PIN_29)
// #define ANALOG_PIN_9		18		// ANI18(P147) (DIGITAL_PIN_40)

//#define ANALOG_PIN_6		18		// ANI18
//#define ANALOG_PIN_7		19		// ANI19

/* Port define. */
#define PORT_0				0
#define PORT_1				1
#define PORT_2				2
#define PORT_3				3
#define PORT_4				4
#define PORT_5				5
#define PORT_6				6
#define PORT_7				7
#define PORT_8				8
#define PORT_9				9
#define PORT_10				10
#define PORT_11				11
#define PORT_12				12
#define PORT_13				13
#define PORT_14				14
#define PORT_15				15
#define PORT_16				16
#define PORT_17				17
#define PORT_18				18
#define PORT_19				19



/* Port of digital pin define. */
#define DIGITAL_PIN_0		PORT_0	/* P04	*/
#define DIGITAL_PIN_1		PORT_0	/* P03	*/
#define DIGITAL_PIN_2		PORT_13	/* P137	*/
#define DIGITAL_PIN_3		PORT_4	/* P41	*/
#define DIGITAL_PIN_4		PORT_2	/* P21	*/
#define DIGITAL_PIN_5		DIGITAL_PIN_14	/* P23	*/
#define DIGITAL_PIN_6		DIGITAL_PIN_15	/* P22	*/
#define DIGITAL_PIN_7		PORT_2	/* P20	*/
#define DIGITAL_PIN_8		PORT_4	/* P40	*/
#define DIGITAL_PIN_9		PORT_12	/* P122	*/
#define DIGITAL_PIN_10		PORT_12	/* P121	*/
#define DIGITAL_PIN_11		DIGITAL_PIN_1	/* P03	*/
#define DIGITAL_PIN_12		DIGITAL_PIN_0	/* P04	*/
#define DIGITAL_PIN_13		PORT_0	/* P05	*/
#define DIGITAL_PIN_14		PORT_2	/* P23	*/
#define DIGITAL_PIN_15		PORT_2	/* P22	*/
#define DIGITAL_PIN_16		PORT_0	/* P02	*/
#define DIGITAL_PIN_17		DIGITAL_PIN_13	/* P05	*/
#define DIGITAL_PIN_18		PORT_0	/* P06	*/
#define DIGITAL_PIN_19		PORT_0	/* P07	*/



/* Bit Num of digital pin define */
#define DIGITAL_PIN_BIT_0	0x04	/* P04	*/
#define DIGITAL_PIN_BIT_1	0x03	/* P03	*/
#define DIGITAL_PIN_BIT_2	0x07	/* P137	*/
#define DIGITAL_PIN_BIT_3	0x01	/* P41	*/
#define DIGITAL_PIN_BIT_4	0x01	/* P21	*/
#define DIGITAL_PIN_BIT_5	DIGITAL_PIN_BIT_14	/* P23	*/
#define DIGITAL_PIN_BIT_6	DIGITAL_PIN_BIT_15	/* P22	*/
#define DIGITAL_PIN_BIT_7	0x00	/* P20	*/
#define DIGITAL_PIN_BIT_8	0x00	/* P40	*/
#define DIGITAL_PIN_BIT_9	0x02	/* P122	*/
#define DIGITAL_PIN_BIT_10	0x01	/* P121	*/
#define DIGITAL_PIN_BIT_11	DIGITAL_PIN_BIT_1	/* P03	*/
#define DIGITAL_PIN_BIT_12	DIGITAL_PIN_BIT_0	/* P04	*/
#define DIGITAL_PIN_BIT_13	0x05	/* P05	*/
#define DIGITAL_PIN_BIT_14	0x03	/* P23(REF)	*/
#define DIGITAL_PIN_BIT_15	0x02	/* P22	*/
#define DIGITAL_PIN_BIT_16	0x02	/* P02	*/
#define DIGITAL_PIN_BIT_17	DIGITAL_PIN_BIT_13	/* P05	*/
#define DIGITAL_PIN_BIT_18	0x06	/* P06	*/
#define DIGITAL_PIN_BIT_19	0x07	/* P07	*/
                                


/* Bit mask of digital pin define. */
#define DIGITAL_PIN_MASK_0		0x10	/* P04	*/
#define DIGITAL_PIN_MASK_1		0x08	/* P03	*/
#define DIGITAL_PIN_MASK_2		0x80	/* P137	*/
#define DIGITAL_PIN_MASK_3		0x02	/* P41	*/
#define DIGITAL_PIN_MASK_4		0x02	/* P21	*/
#define DIGITAL_PIN_MASK_5		DIGITAL_PIN_MASK_14	/* P23	*/
#define DIGITAL_PIN_MASK_6		DIGITAL_PIN_MASK_15	/* P22	*/
#define DIGITAL_PIN_MASK_7		0x01	/* P20	*/
#define DIGITAL_PIN_MASK_8		0x01	/* P40	*/
#define DIGITAL_PIN_MASK_9		0x04	/* P122	*/
#define DIGITAL_PIN_MASK_10		0x02	/* P121	*/
#define DIGITAL_PIN_MASK_11		DIGITAL_PIN_MASK_1	/* P03	*/
#define DIGITAL_PIN_MASK_12		DIGITAL_PIN_MASK_0	/* P04	*/
#define DIGITAL_PIN_MASK_13		0x20	/* P05	*/
#define DIGITAL_PIN_MASK_14		0x08	/* P23(REF)	*/
#define DIGITAL_PIN_MASK_15		0x04	/* P22	*/
#define DIGITAL_PIN_MASK_16		0x04	/* P02	*/
#define DIGITAL_PIN_MASK_17		DIGITAL_PIN_MASK_13	/* P05	*/
#define DIGITAL_PIN_MASK_18		0x40	/* P06	*/
#define DIGITAL_PIN_MASK_19		0x80	/* P07	*/



/*  PMC */
#define DIGITAL_PIN_PMC_0		0x10	/* P04	*/
#define DIGITAL_PIN_PMC_1		0x08	/* P03	*/
#define DIGITAL_PIN_PMC_2		0x00	/* P137	*/
#define DIGITAL_PIN_PMC_3		0x00	/* P41	*/
#define DIGITAL_PIN_PMC_4		0x02	/* P21	*/
#define DIGITAL_PIN_PMC_5		DIGITAL_PIN_PMC_14	/* P23	*/
#define DIGITAL_PIN_PMC_6		DIGITAL_PIN_PMC_15	/* P22	*/
#define DIGITAL_PIN_PMC_7		0x01	/* P20	*/
#define DIGITAL_PIN_PMC_8		0x00	/* P40	*/
#define DIGITAL_PIN_PMC_9		0x00	/* P122	*/
#define DIGITAL_PIN_PMC_10		0x00	/* P121	*/
#define DIGITAL_PIN_PMC_11		DIGITAL_PIN_PMC_1	/* P03	*/
#define DIGITAL_PIN_PMC_12		DIGITAL_PIN_PMC_0	/* P04	*/
#define DIGITAL_PIN_PMC_13		0x20	/* P05	*/
/* 追加(仮)　*/
#define DIGITAL_PIN_PMC_14		0x08	/* P23	*/
#define DIGITAL_PIN_PMC_15		0x04	/* P22	*/
#define DIGITAL_PIN_PMC_16		0x04	/* P02	*/
#define DIGITAL_PIN_PMC_17		DIGITAL_PIN_PMC_13	/* P05	*/
#define DIGITAL_PIN_PMC_18		0x00	/* P06	*/
#define DIGITAL_PIN_PMC_19		0x00	/* P07	*/



#if 0
/* Define Digital Pin CCDE */
#define DIGITAL_PIN_CCDE_0		0x00	/* P03	*/
#define DIGITAL_PIN_CCDE_1		0x00	/* P02	*/
#define DIGITAL_PIN_CCDE_2		0x00	/* P43	*/
#define DIGITAL_PIN_CCDE_3		0x00	/* P42	*/
#define DIGITAL_PIN_CCDE_4		0x00	/* P77	*/
#define DIGITAL_PIN_CCDE_5		0x00	/* P41	*/
#define DIGITAL_PIN_CCDE_6		0x00	/* P31	*/
#define DIGITAL_PIN_CCDE_7		0x00	/* P76	*/
#define DIGITAL_PIN_CCDE_8		0x00	/* P73	*/
#define DIGITAL_PIN_CCDE_9		0x00	/* P06	*/
#define DIGITAL_PIN_CCDE_10		0x00	/* P05	*/
#define DIGITAL_PIN_CCDE_11		0x04	/* P51	*/
#define DIGITAL_PIN_CCDE_12		0x08	/* P50	*/
#define DIGITAL_PIN_CCDE_13		0x00	/* P30	*/
/* 追加(仮)　*/
#define DIGITAL_PIN_CCDE_14		0x00
#define DIGITAL_PIN_CCDE_15		0x00
#define DIGITAL_PIN_CCDE_16		0x00
#define DIGITAL_PIN_CCDE_17		0x00


/* Define Digital Pin PDIDIS */
#define DIGITAL_PIN_PDIDIS_0	0x08	/* P03	*/
#define DIGITAL_PIN_PDIDIS_1	0x04	/* P02	*/
#define DIGITAL_PIN_PDIDIS_2	0x00	/* P43	*/
#define DIGITAL_PIN_PDIDIS_3	0x04	/* P42	*/
#define DIGITAL_PIN_PDIDIS_4	0x00	/* P77	*/
#define DIGITAL_PIN_PDIDIS_5	0x00	/* P41	*/
#define DIGITAL_PIN_PDIDIS_6	0x00	/* P31	*/
#define DIGITAL_PIN_PDIDIS_7	0x00	/* P76	*/
#define DIGITAL_PIN_PDIDIS_8	0x00	/* P73	*/
#define DIGITAL_PIN_PDIDIS_9	0x00	/* P06	*/
#define DIGITAL_PIN_PDIDIS_10	0x00	/* P05	*/
#define DIGITAL_PIN_PDIDIS_11	0x00	/* P51	*/
#define DIGITAL_PIN_PDIDIS_12	0x01	/* P50	*/
#define DIGITAL_PIN_PDIDIS_13	0x00	/* P30	*/
/* 追加(仮)　*/
#define DIGITAL_PIN_PDIDIS_14	0x00
#define DIGITAL_PIN_PDIDIS_15	0x00
#define DIGITAL_PIN_PDIDIS_16	0x00
#define DIGITAL_PIN_PDIDIS_17	0x00
#endif



/* Define Digital Pin PM */
#define DIGITAL_PIN_PM_0		0x10	/* P04	*/
#define DIGITAL_PIN_PM_1		0x08	/* P03	*/
#define DIGITAL_PIN_PM_2		0x00	/* P137	*/
#define DIGITAL_PIN_PM_3		0x02	/* P41	*/
#define DIGITAL_PIN_PM_4		0x02	/* P21	*/
#define DIGITAL_PIN_PM_5		DIGITAL_PIN_PM_14	/* P23	*/
#define DIGITAL_PIN_PM_6		DIGITAL_PIN_PM_15	/* P22	*/
#define DIGITAL_PIN_PM_7		0x01	/* P20	*/
#define DIGITAL_PIN_PM_8		0x01	/* P40	*/
#define DIGITAL_PIN_PM_9		0x04	/* P122	*/
#define DIGITAL_PIN_PM_10		0x02	/* P121	*/
#define DIGITAL_PIN_PM_11		DIGITAL_PIN_PM_1	/* P03	*/
#define DIGITAL_PIN_PM_12		DIGITAL_PIN_PM_0	/* P04	*/
#define DIGITAL_PIN_PM_13		0x20	/* P05	*/
/* 追加(仮)　*/
#define DIGITAL_PIN_PM_14		0x08	/* P23(REF)	*/
#define DIGITAL_PIN_PM_15		0x04	/* P22	*/
#define DIGITAL_PIN_PM_16		0x04	/* P02	*/
#define DIGITAL_PIN_PM_17		DIGITAL_PIN_PM_13	/* P05	*/
#define DIGITAL_PIN_PM_18		0x40	/* P06	*/
#define DIGITAL_PIN_PM_19		0x80	/* P07	*/



/* Define Digital Pin PU */
#define DIGITAL_PIN_PU_0		0x10	/* P04	*/
#define DIGITAL_PIN_PU_1		0x08	/* P03	*/
#define DIGITAL_PIN_PU_2		0x00	/* P137	*/
#define DIGITAL_PIN_PU_3		0x02	/* P41	*/
#define DIGITAL_PIN_PU_4		0x02	/* P21	*/
#define DIGITAL_PIN_PU_5		DIGITAL_PIN_PU_14	/* P23	*/
#define DIGITAL_PIN_PU_6		DIGITAL_PIN_PU_15	/* P22	*/
#define DIGITAL_PIN_PU_7		0x01	/* P20	*/
#define DIGITAL_PIN_PU_8		0x01	/* P40	*/
#define DIGITAL_PIN_PU_9		0x04	/* P122	*/
#define DIGITAL_PIN_PU_10		0x02	/* P121	*/
#define DIGITAL_PIN_PU_11		DIGITAL_PIN_PU_1	/* P03	*/
#define DIGITAL_PIN_PU_12		DIGITAL_PIN_PU_0	/* P04	*/
#define DIGITAL_PIN_PU_13		0x20	/* P05	*/
/* 追加(仮)　*/
#define DIGITAL_PIN_PU_14		0x08	/* P23	*/
#define DIGITAL_PIN_PU_15		0x04	/* P22	*/
#define DIGITAL_PIN_PU_16		0x04	/* P02	*/
#define DIGITAL_PIN_PU_17		DIGITAL_PIN_PU_13	/* P05	*/
#define DIGITAL_PIN_PU_18		0x40	/* P06	*/
#define DIGITAL_PIN_PU_19		0x80	/* P07	*/


#if 0
/* Define Digital Pin PIM */
#define DIGITAL_PIN_PIM_0		0x10	/* P04	*/
#define DIGITAL_PIN_PIM_1		0x08	/* P03	*/
#define DIGITAL_PIN_PIM_2		0x80	/* P137	*/
#define DIGITAL_PIN_PIM_3		0x02	/* P41	*/
#define DIGITAL_PIN_PIM_4		0x02	/* P21	*/
#define DIGITAL_PIN_PIM_5		0x08	/* P23	*/
#define DIGITAL_PIN_PIM_6		0x04	/* P22	*/
#define DIGITAL_PIN_PIM_7		0x01	/* P20	*/
#define DIGITAL_PIN_PIM_8		0x01	/* P40	*/
#define DIGITAL_PIN_PIM_9		0x04	/* P122	*/
#define DIGITAL_PIN_PIM_10		0x02	/* P121	*/
#define DIGITAL_PIN_PIM_11		0x08	/* P03	*/
#define DIGITAL_PIN_PIM_12		0x10	/* P04	*/
#define DIGITAL_PIN_PIM_13		0x20	/* P05	*/
/* 追加(仮)　*/
#define DIGITAL_PIN_PIM_14		0x08	/* P23(REF)	*/
#define DIGITAL_PIN_PIM_15		0x04	/* P22	*/
#define DIGITAL_PIN_PIM_16		0x04	/* P02	*/
#define DIGITAL_PIN_PIM_17		0x20	/* P05	*/
#endif


/* Define Digital Pin POM */
#define DIGITAL_PIN_POM_0		0x10	/* P04	*/
#define DIGITAL_PIN_POM_1		0x08	/* P03	*/
#define DIGITAL_PIN_POM_2		0x00	/* P137	*/
#define DIGITAL_PIN_POM_3		0x02	/* P41	*/
#define DIGITAL_PIN_POM_4		0x00	/* P21	*/
#define DIGITAL_PIN_POM_5		DIGITAL_PIN_POM_14	/* P23	*/
#define DIGITAL_PIN_POM_6		DIGITAL_PIN_POM_15	/* P22	*/
#define DIGITAL_PIN_POM_7		0x00	/* P20	*/
#define DIGITAL_PIN_POM_8		0x00	/* P40	*/
#define DIGITAL_PIN_POM_9		0x00	/* P122	*/
#define DIGITAL_PIN_POM_10		0x00	/* P121	*/
#define DIGITAL_PIN_POM_11		DIGITAL_PIN_POM_1	/* P03	*/
#define DIGITAL_PIN_POM_12		DIGITAL_PIN_POM_0	/* P04	*/
#define DIGITAL_PIN_POM_13		0x20	/* P05	*/
/* 追加(仮)　*/
#define DIGITAL_PIN_POM_14		0x00	/* P23(REF)	*/
#define DIGITAL_PIN_POM_15		0x04	/* P22	*/
#define DIGITAL_PIN_POM_16		0x00	/* P02	*/
#define DIGITAL_PIN_POM_17		DIGITAL_PIN_POM_13	/* P05	*/
#define DIGITAL_PIN_POM_18		0x40	/* P06	*/
#define DIGITAL_PIN_POM_19		0x80	/* P07	*/



#endif

#define PWM_PIN_11			0xE0	// Software PWM0
#define PWM_PIN_22			0xE1	// Software PWM1
#define PWM_PIN_23			0xE2	// Software PWM2
#define PWM_PIN_24			0xE3	// Software PWM3

#define SWPWM_PIN			0xE0
/* 1006 Nhu add */
#define PWM_PIN_0			0		// TO1
#define PWM_PIN_3			3		// TO3
#define PWM_PIN_13			13		// TO2

#define PWM_PIN_5			5		// TO7
#define PWM_PIN_6			6		// TO3
#define PWM_PIN_9			9		// TO6
#define PWM_PIN_10			10		// TO5
#define PWM_PIN_31			31		// TO2
#define PWM_PIN_32			32		// TO1
/* 1006 Nhu add */
/* Define Serial Port Number */
#define SERIAL_TXD0			36 // P12
#define SERIAL_RXD0			37 // P11

#define SERIAL_TXD1			1  // P02
#define SERIAL_RXD1			0  // P03

#define SERIAL_TXD2			35 // P13
#define SERIAL_RXD2			34 // P14
/* Define Serial Port Number */


// #ifdef ARDUINO_MAIN

// On the Arduino board, digital pins are also used
// for the analog output (software PWM).  Analog input
// pins are a separate set.

// ATMEL ATMEGA8 & 168 / ARDUINO
//
//                  +-\/-+
//            PC6  1|    |28  PC5 (AI 5)
//      (D 0) PD0  2|    |27  PC4 (AI 4)
//      (D 1) PD1  3|    |26  PC3 (AI 3)
//      (D 2) PD2  4|    |25  PC2 (AI 2)
// PWM+ (D 3) PD3  5|    |24  PC1 (AI 1)
//      (D 4) PD4  6|    |23  PC0 (AI 0)
//            VCC  7|    |22  GND
//            GND  8|    |21  AREF
//            PB6  9|    |20  AVCC
//            PB7 10|    |19  PB5 (D 13)
// PWM+ (D 5) PD5 11|    |18  PB4 (D 12)
// PWM+ (D 6) PD6 12|    |17  PB3 (D 11) PWM
//      (D 7) PD7 13|    |16  PB2 (D 10) PWM
//      (D 8) PB0 14|    |15  PB1 (D 9) PWM
//                  +----+
//
// (PWM+ indicates the additional PWM pins on the ATmega168.)

// ATMEL ATMEGA1280 / ARDUINO
//
// 0-7 PE0-PE7   works
// 8-13 PB0-PB5  works
// 14-21 PA0-PA7 works
// 22-29 PH0-PH7 works
// 30-35 PG5-PG0 works
// 36-43 PC7-PC0 works
// 44-51 PJ7-PJ0 works
// 52-59 PL7-PL0 works
// 60-67 PD7-PD0 works
// A0-A7 PF0-PF7
// A8-A15 PK0-PK7


// these arrays map port names (e.g. port B) to the
// appropriate addresses for various functions (e.g. reading
// and writing)
#ifndef __RL78__
const uint16_t PROGMEM port_to_mode_PGM[] = {
	NOT_A_PORT,
	NOT_A_PORT,
	(uint16_t) &DDRB,
	(uint16_t) &DDRC,
	(uint16_t) &DDRD,
};

const uint16_t PROGMEM port_to_output_PGM[] = {
	NOT_A_PORT,
	NOT_A_PORT,
	(uint16_t) &PORTB,
	(uint16_t) &PORTC,
	(uint16_t) &PORTD,
};

const uint16_t PROGMEM port_to_input_PGM[] = {
	NOT_A_PORT,
	NOT_A_PORT,
	(uint16_t) &PINB,
	(uint16_t) &PINC,
	(uint16_t) &PIND,
};

const uint8_t PROGMEM digital_pin_to_port_PGM[] = {
	PD, /* 0 */
	PD,
	PD,
	PD,
	PD,
	PD,
	PD,
	PD,
	PB, /* 8 */
	PB,
	PB,
	PB,
	PB,
	PB,
	PC, /* 14 */
	PC,
	PC,
	PC,
	PC,
	PC,
};

const uint8_t PROGMEM digital_pin_to_bit_mask_PGM[] = {
	_BV(0), /* 0, port D */
	_BV(1),
	_BV(2),
	_BV(3),
	_BV(4),
	_BV(5),
	_BV(6),
	_BV(7),
	_BV(0), /* 8, port B */
	_BV(1),
	_BV(2),
	_BV(3),
	_BV(4),
	_BV(5),
	_BV(0), /* 14, port C */
	_BV(1),
	_BV(2),
	_BV(3),
	_BV(4),
	_BV(5),
};

const uint8_t PROGMEM digital_pin_to_timer_PGM[] = {
	NOT_ON_TIMER, /* 0 - port D */
	NOT_ON_TIMER,
	NOT_ON_TIMER,
	// on the ATmega168, digital pin 3 has hardware pwm
#if defined(__AVR_ATmega8__)
	NOT_ON_TIMER,
#else
	TIMER2B,
#endif
	NOT_ON_TIMER,
	// on the ATmega168, digital pins 5 and 6 have hardware pwm
#if defined(__AVR_ATmega8__)
	NOT_ON_TIMER,
	NOT_ON_TIMER,
#else
	TIMER0B,
	TIMER0A,
#endif
	NOT_ON_TIMER,
	NOT_ON_TIMER, /* 8 - port B */
	TIMER1A,
	TIMER1B,
#if defined(__AVR_ATmega8__)
	TIMER2,
#else
	TIMER2A,
#endif
	NOT_ON_TIMER,
	NOT_ON_TIMER,
	NOT_ON_TIMER,
	NOT_ON_TIMER, /* 14 - port C */
	NOT_ON_TIMER,
	NOT_ON_TIMER,
	NOT_ON_TIMER,
	NOT_ON_TIMER,
};
#else

// temp Aono 2022/08/29
// #define PROGMEM
#if 0
const uint8_t PROGMEM digital_pin_to_port_PGM[] = {
		DIGITAL_PIN_0,
		DIGITAL_PIN_1,
		DIGITAL_PIN_2,
		DIGITAL_PIN_3,
		DIGITAL_PIN_4,
		DIGITAL_PIN_5,
		DIGITAL_PIN_6,
		DIGITAL_PIN_7,
		DIGITAL_PIN_8,
		DIGITAL_PIN_9,
		DIGITAL_PIN_10,
		DIGITAL_PIN_11,
		DIGITAL_PIN_12,
		DIGITAL_PIN_13,
		DIGITAL_PIN_14,
		DIGITAL_PIN_15,
		DIGITAL_PIN_16,
		DIGITAL_PIN_17
};

#undef _offset

//#define _VB(mask) (uint8_t)(__builtin_log((uint8_t)mask) / __builtin_log(2))
#define _VB(mask) (uint8_t)(mask/2)

const uint8_t PROGMEM digital_pin_to_bit_PGM[] = {
		_VB(DIGITAL_PIN_MASK_0),
		_VB(DIGITAL_PIN_MASK_1),
		_VB(DIGITAL_PIN_MASK_2),
		_VB(DIGITAL_PIN_MASK_3),
		_VB(DIGITAL_PIN_MASK_4),
		_VB(DIGITAL_PIN_MASK_5),
		_VB(DIGITAL_PIN_MASK_6),
		_VB(DIGITAL_PIN_MASK_7),
		_VB(DIGITAL_PIN_MASK_8),
		_VB(DIGITAL_PIN_MASK_9),
		_VB(DIGITAL_PIN_MASK_10),
		_VB(DIGITAL_PIN_MASK_11),
		_VB(DIGITAL_PIN_MASK_12),
		_VB(DIGITAL_PIN_MASK_13),
		_VB(DIGITAL_PIN_MASK_14),
		_VB(DIGITAL_PIN_MASK_15),
		_VB(DIGITAL_PIN_MASK_16),
		_VB(DIGITAL_PIN_MASK_17)

};

const uint8_t PROGMEM digital_pin_to_bit_mask_PGM[] = {
		DIGITAL_PIN_MASK_0,
		DIGITAL_PIN_MASK_1,
		DIGITAL_PIN_MASK_2,
		DIGITAL_PIN_MASK_3,
		DIGITAL_PIN_MASK_4,
		DIGITAL_PIN_MASK_5,
		DIGITAL_PIN_MASK_6,
		DIGITAL_PIN_MASK_7,
		DIGITAL_PIN_MASK_8,
		DIGITAL_PIN_MASK_9,
		DIGITAL_PIN_MASK_10,
		DIGITAL_PIN_MASK_11,
		DIGITAL_PIN_MASK_12,
		DIGITAL_PIN_MASK_13,
		DIGITAL_PIN_MASK_14,
		DIGITAL_PIN_MASK_15,
		DIGITAL_PIN_MASK_16,
		DIGITAL_PIN_MASK_17

};

#endif

#endif /*__RL78__*/


// These serial port names are intended to allow libraries and architecture-neutral
// sketches to automatically default to the correct port name for a particular type
// of use.  For example, a GPS module would normally connect to SERIAL_PORT_HARDWARE_OPEN,
// the first hardware serial port whose RX/TX pins are not dedicated to another use.
//
// SERIAL_PORT_MONITOR        Port which normally prints to the Arduino Serial Monitor
//
// SERIAL_PORT_USBVIRTUAL     Port which is USB virtual serial
//
// SERIAL_PORT_LINUXBRIDGE    Port which connects to a Linux system via Bridge library
//
// SERIAL_PORT_HARDWARE       Hardware serial port, physical RX & TX pins.
//
// SERIAL_PORT_HARDWARE_OPEN  Hardware serial ports which are open for use.  Their RX & TX
//                            pins are NOT connected to anything by default.
#define SERIAL_PORT_MONITOR   Serial
#define SERIAL_PORT_HARDWARE  Serial

#endif
// #endif
