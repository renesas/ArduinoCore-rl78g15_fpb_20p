/*
  pintable.h
  Copyright (c) 2015 Nozomu Fujita. All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/
#ifndef _PINTABLE_H_
#define _PINTABLE_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pins_arduino.h>

#ifdef __cplusplus
extern "C" {
#endif


#define getPortModeRegisterAddr(port)		    ((volatile uint8_t*)(ADDR_PORT_MODE_REG + port))			/*!< Base Address of Port Mode Register	*/
#define getPortPullUpRegisterAddr(port)		    ((volatile uint8_t*)(ADDR_PORT_PULL_UP_REG + port))			/*!< Base Address of Port Pull-up Register	*/
#define getPortOutputModeRegisterAddr(port)	    ((volatile uint8_t*)(ADDR_PORT_OUT_MODE_REG + port))		/*!< Base Address of Port Output Mode Register	*/
#define getPortRegisterAddr(port)		        ((volatile uint8_t*)(ADDR_PORT_REG + port))					/*!< Base Address of Port Register	*/
#define getPortModeControlRegisterAddr(port)	((volatile uint8_t*)(ADDR_PORT_MODE_CONTROL_REG + port))	/*!< Base Address of Port Mode Control Register	*/
#define getPortOutCurControlRegisterAddr()		((volatile uint8_t*)(ADDR_PORT_OUT_CUR_CONTROL_REG))		/*!< Base Address of Port Output Current Control Register	*/

typedef struct {
  uint8_t mask;
  uint8_t bit;
  uint8_t timer;
  uint8_t pmc;
  uint8_t pm;
  uint8_t pu;
  uint8_t pom;
  volatile uint8_t* portModeRegisterAddr;
  volatile uint8_t* portPullUpRegisterAddr;
  volatile uint8_t* portOutputModeRegisterAddr;
  volatile uint8_t* portRegisterAddr;
  volatile uint8_t* portModeControlRegisterAddr;
} PinTableType;



extern const uint8_t digital_pin[NUM_DIGITAL_PINS] __attribute__((weak));
const uint8_t digital_pin[NUM_DIGITAL_PINS] = {
    DIGITAL_PIN_0,DIGITAL_PIN_1,DIGITAL_PIN_2,DIGITAL_PIN_3,DIGITAL_PIN_4,
    DIGITAL_PIN_5,DIGITAL_PIN_6,DIGITAL_PIN_7,DIGITAL_PIN_8,DIGITAL_PIN_9,
    DIGITAL_PIN_10,DIGITAL_PIN_11,DIGITAL_PIN_12,DIGITAL_PIN_13,DIGITAL_PIN_14,
    DIGITAL_PIN_15,DIGITAL_PIN_16,DIGITAL_PIN_17
};
extern const uint8_t pin_mask[NUM_DIGITAL_PINS] __attribute__((weak));
const uint8_t pin_mask[NUM_DIGITAL_PINS] = {
    DIGITAL_PIN_MASK_0,DIGITAL_PIN_MASK_1,DIGITAL_PIN_MASK_2,DIGITAL_PIN_MASK_3,DIGITAL_PIN_MASK_4,
    DIGITAL_PIN_MASK_5,	DIGITAL_PIN_MASK_6,	DIGITAL_PIN_MASK_7,	DIGITAL_PIN_MASK_8,	DIGITAL_PIN_MASK_9,
    DIGITAL_PIN_MASK_10,DIGITAL_PIN_MASK_11,DIGITAL_PIN_MASK_12,DIGITAL_PIN_MASK_13,DIGITAL_PIN_MASK_14,
    DIGITAL_PIN_MASK_15,DIGITAL_PIN_MASK_16,DIGITAL_PIN_MASK_17
};
extern const uint8_t pin_bit[NUM_DIGITAL_PINS] __attribute__((weak));
const uint8_t pin_bit[NUM_DIGITAL_PINS] = {
    DIGITAL_PIN_BIT_0,DIGITAL_PIN_BIT_1,DIGITAL_PIN_BIT_2,DIGITAL_PIN_BIT_3,DIGITAL_PIN_BIT_4,
    DIGITAL_PIN_BIT_5,DIGITAL_PIN_BIT_6,DIGITAL_PIN_BIT_7,DIGITAL_PIN_BIT_8,DIGITAL_PIN_BIT_9,
    DIGITAL_PIN_BIT_10,DIGITAL_PIN_BIT_11,DIGITAL_PIN_BIT_12,DIGITAL_PIN_BIT_13,DIGITAL_PIN_BIT_14,
    DIGITAL_PIN_BIT_15,DIGITAL_PIN_BIT_16,DIGITAL_PIN_BIT_17
};

extern const uint8_t pin_pmc[NUM_DIGITAL_PINS] __attribute__((weak));
const uint8_t pin_pmc[NUM_DIGITAL_PINS] = {
    DIGITAL_PIN_PMC_0,DIGITAL_PIN_PMC_1,DIGITAL_PIN_PMC_2,DIGITAL_PIN_PMC_3,DIGITAL_PIN_PMC_4,
    DIGITAL_PIN_PMC_5,	DIGITAL_PIN_PMC_6,	DIGITAL_PIN_PMC_7,	DIGITAL_PIN_PMC_8,	DIGITAL_PIN_PMC_9,
    DIGITAL_PIN_PMC_10,DIGITAL_PIN_PMC_11,DIGITAL_PIN_PMC_12,DIGITAL_PIN_PMC_13,DIGITAL_PIN_PMC_14,
    DIGITAL_PIN_PMC_15,DIGITAL_PIN_PMC_16,DIGITAL_PIN_PMC_17
};

