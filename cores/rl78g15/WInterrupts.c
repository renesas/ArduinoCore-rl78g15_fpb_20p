#include <inttypes.h>
// #include <avr/pgmspace.h>
#include <stdio.h>
#include "wiring_variant.h"
#include "wiring_private.h"
#include "r_smc_entry.h"

#include "platform.h"


typedef struct {
    void (*begin)();
    void (*mode)(uint8_t interruptNum, int mode);
    void (*start)();
    void (*stop)(uint8_t interruptNum);
} Interrupts_func;

Interrupts_func Int_func =
{
    .begin  = (void*)R_Config_INTC_Create,
    .mode = (void*)R_Config_INTC_Create_Mode,
    .start = (void*)R_Config_INTC_INTP_Start,
    .stop = (void*)R_Config_INTC_INTP_Stop
};

static bool IsFirst = true;


void attachInterrupt(uint8_t interruptNum, void (*userFunc)(void), int mode)
{
    if (interruptNum < EXTERNAL_NUM_INTERRUPTS)
    {
        g_afInterruptFuncTable[interruptNum] = userFunc;
        if(IsFirst)
        {
            Int_func.begin();
            IsFirst = false;
        }
        Int_func.mode(interruptNum, mode);
        Int_func.start();
    }
}
void detachInterrupt(uint8_t interruptNum)
{
    if (interruptNum < EXTERNAL_NUM_INTERRUPTS)
    {
        Int_func.stop(interruptNum);
        g_afInterruptFuncTable[interruptNum] = NULL;
    }
}

// INTERRUPT HANDLERS *********************************************************/
// NMI and IRQ interrupt handlers. Note that all of these are declared in
// interrupts_handlers.h but defined here for clarity.
/**
 * 外部割込みハンドラ0
 *
 * @return なし
 *
 * @attention なし
 ***************************************************************************/
INTERRUPT void external_interrupt_0(void)
{
    if (g_afInterruptFuncTable[0] != NULL) {
        (*g_afInterruptFuncTable[0])();
    }
}

INTERRUPT void external_interrupt_1(void)
{
    if (g_afInterruptFuncTable[1] != NULL) {
        (*g_afInterruptFuncTable[1])();
    }
}

INTERRUPT void external_interrupt_2(void)
{
    if (g_afInterruptFuncTable[2] != NULL) {
        (*g_afInterruptFuncTable[2])();
    }
}

