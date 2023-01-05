/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products. No
* other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
* applicable laws, including copyright laws.
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED. TO THE MAXIMUM
* EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES
* SHALL BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS
* SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability of
* this software. By using this software, you agree to the additional terms and conditions found by accessing the
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2022 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/
/***********************************************************************************************************************
* File Name    : r_bsp_config_reference.h
* H/W Platform : GENERIC_RL78_G15
* Description  :
***********************************************************************************************************************/
/***********************************************************************************************************************
* History : DD.MM.YYYY Version  Description
*         : 31.05.2022 1.30     First Release

***********************************************************************************************************************/

#ifndef R_BSP_CONFIG_REF_HEADER_FILE
#define R_BSP_CONFIG_REF_HEADER_FILE
/*************************************************
 * MCU information
 *************************************************/
/*
 R 5 F 120  6 8 M  SP #V0
 | | |  |   | | |  |   |_______not used                   Packaging specifications
 | | |  |   | | |  |___________not used                   Package type
 | | |  |   | | |______________not used                   Fields of application
 | | |  |   | |________________BSP_CFG_MCU_PART_ROM_SIZE  ROM capacity
 | | |  |   |__________________BSP_CFG_MCU_PART_PIN_NUM   Pin count
 | | |  |______________________not used                   RL78/G15 group
 | | |_________________________BSP_CFG_MCU_PART_ROM_TYPE  Memory type
 | |___________________________not used                   Renesas MCU
 |_____________________________not used                   Renesas semiconductor product
*/

/* ROM capacity
 7 = 4(KB) : 0x0
 8 = 8     : 0x1
*/
#define BSP_CFG_MCU_PART_ROM_SIZE (0x1)

/* Pin count
 0 = 8-pin   : 0x0
 1 = 10-pin  : 0x1
 4 = 16-pin  : 0x2
 6 = 20-pin  : 0x3
*/
#define BSP_CFG_MCU_PART_PIN_NUM (0x3)

/* group
 120 = RL78/G15 : (true)
*/
#define BSP_CFG_MCU_PART_HAS_DATA_FLASH (true)

/* Memory type
 F = Flash memory : 0
*/
#define BSP_CFG_MCU_PART_ROM_TYPE (0)

#if defined(__ICCRL78__)
/* Option byte setting(When using IAR) */
#define BSP_CFG_OPTBYTE0_VALUE (0xFFU)
#define BSP_CFG_OPTBYTE1_VALUE (0xFFU)
#define BSP_CFG_OPTBYTE2_VALUE (0xF9U)
#define BSP_CFG_OPTBYTE3_VALUE (0x05U)
/* Security ID Codes for On-Chip Debugging setting(When using IAR) */
#define BSP_CFG_SECUID0_VALUE (0xFFU)
#define BSP_CFG_SECUID1_VALUE (0xFFU)
#define BSP_CFG_SECUID2_VALUE (0xFFU)
#define BSP_CFG_SECUID3_VALUE (0xFFU)
#define BSP_CFG_SECUID4_VALUE (0xFFU)
#define BSP_CFG_SECUID5_VALUE (0xFFU)
#define BSP_CFG_SECUID6_VALUE (0xFFU)
#define BSP_CFG_SECUID7_VALUE (0xFFU)
#define BSP_CFG_SECUID8_VALUE (0xFFU)
#define BSP_CFG_SECUID9_VALUE (0xFFU)
#endif

/*************************************************
 * Pin assignment setting
 *************************************************/
/* Peripheral I/O redirection register(PIOR0-PIOR01/PIOR00)
    8,10,16-pin
 00: TI00      - P137
 01: TI00      - P03
 Set PIOR01 to 0.

    20-pin
 00: TI00      - P137
     TO00      - P03
 01: TI00      - P03
     TO00      - P03
 10: TI00      - P20
     TO00      - P21
 11: TI00      - Setting prohibited
     TO00      - Setting prohibited
*/
#define BSP_CFG_PIOR01 (0)
#define BSP_CFG_PIOR00 (0)

