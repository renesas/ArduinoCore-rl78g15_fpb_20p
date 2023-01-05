/*
 wiring_analog.c - analog input and output
 Part of Arduino - http://www.arduino.cc/

 Copyright (c) 2005-2006 David A. Mellis

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

 Modified 28 September 2010 by Mark Sproul

 $Id: wiring.c 248 2007-02-03 15:36:30Z mellis $
 */
/*
 * Modified  4 Mar  2017 by Yuuki Okamiya for RL78/G13
 */
#include "wiring_private.h"
#include "pins_arduino.h"

#ifdef __RL78__
#include "pintable.h"
#include "r_smc_entry.h"
// #include "Config_TAU0_0.h"
#include "Config_TAU0_2.h"
#include "Config_TAU0_25PWM.h"
#include "Config_ADC.h"

#include "main.h"  // 使用する関数を定義

extern uint8_t g_adc_int_flg;
static uint8_t g_u8AnalogReference = DEFAULT;
// static uint8_t g_u8SwPwmTicksCount = 0;
// uint8_t g_u8ADUL = 0xFF;
// uint8_t g_u8ADLL = 0x00;
boolean g_bAdcInterruptFlag = false;

uint16_t g_u16ADUL;
uint16_t g_u16ADLL;

/* ★pow関数の代わり★ */
uint16_t pow2n(uint8_t fact);
const uint16_t  ans[16] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768};

/* 1027 Nhu add */
extern uint32_t R_BSP_GetFclkFreqHz(void);
/* 1027 Nhu add */

/* 1008 Mitsugi add */
/* Match to the value of PWM_PIN */
volatile unsigned short *g_timer_period_reg[PWM_CH_NUM] = {&TDR02,&TDR02};
volatile unsigned short *g_timer_duty_reg[PWM_CH_NUM]   = {&TDR03,&TDR05};
volatile unsigned short *g_timer_analog_mode_reg[PWM_CH_NUM] = {&TMR03,&TMR03};
volatile unsigned short *g_timer_analog_clock_select_reg = &TPS0;
const uint8_t  pwm_channel_table[PWM_CH_NUM]  = {PWM_PIN_3,PWM_PIN_9};

static void _analogPinRead(uint8_t pin);
static int _analogRead(uint8_t u8ADS);
static int _analogDuty(int val, uint16_t frequency);
static uint16_t _analogFrequency (uint8_t pin, uint32_t u32Hz);

/* 追加 */
extern const PinTableType * pinTablelist[NUM_DIGITAL_PINS];

// extern unsigned long _COM_ulrem(unsigned long x, unsigned long y);
// extern unsigned long _COM_uldiv(unsigned long x, unsigned long y);
// 2022/09/02
#if defined(USE_PWM) && USE_PWM == 1
Pwm_func pwm_ch[PWM_CH_NUM] =
{
    {
        .open  = (void*)R_Config_TAU0_2_Create,
        .start = (void*)R_Config_TAU0_2_Start,
        .cycle = CYCLE_VALUE,
    },
    {
        .open  = (void*)R_Config_TAU0_25PWM_Create,
        .start = (void*)R_Config_TAU0_25PWM_Start,
        .cycle = CYCLE_VALUE,
    }
};
#else
Pwm_func pwm_ch[PWM_CH_NUM] =
{
    {
        .open  = 0,
        .start = 0,
        .cycle = 0,
    },
    {
        .open  = 0,
        .start = 0,
        .cycle = 0,
    }
};
#endif

int8_t get_pwm_channel(uint8_t pwm_num)
{
    uint8_t pwm_cnt;

    for(pwm_cnt=0;pwm_cnt<PWM_CH_NUM;pwm_cnt++)
    {
        if (pwm_num == pwm_channel_table[pwm_cnt])
        {
            return pwm_cnt;
        }
    }
    return -1;
}
/* 1008 Mitsugi add */

#endif /*__RL78__*/

