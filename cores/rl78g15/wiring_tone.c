/*
 * writing_tone.c
 *
 *  Created on: 2021/11/02
 *      Author: hmU11983
 */

#include "pins_arduino.h"
/* 1112 nhu add */
#include "wiring_private.h"
#include "pintable.h"
#include "r_smc_entry.h"
/* 1112 nhu add */


volatile long timer1_toggle_count;
volatile uint8_t *timer1_pin_port;
volatile uint8_t timer1_pin_mask;
volatile long timer2_toggle_count;
volatile uint8_t *timer2_pin_port;
volatile uint8_t timer2_pin_mask;

/* 1112 nhu add */
extern uint32_t R_BSP_GetFclkFreqHz(void);

/* ★pow関数の代わり★ */
uint16_t pow2n(uint8_t fact);

/* tone pin set */
volatile unsigned short *g_tone_period_reg[TONE_CH_NUM] = {&TDR01,&TDR02,&TDR03};
volatile unsigned short *g_timer_tone_mode_reg[TONE_CH_NUM] = {&TMR01,&TMR02,&TMR03};
volatile unsigned short *g_timer_tone_clock_select_reg = &TPS0;
const uint8_t  tone_channel_table[TONE_CH_NUM]  = {PWM_PIN_0,PWM_PIN_13,PWM_PIN_3};
tone_func tone_ch[TONE_CH_NUM] =
{
    {
        .open  = (void*)R_Config_TAU0_1_Square_Wave_Create,
        .start = (void*)R_Config_TAU0_1_Square_Wave_Start,
        .stop = (void*)R_Config_TAU0_1_Square_Wave_Stop
    },
    {
        .open  = (void*)R_Config_TAU0_2_Square_Wave_Create,
        .start = (void*)R_Config_TAU0_2_Square_Wave_Start,
        .stop = (void*)R_Config_TAU0_2_Square_Wave_Stop
    },
    {
        .open  = (void*)R_Config_TAU0_3_Square_Wave_Create,
        .start = (void*)R_Config_TAU0_3_Square_Wave_Start,
        .stop = (void*)R_Config_TAU0_3_Square_Wave_Stop
    }
};

int8_t get_tone_channel(uint8_t tone_num)
{
    uint8_t tone_cnt;

    for(tone_cnt=0;tone_cnt<TONE_CH_NUM;tone_cnt++)
    {
        if (tone_num == tone_channel_table[tone_cnt])
        {
            return tone_cnt;
        }
    }
    return -1;
}

/* 1112 nhu add */

// frequency (in hertz) and duration (in milliseconds).

void tone(uint8_t pin, unsigned int frequency, unsigned long duration)
{

  /* 1112 Nhu add */
    uint8_t i;
    uint8_t tone_pin_flg = 0;
    unsigned long tone_interrupt_cnt;
    int8_t tone_channel = get_tone_channel(pin);
    uint32_t fclk_frequency = 0;
    uint32_t timer_frequency = 0;
    uint32_t timer_clock_mode = 0;
    uint32_t operating_clock_select = 0;

    /* If it is not a tone output pin, do nothing and exit */
    for(i = 0; i < TONE_CH_NUM; i ++)
    {
        if(pin == tone_channel_table[i])
        {
            tone_pin_flg = 1;
            i = TONE_CH_NUM;
        }
        else
        {
            tone_pin_flg = 0;
        }
    }

    if(tone_pin_flg == 1)
    {

        /* Initializes the tone channel */
        tone_ch[tone_channel].open();

        /* Frequency Set
         * Frequency of square wave output from TOmn = Frequency of count clock/{(Set value of TDRmn + 1) × 2}
         * Set value of TDRmn = (Frequency of count clock / 2 x Frequency of square wave output from TOmn) - 1
         */
        fclk_frequency = R_BSP_GetFclkFreqHz();

        /* Get timer frequency */
        timer_clock_mode = *((uint32_t*)g_timer_tone_mode_reg[tone_channel]) & TAU_OPERATION_CLOCK;

        if (timer_clock_mode == _4000_TAU_CLOCK_SELECT_CKM2)
        {
            operating_clock_select = *((uint32_t*)g_timer_tone_clock_select_reg) & CK02_OPERATION;
            if(operating_clock_select == _0000_TAU_CKM2_FCLK_1)
            {
                timer_frequency = fclk_frequency/2;
            }
            else
            {
                operating_clock_select = operating_clock_select >> 8;
//                timer_frequency = fclk_frequency/( pow(2, 2 * operating_clock_select));    /*  fclk/2^2 ~ 2^6 */
                timer_frequency = fclk_frequency/( pow2n(2 * operating_clock_select));    /* ★ */

            }
        }
        else if  (timer_clock_mode == _C000_TAU_CLOCK_SELECT_CKM3)
        {
            operating_clock_select = *((uint32_t*)g_timer_tone_clock_select_reg) & CK03_OPERATION;

            operating_clock_select = operating_clock_select >> 12;
//            timer_frequency = fclk_frequency/( pow(2,(2 * operating_clock_select +8)));    /* fclk/2^8 ~ 2^14 */
            timer_frequency = fclk_frequency/( pow2n(2 * operating_clock_select +8));    /* ★ */

        }
        else /* CK00, CK01 Clock Select */
        {
            operating_clock_select = *((uint32_t*)g_timer_tone_clock_select_reg) & CK00_CK01_OPERATION;
//            timer_frequency = fclk_frequency/( pow(2,operating_clock_select));    /* ckm00, ckm01 - fclk/2^0 ~ 2^15 */
            timer_frequency = fclk_frequency/( pow2n(operating_clock_select));    /* ★ */

        }

        /* 500 Hz <= frequency <= 65535Hz */
        frequency = min(max(frequency, FREQUENCY_MIN_VAL), 65535);

        *((uint32_t*)g_tone_period_reg[tone_channel]) = (timer_frequency / 2 / frequency) - 1;

        tone_ch[tone_channel].start();

        if(duration != 0)
        {
            delay(duration);
            noTone(pin);
        }
    }
}

// XXX: this function only works properly for timer 2 (the only one we use
// currently).  for the others, it should end the tone, but won't restore
// proper PWM functionality for the timer.
void disableTimer(uint8_t _timer)
{

}

void noTone(uint8_t pin)
{
    int8_t tone_channel = get_tone_channel(pin);
    if (-1 == tone_channel)
    {
        ;
    }
    else
    {
    tone_ch[tone_channel].stop();
    }
}