/* Peripheral I/O redirection register(PIOR0-PIOR03/PIOR02)
    8-pin
 00: TI01/TO01 - P04
 01: TI01/TO01 - P40
 Set PIOR03 to 0.

    10,16,20-pin
 00: TI01/TO01 - P04
 01: TI01/TO01 - P40
 10: TI01/TO01 - P02
 11: TI01/TO01 - Setting prohibited
*/
#define BSP_CFG_PIOR03 (0)
#define BSP_CFG_PIOR02 (0)

/* Peripheral I/O redirection register(PIOR0-PIOR05/PIOR04)
    8,10-pin
 00: Fixed

    16,20-pin
 00: TI02/TO02 - P05
 01: TI02/TO02 - P01
 10: TI02/TO02 - P41
 11: TI02/TO02 - Setting prohibited
*/
#define BSP_CFG_PIOR05 (0)
#define BSP_CFG_PIOR04 (0)

/* Peripheral I/O redirection register(PIOR0-PIOR07/PIOR06)
    8,10-pin
 00: Fixed

    16-pin
 00: TO03      - P41
 01: TO03      - P07
 Set PIOR07 to 0.

    20-pin
 00: TI03      - P41
     TO03      - P41
 01: TI03      - P41
     TO03      - P07
 10: TI03      - P20
     TO03      - P20
 11: TI03      - Setting prohibited
     TO03      - Setting prohibited
*/
#define BSP_CFG_PIOR07 (0)
#define BSP_CFG_PIOR06 (0)

/* Peripheral I/O redirection register(PIOR1-PIOR11/PIOR10)
    8,10-pin
 00: Fixed

    16,20-pin
 00: SCK00/SCL00     - P02
     SI00/RxD0/SDA00 - P01
     SO00/TxD0       - P00

 01: SCK00/SCL00     - P06
     SI00/RxD0/SDA00 - P05
     SO00/TxD0       - P04

 10: SCK00/SCL00     - P05
     SI00/RxD0/SDA00 - P04
     SO00/TxD0       - P03

 11: SCK00/SCL00     - Setting prohibited
     SI00/RxD0/SDA00 - Setting prohibited
     SO00/TxD0       - Setting prohibited
*/
#define BSP_CFG_PIOR11 (0)
#define BSP_CFG_PIOR10 (0)

/* Peripheral I/O redirection register(PIOR1-PIOR13/PIOR12)
    8,10-pin
 00: Fixed

    16-pin
 00: SCK01/SCL01     - P07
     SI01/SDA01      - P06
     SO01            - P05

 01: SCK01/SCL01     - P00
     SI01/SDA01      - P01
     SO01            - P02
Set PIOR13 to 0.

    20-pin
 00: SCK01           - P07
     SCL01           - P07
     SI01            - P06
     SDA01           - P06
     SO01            - P05

 01: SCK01           - P00
     SCL01           - P00
     SI01            - P01
     SDA01           - P01
     SO01            - P02

 10: SCK01           - P20
     SCL01           - P20
     SI01            - P125
     SDA01           - P41
     SO01            - P41

 11: SCK01           - P07
     SCL01           - P23
     SI01            - P06
     SDA01           - P22
     SO01            - P05
*/
#define BSP_CFG_PIOR13 (0)
#define BSP_CFG_PIOR12 (0)

/* Peripheral I/O redirection register(PIOR1-PIOR14)
    8,10-pin
 0 : Fixed

    16,20-pin
 0 : SCLA0           - P06
     SDAA0           - P07
 1 : SCLA0           - P00
     SDAA0           - P01
*/
#define BSP_CFG_PIOR14 (0)

/* Peripheral I/O redirection register(PIOR2-PIOR20)
    8,10,16-pin
 0: Fixed

    20-pin
 0 : INTP1 - P125
 1 : INTP1 - P20
*/
#define BSP_CFG_PIOR20 (0)

