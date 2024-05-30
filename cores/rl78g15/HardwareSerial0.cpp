/*
  HardwareSerial.cpp - Hardware serial library for Wiring
  Copyright (c) 2006 Nicholas Zambetti.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

  Modified 23 November 2006 by David A. Mellis
  Modified 28 September 2010 by Mark Sproul
  Modified 14 August 2012 by Alarus
  Modified 7 March 2013 by masahiko.nagata.cj@renesas.com
  Modified 30 June 2013 by yuuki.okamiya.yn@renesas.com
  Modified 13 Mar 2018 by yuuki.okamiya.yn@renesas.com
*/
/*
 * FIXME: Temporary: Debug Display Mode
 *    Remove this macro definition and macro use later,
 *    if `Serial.write()` is fixed to work.
 */
/* #define DEBUGDISP_MODE */

#include <stdlib.h>
#include <stdio.h>
#include <Arduino.h>

#include "platform.h"
#include "main.h"
// #include "Arduino.h"
#include "HardwareSerial.h"

#include "r_cg_macrodriver.h"
extern "C" {
#if defined(USE_UART0) & (USE_UART0==1)
    #include "Config_UART0.h"
#endif /* ( UART_CHANNEL == 0 ) */
#if defined(USE_UART1) & (USE_UART1==1)
    #include "Config_UART1.h"
#endif /* ( UART1_CHANNEL == 1 ) */
    void Set_Char_Serial_from_buf(uint8_t chn);
};

#if defined(USE_UART0) & (USE_UART0==1)
#define URT_RXDx     RXD0
#define URT_TXDx     TXD0
#define URT_PERx     PER0.per0
#define URT_SAUxEN   SAU0EN             /* :PER0.2  */
#define URT_SPSx     SPS0
#define URT_STx      ST0
#define URT_MKxx     MK0H.mk0h
#define URT_IFxx     IF0H.if0h
#define URT_PR1xx    PR10H.pr10h
#define URT_PR0xx    PR00H.pr00h
#define URT_STMKx    STMK0              /* :MK0H.5  */
#define URT_STIFx    STIF0              /* :IF0H.5  */
#define URT_SRMKx    SRMK0              /* :MK0H.6  */
#define URT_SRIFx    SRIF0              /* :IF0H.6  */
#define URT_SREMKx   SREMK0             /* :MK0H.7  */
#define URT_SREIFx   SREIF0             /* :IF0H.7  */
#define URT_STPR1x   STPR10             /* :PR10H.5 */
#define URT_STPR0x   STPR00             /* :PR00H.5 */
#define URT_SRPR1x   SRPR10             /* :PR10H.6 */
#define URT_SRPR0x   SRPR00             /* :PR00H.6 */
#define URT_SREPR1x  SREPR10            /* :PR10H.7 */
#define URT_SREPR0x  SREPR00            /* :PR00H.7 */
#define URT_SMRx0    SMR00
#define URT_SCRx0    SCR00
#define URT_SDRx0    SDR00
#define URT_NFENx    NFEN0
#define URT_SNFENxx  SNFEN00            /* :NFEN0.0 */
#define URT_SIRx1    SIR01
#define URT_SMRx1    SMR01
#define URT_SCRx1    SCR01
#define URT_SDRx1    SDR01
#define URT_SOx      SO0.so0
#define URT_SOxx     SO00               /* :SO0.0   */
#define URT_SOLx     SOL0
#define URT_SOLxx    SOL00              /* :SOL0.0  */
#define URT_SOEx     SOE0
#define URT_SOExx    SOE00              /* :SOE0.0  */
#define URT_SSx      SS0
#define URT_SSxx     SS00               /* :SS0.0   */
#define URT_SSRx     SSR00
#define URT_Px       P1
#define URT_PMx      PM1
#define URT_TXD_Px   0x04
#define URT_RXD_Px   0x02
#endif /* ( UART_CHANNEL == 0 ) */

