#include "wiring_variant.h"
#include "wiring_private.h"
#include "pins_arduino.h"
#include "pintable.h"
#include "r_cg_interrupt_handlers.h"

uint8_t g_u8ResetFlag;
extern uint8_t g_u8ResetFlag;

// void (*INT_TM_HOOK)() ;

extern "C" {
#include "r_smc_entry.h"
}

#if defined(G22_FPB) || defined(G23_FPB)
#define USE_PERIODIC (1) // Set 1 when issue was solved. //KAD change from 0 to 1
#else
#define USE_PERIODIC (0) // Set 1 when issue was solved.
#endif // defined(G22_FPB) || defined(G23_FPB)

#if USE_PERIODIC
// 周期起動ハンドラ関数テーブル
static struct {
    fITInterruptFunc_t afCyclicHandler;
    uint32_t au32CyclicTime;
    uint32_t au32RemainTime;
    uint32_t au32LastTime;
} g_CyclicHandlerTable[MAX_CYCLIC_HANDLER] = {
    {NULL, 0, 0, 0},
};
fITInterruptFunc_t    g_fITInterruptFunc = NULL;    //!< ユーザー定義インターバルタイマハンドラ
#endif //USE_PERIODIC

/**
 * タイマーアレイユニットの停止
 *
* @return なし
 *
 * @attention なし
 ***************************************************************************/
void _stopTAU0()
{
    // タイマ・アレイ・ユニットが動作しているか？
    if (TAU0EN != 0) {
        if (TE0 == 0x00000) {
            TAU0EN    = 0;               // タイマ・アレイ・ユニットにクロック供給停止
        }
    }
}

/**
 * タイマー周期の変更
 *
 * @param[in] u8Timer 変更するタイマ番号
 *
 * @return なし
 *
 * @attention なし
 ***************************************************************************/
void _modifyTimerPeriodic(uint8_t u8TimerChannel, uint16_t u16Interval)
{
    switch (u8TimerChannel) {
    case 1:
        TDR01 = u16Interval;    // インターバル（周期）の設定
        break;
    case 2:
        TDR02 = u16Interval;    // インターバル（周期）の設定
        break;
    case 3:
        TDR03 = u16Interval;    // インターバル（周期）の設定
        break;
    case 4:
        TDR04 = u16Interval;    // インターバル（周期）の設定
        break;
    case 5:
        TDR05 = u16Interval;    // インターバル（周期）の設定
        break;
    case 6:
        TDR06 = u16Interval;    // インターバル（周期）の設定
        break;
    case 7:
        TDR07 = u16Interval;    // インターバル（周期）の設定
        break;
    }
}

/**
 * タイマーチャンネルの停止
 *
 * @param[in] u8Timer 停止するタイマ番号
 *
 * @return なし
 *
 * @attention なし
 ***************************************************************************/
void _stopTimerChannel(uint8_t u8TimerChannel)
{
    TT0   |=  (1 << u8TimerChannel);    // タイマ動作停止
    TOE0 &=  ~(1 << u8TimerChannel);    // タイマ出力禁止の設定
    TO0   &= ~(1 << u8TimerChannel);    // タイマ出力の設定
    // 割り込みマスクを禁止に設定
    switch (u8TimerChannel) {
    case 1:    TMMK01  = 1; break;
    case 2:    TMMK02  = 1; break;
    case 3:    TMMK03  = 1; break;
    case 4:    TMMK04  = 1; break;
    case 5:    TMMK05  = 1; break;
    case 6:    TMMK06  = 1; break;
    case 7:    TMMK07  = 1; break;
    }
    if (!(TE0 & 0x009E)) {
        TT0 |= 0x0001;        // Master チャンネルの停止
    }
}

/**
 * Software Reset
 *
 * Generate software reset.
 *
 * @return なし
 *
 * @attention:  This function uses trap instruction.
 *              So RESF register in MCU is set to 0x80 after reset.
 *              Unable to use when using debugger.
 *
 ***************************************************************************/

void softwareReset(void) {
    __asm __volatile(" .byte 0xff");
}

/**
 * Get Reset Flag
 *
 * Get the flag why reset occur.
 *
 * @return 0x00: External reset or Power on reset
 *         0x01: Low voltage detection
 *         0x02: Illegal memory access
 *         0x04: RAM parity error ( read from no initialized area )
 *         0x10: Watch dog timer
 *         0x80: Illegal instruction
 *
 * @attention:
 *
 ***************************************************************************/

uint8_t getResetFlag() {
    return g_u8ResetFlag;
}

/**
 * RLduino78のバージョン情報を取得します。
 *
 * @return バージョン情報を返却します。
 *
 * @attention なし
 ***************************************************************************/
uint16_t getVersion()
{
    return RLDUINO78_VERSION;
}

#if USE_PERIODIC
/** ************************************************************************
 * @defgroup group16 割込みハンドラ/周期起動関数
 *
 * @{
 ***************************************************************************/
