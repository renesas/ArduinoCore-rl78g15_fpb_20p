#define ARDUINO_MAIN 1
#include <wiring_private.h>
#include <pins_arduino.h>
#define PMPUPIMPOM_CHECK_ENABLE		/* Do not change invalid bits */
#include "pintable.h"
// extern bool g_u8AnalogWriteAvailableTable[NUM_DIGITAL_PINS];
// extern volatile SwPwm g_SwPwm[NUM_SWPWM_PINS];
extern const PinTableType * pinTablelist[NUM_DIGITAL_PINS];
extern bool g_u8AnalogReadAvailableTable[NUM_ANALOG_INPUTS];
/**********************************************************************************************************************
 * Function Name: pinmode setting
 * Description  : Set the port register.
 * Arguments    : -
 * Return Value : -
 *********************************************************************************************************************/
void pinMode(uint8_t pin, uint8_t u8Mode)
{
    if (pin < NUM_DIGITAL_PINS)
    {
        const PinTableType **pp;
        PinTableType *p;
        pp = &pinTablelist[pin];
        p = (PinTableType *)*pp;
        switch (u8Mode)
        {
            case INPUT:
                *p->portModeRegisterAddr |=  (unsigned long)(0x1 << p->bit);
                break;
            case OUTPUT:
                *p->portModeRegisterAddr &= (unsigned long)~(0x1 << p->bit);
                if (0 != p->pom)
                {
                    *p->portOutputModeRegisterAddr &= (unsigned long)~(0x1 << p->bit);  /* set Normal Output(not open drain) */
                }
                *p->portRegisterAddr &= (unsigned long)~(0x1 << p->bit);            /* clear Port */

                break;
        }
        //  This is not an analog mode
        if (0!=p->pmc)
        {
            *p->portModeControlRegisterAddr &= (unsigned long)~(p->pmc);
            int8_t pin_index = (int8_t)pin - ANALOG_PIN_START_NUMBER;
            if ((pin_index >= 0) && (pin_index < NUM_ANALOG_INPUTS))
            {
                g_u8AnalogReadAvailableTable[pin_index] = false;
            }
        }
        //  This is not pull-up
        if (0 != p->pu){
            *p->portPullUpRegisterAddr &= (unsigned long)~(0x1 << p->bit);    /* Disable Pullup Reg */
        }
    }
}

/**********************************************************************************************************************
 * Function Name: pin output
 * Description  : Perform port output
 * Arguments    : pin  - pin number
 *              : pp   - output value
 * Return Value : -
 *********************************************************************************************************************/
void digitalWrite(uint8_t pin, uint8_t val)
{
    const PinTableType ** pp;
    PinTableType * p;
    if (pin < NUM_DIGITAL_PINS)
    {
        if(CHECK_OUTPUT_INHIBIT_RL78(pin))
        {
            return;
        }
        pp = &pinTablelist[pin];
        p = (PinTableType *)*pp;
        /* When Output Mode  */
        if (val == LOW)
        {
            *p->portRegisterAddr &= ~p->mask;       /* Write "0" to Port */
        }
        else
        {
            *p->portRegisterAddr |= p->mask;        /* Write "1" to Port */
        }
    }

}

/**********************************************************************************************************************
 * Function Name: pin input
 * Description  : Perform port input
 * Arguments    : pin  - pin number
 * Return Value : input value
 *********************************************************************************************************************/
int digitalRead(uint8_t pin)
{
    if (pin < NUM_DIGITAL_PINS)
    {
        const PinTableType ** pp;
        PinTableType * p;
        pp = &pinTablelist[pin];
        p = (PinTableType *)*pp;
        if (*p->portRegisterAddr & p->mask)
        {
            return HIGH;
        }
    }
    return LOW;
}