#if defined(USE_UART1) & (USE_UART1==1)
#define URT1_RXDx     RXD1
#define URT1_TXDx     TXD1
#define URT1_PERx     PER0.per0
#define URT1_SAUxEN   SAU1EN            /* :PER0.2  */
#define URT1_SPSx     SPS1
#define URT1_STx      ST1
#define URT1_MKxx     MK1L.mk1l
#define URT1_IFxx     IF1L.if1l
#define URT1_PR1xx    PR11L.pr11l
#define URT1_PR0xx    PR01L.pr01l
#define URT1_STMKx    STMK1             /* :MK1L.0  */
#define URT1_STIFx    STIF1             /* :IF1L.0  */
#define URT1_SRMKx    SRMK1             /* :MK1L.1  */
#define URT1_SRIFx    SRIF1             /* :IF1L.1  */
#define URT1_SREMKx   SREMK1            /* :MK1L.2  */
#define URT1_SREIFx   SREIF1            /* :IF1L.2  */
#define URT1_STPR1x   STPR11            /* :PR11L.0 */
#define URT1_STPR0x   STPR01            /* :PR01L.0 */
#define URT1_SRPR1x   SRPR11            /* :PR11L.1 */
#define URT1_SRPR0x   SRPR01            /* :PR01L.1 */
#define URT1_SREPR1x  SREPR11           /* :PR11L.2 */
#define URT1_SREPR0x  SREPR01           /* :PR01L.2 */
#define URT1_SMRx0    SMR02
#define URT1_SCRx0    SCR02
#define URT1_SDRx0    SDR02
#define URT1_NFENx    NFEN0
#define URT1_SNFENxx  SNFEN10           /* :NFEN0.2 */
#define URT1_SIRx1    SIR03
#define URT1_SMRx1    SMR03
#define URT1_SCRx1    SCR03
#define URT1_SDRx1    SDR03
#define URT1_SOx      SO0.so0
#define URT1_SOxx     SO02              /* :SO0.2   */
#define URT1_SOLx     SOL0.sol0
#define URT1_SOLxx    SOL02             /* :SOL0.2  */
#define URT1_SOEx     SOE0
#define URT1_SOExx    SOE02             /* :SOE0.2  */
#define URT1_SSx      SS0
#define URT1_SSxx     SS02              /* :SS0.2   */
#define URT1_SSRx     SSR02
#define URT1_Px       P0
#define URT1_PMx      PM0
#ifdef GRCOTTON
#define URT1_TXD_Px   0x04
#define URT1_RXD_Px   0x08
#define URT1_PMCx     PMC0.pmc0
#else /* GRCOTTON */
#define URT1_TXD_Px   0x01
#define URT1_RXD_Px   0x02
#endif /* GRCOTTON */
#endif /* ( UART1_CHANNEL == 1 ) */


/*
 * this next line disables the entire HardwareSerial.cpp,
 * this is so I can support Attiny series and any other chip without a uart
 */

#include "HardwareSerial.h"

/*
 * Define constants and variables for buffering incoming serial data.  We're
 * using a ring buffer (I think), in which head is the index of the location
 * to which to write the next incoming character and tail is the index of the
 * location from which to read.
 */

// 2022/08/01
//  #define SERIAL_BUFFER_SIZE 256
#define SERIAL_BUFFER_SIZE 32


/*
void serialEventRun(void)
{
;
}
*/

fInterruptFunc_t uart_receive_callback_table[3] __attribute__((weak));
fInterruptFunc_t uart_transmit_callback_table[3] __attribute__((weak));

// Constructors ////////////////////////////////////////////////////////////////

/**********************************************************************************************************************
 * Function Name: HardwareSerial::HardwareSerial
 * Description  : Constructor
 * Arguments    : ubrrh - (Not Used)
 *              : ubrrl - (Not Used)
 *              : ucsra - (Not Used)
 *              : ucsrb - (Not Used)
 *              : ucsrc - (Not Used)
 *              : udr   - (Not Used)
 *              : rxen  - UART channel
 *              : txen  - (Not Used)
 *              : rxcie - (Not Used)
 *              : udrie - (Not Used)
 *              : u2x   - (Not Used)
 * Return Value : void
 *********************************************************************************************************************/