/* 1006 Nhu add */
/***********************************************************************************************************************
* Function Name: analogReference
* Description  : The reference voltage used for analog input.
* Arguments    : mode -
*                    DEFAULT: use VDD as VREF(+)
*                    INTERNAL: use internal voltage as VREF(+)
*                    EXTERNAL: use AVREFP as VREF(+)
* Return Value : None
***********************************************************************************************************************/
void analogReference(uint8_t mode) 
{
    // can't actually set the register here because the default setting
    // will connect AVCC and the AREF pin, which would cause a short if
    // there's something connected to AREF.

//    R_Config_ADC_Create();
//    R_Config_ADC_Set_Reference(mode);
// 2022/07/21
    g_u8AnalogReference = mode;
}
/* 1006 Nhu add */

#ifdef __RL78__

bool g_u8AnalogWriteAvailableTable[NUM_DIGITAL_PINS] = {
false, false, false, false,
false, false, false, false,
false, false, false, false,
false, false, false, false,

};
const uint8_t g_au8AnalogPinTable[NUM_ANALOG_INPUTS] = {

ANALOG_PIN_0, ANALOG_PIN_1 ,ANALOG_PIN_2
};

volatile SwPwm g_SwPwm[NUM_SWPWM_PINS] = { { 0, 0, 0, 0, 0, 0 }, };

bool g_u8AnalogReadAvailableTable[NUM_ANALOG_INPUTS] = { 0 };

// 2022/08/23 Aono trial
// const uint8_t g_analog_pin_input[NUM_ANALOG_INPUTS] = {A1, A2};
const uint8_t g_analog_pin_input[NUM_ANALOG_INPUTS] = {14, 15, 16};
int8_t get_analog_channel(uint8_t analog_num)
{
    uint8_t analog_cnt;

    for(analog_cnt=0;analog_cnt<NUM_ANALOG_INPUTS;analog_cnt++)
    {
        if (analog_num == g_analog_pin_input[analog_cnt])
        {
            return analog_cnt;
        }
    }
    return -1;
}

#endif/*__RL78__*/

/***********************************************************************************************************************
* Function Name: analogRead
* Description  : Reads the value from the specified analog pin.
* Arguments    : analog_pin - the name of the analog input pin to read from A0 (=14) to A2 (=16)
* Return Value : The analog reading on the pin.
*                Although it is limited to the resolution of the analog to digital converter
*                (0-255 for 8 bits or 0-1023 for 10 bits).
***********************************************************************************************************************/
int analogRead(uint8_t analog_pin) {
	int s16Result = 0;
	uint8_t analog_read_flg = 0;
	uint8_t cnt;

	//アナログ入力端子の設定
	_analogPinRead(analog_pin);

	//アナログ入力端子ではない場合、何もしない終了する
	for(cnt = 0; cnt < NUM_ANALOG_INPUTS; cnt ++)
	{
		if(analog_pin == g_analog_pin_input[cnt])
		{
			analog_read_flg = 1;
			cnt = NUM_ANALOG_INPUTS;
		}
		else
		{
		analog_read_flg = 0;
		}
	}

	if(analog_read_flg == 1)
	{
	// アナログ値の読み込み
	s16Result = _analogRead(g_au8AnalogPinTable[get_analog_channel(analog_pin)]);
	}
	return s16Result;
}

