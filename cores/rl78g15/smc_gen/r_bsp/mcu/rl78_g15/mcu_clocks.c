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
* File Name    : mcu_clocks.c
* Description  : 
***********************************************************************************************************************/
/***********************************************************************************************************************
* History : DD.MM.YYYY Version  Description
*         : 31.05.2022 1.30     First Release

***********************************************************************************************************************/
/*************************************************
 * Includes  <System Includes> , "Project Includes"
 *************************************************/
#include "platform.h"

/*************************************************
 * Macro definitions
 *************************************************/

/*************************************************
 * External function Prototypes
 *************************************************/

/*************************************************
 * Private global variables and functions
 *************************************************/
/* Frequency of the high-speed on-chip oscillator */
#if BSP_CFG_GET_FREQ_API_FUNCTIONS_DISABLE == 0
const uint32_t g_fih_hz[] = {
    0,                  /* Setting prohibited */
    16000000,
    8000000,
    4000000,
    2000000,
    1000000,
    0,                  /* Setting prohibited */
    0                   /* Setting prohibited */
};
#endif

/*************************************************
 * Function definition
 *************************************************/
/*************************************************
 * Function name: start_clock
 * Description  : Start the specified clock
 * Arguments    : Clock to start
 * Return value : BSP_OK if the specified clock is started.
 *                BSP_ARG_ERROR if the specified clock is incorrect.
**************************************************/
#if BSP_CFG_CLOCK_OPERATION_API_FUNCTIONS_DISABLE == 0
e_bsp_err_t start_clock(e_clock_mode_t mode)
{
    e_bsp_err_t          status = BSP_OK;
#if BSP_CFG_HISYSCLK_SOURCE == 1
    uint8_t              tmp_stab_wait;
    uint8_t              tmp_stab_set;
#endif
    volatile uint32_t    w_count;

    switch (mode)
    {
#if BSP_CFG_MCU_PART_PIN_NUM >= 2
        case SYSCLK:

            if (1U == MSTOP)
            {
                MSTOP = 0U;

#if BSP_CFG_HISYSCLK_SOURCE == 1
                tmp_stab_set = (uint8_t)~(0x7FU >> OSTS);

                /* WAIT_LOOP */
                do
                {
                    tmp_stab_wait  = OSTC;
                    tmp_stab_wait &= tmp_stab_set;
                }
                while (tmp_stab_wait != tmp_stab_set);
#endif
            }

            break;

#endif

        case HIOCLK:

            if (1U == HIOSTOP)
            {
                HIOSTOP = 0U;
                
                /* WAIT_LOOP */
                for (w_count = 0U; w_count <= BSP_CFG_FIHWAITTIME; w_count++)
                {
                    BSP_NOP();
                }
            }

            break;

        case LOCLK:

            OSMC = 0x10U;

            break;

        default:

            status = BSP_ARG_ERROR;

            break;

    }

    return status;
} /* End of function start_clock() */
#endif /* BSP_CFG_CLOCK_OPERATION_API_FUNCTIONS_DISABLE == 0 */

/*************************************************
 * Function name: stop_clock
 * Description  : Stop the specified clock
 * Arguments    : Clock to stop
 * Return value : BSP_OK if the specified clock is stopped.
 *                BSP_ARG_ERROR if the specified clock is incorrect.
**************************************************/
#if BSP_CFG_CLOCK_OPERATION_API_FUNCTIONS_DISABLE == 0
e_bsp_err_t stop_clock(e_clock_mode_t mode)
{
    e_bsp_err_t    status = BSP_OK;

    switch (mode)
    {
#if BSP_CFG_MCU_PART_PIN_NUM >= 2
        case SYSCLK:

            MSTOP = 1U;

            break;

#endif
        case HIOCLK:

            HIOSTOP = 1U;

            break;

        case LOCLK:

            OSMC = 0x00U;

            break;

        default:

            status = BSP_ARG_ERROR;

            break;

    }

    return status;
} /* End of function stop_clock() */
#endif /* BSP_CFG_CLOCK_OPERATION_API_FUNCTIONS_DISABLE == 0 */