HardwareSerial::HardwareSerial(
  volatile uint8_t *ubrrh, volatile uint8_t *ubrrl,
  volatile uint8_t *ucsra, volatile uint8_t *ucsrb,
  volatile uint8_t *ucsrc, volatile uint8_t *udr,
  uint8_t rxen, uint8_t txen, uint8_t rxcie, uint8_t udrie, uint8_t u2x)
{
    _urt_channel    = rxen;
    _rx_buffer_head = 0;
    _rx_buffer_tail = 0;
    _tx_buffer_head = 0;
    _tx_buffer_tail = 0;
    _rx_buf_size    = 0;
    _tx_buf_size    = 0;
    _rx_buffer      = 0;
    _tx_buffer      = 0;
    transmitting    = 0;
    receive_buffer  = 0;
    write_error = 0;
}

/**********************************************************************************************************************
 * Function Name: HardwareSerial::HardwareSerial
 * Description  : Constructor
 * Arguments    : rxen - UART channel
 * Return Value : void
 *********************************************************************************************************************/
HardwareSerial::HardwareSerial(uint8_t rxen)
{
    _urt_channel   = rxen;
    _rx_buffer_head = 0;
    _rx_buffer_tail = 0;
    _tx_buffer_head = 0;
    _tx_buffer_tail = 0;
    _rx_buf_size    = 0;
    _tx_buf_size    = 0;
    _rx_buffer      = 0;
    _tx_buffer      = 0;
    transmitting    = 0;
    receive_buffer  = 0;
    write_error = 0;
}

// Public Methods //////////////////////////////////////////////////////////////

/**********************************************************************************************************************
 * Function Name: HardwareSerial::begin
 * Description  : Initialize and configure the serial port.
 * Arguments    : baud   - baud rate
 *              :          { 300, 600, 1200, 2400, 4800, 9600, 14400, 19200, 28800, 31250, 38400, 57600, 115200 }
 * Return Value : void
 *********************************************************************************************************************/
void HardwareSerial::begin(unsigned long baud)
{
    begin(baud, SERIAL_8N1);
}

/**********************************************************************************************************************
 * Function Name: HardwareSerial::begin
 * Description  : Initialize and configure the serial port.
 * Arguments    : baud   - baud rate
 *              :          { 300, 600, 1200, 2400, 4800, 9600, 14400, 19200, 28800, 31250, 38400, 57600, 115200 }
 *              : config - serial port setting
 *               :         SERIAL_{ 8, 7 }{ N, E }{ 1, 2 }
 * Return Value : void
 *********************************************************************************************************************/
void HardwareSerial::begin(unsigned long baud, uint16_t config){
    begin(baud, config, SERIAL_BUFFER_SIZE, SERIAL_BUFFER_SIZE);
}

/**********************************************************************************************************************
 * Function Name: HardwareSerial::begin
 * Description  : Initialize and configure the serial port.
 * Arguments    : baud   - baud rate
 *              :          { 300, 600, 1200, 2400, 4800, 9600, 14400, 19200, 28800, 31250, 38400, 57600, 115200 }
 *              : rx_buf - receive  buffer size
 *              : tx_buf - transmit buffer size
 * Return Value : void
 *********************************************************************************************************************/
void HardwareSerial::begin(unsigned long baud, int rx_buf, int tx_buf){
    begin(baud, SERIAL_8N1, rx_buf, tx_buf);
}


/**********************************************************************************************************************
 * Function Name: HardwareSerial::begin
 * Description  : Initialize and configure the serial port.
 * Arguments    : baud   - baud rate
 *              :          { 300, 600, 1200, 2400, 4800, 9600, 14400, 19200, 28800, 31250, 38400, 57600, 115200 }
 *              : config - serial port setting
 *               :         SERIAL_{ 8, 7 }{ N, E }{ 1, 2 }
 *              : rx_buf - receive  buffer size
 *              : tx_buf - transmit buffer size
 * Return Value : void
 *********************************************************************************************************************/