// Right now, PWM output only works on the pins with
// hardware support.  These are defined in the appropriate
// pins_*.c file.  For the rest of the pins, we default
// to digital output.
/***********************************************************************************************************************
* Function Name: analogWrite
* Description  : Writes an analog value (PWM wave) to a pin.
* Arguments    : pin - the name of output pin (5,6,10,32)
*                value - Output PWM duty 0 ~ 255
* Return Value : None
***********************************************************************************************************************/
void analogWrite(uint8_t pin, int value) {
  if (pin < NUM_DIGITAL_PINS) {
    {
      value = min(max(value, PWM_MIN), PWM_MAX);
#if !defined(G23_FPB)
      u8Timer = getPinTable(pin)->timer;
      if (u8Timer == SWPWM_PIN) {
      /////////////////////
      Software PWM対応ピンの場合
      /////////////////////
#if defined(__RL78__)
        _startTAU0(TIMER_CLOCK);
        if (!g_u8AnalogWriteAvailableTable[pin]) {
          pinMode(pin, OUTPUT);        // 初期時のみ出力モードを設定
          g_u8AnalogWriteAvailableTable[pin] = true;
        }
        int i;
        int j = NUM_SWPWM_PINS;
        for (i = 0; i < NUM_SWPWM_PINS; i++) {
          if (!g_SwPwm[i].valid) {
            if (j >= NUM_SWPWM_PINS) {
              j = i;
            }
          } else if (g_SwPwm[i].pin == pin) {
            break;
          }
        }
        if (i >= NUM_SWPWM_PINS) {
          i = j;
        }
        if (i < NUM_SWPWM_PINS) {
          if (g_SwPwm[i].valid && g_SwPwm[i].pin == pin) {
            g_SwPwm[i].newValue = val;
          } else {
//            const PinTableType* p = getPinTable(pin);
            PinTableType* p;
            getPinTable(pin,p);
            g_SwPwm[i].valid = false;
            g_SwPwm[i].pin = pin;
            g_SwPwm[i].value = g_SwPwm[i].newValue = val;
            g_SwPwm[i].port = p->portRegisterAddr;
            g_SwPwm[i].mask = p->mask;
            g_SwPwm[i].valid = true;
          }
          if (!(TE0 & 0x0040)) { // No pin uses Software PWM
            _startTimerChannel( SW_PWM_TIMER, 0x0001, SWPWM_MIN, false, true);
          }
        } else {
          digitalWrite(pin,
          val >= ((PWM_MIN + PWM_MAX + 1) / 2) ? HIGH : LOW);
        }

#endif
      } else {
        ///////////////////////
        // PWM対応ピンの場合
        ///////////////////////
          _startTAU0(TIMER_CLOCK);

        if (((TE0 & 0x0001) == 0) || (TDR00 != g_u16TDR00)) {
          // Masterチャネルの設定
          TT0 |= 0x0001;            // タイマ停止
          TMR00 = PWM_MASTER_MODE;    // 動作モードの設定
          TDR00 = g_u16TDR00;        // PWM出力の周期の設定
          TO0 &= ~0x0001;            // タイマ出力の設定
          TOE0 &= ~0x0001;            // タイマ出力許可の設定
          // マスタチャネルのタイマ動作許可
          TS0 |= 0x00001;
        }

        u16Duty = (unsigned short) (((unsigned long) val * (g_u16TDR00 + 1)) / PWM_MAX);
        if (!g_u8AnalogWriteAvailableTable[pin]) {
          pinMode(pin, OUTPUT);            // 出力モードに設定
          digitalWrite(pin, LOW);

          // Slaveチャネルの設定
          _startTimerChannel(u8Timer, PWM_SLAVE_MODE, u16Duty, true, false);
          g_u8AnalogWriteAvailableTable[pin] = true;

        } else {
          _modifyTimerPeriodic(u8Timer, u16Duty);
        }
      }
    }
  }
#endif
/* 1006 Nhu add */
      /* 1008 Mitsugi add */
      uint8_t cnt;
      uint8_t analog_write_flg = 0;
      int8_t pwm_channel = get_pwm_channel(pin);

      if (-1 ==(*(int8_t*)get_pwm_channel))
      {
        NOP();
      }

      /* If it is not a PWM output terminal, do nothing and exit */
      for(cnt = 0; cnt < PWM_CH_NUM; cnt ++)
      {
        if(pin == pwm_channel_table[cnt])
        {
          analog_write_flg = 1;
          cnt = PWM_CH_NUM;
        }
        else
        {
          analog_write_flg = 0;
        }
      }

      if(analog_write_flg == 1)
      {
      pwm_ch[pwm_channel].open();

      /* Frequency Set */
      if(pwm_ch[pwm_channel].cycle == CYCLE_VALUE)
      {
        pwm_ch[pwm_channel].cycle = _analogFrequency(pin,FREQUENCY_MIN_VAL);
      }
      else
      {
        *((uint32_t*)g_timer_period_reg[pwm_channel]) = pwm_ch[pwm_channel].cycle;
      }


      /* Duty set */
      *((uint32_t*)g_timer_duty_reg[pwm_channel])   = _analogDuty(value, pwm_ch[pwm_channel].cycle);

      pwm_ch[pwm_channel].start();
      }
      /* 1008 Mitsugi add */
    }
  }
}

