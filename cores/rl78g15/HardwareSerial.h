#ifndef HardwareSerial_h
#define HardwareSerial_h

// #include <inttypes.h>
// #include "Stream.h"
#include "pintable.h"
// #include "Printable.h"

#include "main.h"

#define DEC 10
#define HEX 16
#define OCT 8
#ifdef BIN // Prevent warnings if BIN is previously defined in "iotnx4.h" or similar
#undef BIN
#endif
#define BIN 2

class HardwareSerial
{
  private:
    /* uint8_t _urt_channel; */
    uint8_t receive_buffer;
    bool transmitting;
    size_t UART_Send(uint8_t c);
    /* size_t UART_Send(const uint8_t *buffer, size_t size); */
    void Set_SerialPort(void);
    /* Add 2021.02.09 */
    void Set_Baudrate(unsigned long baurate);
    void Set_Config(uint16_t config);
    int write_error;
    size_t printNumber(unsigned long, uint8_t);
    size_t printFloat(double, uint8_t);

  public:
    HardwareSerial(
      volatile uint8_t *ubrrh, volatile uint8_t *ubrrl,
      volatile uint8_t *ucsra, volatile uint8_t *ucsrb,
      volatile uint8_t *ucsrc, volatile uint8_t *udr,
      uint8_t rxen, uint8_t txen, uint8_t rxcie, uint8_t udrie, uint8_t u2x);
    HardwareSerial(uint8_t rxen);
    /*API*/
    void begin(unsigned long baud);
    void begin(unsigned long baud, uint16_t config);
    void begin(unsigned long baud, int rx_buf, int tx_buf);
    void begin(unsigned long baud, uint16_t config, int rx_buf, int tx_buf);
    void end();
//    virtual int available(void) override;
    int available(void);
//    virtual int peek(void) override;
//    virtual int read(void) override ;
    int read(void);
    void flush();
//    virtual void flush(void) override;
//    virtual size_t write(uint8_t c) override;
    size_t write(const uint8_t *buffer, size_t size);
    size_t write(uint8_t c);
    inline size_t write(unsigned long n) { return write((uint8_t)n); }
    inline size_t write(long n) { return write((uint8_t)n); }
    inline size_t write(unsigned int n) { return write((uint8_t)n); }
    inline size_t write(int n) { return write((uint8_t)n); }
    size_t write(const char *str);
//    virtual size_t write(const uint8_t *buffer, size_t size);
    size_t write(const char *buffer, size_t size);
//    using Print::write; /* pull in write(str) and write(buf, size) from Print */
//    int availableForWrite(void) override;
    int availableForWrite(void);
    int availableForRead(void);
    void store_char(unsigned char c);
    void setReceiveCallback(void (*userFunc)(void));
    void setTransmitCallback(void (*userFunc)(void));
    void load_char(void);
    void store_char(void);
    size_t print(const String &);
    size_t print(const char[]);
    size_t print(char);
    size_t print(unsigned char, int = DEC);
    size_t print(int, int = DEC);
    size_t print(unsigned int, int = DEC);
    size_t print(long, int = DEC);
    size_t print(unsigned long, int = DEC);
    size_t print(double, int = 2);
//    size_t print(const Printable&);
    size_t println(const String &s);
    size_t println(const char[]);
    size_t println(char);
    size_t println(unsigned char, int = DEC);
    size_t println(int, int = DEC);
    size_t println(unsigned int, int = DEC);
    size_t println(long, int = DEC);
    size_t println(unsigned long, int = DEC);
    size_t println(double, int = 2);
//    size_t println(const Printable&);
    size_t println(void);
    operator bool();
    
  private:
    volatile int _rx_buffer_head;
    volatile int _rx_buffer_tail;
    volatile int _tx_buffer_head;
    volatile int _tx_buffer_tail;
    volatile int _rx_buf_size;
    volatile int _tx_buf_size;
    unsigned char *_rx_buffer;
    unsigned char *_tx_buffer;

    unsigned char base_rx_buffer[32];
    unsigned char base_tx_buffer[32];

    uint8_t _urt_channel;

};


/* Define config for Serial.begin(baud, config); */

#define SERIAL_5N1  0x0013  /* 5bit->8bit */
#define SERIAL_6N1  0x0013  /* 6bit->8bit */
#define SERIAL_7N1  0x0012
#define SERIAL_8N1  0x0013
#define SERIAL_5N2  0x0023  /* 5bit->8bit */
#define SERIAL_6N2  0x0023  /* 6bit->8bit */
#define SERIAL_7N2  0x0022
#define SERIAL_8N2  0x0023
#define SERIAL_5E1  0x0213  /* 5bit->8bit */
#define SERIAL_6E1  0x0213  /* 6bit->8bit */
#define SERIAL_7E1  0x0212
#define SERIAL_8E1  0x0213
#define SERIAL_5E2  0x0223  /* 5bit->8bit */
#define SERIAL_6E2  0x0223  /* 6bit->8bit */
#define SERIAL_7E2  0x0222
#define SERIAL_8E2  0x0223
#define SERIAL_5O1  0x0313  /* 5bit->8bit */
#define SERIAL_6O1  0x0313  /* 6bit->8bit */
#define SERIAL_7O1  0x0312
#define SERIAL_8O1  0x0313
#define SERIAL_5O2  0x0323  /* 5bit->8bit */
#define SERIAL_6O2  0x0323  /* 6bit->8bit */
#define SERIAL_7O2  0x0322
#define SERIAL_8O2  0x0323
#define SERIAL_MASK 0xFCCC

#if defined(USE_UART0) & (USE_UART0==1)
    extern HardwareSerial Serial;
#endif /* (UART_CHANNEL==0)  */
#if defined(USE_UART1) & (USE_UART1==1)
    extern HardwareSerial Serial1;
#endif /* (UART1_CHANNEL==1) */

// extern void serialEventRun(void) __attribute__((weak));

#endif /* HardwareSerial_h */
