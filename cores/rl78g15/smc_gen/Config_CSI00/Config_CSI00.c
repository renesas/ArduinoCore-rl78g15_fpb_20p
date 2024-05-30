/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products.
* No other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
* applicable laws, including copyright laws. 
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED
* OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY
* LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE FOR ANY DIRECT,
* INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR
* ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability 
* of this software. By using this software, you agree to the additional terms and conditions found by accessing the 
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2020 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name    : Config_CSI00.c
* Version      : 1.1.0
* Device(s)    : R5F12068xSP
* Description  : This file implements device driver for Config_CSI00.
* Creation Date: 
***********************************************************************************************************************/

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "Arduino.h"
#include "r_cg_macrodriver.h"
#include "Config_CSI00.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
volatile uint8_t * gp_csi00_tx_address;    /* csi00 send buffer address */
volatile uint16_t g_csi00_tx_count;        /* csi00 send data count */
volatile uint8_t * gp_csi00_rx_address;    /* csi00 receive buffer address */
/* Start user code for global. Do not edit comment generated here */
volatile uint16_t g_csi00_status_flag;
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_Config_CSI00_Create
* Description  : This function initializes the CSI00 module.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_CSI00_Create(void)
{
    SPS0 &= _00F0_SAU_CK00_CLEAR;
    SPS0 |= _0000_SAU_CK00_FCLK_0;
    /* Stop channel 0 */
    ST0 |= _0001_SAU_CH0_STOP_TRG_ON;
    /* Mask channel 0 interrupt */
    CSIMK00 = 1U;    /* disable INTCSI00 interrupt */
    CSIIF00 = 0U;    /* clear INTCSI00 interrupt flag */
    /* Set INTCSI00 low priority */
    CSIPR100 = 1U;
    CSIPR000 = 1U;
    SIR00 = _0002_SAU_SIRMN_PECTMN | _0001_SAU_SIRMN_OVCTMN;    /* clear error flag */
    SMR00 = _0020_SAU_SMRMN_INITIALVALUE | _0000_SAU_CLOCK_SELECT_CK00 | _0000_SAU_CLOCK_MODE_CKS | 
            _0000_SAU_TRIGGER_SOFTWARE | _0000_SAU_MODE_CSI | _0000_SAU_TRANSFER_END;
    SCR00 = _C000_SAU_RECEPTION_TRANSMISSION | _0000_SAU_TIMING_1 | _0000_SAU_MSB | _0003_SAU_LENGTH_8;
    SDR00 = _0600_SAU0_CH0_BAUDRATE_DIVISOR;
    SO0 |= _0100_SAU_CH0_CLOCK_OUTPUT_1;    /* CSI00 clock initial level */
    SO0 &= (uint16_t)~_0001_SAU_CH0_DATA_OUTPUT_1;    /* CSI00 SO initial level */
    SOE0 |= _0001_SAU_CH0_OUTPUT_ENABLE;    /* enable CSI00 output */
    /* Set SI00 pin */
    PMC0 &= 0xFDU;
    PM0 |= 0x02U;
    /* Set SO00 pin */
    POM0 &= 0xFEU;
    P0 |= 0x01U;
    PM0 &= 0xFEU;
    /* Set SCK00 pin */
    PMC0 &= 0xFBU;
    P0 |= 0x04U;
    PM0 &= 0xFBU;

    R_Config_CSI00_Create_UserInit();
}

/***********************************************************************************************************************
* Function Name: R_Config_CSI00_Start
* Description  : This function starts the CSI00 module operation.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_CSI00_Start(void)
{
    SO0 |= _0100_SAU_CH0_CLOCK_OUTPUT_1;    /* CSI00 clock initial level */
    SO0 &= (uint16_t)~_0001_SAU_CH0_DATA_OUTPUT_1;    /* CSI00 SO initial level */
    SOE0 |= _0001_SAU_CH0_OUTPUT_ENABLE;    /* enable CSI00 output */
    SS0 |= _0001_SAU_CH0_START_TRG_ON;    /* enable CSI00 */
    CSIIF00 = 0U;    /* clear INTCSI00 interrupt flag */
    CSIMK00 = 0U;    /* enable INTCSI00 interrupt */
}