void HardwareSerial::begin(unsigned long baud, uint16_t config, int rx_buf, int tx_buf)
{
    /* Initialize Unit */
    /* begin executed. end call */
    if ((0 != _rx_buffer) || (0 != _tx_buffer)){
        return;
    }
    if ((1 == rx_buf) || (1 == tx_buf)){
        return;
    }
//    _rx_buffer = (uint8_t *)malloc(rx_buf * sizeof(uint8_t));
    _rx_buffer = base_rx_buffer;
    if (0 == _rx_buffer){
        _rx_buf_size = 0;
        _tx_buf_size = 0;
        return;
    }
//    _tx_buffer = (uint8_t *)malloc(tx_buf * sizeof(uint8_t));
    _tx_buffer = base_tx_buffer;
    if (0 == _tx_buffer){
//        free((uint8_t *)_rx_buffer);
        _rx_buffer = 0;
        _rx_buf_size = 0;
        _tx_buf_size = 0;
        return;
    }
    _rx_buf_size = rx_buf;
    _tx_buf_size = tx_buf;
    _rx_buffer_head = 0;
    _rx_buffer_tail = 0;
    _tx_buffer_head = 0;
    _tx_buffer_tail = 0;

#if defined(USE_UART0) & (USE_UART0==1)
    R_Config_UART0_Create();
    Set_Baudrate(baud);
    Set_SerialPort(SERIAL_TXD0,SERIAL_RXD0);
    Set_Config(config);
    R_Config_UART0_Start();
    R_Config_UART0_Receive((uint8_t * const)&receive_buffer,1);
#endif /* UART_CHANNEL==0 */
#if defined(USE_UART1) & (USE_UART1==1)
    R_Config_UART1_Create();
    Set_Baudrate(baud);
    Set_SerialPort(SERIAL_TXD1,SERIAL_RXD1);
    Set_Config(config);
    R_Config_UART1_Start();
    R_Config_UART1_Receive((uint8_t * const)&receive_buffer,1);
#endif /* UART1_CHANNEL==1 */


}

/**********************************************************************************************************************
 * Function Name: HardwareSerial::end
 * Description  : Terminate the serial port processing.
 * Arguments    : -
 * Return Value : void
 *********************************************************************************************************************/
void HardwareSerial::end()
{
#if defined(USE_UART0) & (USE_UART0==1)
    R_Config_UART0_Stop();
#endif /* UART_CHANNEL==0 */
#if defined(USE_UART1) & (USE_UART1==1)
    R_Config_UART1_Stop();
#endif /* UART1_CHANNEL==1 */

    if(_rx_buffer!= 0)
    {
//        free((uint8_t *)_rx_buffer);
        _rx_buffer = 0;
    }
    if(_tx_buffer!= 0)
    {
//        free((uint8_t *)_tx_buffer);
        _tx_buffer = 0;
    }
    _rx_buffer_head = 0;
    _rx_buffer_tail = 0;
    _tx_buffer_head = 0;
    _tx_buffer_tail = 0;
    _rx_buf_size = 0;
    _tx_buf_size = 0;
}

/**********************************************************************************************************************
 * Function Name: HardwareSerial::available
 * Description  : Get the number of readable data bytes of received data.
 * Arguments    : -
 * Return Value : size of readable data
 *********************************************************************************************************************/
int HardwareSerial::available(void)
{
    int head = 0;
    int tail = 0;
    noInterrupts();
    head = _rx_buffer_head;
    tail = _rx_buffer_tail;
    interrupts();
    if (head >= tail) return head - tail;
    return (_rx_buf_size - tail + head );
}

/**********************************************************************************************************************
 * Function Name: HardwareSerial::peek
 * Description  : Read received data by 1 byte and do not change the buffer position.
 * Arguments    : -
 * Return Value : -1    - no read data
 *              : other - read data
 *********************************************************************************************************************/
/*
int HardwareSerial::peek(void)
{
  if (_rx_buffer_head == _rx_buffer_tail) {
    return -1;
  } else {
    return _rx_buffer[_rx_buffer_tail];
  }
}
*/
/**********************************************************************************************************************
 * Function Name: HardwareSerial::read
 * Description  : Read received data by 1 byte and advance the buffer position by 1 byte.
 * Arguments    : -
 * Return Value : -1    - no read data
 *              : other - read data
 *********************************************************************************************************************/
int HardwareSerial::read(void)
{
    /* if the head isn't ahead of the tail, we don't have any characters */
    noInterrupts();
    if (_rx_buffer_head == _rx_buffer_tail) {
        interrupts();
        return -1;
    }
    unsigned char c = _rx_buffer[_rx_buffer_tail];
    _rx_buffer_tail = (_rx_buffer_tail + 1) % _rx_buf_size;
    interrupts();

    return c;
}

