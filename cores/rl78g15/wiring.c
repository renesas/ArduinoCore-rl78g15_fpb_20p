/*
  wiring.c - Partial implementation of the Wiring API for the ATmega8.
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

  $Id$
*/
/*
 * Modified 15 July 2014 by Nozomu Fujita for GR-SAKURA
 * Modified  4 Mar  2017 by Yuuki Okamiya for RL78/G13
*/

#include "wiring_private.h"
#ifdef __RL78__
#include "utilities.h"
#include "r_smc_entry.h"
#include "r_cg_it.h"
#endif


#ifndef __RL78__
// the prescaler is set so that timer0 ticks every 64 clock cycles, and the
// the overflow handler is called every 256 ticks.
#define MICROSECONDS_PER_TIMER0_OVERFLOW (clockCyclesToMicroseconds(64 * 256))

// the whole number of milliseconds per timer0 overflow
#define MILLIS_INC (MICROSECONDS_PER_TIMER0_OVERFLOW / 1000)

// the fractional number of milliseconds per timer0 overflow. we shift right
// by three to fit these numbers into a byte. (for the clock speeds we care
// about - 8 and 16 MHz - this doesn't lose precision.)
#define FRACT_INC ((MICROSECONDS_PER_TIMER0_OVERFLOW % 1000) >> 3)
#define FRACT_MAX (1000 >> 3)
#else  /*__RL78__*/
extern void delay_wait (uint32_t count);

volatile unsigned long g_u32timer_millis = 0u;    //!< インターバルタイマ変数
volatile unsigned long g_u32delay_timer  = 0u;    //!< delay() 用タイマ変数
volatile unsigned long g_timer06_overflow_count = 0;//
uint8_t g_delay_cnt_flg = 0;
uint8_t g_delay_cnt_micros_flg = 0;

volatile unsigned long g_u32timer_micros = 0u;    //!< インターバルタイマ変数
volatile unsigned long g_u32delay_micros_timer  = 0u;    //!< delay() 用タイマ変数

uint8_t g_timer_millis_overflow_cnt = 0;        /* mills over flow couner */
unsigned long g_starttime_ms  = 0u;                /* mills starttime counter */

#endif /*__RL78__*/

#ifndef __RL78__
volatile unsigned long timer0_overflow_count = 0;
volatile unsigned long timer0_millis = 0;
static unsigned char timer0_fract = 0;

#if defined(__AVR_ATtiny24__) || defined(__AVR_ATtiny44__) || defined(__AVR_ATtiny84__)
ISR(TIM0_OVF_vect)
#else
ISR(TIMER0_OVF_vect)
#endif
{
    // copy these to local variables so they can be stored in registers
    // (volatile variables must be read from memory on every access)
    unsigned long m = timer0_millis;
    unsigned char f = timer0_fract;

    m += MILLIS_INC;
    f += FRACT_INC;
    if (f >= FRACT_MAX) {
        f -= FRACT_MAX;
        m += 1;
    }

    timer0_fract = f;
    timer0_millis = m;
    timer0_overflow_count++;
}
#else /*__RL78__*/

#endif/*__RL78__*/

unsigned long millis()
{
#ifndef __RL78__
    unsigned long m;
    uint8_t oldSREG = SREG;

    // disable interrupts while we read timer0_millis or we might get an
    // inconsistent value (e.g. in the middle of a write to timer0_millis)
    cli();
    m = timer0_millis;
    SREG = oldSREG;

    return m;
#else /*__RL78__*/
    unsigned long u32ms;

    noInterrupts();
    u32ms = g_u32timer_millis;
    interrupts();

    return u32ms;
#endif/*__RL78__*/
}

