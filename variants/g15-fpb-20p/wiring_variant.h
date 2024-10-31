#ifndef WiringVariante_h
#define WiringVariante_h

#include <stdio.h>
#include <stdarg.h>
#include "Arduino.h"
#include "utilities.h"

#ifdef __cplusplus
extern "C"{
#endif

#define ANALOG_PIN_START_NUMBER    (14)
//#define MAX_CYCLIC_HANDLER         (8)

#define EXTERNAL_NUM_INTERRUPTS (3)

/* PWM defines. */
#define PWM_MIN            0L
#define PWM_MAX            255L

/* External interrupt define. */
#define EXTERNAL_INTERRUPT_0    0
#define EXTERNAL_INTERRUPT_1    2
#define EXTERNAL_INTERRUPT_2    3

#define    PWM_CH_NUM    (1)


#define FREQUENCY_MIN_VAL    (500)
#define FREQUENCY_MAX_VAL    (8000000)

#ifdef __cplusplus
} // extern "C"
#endif

// extern uint32_t R_BSP_GetFclkFreqHz(void);

#endif /* WiringVariante_h */