/**********************************************************************************************************************
 * Function Name: HardwareSerial::flush
 * Description  : Wait for all data transmission in the transmission buffer to be completed.
 * Arguments    : -
 * Return Value : void
 *********************************************************************************************************************/
/*
void HardwareSerial::flush()
{
  //  buffer is none
  if (0 == _tx_buf_size || 0 == _tx_buffer){
    return;
  }

#if defined(USE_UART0) & (USE_UART0==1)
    while (SSR00 & 0x0060) {  // check TSF00 and BFF00
      ;
  }
#endif // ( UART_CHANNEL == 0 )
#if defined(USE_UART1) & (USE_UART1==1)
    while (SSR02 & 0x0060) {  // check TSF02 and BFF02
      ;
    }
#endif //  ( UART1_CHANNEL == 1 )


  while(_tx_buf_size-1!=availableForWrite())
  {
    NOP();
  }
}
*/

/**********************************************************************************************************************
 * Function Name: HardwareSerial::UART_Send
 * Description  : Transmit data to the target serial port (actual implementation of write operation).
 * Arguments    : c - transmission data
 * Return Value : -1    - write failed with the transmission buffer overflow
 *              : other - written data size
 *********************************************************************************************************************/
size_t HardwareSerial::UART_Send(uint8_t c)
{
    MD_STATUS err = MD_OK;
    int i;
    uint8_t isp;

    /* buffer is none */
    if (0 == _tx_buf_size){
        return -1;
    }

    isp = GET_PSW_ISP();

    noInterrupts();
    if(_tx_buffer_tail == _tx_buffer_head){
        /* Unsent */
        int head = (_tx_buffer_head + 1);
        i = (_tx_buffer_head + 1) % _tx_buf_size;
        _tx_buffer[_tx_buffer_head] = c;
        _tx_buffer_head = i;
        interrupts();
#if defined(USE_UART0) & (USE_UART0==1)
        if((SSR00 & 0x20) != 0)/*BFF00*/
        {
            return -1;
        }
        err = R_Config_UART0_Send((uint8_t * const)&c,1);
#endif /* ( UART_CHANNEL == 0 ) */
#if defined(USE_UART1) & (USE_UART1==1)
        if((SSR02 & 0x20) != 0)/*BFF00*/
        {
            return -1;
        }
        err = R_Config_UART1_Send((uint8_t * const)&c,1);
#endif /* ( UART1_CHANNEL == 1 ) */

    }
    else
    {
        /* only buffer copy during transmission process */
        i = (_tx_buffer_head + 1) % _tx_buf_size;
        if(i == _tx_buffer_tail)
        {
            /* buffer over */
			if(ISP_LEVEL_3 == isp)
			{
				/* When called from main program(setup() or loop() */
				interrupts();
				while(i == _tx_buffer_tail)
				{
					;
				}
				noInterrupts();
			}
			else
			{
				/* When called from interuupt function (ex. callback routine for periodic processing */
                switch (_urt_channel)
                {
                    case 0:
        #if defined(USE_UART0) & (USE_UART0==1)
                        while((SSR00 & 0x20) != 0)/*BFF00*/
                        {
                            ;
                        }
                        STIF0 = 0;
        #endif /* ( UART_CHANNEL == 0 ) */
                        break;
                    case 1:
        #if defined(USE_UART1) & (USE_UART1==1)
                        while((SSR02 & 0x20) != 0)/*BFF00*/
                        {
                            ;
                        }
                        STIF1 = 0;
        #endif /* ( UART1_CHANNEL == 1 ) */
                        break;
                }
                Set_Char_Serial_from_buf(_urt_channel);
                if(0 != uart_transmit_callback_table[_urt_channel])
                {
                    (*uart_transmit_callback_table[_urt_channel])();
                }
            }
//            interrupts();
//            return -1;
        }
        _tx_buffer[_tx_buffer_head] = c;
        _tx_buffer_head = i;
        interrupts();
    }
    if(err == MD_OK){
        return 1;
    }
    return -1;
}