/*************************************************
 * Function name: set_fclk_clock_source
 * Description  : Switch CPU/peripheral hardware clock(fCLK) clock source.
 * Arguments    : Clock to switch.
 * Return value : BSP_OK when switching to the specified clock.
 *                BSP_ERROR1 The specified clock is not oscillating.
 *                BSP_ERROR2 When switching between clock resource, a clock resource that is not
 *                           oscillating may have been switched to.
 *                BSP_ERROR3 An unsupported state transition was specified. Refer to the user's manual.
 *                BSP_ARG_ERROR An invalid argument was input.
 * Attention    : Start the clock to switch to before calling this function.
**************************************************/
#if BSP_CFG_SET_CLOCK_SOURCE_API_FUNCTIONS_DISABLE == 0
e_bsp_err_t set_fclk_clock_source(e_clock_mode_t mode)
{
    e_bsp_err_t       status = BSP_OK;
    e_clock_mode_t    old_mode;

    /* Get current clock source */
    if (1U == MCS)
    {
        old_mode = SYSCLK;
    }
    else
    {
        old_mode = HIOCLK;
    }

    /* Only switch if the current clock source and the
     * specified clock source are different.
     */
    if (mode != old_mode)
    {
        switch (mode)
        {
#if BSP_CFG_MCU_PART_PIN_NUM >= 2
            case SYSCLK:

                if (1U == MSTOP)
                {
                    /* Error if the high-speed system clock is stopped. */
                    status = BSP_ERROR1;
                }
#if BSP_CFG_PARAM_CHECKING_ENABLE == 1
                else if ((CMC & 0x40U) != 0x40U)
                {
                    /* Error if the high-speed system clock is invalid. */
                    status = BSP_ERROR1;
                }
#endif
                else
                {
                    MCM0 = 1U;
                }

                break;

#endif

            case HIOCLK:

                if (1U == HIOSTOP)
                {
                    /* Error if the high-speed on-chip oscillator is stopped. */
                    status = BSP_ERROR1;
                }
                else
                {
                    MCM0 = 0U;
                }

                break;

            default:

                status = BSP_ARG_ERROR;

                break;

        }
    }

    return status;
} /* End of function set_fclk_clock_source() */
#endif /* BSP_CFG_SET_CLOCK_SOURCE_API_FUNCTIONS_DISABLE == 0 */

/*************************************************
 * Function name: get_fclk_freq_hz
 * Description  : Returns CPU/peripheral hardware clock(fCLK) frequency.
 * Arguments    : none
 * Return value : CPU/peripheral hardware clock(fCLK) frequency specified by the r_bsp.
 * Attention    : Error if 0Hz is returned.
 *                When fCLK is a high-speed on-chip oscillator, 0Hz is returned
 *                when the value of the register to which it refers is out of the allowable range.
**************************************************/
#if BSP_CFG_GET_FREQ_API_FUNCTIONS_DISABLE == 0
uint32_t get_fclk_freq_hz(void)
{
    uint32_t    sys_clock_src_freq;

    /* fCLK clock source is fMX */
    /* fCLK : CPU/peripheral hardware clock */
    /* fMX   : High-speed system clock */
    if (1U == MCS)
    {
#if BSP_CFG_MCU_PART_PIN_NUM >= 2
        sys_clock_src_freq = BSP_CFG_FMX_HZ;
#else
        sys_clock_src_freq = 0U;
#endif
    }
    /* fCLK clock source is fIH */
    /* fCLK : CPU/peripheral hardware clock */
    /* fIH  : High-speed on-chip oscillator clock */
    else
    {

        sys_clock_src_freq = g_fih_hz[HOCODIV];
    }

    return sys_clock_src_freq;
} /* End of function get_fclk_freq_hz() */
#endif /* BSP_CFG_GET_FREQ_API_FUNCTIONS_DISABLE == 0 */

/**************************************************
 * Function name: change_clock_setting
 * Description  : Change the specified clock setting.
 * Arguments    : Clock to change setting.
 *              : Value to set for the specified clock.
 * Return value : BSP_OK if the specified clock setting is changed.
 *                BSP_ERROR1 if no high-speed on-chip oscillator clock is supplied to fCLK.
 *                BSP_ARG_ERROR An invalid argument was input.
 * Attention    : Supply high-speed on-chip oscillator clock to fCLK before calling this function.
**************************************************/
#if BSP_CFG_CHANGE_CLOCK_SETTING_API_FUNCTIONS_DISABLE == 0
e_bsp_err_t change_clock_setting(e_clock_mode_t mode, uint8_t * set_values)
{
    e_bsp_err_t    status = BSP_OK;

    switch (mode)
    {
        case HIOCLK:

            if (1U == MCS)
            {
                status = BSP_ERROR1;
            }
            else
            {
                HOCODIV = set_values[0];
            }

            break;

        default :

            /* Setting prohibited */
            status = BSP_ARG_ERROR;

            break;

    }

    return status;
} /* End of function change_clock_setting() */
#endif /* BSP_CFG_CHANGE_CLOCK_SETTING_API_FUNCTIONS_DISABLE == 0 */

