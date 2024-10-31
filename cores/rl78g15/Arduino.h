#ifndef Arduino_h
#define Arduino_h

#include <stdbool.h>
#include "utilities.h"
#ifdef __cplusplus
extern "C" {
#endif
#include "r_cg_macrodriver.h"
#ifdef __cplusplus
}
#endif
#include "pintable.h"
#include "pins_variant.h"

#define RLDUINO78_VERSION 0x0203
#define INTERRUPT
#define _BV(bit) (1 << (bit))
#define _HALT()		asm("halt;");
#define _STOP()		asm("stop;");

#ifndef configCPU_CLOCK_HZ
#define configCPU_CLOCK_HZ 					(16000000)	//!< CPUの動作周波数（RTOS未使用時に定義）
#endif

/* Timer clock setting. */
#define TIMER_CLOCK			(0x0050)	// CK0 = 32MHz, CK1 = 1MHz, CK2 = 16MHz, CK3 = 125kHz
#define CLK_SOURCE_XT1 1
#define CLK_SOURCE_FIL 2

#define clockCyclesPerMicrosecond()			(configCPU_CLOCK_HZ / 1000000)				//!< CPUの動作周波数を1000000で割ったもの
#define clockCyclesToMicroseconds(cycle)	((cycle) / clockCyclesPerMicrosecond())		//!< サイクルあたりの時間[us]
#define microsecondsToClockCycles(us)		((us) * clockCyclesPerMicrosecond())		//!< 時間当たりのサイクル数

#define HOOK_TIMER_CHANNEL  7

#define MICROSECONDS_PER_TIMER05_OVERFLOW 0xffff //1us * 2 ^ 16
#define MILLISECONDS_PER_TIMER05_OVERFLOW (MICROSECONDS_PER_TIMER05_OVERFLOW / 1000)
#define INTERVAL_MICRO_TDR	(MICROSECONDS_PER_TIMER05_OVERFLOW - 1)

/* Output clock setting. */
#define OUTPUT_CLOCK_CKx	(32000000)
#define OUTPUT_CLOCK_MODE 	(0x0000)    // CK0を選択
#define OUTPUT_CLOCK_MIN	(245)
#define OUTPUT_CLOCK_MAX	(16000000)

/* Serial define */
#define USE_SMART_CONFIGRATOR (1)

#ifdef __cplusplus

extern "C"{
#endif // __cplusplus

#define HIGH 0x1
#define LOW  0x0

#define INPUT 0x0
#define OUTPUT 0x1
#define INPUT_PULLUP 0x2

#define INPUT_TTL	0x3
#define INPUT_TTL_PULLUP	0x4
#define OUTPUT_OPENDRAIN	0x5

#define PI 3.1415926535897932384626433832795
#define HALF_PI 1.5707963267948966192313216916398
#define TWO_PI 6.283185307179586476925286766559
#define DEG_TO_RAD 0.017453292519943295769236907684886
#define RAD_TO_DEG 57.295779513082320876798154814105
#define EULER 2.718281828459045235360287471352

#define LSBFIRST 0
#define MSBFIRST 1

#define CHANGE 1
#define FALLING 2
#define RISING 3

/* Analog reference mode. */
#define DEFAULT			0x00
#define EXTERNAL		0x01
#define INTERNAL		0x02

/* PWM setting. */
#define PWM_MASTER_CLOCK    (32000000)
#if PWM_MASTER_CLOCK == 32000000
#define PWM_MASTER_MODE     (0x0801)    // CK0を選択
#define PWM_SLAVE_MODE      (0x0409)
#elif PWM_MASTER_CLOCK == 1000000
#define PWM_MASTER_MODE     (0x8801)    // CK1を選択
#define PWM_SLAVE_MODE      (0x8409)
#endif

#define PWM_DEFAULT_FREQ    (490)       // 490Hz
#define PWM_TDR00           (PWM_MASTER_CLOCK / PWM_DEFAULT_FREQ - 1)

#define interrupts()  EI()
#define noInterrupts()  DI()

#ifdef __RL78__
#define F_CPU (16 * 1000 * 1000L)
#endif

#define lowByte(w) ((uint8_t) ((w) & 0xff))
#define highByte(w) ((uint8_t) ((w) >> 8))

#define bitRead(value, bit) (((value) >> (bit)) & 0x01)
#define bitSet(value, bit) ((value) |= (1UL << (bit)))
#define bitClear(value, bit) ((value) &= ~(1UL << (bit)))
#define bitWrite(value, bit, bitvalue) (bitvalue ? bitSet(value, bit) : bitClear(value, bit))
#ifndef _NOP
#define _NOP() do { __asm__ volatile ("nop"); } while (0)
#endif

#ifndef __RL78__
typedef unsigned int word;
#else
typedef unsigned char	uint8_t;
typedef signed char     int8_t;
typedef unsigned short	uint16_t;
typedef signed short    int16_t;
typedef unsigned long   uint32_t;
typedef signed long     int32_t;
typedef uint8_t			byte;
typedef unsigned int	word;
typedef uint8_t			boolean;
#endif/*__RL78__*/
#define bit(b) (1UL << (b))

void init(void);
void initVariant(void);
int atexit(void (*func)()) __attribute__((weak));
void pinMode(uint8_t, uint8_t);
void digitalWrite(uint8_t, uint8_t);
int digitalRead(uint8_t);
void DisableDigitalInput(uint8_t pin);
void EnableDigitalInput(uint8_t pin);
int analogRead(uint8_t analog_pin);
void analogReference(uint8_t mode);
void analogWrite(uint8_t pin, int value);
void analogWriteFrequency(uint32_t Hz);
void analogWritePinFrequency(uint8_t pin, uint32_t Hz);
unsigned long millis(void);
unsigned long micros(void);
void delay(unsigned long ms);
void delayMicroseconds(unsigned long us);
void set_starttime(void);
long set_endtime();
uint8_t shiftIn(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder);
void shiftOut(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, uint8_t value);
void shiftOutEx(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, uint8_t len, uint32_t value);
#ifdef __cplusplus
void tone(uint8_t pin, unsigned int frequency, unsigned long duration = 0);
unsigned long pulseIn(uint8_t pin, uint8_t state, unsigned long timeout = 65535);
#endif
void randomSeed(unsigned long);
long map(long, long, long, long, long);
void noTone(uint8_t pin);
void attachInterrupt(uint8_t, void (*)(void), int mode);
void detachInterrupt(uint8_t);
void setup();
void loop();
#define analogInPinToBit(P) (P)
#define NOT_AN_INTERRUPT -1

#ifdef __cplusplus
} // extern "C"
#endif