/**********************************************************************************************************************
 * Function Name: HardwareSerial::write
 * Description  : Transmit data to the target serial port.
 * Arguments    : c - transmission data
 * Return Value : -1    - write failed with the transmission buffer overflow
 *              : other - written data size
 *********************************************************************************************************************/

size_t HardwareSerial::write(uint8_t c)
{
    size_t err = 0;
    err = UART_Send(c);
    return err;
}


/**********************************************************************************************************************
 * Function Name: HardwareSerial::availableForWrite
 * Description  : Get the number of available transmit buffer space for write.
 * Arguments    : -
 * Return Value : size of transmit buffer free space
 *********************************************************************************************************************/
int HardwareSerial::availableForWrite(void)
{
  int head = 0;
  int tail = 0;
  noInterrupts();
  head = _tx_buffer_head;
  tail = _tx_buffer_tail;
  interrupts();
  if (head >= tail) return _tx_buf_size - 1 - head + tail;
  return (tail - head - 1);
}

/**********************************************************************************************************************
 * Function Name: HardwareSerial::availableForRead
 * Description  : Get the number of available receive buffer space for read.
 * Arguments    : -
 * Return Value : size of receive buffer free space
 *********************************************************************************************************************/
int HardwareSerial::availableForRead(void)
{
  int head = 0;
  int tail = 0;
  noInterrupts();
  head = _rx_buffer_head;
  tail = _rx_buffer_tail;
  interrupts();
  if (head >= tail) return _rx_buf_size - 1 - head + tail;
  return (tail - head - 1);
}

HardwareSerial::operator bool() {
    return true;
}

/* Load Send data from Send Buffer & Start New Send Function */
/**********************************************************************************************************************
 * Function Name: HardwareSerial::load_char
 * Description  : Extract 1 byte from the transmit buffer and send it.
 *              : Called from the transmission complete interrupt handler.
 *              : Unavailable for the other purpose.
 * Arguments    :  -
 * Return Value :  -
 *********************************************************************************************************************/
void HardwareSerial::load_char(void){
    int i = (_tx_buffer_tail + 1) % _tx_buf_size;
    _tx_buffer_tail = i;
    if (i != _tx_buffer_head) {
        uint8_t send_buffer  = _tx_buffer[i];
#if defined(USE_UART0) & (USE_UART0==1)
        R_Config_UART0_Send((uint8_t * const)&send_buffer,1);
#endif /* (UART_CHANNEL == 0) */
#if defined(USE_UART1) & (USE_UART1==1)
        R_Config_UART1_Send((uint8_t * const)&send_buffer,1);
#endif /* (UART1_CHANNEL == 1) */
    }
}

/* Store Received data to Receive Buffer & Start New Receive Function */
/**********************************************************************************************************************
 * Function Name: HardwareSerial::store_char
 * Description  : Store 1 byte of the last received data in the receive buffer
 *              : and continue the receive process for the following bytes.
 *              : Called from the receive complete interrupt handler.
 *              : Unavailable for the other purpose.
 * Arguments    : -
 * Return Value : -
 *********************************************************************************************************************/
void HardwareSerial::store_char(void){
    store_char(receive_buffer);
    receive_buffer = 0;
#if defined(USE_UART0) & (USE_UART0==1)
    R_Config_UART0_Receive((uint8_t * const)&receive_buffer,1);
#endif /* (UART_CHANNEL == 0) */
#if defined(USE_UART1) & (USE_UART1==1)
    R_Config_UART1_Receive((uint8_t * const)&receive_buffer,1);
#endif /* (UART1_CHANNEL == 1) */


}

/**********************************************************************************************************************
 * Function Name: HardwareSerial::store_char
 * Description  : Store 1 byte of the last received data in the receive buffer
 *              : and continue the receive process for the following bytes.
 *              : Make sure to disable interrupts before calling this from outside of the interrupt handler.
 * Arguments    : c - byte to store
 * Return Value : -
 *********************************************************************************************************************/
void HardwareSerial::store_char(unsigned char c){
  int i = (_rx_buffer_head + 1) % _rx_buf_size;
  if (i != _rx_buffer_tail) {
    _rx_buffer[_rx_buffer_head] = c;
    _rx_buffer_head = i;
  }
}