/***********************************************************************************************************************
* Function Name: R_Config_CSI00_Stop
* Description  : This function stops the CSI00 module operation.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_CSI00_Stop(void)
{
    CSIMK00 = 1U;    /* disable INTCSI00 interrupt */
    ST0 |= _0001_SAU_CH0_STOP_TRG_ON;    /* disable CSI00 */
    SOE0 &= (uint16_t)~_0001_SAU_CH0_OUTPUT_ENABLE;    /* disable CSI00 output */
    CSIIF00 = 0U;    /* clear INTCSI00 interrupt flag */
}

/***********************************************************************************************************************
* Function Name: R_Config_CSI00_Send_Receive
* Description  : This function sends and receives CSI00 data.
* Arguments    : tx_buf -
*                    transfer buffer pointer
*                tx_num -
*                    buffer size
*                rx_buf -
*                    receive buffer pointer
* Return Value : status -
*                    MD_OK or MD_ARGERROR
***********************************************************************************************************************/
MD_STATUS R_Config_CSI00_Send_Receive(uint8_t * const tx_buf, uint16_t tx_num, uint8_t * const rx_buf)
{
    MD_STATUS status = MD_OK;

    if (tx_num < 1U)
    {
        status = MD_ARGERROR;
    }
    else
    {
        g_csi00_tx_count = tx_num;    /* send data count */
        gp_csi00_tx_address = tx_buf;    /* send buffer pointer */
        gp_csi00_rx_address = rx_buf;    /* receive buffer pointer */
        CSIMK00 = 1U;    /* disable INTCSI00 interrupt */

        if (0U != gp_csi00_tx_address)
        {
            SIO00 = *gp_csi00_tx_address;    /* started by writing data to SDR00[7:0] */
            gp_csi00_tx_address++;
        }
        else
        {
            SIO00 = 0xFFU;
        }

        g_csi00_tx_count--;
        CSIMK00 = 0U;    /* enable INTCSI00 interrupt */
    }

    return (status);
}

/* Start user code for adding. Do not edit comment generated here */

/**********************************************************************************************************************
 * Function Name: R_Config_CSI11_GetBitOrder
 * Description  : Get the order of the bits shifted out of and into the SPI bus.
 * Arguments    : -
 * Return Value : Current bit order setting
 *              :   LSBFIRST
 *              :   MSBFIRST
 *********************************************************************************************************************/
uint8_t R_Config_CSI00_GetBitOrder(void) {

    return (SCR00 & (uint16_t)_0080_SAU_LSB) == _0080_SAU_LSB
                ? LSBFIRST : MSBFIRST;
}

/**********************************************************************************************************************
 * Function Name: R_Config_CSI11_SetBitOrder
 * Description  : Set the order of the bits shifted out of and into the SPI bus.
 * Arguments    : bitOrder - Bit order setting
 *              :   LSBFIRST
 *              :   MSBFIRST
 * Return Value : -
 *********************************************************************************************************************/
void R_Config_CSI00_SetBitOrder(uint8_t bitOrder) {
    /* Stop channel 0 */
    ST0 |= _0001_SAU_CH0_STOP_TRG_ON;
    SOE0 &= (uint16_t)~_0001_SAU_CH0_OUTPUT_ENABLE;    /* disable CSI00 output */


    SCR00    = (SCR00 & (uint16_t)~_0080_SAU_LSB)
             | (bitOrder == LSBFIRST ? _0080_SAU_LSB : _0000_SAU_MSB);

    CSIIF00 = 0U;    /* clear INTCSI00 interrupt flag */
    SO0 |= _0100_SAU_CH0_CLOCK_OUTPUT_1;    /* CSI00 clock initial level */
    SO0 &= (uint16_t)~_0001_SAU_CH0_DATA_OUTPUT_1;    /* CSI00 SO initial level */
    SOE0 |= _0001_SAU_CH0_OUTPUT_ENABLE;    /* enable CSI00 output */
    SS0 |= _0001_SAU_CH0_START_TRG_ON;    /* enable CSI00 */

}

/**********************************************************************************************************************
 * Function Name: R_Config_CSI11_SetDataMode
 * Description  : Set the SPI data mode (clock polarity and phase).
 * Arguments    : dataMode - SPI data mode
 *              :   SPI_MODE0
 *              :   SPI_MODE1
 *              :   SPI_MODE2
 *              :   SPI_MODE3
 * Return Value : -
 *********************************************************************************************************************/