/***********************************************************************************************************************
* Function Name: analogWriteFrequency
* Description  : Sets the cycle. The default is 490Hz.
* Arguments    : Hz: cycle
* Return Value : None
***********************************************************************************************************************/
#ifdef __RL78__
void analogWriteFrequency(uint32_t Hz) {
  /* PWM output pulse cycle setting
  Pulse period = (TDR00 setting value + 1) x count clock period
  Example) When the pulse period is 2 [ms]
  2 [ms] = 1/32 [MHz] x (TDR00 setting + 1)
  TDR00 setting value = 63999 */

  pwm_ch[0].cycle = _analogFrequency(PWM_PIN_3,Hz);
  pwm_ch[1].cycle = _analogFrequency(PWM_PIN_9,Hz);

  /* 1008 Mitsugi add */
}

/***********************************************************************************************************************
* Function Name: analogWritePinFrequency
* Description  : Sets the cycle. The default is 490Hz.
* Arguments    : pin - the name of analog value (PWM wave) output pin (5,6,10,32)
*                Hz - cycle
* Return Value : None
***********************************************************************************************************************/
/* 1011 Nhu add */
void analogWritePinFrequency(uint8_t pin, uint32_t Hz) {
    /* PWM output pulse cycle setting
    Pulse period = (TDR00 setting value + 1) x count clock period
    Example) When the pulse period is 2 [ms]
    2 [ms] = 1/32 [MHz] x (TDR00 setting + 1)
    TDR00 setting value = 63999 */
    int8_t pwm_channel = get_pwm_channel(pin);
    pwm_ch[pwm_channel].cycle = _analogFrequency(pin, Hz);
}

static uint16_t _analogFrequency (uint8_t pin, uint32_t u32Hz)
{
    uint16_t Result;
    uint32_t fclk_frequency = 0;
    uint32_t timer_frequency = 0;
    uint32_t timer_clock_mode = 0;
    uint32_t operating_clock_select = 0;
    int8_t pwm_channel = get_pwm_channel(pin);

    fclk_frequency = R_BSP_GetFclkFreqHz();

  /* Get timer frequency */
    timer_clock_mode = *((uint32_t*)g_timer_analog_mode_reg[pwm_channel]) & TAU_OPERATION_CLOCK;

    if (timer_clock_mode == _4000_TAU_CLOCK_SELECT_CKM2) /* CK02 Clock Selected */
    {
      operating_clock_select = *((uint32_t*)g_timer_analog_clock_select_reg) & CK02_OPERATION;
      if(operating_clock_select == _0000_TAU_CKM2_FCLK_1)
      {
        timer_frequency = fclk_frequency/2;    /*  fclk/2 */
      }
      else
      {
        operating_clock_select = operating_clock_select >> 8;
        //timer_frequency = fclk_frequency/( pow(2, 2 * operating_clock_select));    /*  fclk/2^2 ~ 2^6 */
        timer_frequency = fclk_frequency/( pow2n(2 * operating_clock_select));    /* ★ */
      }
    }
    else if  (timer_clock_mode == _C000_TAU_CLOCK_SELECT_CKM3) /* CK03 Clock Selected */
    {
      operating_clock_select = *((uint32_t*)g_timer_analog_clock_select_reg) & CK03_OPERATION;

      operating_clock_select = operating_clock_select >> 12;
      //timer_frequency = fclk_frequency/( pow(2,(2 * operating_clock_select +8)));    /* fclk/2^8 ~ 2^14 */
      timer_frequency = fclk_frequency/( pow2n(2 * operating_clock_select +8));    /* ★ */
    }
    else /* CK00, CK01 Clock Selected */
    {
      operating_clock_select = *((uint32_t*)g_timer_analog_clock_select_reg) & CK00_CK01_OPERATION;
      //timer_frequency = fclk_frequency/( pow(2,operating_clock_select));    /* ckm00, ckm01 - fclk/2^0 ~ 2^15 */
      timer_frequency = fclk_frequency/( pow2n(operating_clock_select));    /* ★ */
    }

  /* 490 Hz <= frequency <= 8MHz */
  u32Hz = min(max(u32Hz, FREQUENCY_MIN_VAL), FREQUENCY_MAX_VAL);

  /* Pulse period = {Set value of TDRmn (master) + 1} × Count clock period
  Set value of TDRmn (master) = (Pulse period / Count clock period) - 1 */
  Result = (timer_frequency / u32Hz) - 1;

  return Result;
}

