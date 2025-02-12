#include "wiring_private.h"
 #include "utilities.h"
#include "r_smc_entry.h"

volatile unsigned long g_u32timer_millis = 0u;    //!< インターバルタイマ変数
volatile unsigned long g_u32delay_timer  = 0u;    //!< delay() 用タイマ変数
volatile unsigned long g_timer06_overflow_count = 0;
uint8_t g_delay_cnt_flg = 0;
uint8_t g_delay_cnt_micros_flg = 0;

volatile unsigned long g_u32timer_micros = 0u;    //!< インターバルタイマ変数
volatile unsigned long g_u32delay_micros_timer  = 0u;    //!< delay() 用タイマ変数

uint8_t g_timer_millis_overflow_cnt = 0;        /* mills over flow couner */
unsigned long g_starttime_ms  = 0u;                /* mills starttime counter */
extern void delay_wait (uint32_t count);

unsigned long millis()
{
    unsigned long u32ms;
    noInterrupts();
    u32ms = g_u32timer_millis;
    interrupts();
    return u32ms;
}

unsigned long micros() {
    unsigned long a;
    unsigned long m;
    uint16_t t;
    boolean ov0,ov1;

    // 割り込み禁止状態で
    if (isNoInterrupts())
    {
        // TCR05.tcr05 を参照する前の g_timer05_overflow_count の値
        m = g_timer06_overflow_count;
        // TCR05.tcr05 を参照する直前でオーバーフローしてるか?
        ov0 = TMIF06;
        // TCR05.tcr05 の値
        t = TCR06;
        // TCR05.tcr05 を参照した直前でオーバーフローしてるか?
        ov1 = TMIF06;

        if (!ov0 && ov1)
        {
            // TCR05.tcr05 を参照した付近でオーバーフローしたのであれば、
            // t の値は捨てて TDR の初期値を代入し、オーバーフローの補正を行う
            t = INTERVAL_MICRO_TDR;
            m++;
        }
        else if (ov0)
        {
            // タイマーが最初っからオーバーフローしてるのであれば、g_timer05_overflow_count の値の補正を行う
            m++;
        }
    // 割り込み許可状態で
    }
    else
    {
        // TCR05.tcr05 を参照する直前の g_timer05_overflow_count の値
        a = g_timer06_overflow_count;
        // TCR05.tcr05 の値
        t = TCR06;
        // TCR05.tcr05 を参照した直後の g_timer05_overflow_count の値
        m = g_timer06_overflow_count;

        if (a != m)
        {
            // TCR05.tcr05 を参照する直前と直後の g_timer05_overflow_count の値が
            // 異なっているのであれば、これはどう考えても TCR05.tcr05 の値を参照した付近で
            // インターバルのタイミングが発生してたということなので、t に格納されてる値は捨てて、
            // TCR05.tcr05 の値は TDR の値に設定して問題ない
            t = INTERVAL_MICRO_TDR;
        }
        else if (t == INTERVAL_MICRO_TDR)
        {
            // TCR05 がオーバーフローを起こし、割り込みが発生していれば割り込みの処理で
            // 32クロック以上掛かるので、TCR05.tcr05 の値は TDR05 の値より -1 以上
            // 小さくなっている筈。それがなく、TCR05.tcr05 の値が TDR05 と等しいということは
            // 割り込み処理がまだ行われてないということなので補正を行う
            m++;
        }
    }
    m = m * MICROSECONDS_PER_TIMER05_OVERFLOW + (INTERVAL_MICRO_TDR - t);

    return m;
}

void delay(unsigned long ms)
{
    volatile unsigned lms = ms;
    g_u32delay_timer = 0U;
    g_delay_cnt_flg  = 1U;
    while (g_u32delay_timer<lms)
    {
        NOP();
    }
    g_delay_cnt_flg=0U;

    set_endtime();

}


/* Delay for the given number of microseconds.  Assumes a 8 or 16 MHz clock. */
void delayMicroseconds(unsigned long us)
{
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
	unsigned long s, w, d;
	s = micros();
	w = us - DELAYMICROSECONDS_ADJUST2 ;
	d = 0;
	while (w > d) {
		d = micros() - s;
	}
    g_delay_cnt_micros_flg  = 0U;
}


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
    if (0 == g_timer_millis_overflow_cnt)
    {
        val = g_u32timer_millis - g_starttime_ms;
    }
    else if (1 == g_timer_millis_overflow_cnt)
    {
        if (g_starttime_ms <= g_u32timer_millis)
        {
            val = 0xffffffff;        /* 32bit over flow */
        }
        else
        {
            val = (0xffffffffu - g_starttime_ms) + g_u32timer_millis + 1;
        }
    }
    else
    {
        val = 0xffffffff;            /* 32bit over flow */
    }
    interrupts();

    if (0x80000000 <= val)
    {
        ret = -1;
    }
    else
    {
        ret = (long)val;
    }

ERR_END:

    return ret;
}

