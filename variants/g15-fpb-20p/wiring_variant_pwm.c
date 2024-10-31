#include "pins_variant.h"
#include "wiring_private.h"
#include "wiring_variant.h"
#include "r_smc_entry.h"

volatile unsigned short *g_timer_period_reg[PWM_CH_NUM] = {&TDR02};
volatile unsigned short *g_timer_duty_reg[PWM_CH_NUM]   = {&TDR03};
volatile unsigned short *g_timer_analog_mode_reg[PWM_CH_NUM] = {&TMR03};
volatile unsigned short *g_timer_analog_clock_select_reg = &TPS0;
const uint8_t  pwm_channel_table[PWM_CH_NUM]  = {PWM_PIN_3};


const uint8_t g_au8AnalogPinTable[NUM_ANALOG_INPUTS] = {
ANALOG_PIN_0, ANALOG_PIN_1, ANALOG_PIN_2};
const uint8_t g_analog_pin_input[NUM_ANALOG_INPUTS] = {PIN_A0, PIN_A1, PIN_A2};

Pwm_func pwm_ch[PWM_CH_NUM] =
{
    {
        .open  = (void*)R_Config_TAU0_2_Create,
        .start = (void*)R_Config_TAU0_2_Start,
        .cycle = CYCLE_VALUE,
    }
};