#define NUM_BAUD_RATE 6
unsigned long constBaudRate[]={2400, 4800, 9600, 19200, 38400, 115200};
int16_t constSDR[]={103, 103, 103, 103, 103, 34};
int16_t constPRS[]={5, 4, 3, 2, 1, 1};

/* Add for RL78/G23 */
/**********************************************************************************************************************
 * Function Name: HardwareSerial::Set_Baudrate
 * Description  : Set baud rate for the serial port.
 * Arguments    : baudrate - baud rate
 *              :            { 300, 600, 1200, 2400, 4800, 9600, 14400, 19200, 28800, 31250, 38400, 57600, 115200 }
 * Return Value : void
 *********************************************************************************************************************/
void HardwareSerial::Set_Baudrate(unsigned long baudrate)
{
    uint8_t  sdr;
    uint8_t  prs;

    for(int i = 0;i<NUM_BAUD_RATE;i++){
        if(baudrate == constBaudRate[i]){
            sdr = constSDR[i];
            prs = constPRS[i];
            break;
        }
    }

#if defined(USE_UART0) & (USE_UART0==1)
    ST0  &= 0xFC;
    SS0  &= 0xFC;
    SPS0 &= (0x00F0) ;
    SPS0 |=  prs ;
    SDR00 = sdr << 9 ;
    SDR01 = sdr << 9 ;
    SS0  |= 0x03;
    ST0  |= 0x03;
#endif /* ( UART_CHANNEL == 0 ) */
#if defined(USE_UART1) & (USE_UART1==1)
    ST0  &= 0xF3;
    SS0  &= 0xF3;
    SPS0 &= (0x00F0) ;
    SPS0 |=  prs ;
    SDR02 = sdr << 9 ;
    SDR03 = sdr << 9 ;
    SS0  |= 0x0C;
    ST0  |= 0x0C;
#endif /* ( UART1_CHANNEL == 1 ) */
}

/*
void HardwareSerial::Set_Baudrate(unsigned long baurate)
{
    uint32_t fclk_frequency;
    uint32_t  peri_clk    ;
    uint8_t  sdr     ;
    uint16_t tmp_sdr ;
    uint8_t  prs = 0U;
    fclk_frequency = R_BSP_GetFclkFreqHz();

    peri_clk    = (fclk_frequency) ; // SPSmk0\[3:0] = 0x0

    tmp_sdr = ((peri_clk/baurate) >> 1) -1 ;
    while(0x007F<tmp_sdr)
    {
        prs++;
        peri_clk = (peri_clk >> 1);
        tmp_sdr  = ((peri_clk/baurate) >> 1) -1 ;
    }
    sdr     = (uint8_t)(tmp_sdr & 0x007F) ;

    ST0  &= 0xFC;
    SS0  &= 0xFC;
    SPS0 &= (0x00F0) ;
    SPS0 |=  prs ;
    SDR00 = sdr << 9 ;
    SDR01 = sdr << 9 ;
    SS0  |= 0x03;
    ST0  |= 0x03;
}
*/

/**********************************************************************************************************************
 * Function Name: HardwareSerial::Set_Config
 * Description  : Set the serial data length, parity, and stop bit.
 * Arguments    : config - serial port setting
 *               :         SERIAL_{ 8, 7 }{ N, E }{ 1, 2 }
 * Return Value : void
 *********************************************************************************************************************/
