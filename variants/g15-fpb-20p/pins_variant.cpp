#include "pins_variant.h"
#include "wiring_private.h"
#include "wiring_private_tone.h"
#include "r_smc_entry.h"

/*
 * Pins descriptions
 */

const uint8_t A0 = PIN_A0;
const uint8_t A1 = PIN_A1;
const uint8_t A2 = PIN_A2;

/* tone pin set */
volatile unsigned short *g_tone_period_reg[TONE_CH_NUM] = {&TDR01,&TDR02,&TDR03};
volatile unsigned short *g_timer_tone_mode_reg[TONE_CH_NUM] = {&TMR01,&TMR02,&TMR03};
volatile unsigned short *g_timer_tone_clock_select_reg = &TPS0;
const uint8_t  tone_channel_table[TONE_CH_NUM]  = {PWM_PIN_0,PWM_PIN_13,PWM_PIN_3};
tone_func tone_ch[TONE_CH_NUM] =
{
    {
        .open  = R_Config_TAU0_1_Square_Wave_Create,
        .start = R_Config_TAU0_1_Square_Wave_Start,
        .stop = R_Config_TAU0_1_Square_Wave_Stop
    },
    {
        .open  = R_Config_TAU0_2_Square_Wave_Create,
        .start = R_Config_TAU0_2_Square_Wave_Start,
        .stop = R_Config_TAU0_2_Square_Wave_Stop
    },
    {
        .open  = R_Config_TAU0_3_Square_Wave_Create,
        .start = R_Config_TAU0_3_Square_Wave_Start,
        .stop = R_Config_TAU0_3_Square_Wave_Stop
    }
};