/*
extern const uint8_t pin_pmc[NUM_DIGITAL_PINS] __attribute__((weak));
const uint8_t pin_pmc[NUM_DIGITAL_PINS] = {
    DIGITAL_PIN_PMCA_0,DIGITAL_PIN_PMCA_1,DIGITAL_PIN_PMCA_2,DIGITAL_PIN_PMCA_3,DIGITAL_PIN_PMCA_4,
    DIGITAL_PIN_PMCA_5,	DIGITAL_PIN_PMCA_6,	DIGITAL_PIN_PMCA_7,	DIGITAL_PIN_PMCA_8,	DIGITAL_PIN_PMCA_9,
    DIGITAL_PIN_PMCA_10,DIGITAL_PIN_PMCA_11,DIGITAL_PIN_PMCA_12,DIGITAL_PIN_PMCA_13,DIGITAL_PIN_PMCA_14,
    DIGITAL_PIN_PMCA_15,DIGITAL_PIN_PMCA_16,DIGITAL_PIN_PMCA_17
};


extern const uint8_t pin_ccde[NUM_DIGITAL_PINS] __attribute__((weak));
const uint8_t pin_ccde[NUM_DIGITAL_PINS] = {
    DIGITAL_PIN_CCDE_0,DIGITAL_PIN_CCDE_1,DIGITAL_PIN_CCDE_2,DIGITAL_PIN_CCDE_3,DIGITAL_PIN_CCDE_4,
    DIGITAL_PIN_CCDE_5,	DIGITAL_PIN_CCDE_6,	DIGITAL_PIN_CCDE_7,	DIGITAL_PIN_CCDE_8,	DIGITAL_PIN_CCDE_9,
    DIGITAL_PIN_CCDE_10,DIGITAL_PIN_CCDE_11,DIGITAL_PIN_CCDE_12,DIGITAL_PIN_CCDE_13,DIGITAL_PIN_CCDE_14,
    DIGITAL_PIN_CCDE_15,DIGITAL_PIN_CCDE_16,DIGITAL_PIN_CCDE_17
};
*/

extern const uint8_t pin_pm[NUM_DIGITAL_PINS] __attribute__((weak));
const uint8_t pin_pm[NUM_DIGITAL_PINS] = {
    DIGITAL_PIN_PM_0,DIGITAL_PIN_PM_1,DIGITAL_PIN_PM_2,DIGITAL_PIN_PM_3,DIGITAL_PIN_PM_4,
    DIGITAL_PIN_PM_5,DIGITAL_PIN_PM_6,DIGITAL_PIN_PM_7,DIGITAL_PIN_PM_8,DIGITAL_PIN_PM_9,
    DIGITAL_PIN_PM_10,DIGITAL_PIN_PM_11,DIGITAL_PIN_PM_12,DIGITAL_PIN_PM_13,DIGITAL_PIN_PM_14,
    DIGITAL_PIN_PM_15,DIGITAL_PIN_PM_16,DIGITAL_PIN_PM_17
};

extern const uint8_t pin_pu[NUM_DIGITAL_PINS] __attribute__((weak));
const uint8_t pin_pu[NUM_DIGITAL_PINS] = {
    DIGITAL_PIN_PU_0,DIGITAL_PIN_PU_1,DIGITAL_PIN_PU_2,DIGITAL_PIN_PU_3,DIGITAL_PIN_PU_4,
    DIGITAL_PIN_PU_5,DIGITAL_PIN_PU_6,DIGITAL_PIN_PU_7,DIGITAL_PIN_PU_8,DIGITAL_PIN_PU_9,
    DIGITAL_PIN_PU_10,DIGITAL_PIN_PU_11,DIGITAL_PIN_PU_12,DIGITAL_PIN_PU_13,DIGITAL_PIN_PU_14,
    DIGITAL_PIN_PU_15,DIGITAL_PIN_PU_16,DIGITAL_PIN_PU_17
};

extern const uint8_t pin_pom[NUM_DIGITAL_PINS] __attribute__((weak));
const uint8_t pin_pom[NUM_DIGITAL_PINS] = {
    DIGITAL_PIN_POM_0,DIGITAL_PIN_POM_1,DIGITAL_PIN_POM_2,DIGITAL_PIN_POM_3,DIGITAL_PIN_POM_4,
    DIGITAL_PIN_POM_5,DIGITAL_PIN_POM_6,DIGITAL_PIN_POM_7,DIGITAL_PIN_POM_8,DIGITAL_PIN_POM_9,
    DIGITAL_PIN_POM_10,DIGITAL_PIN_POM_11,DIGITAL_PIN_POM_12,DIGITAL_PIN_POM_13,DIGITAL_PIN_POM_14,
    DIGITAL_PIN_POM_15,DIGITAL_PIN_POM_16,DIGITAL_PIN_POM_17
};


void getPinTable(uint8_t pin,PinTableType *pp);

#ifdef __cplusplus
};
#endif

#endif/*_PINTABLE_H_*/