void HardwareSerial::Set_Config(uint16_t config )
{
    /* Rewriting prohibited when SEmn = 1 / Set_Config is called between R_Config_UART0_Create () and R_Config_UART0_Start (), so SEmn = 0*/
    /* SCR00 16bit*/
#if defined(USE_UART0) & (USE_UART0==1)
    unsigned short SCR00data=_8000_SAU_TRANSMISSION| _0000_SAU_INTSRE_MASK |0x4 |_0080_SAU_LSB | config;
    /* When sending, _0000_SAU_INTSRE_MASK :EOCmn = 0*/
    unsigned short SCR01data=_4000_SAU_RECEPTION| _0400_SAU_INTSRE_ENABLE |0x4 |_0080_SAU_LSB |config;
    /* _0400_SAU_INTSRE_ENABLE: EOCmn = 1 Allow the occurrence of the error interrupt INTSREx */
    /* SLCmn1: 0 SLCmn0: 1 when receiving XXXXXXXXXX01XXXX*/
    SCR01data &= 0xFFDF;
    SCR01data |= 0x0010;
    SCR00 = SCR00data;
    SCR01 = SCR01data;
#endif /* ( UART_CHANNEL == 0 ) */
#if defined(USE_UART1) & (USE_UART1==1)
    unsigned short SCR02data=_8000_SAU_TRANSMISSION| _0000_SAU_INTSRE_MASK |0x4 |_0080_SAU_LSB |config;
    unsigned short SCR03data=_4000_SAU_RECEPTION| _0400_SAU_INTSRE_ENABLE |0x4 |_0080_SAU_LSB |config;
    /* SLCmn1: 0 SLCmn0: 1 when receiving XXXXXXXXXX01XXXX*/
    SCR03data &= 0xFFDF;
    SCR03data |= 0x0010;

    SCR02 = SCR02data;
    SCR03 = SCR03data;
#endif /* ( UART1_CHANNEL == 1 ) */

}

/**********************************************************************************************************************
 End of function Set_Config
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Function Name: HardwareSerial::Set_SerialPort
 * Description  : Set serial port pins for the target port.
 * Arguments    : txd_pin - transmit pin no.
 *              : rxd_pin - receive  pin no.
 * Return Value : void
 *********************************************************************************************************************/
void HardwareSerial::Set_SerialPort(uint8_t txd_pin,uint8_t rxd_pin)
{
//    PinTableType* p;
//    PinTableType pin_tbl;
//    p = (PinTableType*)&pin_tbl;

    /* Set RxD pin */

    /* Set RxD0 pin */
    PMC0 &= 0xFDU;
    PM0 |= 0x02U;
//    getPinTable(rxd_pin,p);
    /* Set PM Register for Input */
//    *p->portModeRegisterAddr |=  (unsigned long)(0x1 << p->bit);

    /* Set PMC Register */
//    if (0!=p->pmc){
//      *p->portModeControlRegisterAddr &= (unsigned long)~(p->pmc);
//    }


    /* Set TxD pin */
//    getPinTable(txd_pin,p);
    /* Set TxD0 pin */

    PM0 &= 0xFEU;
    P0 |= 0x01U;

    /* Set P Register for Set "H" Output Port*/
//    *p->portRegisterAddr |= (unsigned long)(0x1 << p->bit);

    /* Set PM Register for Output */
//    *p->portModeRegisterAddr &= (unsigned long)~(0x1 << p->bit);

}

void HardwareSerial::setReceiveCallback(void (*userFunc)(void))
{
    uart_receive_callback_table[_urt_channel] = userFunc;
}
void HardwareSerial::setTransmitCallback(void (*userFunc)(void))
{
    uart_transmit_callback_table[_urt_channel] = userFunc;
}

extern "C" {
    /**********************************************************************************************************************
     * Function Name: Set_Char_Serial_to_buf
     * Description  : Store the received data in the buffer.
     *              : Called from the receive interrupt handler.
     * Arguments    : chn - UART channel
     * Return Value : void
     *********************************************************************************************************************/
    void Set_Char_Serial_to_buf(uint8_t chn)
    {
    #if defined(USE_UART0) & (USE_UART0==1)
            Serial.store_char();
    #endif
    #if defined(USE_UART1) & (USE_UART1==1)
            Serial1.store_char();
    #endif
    }

    /**********************************************************************************************************************
     * Function Name: Set_Char_Serial_from_buf
     * Description  : Load write data from the buffer.
     * Arguments    : chn  - UART_CHANNEL
     * Return Value : void         -
     *********************************************************************************************************************/

    void Set_Char_Serial_from_buf(uint8_t chn)
    {

#if defined(USE_UART0) & (USE_UART0==1)
        Serial.load_char();
#endif
#if defined(USE_UART1) & (USE_UART1==1)
        Serial1.load_char();
#endif
    }

}

// Preinstantiate Objects //////////////////////////////////////////////////////
#if defined(USE_UART0) & (USE_UART0==1)
  HardwareSerial Serial(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
#endif
#if defined(USE_UART1) & (USE_UART1==1)
  HardwareSerial Serial1(0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0);
#endif