/**
 * インターバル・タイマ割り込みハンドラ内から実行するコールバック関数を登録します。
 *
 * コールバック関数を登録すると1[ms]のインターバル・タイマ割り込み毎に登録した
 * コールバック関数が呼び出されます。また、コールバック関数呼び出し時にはシステム
 * 開始からの時間（ms）が引数として渡されます。
 *
 * @param[in] fFunction インターバル・タイマ割り込み時に実行するハンドラを指定します。
 *
 * @return なし
 *
 * @attention
 * - コールバック関数内では時間のかかる処理は行わないでください。
 * - コールバック関数内では以下の関数が呼び出し可能です。
 *
 * pinMode()、 digitalWrite()、 digitalRead()、 millis()、 micros()、 delayMicroseconds()、
 * min()、 max()、 constrain()、 map()、 lowByte()、 highByte()、 bitRead()、 bitWrite()、
 * bitSet()、 bitClear()、 bit()、 randomSeed()、 random()
 * - pinMode()関数と digitalWrite()関数は、 loop()関数内とコールバック関数内で同じピン
 * 番号を指定すると誤動作する可能性があります。
 ***************************************************************************/
void attachIntervalTimerHandler(void (*fFunction)(unsigned long u32Milles))
{
    g_fITInterruptFunc = fFunction;
}

/**
 * インターバル・タイマ割り込みハンドラ内から実行するコールバック関数の登録を解除します。
 *
 * @return なし
 *
 * @attention なし
 ***************************************************************************/
void detachIntervalTimerHandler()
{
    g_fITInterruptFunc = NULL;
}

/**
 * 周期起動コールバック関数を登録します。
 *
 * 登録したコールバック関数は、u32CyclicTimeで指定した周期間隔[ms]で呼び出されます。
 * また、コールバック関数呼び出し時にはシステム開始からの時間(ms)が引数として渡されます。
 *
 * @param[in] u8HandlerNumber 周期起動コールバック関数の識別番号(0~7)を指定します。
 * @param[in] fFunction       インターバル・タイマ割り込み時に実行するハンドラを指定します。
 * @param[in] u32CyclicTime   周期起動する間隔[ms]を指定します。
 *
 * @return なし
 *
 * @attention なし
 ***************************************************************************/
void attachCyclicHandler(uint8_t u8HandlerNumber, void (*fFunction)(unsigned long u32Milles), uint32_t u32CyclicTime)
{
    if (u8HandlerNumber < MAX_CYCLIC_HANDLER) {
        detachCyclicHandler(u8HandlerNumber);
        g_CyclicHandlerTable[u8HandlerNumber].au32CyclicTime  = u32CyclicTime;
        g_CyclicHandlerTable[u8HandlerNumber].au32RemainTime = u32CyclicTime;
        g_CyclicHandlerTable[u8HandlerNumber].au32LastTime = millis();
        g_CyclicHandlerTable[u8HandlerNumber].afCyclicHandler = fFunction;
    }
}

/**
 * 周期起動コールバック関数の登録を解除します。
 *
 * @param[in] u8HandlerNumber 周期起動コールバック関数の識別番号( 0 ～ 7 )を指定します。
 *
 * @return なし
 *
 * @attention
 ***************************************************************************/
void detachCyclicHandler(uint8_t u8HandlerNumber)
{
    if (u8HandlerNumber < MAX_CYCLIC_HANDLER) {
        g_CyclicHandlerTable[u8HandlerNumber].afCyclicHandler = NULL;
        g_CyclicHandlerTable[u8HandlerNumber].au32CyclicTime  = 0;
        g_CyclicHandlerTable[u8HandlerNumber].au32RemainTime = 0;
        g_CyclicHandlerTable[u8HandlerNumber].au32LastTime = 0;
    }
}

/**
 * 周期起動コールバック関数を起動します。
 *
 * @return なし
 *
 * @attention
 ***************************************************************************/
void execCyclicHandler()
{
    int i;

    for (i = 0; i < MAX_CYCLIC_HANDLER; i++) {
        if (g_CyclicHandlerTable[i].afCyclicHandler != NULL) {
            unsigned long currentTime = millis();
            unsigned long elapsedTime = currentTime - g_CyclicHandlerTable[i].au32LastTime;
            g_CyclicHandlerTable[i].au32LastTime = currentTime;
            bool exec = g_CyclicHandlerTable[i].au32RemainTime <= elapsedTime;
            g_CyclicHandlerTable[i].au32RemainTime -= elapsedTime;
            if (exec) {
                g_CyclicHandlerTable[i].au32RemainTime += g_CyclicHandlerTable[i].au32CyclicTime;
                g_CyclicHandlerTable[i].afCyclicHandler(currentTime);
            }
        }
    }
}
#endif// USE_PERIODIC == 1