void R_Config_CSI00_SetDataMode(uint8_t dataMode) {
    /* Stop channel 0 */
    ST0 |= _0001_SAU_CH0_STOP_TRG_ON;
    SOE0 &= (uint16_t)~_0001_SAU_CH0_OUTPUT_ENABLE;    /* disable CSI00 output */

//    #warning XXX: Check whether this register setting mapping is correct.
    //
    // This mapping is obeying the base code.
    // Fix the `SPI_MODEx` macros together.
    //
    switch (dataMode) {
    case SPI_MODE3:     SCR00 = (SCR00 & (uint16_t)~SPI_MODE_MASK) | _0000_SAU_TIMING_1; break;
    case SPI_MODE2:     SCR00 = (SCR00 & (uint16_t)~SPI_MODE_MASK) | _2000_SAU_TIMING_3; break;
    case SPI_MODE1:     SCR00 = (SCR00 & (uint16_t)~SPI_MODE_MASK) | _1000_SAU_TIMING_2; break;
    case SPI_MODE0:
    default:            SCR00 = (SCR00 & (uint16_t)~SPI_MODE_MASK) | _3000_SAU_TIMING_4; break;
    }

    CSIIF00 = 0U;    /* clear INTCSI00 interrupt flag */
    SO0 |= _0100_SAU_CH0_CLOCK_OUTPUT_1;    /* CSI00 clock initial level */
    SO0 &= (uint16_t)~_0001_SAU_CH0_DATA_OUTPUT_1;    /* CSI00 SO initial level */
    SOE0 |= _0001_SAU_CH0_OUTPUT_ENABLE;    /* enable CSI00 output */
    SS0 |= _0001_SAU_CH0_START_TRG_ON;    /* enable CSI00 */
}

/**********************************************************************************************************************
 * Function Name: R_Config_CSI11_SetClockDivider
 * Description  : Set the SPI clock divider relative to the system clock.
 * Arguments    : clockDiv - SPI clock divider
 *              :   SPI_CLOCK_DIV2
 *              :   SPI_CLOCK_DIV4
 *              :   SPI_CLOCK_DIV8
 *              :   SPI_CLOCK_DIV16
 *              :   SPI_CLOCK_DIV32
 *              :   SPI_CLOCK_DIV64
 *              :   SPI_CLOCK_DIV128
 *              :   or an immediate { 2, 4, 6, 8, ..., 256 }
 * Return Value : -
 *********************************************************************************************************************/
void R_Config_CSI00_SetClockDivider(uint16_t clockDiv) {
    /* Stop channel 0 */
    ST0 |= _0001_SAU_CH0_STOP_TRG_ON;
    SOE0 &= (uint16_t)~_0001_SAU_CH0_OUTPUT_ENABLE;    /* disable CSI00 output */

    clockDiv = clockDiv <   2 ?   2U
             : clockDiv > 256 ? 256U
             :                  clockDiv + (clockDiv & 1U);

    SDR00    = ((clockDiv >> 1) - 1) << 9;


    CSIIF00 = 0U;    /* clear INTCSI00 interrupt flag */
    SO0 |= _0100_SAU_CH0_CLOCK_OUTPUT_1;    /* CSI00 clock initial level */
    SO0 &= (uint16_t)~_0001_SAU_CH0_DATA_OUTPUT_1;    /* CSI00 SO initial level */
    SOE0 |= _0001_SAU_CH0_OUTPUT_ENABLE;    /* enable CSI00 output */
    SS0 |= _0001_SAU_CH0_START_TRG_ON;    /* enable CSI00 */
}

/**********************************************************************************************************************
 * Function Name: R_Config_CSI11_SetClock
 * Description  : Set the SPI maximum speed of communication.
 * Arguments    : clock - SPI clock speed
 * Return Value : -
 *********************************************************************************************************************/
void R_Config_CSI00_SetClock(uint32_t clock) {
    uint16_t clockDiv;
    uint32_t spi_frequency = R_BSP_GetFclkFreqHz() >> ((SPS0 >> 4) & 0x0F);

    for (clockDiv = 2; clockDiv < 256; clockDiv += 2) {
    	if (clock >= spi_frequency / clockDiv) {
            break;
        }
    }

    R_Config_CSI00_SetClockDivider(clockDiv);
}

/* End user code. Do not edit comment generated here */
