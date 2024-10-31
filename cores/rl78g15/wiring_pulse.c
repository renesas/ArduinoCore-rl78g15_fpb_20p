#include "wiring_private.h"
#include "pins_arduino.h"
#include "pintable.h"
#include "r_smc_entry.h"
extern volatile uint8_t g_tau0_ch0_interrupt_flag;
extern volatile uint8_t g_tau0_ch3_interrupt_flag;
extern uint32_t R_BSP_GetFclkFreqHz(void);
volatile uint8_t g_pulse_enable_interrupt_flag = 0;
volatile unsigned short *g_timer_pulse_mode_reg[PULSE_IN_CH_NUM] = {&TMR03};
volatile unsigned short *g_timer_pulse_clock_select_reg = &TPS0;
volatile unsigned short *g_timer_timeout_data_reg = &TDR00;
volatile unsigned short *g_timer_timeout_mode_reg = &TMR00;
const uint8_t  pulse_in_channel_table[PULSE_IN_CH_NUM]  = {PWM_PIN_3};

pulse_in_func pulse_in_ch[PULSE_IN_CH_NUM] =
{
	{
		.open  = (void*)R_Config_TAU0_0_3_Measure_Signal_Create,
		.start = (void*)R_Config_TAU0_0_3_Measure_Signal_Start,
		.stop = (void*)R_Config_TAU0_0_3_Measure_Signal_Stop,
		.get_width = (void*)R_Config_TAU0_3_Measure_Signal_Get_PulseWidth,
	},
};

/* ★pow関数の代わり★ */
uint16_t pow2n(uint8_t fact);

int8_t get_pulse_in_channel(uint8_t pulse_in_num)
{
	uint8_t pulse_in_cnt;

	for(pulse_in_cnt=0;pulse_in_cnt<PULSE_IN_CH_NUM;pulse_in_cnt++)
	{
		if (pulse_in_num == pulse_in_channel_table[pulse_in_cnt])
		{
			return pulse_in_cnt;
		}
	}
	return -1;
}

static uint32_t get_timer_frequency(uint32_t clock_mode);



/* Measures the length (in microseconds) of a pulse on the pin; state is HIGH
 * or LOW, the type of pulse to measure.  Works on pulses from 2-3 microseconds
 * to 3 minutes in length, but must be called at least a few dozen microseconds
 * before the start of the pulse. */

unsigned long pulseIn(uint8_t pin, uint8_t state, unsigned long timeout)
{
	uint8_t i;
	uint8_t pulse_in_flg = 0;
	uint8_t l_tau_interrupt_flag = 0;
	uint32_t Result = 0;
	uint32_t timer_clock_mode = 0;
	uint32_t pulse_frequency = 0;
	uint32_t timeout_frequency = 0;
	g_pulse_enable_interrupt_flag = 1;
	int8_t pulse_in_channel = get_pulse_in_channel(pin);

	/* If it is not a pulse input pin, do nothing and exit */
	for(i = 0; i < PULSE_IN_CH_NUM; i ++)
	{
		if(pin == pulse_in_channel_table[i])
		{
			pulse_in_flg = 1;
			i = PULSE_IN_CH_NUM;
		}
		else
		{
			pulse_in_flg = 0;
		}
	}

	if(pulse_in_flg == 1)
	{
		/* Timer create */
		pulse_in_ch[pulse_in_channel].open();

		/* State Set */
		if(state == LOW)
		{
			*((uint32_t*)g_timer_pulse_mode_reg[pulse_in_channel]) |= _0200_TAU_TRIGGER_TIMN_BOTH | _0080_TAU_TIMN_EDGE_BOTH_LOW;
		}
		else
		{
			*((uint32_t*)g_timer_pulse_mode_reg[pulse_in_channel]) |= _00C0_TAU_TIMN_EDGE_BOTH_HIGH;
		}

		/* Get timeout frequency */
		timer_clock_mode = *((uint32_t*)g_timer_timeout_mode_reg) & TAU_OPERATION_CLOCK;
		timeout_frequency = get_timer_frequency(timer_clock_mode);

		/* Timeout Set */
		timeout = min(timeout, TIMEOUT_MAX_VAL);
		//*((uint32_t*)g_timer_timeout_data_reg) = ((timeout * timeout_frequency/1000000)-1);
		*g_timer_timeout_data_reg = timeout - 1;

		/* Timer Start */
		pulse_in_ch[pulse_in_channel].start();

		/* Get width */
				switch(pin)
				{
					case PWM_PIN_3:
						while((g_tau0_ch3_interrupt_flag == 0) && (g_tau0_ch0_interrupt_flag == 0));    	/* Wait get width */
						if(0  != g_tau0_ch3_interrupt_flag)
						{
							l_tau_interrupt_flag = 1;
						}
						g_tau0_ch3_interrupt_flag = 0;
						break;
					default:
						break;
					}
			/* Timer Stop */
			pulse_in_ch[pulse_in_channel].stop();
			if(0 != l_tau_interrupt_flag)
			{
				pulse_in_ch[pulse_in_channel].get_width(&Result);	/* Store capture value */

				/* Get pulse frequency */
				timer_clock_mode = *((uint32_t*)g_timer_pulse_mode_reg[pulse_in_channel]) & TAU_OPERATION_CLOCK;
				pulse_frequency = get_timer_frequency(timer_clock_mode);

				Result = Result * (1000000/pulse_frequency);
			}
			else
			{
				Result = 0;
			}


			g_tau0_ch0_interrupt_flag = 0;

	}
	return Result;
}

static uint32_t get_timer_frequency(uint32_t clock_mode)
{
	uint32_t fclk_frequency = 0;
	uint32_t timer_frequency = 0;
	uint32_t operating_clock_select = 0;

	fclk_frequency = R_BSP_GetFclkFreqHz();

	if (clock_mode == _4000_TAU_CLOCK_SELECT_CKM2)
	{
		operating_clock_select = *((uint32_t*)g_timer_pulse_clock_select_reg) & CK02_OPERATION;
		if(operating_clock_select == _0000_TAU_CKM2_FCLK_1)
		{
			timer_frequency = fclk_frequency/2;
		}
		else
		{
			operating_clock_select = operating_clock_select >> 8;
//			timer_frequency = fclk_frequency/( pow(2, 2 * operating_clock_select));	/*  fclk/2^2 ~ 2^6 */
			timer_frequency = fclk_frequency/( pow2n(2 * operating_clock_select));    /* ★ */
		}
	}
	else if  (clock_mode == _C000_TAU_CLOCK_SELECT_CKM3)
	{
		operating_clock_select = *((uint32_t*)g_timer_pulse_clock_select_reg) & CK03_OPERATION;

		operating_clock_select = operating_clock_select >> 12;
//		timer_frequency = fclk_frequency/( pow(2,(2 * operating_clock_select +8)));	/* fclk/2^8 ~ 2^14 */
		timer_frequency = fclk_frequency/( pow2n(2 * operating_clock_select+8));    /* ★ */
	}
	else /* CK00, CK01 Clock Select */
	{
		operating_clock_select = *((uint32_t*)g_timer_pulse_clock_select_reg) & CK00_CK01_OPERATION;
//		timer_frequency = fclk_frequency/( pow(2,operating_clock_select));	/* ckm00, ckm01 - fclk/2^0 ~ 2^15 */
		timer_frequency = fclk_frequency/( pow2n(operating_clock_select));    /* ★ */
	}
	return timer_frequency;
}
