#include <Arduino.h>
#include "utilities.h"
extern "C" {
    #include "r_smc_entry.h"
#include "Config_IT.h"
}

extern "C" {
}


/* This declaration is used to force the constant in
 * r_cg_vect_table.c to be linked to the static library (*.a). */
extern const unsigned char Option_Bytes[];
void * p_force_link = (void * )Option_Bytes;

int main(void)
{
/******************************************************/
    interrupts();                /* Enable Interrupt */

/* Start Interval Timer */
    R_Config_IT_Create();    /* Create 1ms Interval Timer */
    R_Config_IT_Start();

    R_Config_TAU0_6_Micros_Create();
    R_Config_TAU0_6_Micros_Start();

/* Power Off unused Peripheral */
/* SERIAL ARRAY UNIT (SAU) */
#if defined(USE_I2C) && USE_I2C == 1
//    #if !defined(UART_CHANNEL) & (UART1_CHANNEL == 0) & !defined(CSI_CHANNEL)
//    R_SAU0_Set_Reset();
//    R_SAU0_Set_PowerOff();
#endif
#if (UART2_CHANNEL == 0)
//    R_SAU1_Set_Reset();
//    R_SAU1_Set_PowerOff();
#endif

/* IICA UNIT(IICA*) */
#if !defined(IIC_CHANNEL0) | (IIC_CHANNEL0!=0)
    R_IICA0_Set_Reset();
    R_IICA0_Set_PowerOff();
#endif
#if (IIC_CHANNEL1!=1)
//    R_IICA1_Set_Reset();
//    R_IICA1_Set_PowerOff();
#endif

#if WDT_EN==1
    R_Config_WDT_Start();
#endif

    SOE0 &= 0xf3;
    SO0 |= 0x08;

/******************************************************/
    
    setup();
    
    for (;;) {
        loop();
    }
    return 0;
}

/**
 * Finish Function
 *
 * RLduino78 Framework finish
 *  *
 * @return None
 *
 * @attention No return
 ***************************************************************************/
#include <stdlib.h>
/*
void abort(void)
{
    for(;;);
}

void exit(int) __attribute__ ((weak, alias ("abort")));
*/
#include <exception>

