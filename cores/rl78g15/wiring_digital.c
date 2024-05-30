/*
  wiring_digital.c - digital input and output functions
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

#define ARDUINO_MAIN 1
#include <wiring_private.h>
#include <pins_arduino.h>

#define PMPUPIMPOM_CHECK_ENABLE		/* Do not change invalid bits */

#include "pintable.h"

// extern bool g_u8AnalogWriteAvailableTable[NUM_DIGITAL_PINS];
// extern volatile SwPwm g_SwPwm[NUM_SWPWM_PINS];

/**********************************************************************************************************************
 * Function Name: pintable setting
 * Description  : Set the pintable.
 * Arguments    : pin  - pin number
 *              : pp   - pin table
 * Return Value : -
 *********************************************************************************************************************/
void getPinTable(uint8_t pin,PinTableType *pp)
{
    pp->mask                         = pin_mask[pin];
    pp->bit                          = pin_bit[pin];
    pp->pmc                         = pin_pmc[pin];

    pp->portModeRegisterAddr         = getPortModeRegisterAddr(digital_pin[pin]);
    pp->portRegisterAddr             = getPortRegisterAddr(digital_pin[pin]);
    pp->portModeControlRegisterAddr = getPortModeControlRegisterAddr(digital_pin[pin]);

}

extern const PinTableType * pinTablelist[NUM_DIGITAL_PINS];

void _turnOffPwmPin(uint8_t u8Pin)
{
/*
  unsigned int u16TMR0x;

  uint8_t u8Timer = 0xFF;
  if (u8Pin < NUM_DIGITAL_PINS) {
    g_u8AnalogWriteAvailableTable[u8Pin] = false;
  }
  if (u8Timer == SWPWM_PIN) {
    int i;

    for (i = 0; i < NUM_SWPWM_PINS; i++) {
      if (g_SwPwm[i].valid) {
        if (g_SwPwm[i].pin == u8Pin) {
          g_SwPwm[i].valid = false;
        } else {
          break;
        }
      }
    }
    if (i >= NUM_SWPWM_PINS) {			// SoftwarePWM
      _stopTimerChannel(SW_PWM_TIMER);
    }
  }
  else {
    switch (u8Timer) {
    case 1:
      u16TMR0x = TMR01;
      break;

    case 2:
      u16TMR0x = TMR02;
      break;

    case 3:
      u16TMR0x = TMR03;
      break;

    case 4:
      u16TMR0x = TMR04;
      break;

    case 5:
      u16TMR0x = TMR05;
      break;

    case 6:
      u16TMR0x = TMR06;
      break;

    case 7:
      u16TMR0x = TMR07;
      break;

    default:
      u16TMR0x = PWM_MASTER_MODE;
      break;
    }
    if (u16TMR0x == PWM_SLAVE_MODE) {
      _stopTimerChannel(u8Timer);
    }
  }
  */
}


/**********************************************************************************************************************
 * Function Name: pinmode setting
 * Description  : Set the port register.
 * Arguments    : -
 * Return Value : -
 *********************************************************************************************************************/
void pinMode(uint8_t pin, uint8_t u8Mode)
{
  if (pin < NUM_DIGITAL_PINS) {
    //PinTableType *p;
    //PinTableType pin_tbl;
    //p = (PinTableType*)&pin_tbl;
    //getPinTable(pin,p);

    const PinTableType **pp;
    PinTableType *p;
    pp = &pinTablelist[pin];
    p = (PinTableType *)*pp;


    switch (u8Mode) {
      case OUTPUT:
        *p->portModeRegisterAddr &= (unsigned long)~(0x1 << p->bit);
        break;
      case INPUT:
        *p->portModeRegisterAddr |=  (unsigned long)(0x1 << p->bit);
        break;
    }

    /* clear pmca register when analog pin */
/*
    if (g_u8AnalogWriteAvailableTable[pin]) {
      _turnOffPwmPin(pin);	//  PWM setting cancel
    }
*/

//  2022/09/01 necessary to improve
    if (0!=p->pmc)
    {
      *p->portModeControlRegisterAddr &= (unsigned long)~(p->pmc);
    }

    if (!(*p->portModeRegisterAddr & p->mask)) {
      if (*p->portRegisterAddr & p->mask) {
        if (u8Mode == INPUT) {
          u8Mode = INPUT_PULLUP;
        } else if (u8Mode == INPUT_TTL) {
          u8Mode = INPUT_TTL_PULLUP;
        }
      }
    }

    switch (u8Mode) {
    case INPUT:
      *p->portModeRegisterAddr |= (unsigned long)(1U << p->bit);             /* set Input Mode */
// ??
//    *p->portOutputModeRegisterAddr &= (unsigned long)~(0x1 << p->bit);  /* set Normal Output */

            break;


        case OUTPUT:
            *p->portModeRegisterAddr &= (unsigned long)~(0x1 << p->bit);        /* set Output Mode */
            *p->portRegisterAddr &= (unsigned long)~(0x1 << p->bit);            /* clear Port */
            break;
        }
    }
}

// Forcing this inline keeps the callers from having to push their own stuff
// on the stack. It is a good performance win and only takes 1 more byte per
// user than calling. (It will take more bytes on the 168.)
//
// But shouldn't this be moved into pinMode? Seems silly to check and do on
// each digitalread or write.
//
// Mark Sproul:
// - Removed inline. Save 170 bytes on atmega1280
// - changed to a switch statment; added 32 bytes but much easier to read and maintain.
// - Added more #ifdefs, now compiles for atmega645
//


/**********************************************************************************************************************
 * Function Name: pin output
 * Description  : Perform port output
 * Arguments    : pin  - pin number
 *              : pp   - output value
 * Return Value : -
 *********************************************************************************************************************/
void digitalWrite(uint8_t pin, uint8_t val)
{
  //PinTableType* p;
  //PinTableType pin_tbl;
  //p =(PinTableType*)&pin_tbl;

  const PinTableType **pp;
  PinTableType *p;
  pp = &pinTablelist[pin];

  if (pin < NUM_DIGITAL_PINS) {
    //getPinTable(pin,p);
    p = (PinTableType *)*pp;
#if 0
        if (*p->portModeRegisterAddr & p->mask) {
            /* When Input Mode */
        }
        else
#endif
    {
      /* When Output Mode  */
      if (val == LOW) {
        *p->portRegisterAddr &= ~p->mask;        /* Write "0" to Port */
      } else {
        *p->portRegisterAddr |= p->mask;        /* Write "1" to Port */
      }
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
  int    s16Value;
  if (pin < NUM_DIGITAL_PINS) {
    //PinTableType* p;
    //PinTableType pin_tbl;
    //p =(PinTableType*)&pin_tbl;
    //getPinTable(pin,p);

    const PinTableType **pp;
    PinTableType *p;
    pp = &pinTablelist[pin];
    p = (PinTableType *)*pp;

    if (*p->portRegisterAddr & p->mask) {
      return HIGH;
    }
  }
  return LOW;
}

