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

#ifdef __cplusplus
};
#endif

#endif/*_PINTABLE_H_*/
