#ifndef _PINS_VARIANT_H_
#define _PINS_VARIANT_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#ifndef configCPU_CLOCK_HZ
#define configCPU_CLOCK_HZ 					(16000000)	// CPUの動作周波数（RTOS未使用時に定義）
#endif

/* IIC Definition */
#define IIC_CHANNEL0 (0)
// #define IIC_CHANNEL1 (1)

#define CHECK_OUTPUT_INHIBIT_RL78(p) ((p) == 5 || (p) == 6 || (p) == 8 || (p) == 9  || (p) == 10 || (p) == 11 || (p) == 12)

#define digitalPinHasPWM(p)         ((p) == 3)

/*----------------------------------------------------------------------------
 *        Pins
 *----------------------------------------------------------------------------*/

#define NUM_DIGITAL_PINS            20
#define NUM_ANALOG_INPUTS           3
#define analogInputToDigitalPin(p)  ((p < 3) ? (p) + 14 : -1)

#define PIN_WIRE_SDA        (19)
#define PIN_WIRE_SCL        (18)

#define BUILTIN_LED1 7
#define BUILTIN_LED2 4
#define LED_BUILTIN  BUILTIN_LED1

#define LED_ON  LOW
#define LED_OFF HIGH

#define PIN_A0   (14)
#define PIN_A1   (15)
#define PIN_A2   (16)

extern const uint8_t A0;
extern const uint8_t A1;
extern const uint8_t A2;

#define digitalPinToInterrupt(p)  ((p) == 0 ? 0 : ((p) == 2 ? 1 : (p) == 3 ? 2 : NOT_AN_INTERRUPT))  // RL78/G15

#ifdef __RL78__
/***************************************************************************/
/*    Macro Definitions                                                    */
/***************************************************************************/
#define ADDR_PORT_REG			0xFFFFFF00
#define ADDR_PORT_MODE_REG		0xFFFFFF20
#define ADDR_PORT_PULL_UP_REG	0xFFFF0030
#define	ADDR_PORT_IN_MODE_REG	0xFFFF0040
#define ADDR_PORT_OUT_MODE_REG	0xFFFF0050
#define ADDR_PORT_MODE_CONTROL_REG		0xFFFF0060

#define ANALOG_PIN_0		7		// ANI7 (A0 J4-1 DIGITAL_PIN_14)
#define ANALOG_PIN_1		8		// ANI8 (A1 DIGITAL_PIN_15)
#define ANALOG_PIN_2		1		// ANI1 (A2 DIGITAL_PIN_16)

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
// only the bit num (not port) 0->01, 1->02, 2->04, 3->08, 4->10, 5->20, 6->40, 7->80
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
#define DIGITAL_PIN_PMC_14		0x08	/* P23	*/
#define DIGITAL_PIN_PMC_15		0x04	/* P22	*/
#define DIGITAL_PIN_PMC_16		0x04	/* P02	*/
#define DIGITAL_PIN_PMC_17		DIGITAL_PIN_PMC_13	/* P05	*/
#define DIGITAL_PIN_PMC_18		0x40	/* P06	*/
#define DIGITAL_PIN_PMC_19		0x80	/* P07	*/

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
#define DIGITAL_PIN_PU_14		0x08	/* P23	*/
#define DIGITAL_PIN_PU_15		0x04	/* P22	*/
#define DIGITAL_PIN_PU_16		0x04	/* P02	*/
#define DIGITAL_PIN_PU_17		DIGITAL_PIN_PU_13	/* P05	*/
#define DIGITAL_PIN_PU_18		0x40	/* P06	*/
#define DIGITAL_PIN_PU_19		0x80	/* P07	*/

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
#define DIGITAL_PIN_POM_14		0x00	/* P23(REF)	*/
#define DIGITAL_PIN_POM_15		0x04	/* P22	*/
#define DIGITAL_PIN_POM_16		0x00	/* P02	*/
#define DIGITAL_PIN_POM_17		DIGITAL_PIN_POM_13	/* P05	*/
#define DIGITAL_PIN_POM_18		0x40	/* P06	*/
#define DIGITAL_PIN_POM_19		0x80	/* P07	*/

#endif

#define PWM_PIN_0			0		// TO1
#define PWM_PIN_3			3		// TO3
#define PWM_PIN_13			13		// TO2

#endif /* ARDUINO_H */