static int _analogDuty(int val, uint16_t frequency)
{
/*    Duty factor [0 ~ 255] = {Set value of TDRmp (slave)}/{Set value of TDRmn (master) + 1} × 255
  {Set value of TDRmp (slave)} = Duty factor * {Set value of TDRmn (master) + 1} / 255 */

  unsigned short u16Duty = 0;

  /* Duty set */
  if(val> PWM_MAX)
  {
    val = PWM_MAX;
  }
  else
  {
    u16Duty = (unsigned short) (((unsigned long) val    * (frequency + 1)) / PWM_MAX);
  }

  return u16Duty;
}

/* 1011 Nhu add */
static void _analogPinRead (uint8_t pin)
{
  if (g_u8AnalogReadAvailableTable[pin] == false) {
    // ピンモードをAnalogモードに変更
    //PinTableType *p;
    //PinTableType pin_tbl;
    //p = (PinTableType*)&pin_tbl;
    //getPinTable(pin,p);

    const PinTableType **pp;
    PinTableType *p;
    pp = &pinTablelist[pin];
    p = (PinTableType *)*pp;

    if (0!=p->pmc)
    {
      pinMode(pin, INPUT);
      /* アナログピンの場合PMCAをセットする */
// 2022/07/21 need modification
//      *p->portModeControlARegisterAddr |= (unsigned long)(p->pmca);
//      *p->portModeControlARegisterAddr &= (unsigned long)~(p->pmca);
 /* アナログピンの場合PMCをセットする */
      *p->portModeControlRegisterAddr |= (unsigned long)(p->pmc);
      g_u8AnalogReadAvailableTable[pin] = true;
    }
  }

  if (pin==29)
  {
    pin = 8;
  }
  else if (pin==40)
  {
    pin = 9;
  }
  else if (pin<ANALOG_PIN_START_NUMBER && pin < 2)
  {
    pin += 6;
  }
  else
  {
    pin -= ANALOG_PIN_START_NUMBER;
  }
}

static int _analogRead(uint8_t u8ADS) {
    int s16Result = 0;
#if defined(USE_ADC) && USE_ADC == 1
    uint8_t adc_end_flg = 0;

    R_Config_ADC_Set_ADChannel(u8ADS);

    while(0 == adc_end_flg)
    {
        g_adc_int_flg=0;

        R_Config_ADC_Set_OperationOn();  //ADCE=1 & wait
        delay(100);
        R_Config_ADC_Start();            //ADCS=1 & enable interrupt

        // 7. After STOP mode until AD interrupt occurs (loop processing)
        while (0 == g_adc_int_flg)
        {
            NOP();
        }
        delay(100);
        // 8. Snooze mode Off (interrupt stop)
        R_Config_ADC_Stop();

        // 9. Get AD conversion result
        R_Config_ADC_Get_Result_10bit ((uint16_t*) &s16Result);

        adc_end_flg = 1;
    }
    // 10.AD Comparator Off
    R_Config_ADC_Set_OperationOff();

    // 11. Return the result
#endif // USE_ADC
    return s16Result;
}



/**
 * SoftwarePWMの次回割り込みタイミングの設定処理
 *
 * @return なし
 *
 * @attention なし
 ***************************************************************************/
#if !defined(G23_FPB)
void _softwarePWM(void) {
  SwPwm* p;
  for (p = (SwPwm*) &g_SwPwm[0]; p < (SwPwm*) &g_SwPwm[NUM_SWPWM_PINS]; p++) {
    if (p->valid) {
      if (g_u8SwPwmTicksCount == PWM_MIN) {
        p->value = p->newValue;
      }
      if (g_u8SwPwmTicksCount == p->value) {
        *p->port &= ~p->mask;    // 出力をLOWに設定
      } else if (g_u8SwPwmTicksCount == PWM_MIN) {
        *p->port |= p->mask;    // 出力をHIGHに設定
      }
    }
  }
  if (++g_u8SwPwmTicksCount >= PWM_MAX) {
    g_u8SwPwmTicksCount = PWM_MIN;
  };
}

INTERRUPT void adc_interrupt(void) {
  g_bAdcInterruptFlag = true;
}

INTERRUPT void tm06_interrupt(void) {
  _softwarePWM();
}
#endif
#endif/*__RL78__*/
/* ★ */
uint16_t pow2n(uint8_t fact)
{
    return ans[fact];
}