/* Peripheral I/O redirection register(PIOR2-PIOR21)
    8,10-pin
 0 : Fixed

    16,20-pin
 0 : INTP2 - P40
 1 : INTP2 - P122
*/
#define BSP_CFG_PIOR21 (0)

/* Peripheral I/O redirection register(PIOR2-PIOR22)
    8,10-pin
 0 : Fixed

    16,20-pin
 0 : INTP3 - P04
 1 : INTP3 - P121
*/
#define BSP_CFG_PIOR22 (0)

/* Peripheral I/O redirection register(PIOR2-PIOR23)
    8,10-pin
 0 : Fixed

    16,20-pin
 0 : INTP4 - P03
 1 : INTP4 - P41
*/
#define BSP_CFG_PIOR23 (0)

/* Peripheral I/O redirection register(PIOR2-PIOR25/PIOR24)
    8,10-pin
 00: Fixed

    16-pin
 00: INTP5 - P01
 01: INTP5 - P07
 Set PIOR25 to 0.

    20-pin
 00: INTP5 - P01
 01: INTP5 - P07
 10: INTP5 - P22
 11: INTP5 - Setting prohibited
*/
#define BSP_CFG_PIOR25 (0)
#define BSP_CFG_PIOR24 (0)

/* Peripheral I/O redirection register(PIOR2-PIOR27/PIOR26)
    8,10-pin
 00: Fixed

    16-pin
 00: INTP6 - P00
 01: INTP6 - P05
 Set PIOR27 to 0.

    20-pin
 00: INTP6 - P00
 01: INTP6 - P05
 10: INTP6 - P23
 11: INTP6 - Setting prohibited
*/
#define BSP_CFG_PIOR27 (0)
#define BSP_CFG_PIOR26 (0)

/* Peripheral I/O redirection register(PIOR3-PIOR31/PIOR30)
    8-pin
 00: Fixed

    10-pin
 00: PCLBUZ0 - P02
 01: PCLBUZ0 - P40
 Set PIOR31 to 0.

    16,20-pin
 00: PCLBUZ0 - P02
 01: PCLBUZ0 - P40
 10: PCLBUZ0 - P06
 11: PCLBUZ0 - Setting prohibited
*/
#define BSP_CFG_PIOR31 (0)
#define BSP_CFG_PIOR30 (0)

/* Peripheral I/O redirection register(PIOR3-PIOR32)
    8-pin
 0 : VCOUT0 - P40
 1 : VCOUT0 - P125

    10,16,20-pin
 0 : VCOUT0 - P02
 1 : VCOUT0 - P125
*/
#define BSP_CFG_PIOR32 (0)

/* Peripheral I/O redirection register(PIOR3-PIOR33)
    8,10,16-pin
 0 : Fixed

    20-pin
 0 : VCOUT1  - P41
 1 : VCOUT1  - P125
*/
#define BSP_CFG_PIOR33 (0)

/* Peripheral I/O redirection register(PIOR3-PIOR35/PIOR34)
    8,10-pin
 00: Fixed

    16-pin
 00: INTP7 - P02
 01: INTP7 - P06
 Set PIOR35 to 0.

    20-pin
 00: INTP7 - P02
 01: INTP7 - P06
 10: INTP7 - P21
 11: INTP7 - Setting prohibited
*/
#define BSP_CFG_PIOR35 (0)
#define BSP_CFG_PIOR34 (0)

/*************************************************
 * Definition for switching functions
 *************************************************/

/* Start up select
 0 : Enable BSP startup program.
 1 : Disable BSP startup program.(e.g. Using user startup program.)
*/
#define BSP_CFG_STARTUP_DISABLE (0)

/* Initialization of peripheral functions by Code Generator/Smart Configurator
 0 : Disable initialization of peripheral functions by Code Generator/Smart Configurator.
 1 : Enable initialization of peripheral functions by Code Generator/Smart Configurator.
*/
#define BSP_CFG_CONFIGURATOR_SELECT (0)

