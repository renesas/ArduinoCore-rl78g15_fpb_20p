
#ifndef UTILITIES_H_
#define UTILITIES_H_
#include <stdint.h>

typedef void (*fInterruptFunc_t)(void);
typedef void (*fITInterruptFunc_t)(unsigned long u32timer_millis);
extern uint8_t g_u8ResetFlag;
extern fITInterruptFunc_t    g_fITInterruptFunc;
uint16_t getVersion();

void attachIntervalTimerHandler(void (*fFunction)(unsigned long u32Milles));
void detachIntervalTimerHandler();
void attachMicroIntervalTimerHandler(void (*fFunction)(void), uint16_t interval);
void attachClockIntervalTimerHandler(void (*fFunction)(void), uint16_t interval);
void detachMicroIntervalTimerHandler();
void detachClockIntervalTimerHandler();
void attachCyclicHandler(uint8_t u8HandlerNumber, void (*fFunction)(unsigned long u32Milles), uint32_t u32CyclicTime);
void detachCyclicHandler(uint8_t u8HandlerNumber);
void softwareReset(void);
uint8_t getResetFlag(void);
void execCyclicHandler();

#ifdef __cplusplus
extern "C" {
#endif
void _startTAU0(uint16_t u16TimerClock);
void _stopTAU0();
void _startTimerChannel(uint8_t u8TimerChannel, uint16_t u16TimerMode, uint16_t u16Interval, bool bPWM, bool bInterrupt);
void _modifyTimerPeriodic(uint8_t u8TimerChannel, uint16_t u16Interval);
void _stopTimerChannel(uint8_t u8TimerChannel);
void _softwarePWM(void);

#ifdef __cplusplus
}
#endif

#endif // UTILITIES_H_