unsigned long micros() {
#ifndef __RL78__
    unsigned long m;
    uint8_t oldSREG = SREG, t;

    cli();
    m = timer0_overflow_count;
#if defined(TCNT0)
    t = TCNT0;
#elif defined(TCNT0L)
    t = TCNT0L;
#else
    #error TIMER 0 not defined
#endif


#ifdef TIFR0
    if ((TIFR0 & _BV(TOV0)) && (t < 255))
        m++;
#else
    if ((TIFR & _BV(TOV0)) && (t < 255))
        m++;
#endif

    SREG = oldSREG;

    return ((m << 8) + t) * (64 / clockCyclesPerMicrosecond());
#else /*__RL78__*/
    unsigned long a;
    unsigned long m;
    uint16_t t;
    boolean ov0,ov1;

#ifdef USE_RTOS
    u32us = (unsigned long)xTaskGetTickCount() / portTICK_RATE_MS * 1000;
#else /* USE_RTOS */

    // 割り込み禁止状態で
    if (isNoInterrupts()) {
        // TCR05.tcr05 を参照する前の g_timer05_overflow_count の値
        m = g_timer06_overflow_count;
        // TCR05.tcr05 を参照する直前でオーバーフローしてるか?
        ov0 = TMIF06;
        // TCR05.tcr05 の値
        t = TCR06;
        // TCR05.tcr05 を参照した直前でオーバーフローしてるか?
        ov1 = TMIF06;

        if (!ov0 && ov1) {
            // TCR05.tcr05 を参照した付近でオーバーフローしたのであれば、
            // t の値は捨てて TDR の初期値を代入し、オーバーフローの補正を行う
            t = INTERVAL_MICRO_TDR;
            m++;
        } else if (ov0) {
            // タイマーが最初っからオーバーフローしてるのであれば、g_timer05_overflow_count の値の補正を行う
            m++;
        }
    // 割り込み許可状態で
    } else {
        // TCR05.tcr05 を参照する直前の g_timer05_overflow_count の値
        a = g_timer06_overflow_count;
        // TCR05.tcr05 の値
        t = TCR06;
        // TCR05.tcr05 を参照した直後の g_timer05_overflow_count の値
        m = g_timer06_overflow_count;

        if (a != m) {
            // TCR05.tcr05 を参照する直前と直後の g_timer05_overflow_count の値が
            // 異なっているのであれば、これはどう考えても TCR05.tcr05 の値を参照した付近で
            // インターバルのタイミングが発生してたということなので、t に格納されてる値は捨てて、
            // TCR05.tcr05 の値は TDR の値に設定して問題ない
            t = INTERVAL_MICRO_TDR;
        } else if (t == INTERVAL_MICRO_TDR) {
            // TCR05 がオーバーフローを起こし、割り込みが発生していれば割り込みの処理で
            // 32クロック以上掛かるので、TCR05.tcr05 の値は TDR05 の値より -1 以上
            // 小さくなっている筈。それがなく、TCR05.tcr05 の値が TDR05 と等しいということは
            // 割り込み処理がまだ行われてないということなので補正を行う
            m++;
        }
    }
    m = m * MICROSECONDS_PER_TIMER05_OVERFLOW + (INTERVAL_MICRO_TDR - t);
#endif /* USE_RTOS */

    return m;
#endif/*__RL78__*/
}

void delay(unsigned long ms)
{
#ifndef __RL78__
    uint16_t start = (uint16_t)micros();

    while (ms > 0) {
        yield();
        if (((uint16_t)micros() - start) >= 1000) {
            ms--;
            start += 1000;
        }
    }
#else /*__RL78__*/

    volatile unsigned lms = ms;
    g_u32delay_timer = 0U;
    g_delay_cnt_flg  = 1U;
// 2022/07/20 special for RL78/G15
//    R_Config_IT_Start();
//    while (g_u32delay_timer<ms)
    while (g_u32delay_timer<lms)
    {
        NOP();
    }
    g_delay_cnt_flg=0U;

    set_endtime();

#endif/*__RL78__*/
}