/* Version number of Smart Configurator.
   This macro definitions is updated by Smart Configurator.
   If you are using e2studio, set the following values.
   2021-04  : 1001
   2021-07  : 1010
   2021-10  : 1010
   2022-01  : 1030
   If you are using Smart the standalone version of Smart Configurator,
   set the following values.
   v1.0.1   : 1001
   v1.1.0   : 1010
   v1.3.0   : 1030
 */
#define BSP_CFG_CONFIGURATOR_VERSION (1001)

/* API function disable(R_BSP_StartClock, R_BSP_StopClock)
 0 : Enable API functions
 1 : Disable API functions
*/
#define BSP_CFG_CLOCK_OPERATION_API_FUNCTIONS_DISABLE (0)

/* API function disable(R_BSP_GetFclkFreqHz)
 0 : Enable API functions
 1 : Disable API functions
*/
#define BSP_CFG_GET_FREQ_API_FUNCTIONS_DISABLE (0)

/* API function disable(R_BSP_SetClockSource)
 0 : Enable API functions
 1 : Disable API functions
*/
#define BSP_CFG_SET_CLOCK_SOURCE_API_FUNCTIONS_DISABLE (0)

/* API function disable(R_BSP_ChangeClockSetting)
 0 : Enable API functions
 1 : Disable API functions
*/
#define BSP_CFG_CHANGE_CLOCK_SETTING_API_FUNCTIONS_DISABLE (0)

/* API function disable(R_BSP_SoftwareDelay)
 0 : Enable API functions
 1 : Disable API functions
*/
#define BSP_CFG_SOFTWARE_DELAY_API_FUNCTIONS_DISABLE (0)

/* Parameter check enable
 0 : Disable parameter check.
 1 : Enable parameter check.
*/
#define BSP_CFG_PARAM_CHECKING_ENABLE (1)

/*************************************************
 * Clock settings
 *************************************************/
/* High-speed system clock frequency(fMX)
   Clock operation mode control register(CMC)
   (Products with 16 and 20 pins)
    EXCLK/OSCSEL
 0 : I/O Port
 1 : fX(Crystal/ceramic resonator connection)
 2 : fEX(External clock input)
*/
#define BSP_CFG_HISYSCLK_SOURCE (1)

/* High-speed system clock operation control
   Clock operation status control register(CSC)
   MSTOP
 (X1 oscillation mode)
  0 : X1 oscillator operating
  1 : X1 oscillator stopped
 (External clock input mode)
  0 : External clock from EXCLK pin is valid
  1 : External clock from EXCLK pin is invalid
 (Input port mode)
  0 : Input port
  1 : Input port
*/
#define BSP_CFG_HISYSCLK_OPERATION (0)

/* Main system clock(fMAIN) operation control
   System clock control register(CKC)
   MCM0
 0 : Selects the high-speed on-chip oscillator clock(fIH) as the main system clock(fMAIN)
 1 : Selects the high-speed system clock(fMX) as the main system clock(fMAIN)
*/
#define BSP_CFG_MAINCLK_SOURCE (0)

/* Input clock frequency in Hz(High-speed system clock(X1))
*/
#define BSP_CFG_FMX_HZ (12000000)
/* Control of X1 clock oscillation frequency
   Clock operation mode control register(CMC)
   AMPH
 0 : 1 MHz <= fX <= 10 MHz
 1 : 10 MHz < fX <= 12 MHz
 Set the value corresponding to the setting of BSP_CFG_FMX_HZ
*/

/* Supply of operation clock for 12-bit interval timer
   Operation speed mode control register(OSMC)
   WUTMMCK0
 0 : Stops Clock supply
 1 : Low-speed on-chip oscillator clock(fIL) supply
 */
#define BSP_CFG_FIL_OPERATION (0)