#ifdef __cplusplus
#include <rl78g15/WCharacter.h>
#include <rl78g15/WString.h>
#include <rl78g15/HardwareSerial.h>

long random(long howbig);
long random(long howsmall, long howbig);

#endif /*  __cplusplus  */

#include "pins_variant.h"

// undefine stdlib's abs if encountered
#ifdef abs
#undef abs
#endif // abs

#define abs(x) ((x)>0?(x):-(x))

#ifndef configCPU_CLOCK_HZ
#define configCPU_CLOCK_HZ 					(32000000)	//!< CPUの動作周波数（RTOS未使用時に定義）
#endif
/* Analog reference mode. */
#define DEFAULT			0x00
#define EXTERNAL		0x01
#define INTERNAL		0x02

// undefine stdlib's abs if encountered
#ifdef abs
#undef abs
#endif

#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))
#define abs(x) ((x)>0?(x):-(x))
#define constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt)))
#define round(x)     ((x)>=0?(long)((x)+0.5):(long)((x)-0.5))
#define radians(deg) ((deg)*DEG_TO_RAD)
#define degrees(rad) ((rad)*RAD_TO_DEG)
#define sq(x) ((x)*(x))

#ifdef __RL78__
#define ISP_LEVEL_3 (3)
#define ISP_LEVEL_2 (2)
#define ISP_LEVEL_1 (1)
#define ISP_LEVEL_0 (0)
#define GET_PSW_ISP()  (__builtin_rl78_getpswisp ())
#define isNoInterrupts() (!__builtin_rl78_pswie ())

#if defined(__RL78_S3__)
/* S3 core (with Multiply/divide/multiply & accumulate instructions)*/

#if (F_CPU == 32000000)
/* For RL78/G23, RL78/G22, etc. */
#define MICROS_EXEC_TIME  (3) /* micros() execution time(unit:us) */
#define DELAYMICROSECONDS_ADJUST1  (1) /* Processing time(unit:us) if delayMicroseconds() function returns immediately */
#define DELAYMICROSECONDS_ADJUST2  (MICROS_EXEC_TIME + DELAYMICROSECONDS_ADJUST1 + 1)
#define DELAYMICROSECONDS_ADJUST3  (DELAYMICROSECONDS_ADJUST2 + MICROS_EXEC_TIME)
#define DELAYMICROSECONDS_ADJUST4  (5) /* Adjustment when waiting for time in delay_wait().　(visual check) */
#else /* (F_CPU == 16000000) */
#endif /* (F_CPU == 16000000) */

#elif defined(__RL78_S2__)

#if defined(__MDA_ENABLED__)
/* S2 core & with MDA(Multiplier and Divider/Multiply-Accumulator) */

#if (F_CPU == 32000000)
#elif (F_CPU == 16000000)
#else /* (F_CPU == XXX) */
#endif /* (F_CPU == XXX) */

#elif defined(__MDA_DISABLED__)
/* S2 core & with no MDA */

#if (F_CPU == 32000000)
#elif (F_CPU == 16000000)
/* For RL78/G15, etc */
#define MICROS_EXEC_TIME  (5) /* unit : us */
#define DELAYMICROSECONDS_ADJUST1  (2) /* Processing time(unit:us) if delayMicroseconds() function returns immediately */
#define DELAYMICROSECONDS_ADJUST2  (MICROS_EXEC_TIME + DELAYMICROSECONDS_ADJUST1 + 1)
#define DELAYMICROSECONDS_ADJUST3  (DELAYMICROSECONDS_ADJUST2 + MICROS_EXEC_TIME)
#define DELAYMICROSECONDS_ADJUST4  (2) /* Adjustment when waiting for time in delay_wait().　(visual check) */
#else /* (F_CPU == XXX) */
#endif /* (F_CPU == XXX) */
#endif /* defined(__MDA_DISABLED__),defined(__MDA_DISABLED__) */
#endif /* defined(__RL78_S3__), defined(__RL78_S2__) */
#endif // __RL78__
#endif // Arduino_h
