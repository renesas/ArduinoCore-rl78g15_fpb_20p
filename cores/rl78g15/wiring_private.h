#ifndef WiringPrivate_h
#define WiringPrivate_h


#include <stdio.h>
#include <stdarg.h>
#include <Arduino.h>
#include "wiring_variant.h"

#ifdef __cplusplus
extern "C"{
#endif

fInterruptFunc_t g_afInterruptFuncTable[EXTERNAL_NUM_INTERRUPTS] __attribute__((weak));

#define CYCLE_VALUE    (0)

#define TAU_OPERATION_CLOCK       (0xC000U)    /* operation clock set by PRS register */
#define CK00_CK01_OPERATION       (0x000F)    /* Selection of operation clock CK00, CK01 */
#define CK02_OPERATION            (0x0300)    /* Selection of operation clock CK02 */
#define CK03_OPERATION            (0x3000)    /* Selection of operation clock CK03 */
#define TIMEOUT_MAX_VAL           (65535)
#define PULSE_INTERUPT            (1)

typedef struct {
    void (*open)();
    void (*start)();
    uint16_t cycle;
} Pwm_func;

int8_t get_pwm_channel(uint8_t pwm_num);
int8_t get_analog_channel(uint8_t analog_num);
#define PULSE_IN_CH_NUM            (1)
int8_t get_tone_channel(uint8_t tone_num);

typedef struct {
    void (*open)();
    void (*start)();
    void (*stop)();
    void (*get_width)(uint32_t * const width);
} pulse_in_func;

int8_t get_pulse_in_channel(uint8_t pulse_in_num);

typedef void (*voidFuncPtr)(void);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* WiringPrivate_h */