/* Delay for the given number of microseconds.  Assumes a 8 or 16 MHz clock. */
void delayMicroseconds(unsigned long us)
{
#ifndef __RL78__
    // calling avrlib's delay_us() function with low values (e.g. 1 or
    // 2 microseconds) gives delays longer than desired.
    //delay_us(us);
#if F_CPU >= 20000000L
    // for the 20 MHz clock on rare Arduino boards

    // for a one-microsecond delay, simply wait 2 cycle and return. The overhead
    // of the function call yields a delay of exactly a one microsecond.
    __asm__ __volatile__ (
        "nop" "\n\t"
        "nop"); //just waiting 2 cycle
    if (--us == 0)
        return;

    // the following loop takes a 1/5 of a microsecond (4 cycles)
    // per iteration, so execute it five times for each microsecond of
    // delay requested.
    us = (us<<2) + us; // x5 us

    // account for the time taken in the preceeding commands.
    us -= 2;

#elif F_CPU >= 16000000L
    // for the 16 MHz clock on most Arduino boards

    // for a one-microsecond delay, simply return.  the overhead
    // of the function call yields a delay of approximately 1 1/8 us.
    if (--us == 0)
        return;

    // the following loop takes a quarter of a microsecond (4 cycles)
    // per iteration, so execute it four times for each microsecond of
    // delay requested.
    us <<= 2;

    // account for the time taken in the preceeding commands.
    us -= 2;
#else
    // for the 8 MHz internal clock on the ATmega168

    // for a one- or two-microsecond delay, simply return.  the overhead of
    // the function calls takes more than two microseconds.  can't just
    // subtract two, since us is unsigned; we'd overflow.
    if (--us == 0)
        return;
    if (--us == 0)
        return;

    // the following loop takes half of a microsecond (4 cycles)
    // per iteration, so execute it twice for each microsecond of
    // delay requested.
    us <<= 1;

    // partially compensate for the time taken by the preceeding commands.
    // we can't subtract any more than this or we'd overflow w/ small delays.
    us--;
#endif

    // busy wait
    __asm__ __volatile__ (
        "1: sbiw %0,1" "\n\t" // 2 cycles
        "brne 1b" : "=w" (us) : "0" (us) // 2 cycles
    );
#else /*__RL78__*/

    if(DELAYMICROSECONDS_ADJUST1 >= us)
    {
    	return;
    }
    if(DELAYMICROSECONDS_ADJUST3 > us)
    {
    	delay_wait((us-DELAYMICROSECONDS_ADJUST1) * DELAYMICROSECONDS_ADJUST4);
    	return;
    }

    g_delay_cnt_micros_flg  = 1U;

    if (g_u8PowerManagementMode == PM_NORMAL_MODE) {
		unsigned long s, w, d;
		s = micros();
		w = us - DELAYMICROSECONDS_ADJUST2 ;
		d = 0;
		while (w > d) {
			d = micros() - s;
		}
	} else {
		unsigned long s, w, d;
		s = micros();
		w = us - DELAYMICROSECONDS_ADJUST2 ;
		d = 0;
		while (w > d) {
			_HALT();
			d = micros() - s;
		}
	}
    g_delay_cnt_micros_flg  = 0U;

#endif/*__RL78__*/
}



#ifdef __RL78__
/**********************************************************************************************************************
 * Function Name: start time setting
 * Description  : Set the current count value to startup_ms.
 * Arguments    : -
 * Return Value : -
 *********************************************************************************************************************/
void set_starttime(void)
{
    noInterrupts();
    g_timer_millis_overflow_cnt = 0;
    g_starttime_ms = g_u32timer_millis;        /* set current time */
    interrupts();
}

/**********************************************************************************************************************
 * Function Name: set_endtime 
 * Description  : Get elapsed time form set_starttime.
 * Arguments    : -
 * Return Value : result
 *                 0  : OK
 *                 -1 : NG
 *                 -2 : parameter error
 *********************************************************************************************************************/
long set_endtime()
{
    long ret;
    unsigned long val = 0;

    noInterrupts();
    if (0 == g_timer_millis_overflow_cnt){
        val = g_u32timer_millis - g_starttime_ms;
    }
    else if (1 == g_timer_millis_overflow_cnt){
        if (g_starttime_ms <= g_u32timer_millis){
            val = 0xffffffff;        /* 32bit over flow */
        }
        else{
            val = (0xffffffffu - g_starttime_ms) + g_u32timer_millis + 1;
        }
    }
    else{
        val = 0xffffffff;            /* 32bit over flow */
    }
    interrupts();

    if (0x80000000 <= val){
        ret = -1;
    }
    else{
        ret = (long)val;
    }

ERR_END:

    return ret;
}

#endif/*__RL78__*/