/* X1 clock oscillation stabilization time selection
   Oscillation stabilization time select register(OSTS)
   OSTS2, OSTS1, OSTS0
 0 : (2^8  + 16)/fX (fX = 10MHz : 27.2us, fX = 16MHz : 17.0us)
 1 : (2^9  + 16)/fX (fX = 10MHz : 52.8us, fX = 16MHz : 33.0us)
 2 : (2^10 + 16)/fX (fX = 10MHz : 104us,  fX = 16MHz : 65.0us)
 3 : (2^11 + 16)/fX (fX = 10MHz : 206us,  fX = 16MHz : 129us)
 4 : (2^13 + 16)/fX (fX = 10MHz : 820us,  fX = 16MHz : 513us)
 5 : (2^15 + 16)/fX (fX = 10MHz : 3.27ms, fX = 16MHz : 2.05ms)
 6 : (2^17 + 16)/fX (fX = 10MHz : 13.1ms, fX = 16MHz : 8.19ms)
 7 : (2^18 + 16)/fX (fX = 10MHz : 26.2ms, fX = 16MHz : 16.4ms)
*/
#define BSP_CFG_X1_WAIT_TIME_SEL (0)

/* High-speed on-chip oscillator clock frequency selection
   High-speed on-chip oscillator frequency select register(HOCODIV)
   HOCODIV2, HOCODIV1, HOCODIV0
 1                : fIH = 16MHz
 2                : fIH = 8MHz
 3                : fIH = 4MHz
 4                : fIH = 2MHz
 5                : fIH = 1MHz
 Other than above : Setting prohibited
*/
#define BSP_CFG_HOCO_DIVIDE (1)

/* Operation setting at initial setting */
/* Starts the high-speed on-chip oscillator at initialization
 0 : Stops the high-speed on-chip oscillator at initialization
 1 : Starts the high-speed on-chip oscillator at initialization
*/
#define BSP_CFG_FIH_START_ON_STARTUP (1)

/* This macro lets other modules no if a RTOS is being used.
   0 = RTOS is not used.
   1 = FreeRTOS is used.(This is not available.)
   2 = embOS is used.(This is not available.)
   3 = MicroC_OS is used.(This is not available.)
   4 = Renesas ITRON is used.
 */
#define BSP_CFG_RTOS_USED (0)

/* High-speed on-chip oscillator clock stabilization time.    (T.B.D.)
   If the main system clock is 16 MHz, 30 means 0.00us. */
#define BSP_CFG_FIHWAITTIME              (30U)

/* If the user would like to determine if a warm start reset has occurred, then they may enable one or more of the
   following callback definitions AND provide a call back function name for the respective callback
   function (to be defined by the user). Setting BSP_CFG_USER_WARM_START_CALLBACK_PRE_INITC_ENABLED = 1 will result
   in a callback to the user defined my_sw_warmstart_prec_function just prior to the initialization of the C
   runtime environment by bsp_init_system.
   Setting BSP_CFG_USER_WARM_START_CALLBACK_POST_INITC_ENABLED = 1 will result in a callback to the user defined
   my_sw_warmstart_postc_function just after the initialization of the C runtime environment by bsp_init_hardware.
*/
#define BSP_CFG_USER_WARM_START_CALLBACK_PRE_INITC_ENABLED    (0)
#define BSP_CFG_USER_WARM_START_PRE_C_FUNCTION                my_sw_warmstart_prec_function

#define BSP_CFG_USER_WARM_START_CALLBACK_POST_INITC_ENABLED    (0)
#define BSP_CFG_USER_WARM_START_POST_C_FUNCTION                my_sw_warmstart_postc_function

/* Defines whether or not use Watchdog timer refresh
 0 : Enable Watchdog timer refresh.
 1 : Disable Watchdog timer refresh.
*/
#define BSP_CFG_WDT_REFRESH_ENABLE                   (1)

#endif /* R_BSP_CONFIG_REF_HEADER_FILE */