/*************************************************
 * Function name: mcu_clock_setup
 * Description  : Clock initialization.
 * Arguments    : none
 * Return value : none
**************************************************/
#if BSP_CFG_STARTUP_DISABLE == 0
void mcu_clock_setup(void)
{
    uint8_t    cmc_tmp;

#if (BSP_CFG_HISYSCLK_OPERATION == 0) && (BSP_CFG_HISYSCLK_SOURCE == 1)
    uint8_t    tmp_stab_wait;
    uint8_t    tmp_stab_set;
#endif

    cmc_tmp = 0x00U;

    /* High-speed system clock(fMX) setting */
#if BSP_CFG_HISYSCLK_SOURCE == 0
    /* Not used.
     * When using high-speed on-chip oscillator.
     */
#elif BSP_CFG_HISYSCLK_SOURCE == 1
    /* fX(Crystal/ceramic resonator connection */
    /* Control of X1 clock oscillation frequency(EXCLK/OSCSEL/AMPH) setting */
#if BSP_CFG_FMX_HZ >= 1000000 && BSP_CFG_FMX_HZ <= 10000000
    /* 1MHz <= fX <= 10MHz */
    cmc_tmp |= 0x40U;
#else
    /* 10MHz < fX <= 16MHz */
    cmc_tmp |= 0x41U;
#endif
#else
    /* fEX(External clock input) */
    /* Control of X1 clock oscillation frequency(EXCLK/OSCSEL/AMPH) setting */
#if BSP_CFG_FMX_HZ >= 1000000 && BSP_CFG_FMX_HZ <= 10000000
    /* 1MHz <= fX <= 10MHz */
    cmc_tmp |= 0xC0U;
#else
    /* 10MHz < fX <= 16MHz */
    cmc_tmp |= 0xC1U;
#endif
#endif
    /* Clock operation mode control register(CMC) setting */
    CMC = cmc_tmp;

    /* High-speed on-chip oscillator(fIH) setting */
    /* High-speed on-chip oscillator frequency select register(HOCODIV) setting */
    HOCODIV = BSP_CFG_HOCO_DIVIDE;

    /* When to use X1 clock oscillator(fX) */
#if BSP_CFG_HISYSCLK_SOURCE == 1
    /* Oscillation stabilization time select register(OSTS) setting */
    OSTS = BSP_CFG_X1_WAIT_TIME_SEL;
#endif

    /* High-speed system clock oscillation */
#if BSP_CFG_HISYSCLK_OPERATION == 0
    /* Start oscillation */
    MSTOP = 0U;

#if BSP_CFG_HISYSCLK_SOURCE == 1
    /* Wait for oscillation stabilization unless external clock input */
    tmp_stab_set = (uint8_t)~(0x7FU >> OSTS);

    /* WAIT_LOOP */
    do
    {
        tmp_stab_wait  = OSTC;
        tmp_stab_wait &= tmp_stab_set;
    }
    while (tmp_stab_wait != tmp_stab_set);
#endif
#else
    /* X1 oscillation stopped if high-speed system clock is not used */
    MSTOP = 1U;
#endif

    /* CPU/peripheral hardware clock(fCLK) setting */
#if BSP_CFG_MAINCLK_SOURCE == 0
    /* High-speed on-chip oscillator clock(fIH) */
    MCM0 = 0U;
#else
    /* High-speed system clock(fMX) */
    MCM0 = 1U;
#endif

    /* Low-speed on-chip oscillator supply mode control register(OSMC) setting */
#if BSP_CFG_FIL_OPERATION == 0
    OSMC = 0x00U;
#else
    OSMC = 0x10U;
#endif

    /* Starts high-speed on-chip oscillator */
    /* Only the high-speed on-chip oscillator is activated after reset,
     * so stop this clock last.
     */
#if BSP_CFG_FIH_START_ON_STARTUP == 1
    HIOSTOP = 0U;
#else
    HIOSTOP = 1U;
#endif
} /* End of function mcu_clock_setup() */
#endif /* BSP_CFG_STARTUP_DISABLE == 0 */
