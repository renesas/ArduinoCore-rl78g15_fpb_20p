
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
* File Name    : r_bsp.h
* H/W Platform : GENERIC_RL78_G15
* Description  : 
***********************************************************************************************************************/
/***********************************************************************************************************************
* History : DD.MM.YYYY Version  Description
*         : 31.05.2022 1.30     First Release

***********************************************************************************************************************/
/* Make sure that no other platforms have already been defined. Do not touch this! */
#ifdef  PLATFORM_DEFINED
#error  "Error - Multiple platforms defined in platform.h!"
#else
#define PLATFORM_DEFINED
#endif


/***********************************************************************************************************************
INCLUDE APPROPRIATE MCU AND BOARD FILES
***********************************************************************************************************************/
// #include    <rl78g15/smc_gen/r_config/r_bsp_config.h>
#include    "r_bsp_config.h"
#include    <rl78g15/smc_gen/r_bsp/mcu/all/r_bsp_rl78_compiler.h>
#include    <rl78g15/smc_gen/r_bsp/mcu/all/r_bsp_common.h>
#include    <rl78g15/smc_gen/r_bsp/mcu/all/r_rtos.h>

#include    <rl78g15/smc_gen/r_bsp/mcu/all/fsp_common_api.h>
#include    <rl78g15/smc_gen/r_bsp/mcu/all/r_fsp_error.h>

#if defined(__CCRL__)
#include    "mcu/rl78_g15/register_access/ccrl/iodefine.h"
#elif defined(__ICCRL78__)
#include "mcu/rl78_g15/register_access/iccrl/iodefine.h"
#include "mcu/rl78_g15/register_access/iccrl/iodefine_ext.h"
#include "mcu/rl78_g15/register_access/iccrl/intrinsics.h"
#elif defined(__llvm__)
#include <rl78g15/smc_gen/r_bsp/mcu/rl78_g15/register_access/llvm/iodefine.h>
#include <rl78g15/smc_gen/r_bsp/mcu/rl78_g15/register_access/llvm/iodefine_ext.h>
#endif /* defined(__CCRL__), defined(__ICCRL__), defined(__llvm__) */

#include    <rl78g15/smc_gen/r_bsp/mcu/rl78_g15/mcu_clocks.h>
#include    <rl78g15/smc_gen/r_bsp/mcu/rl78_g15/mcu_info.h>

#include    <rl78g15/smc_gen/r_bsp/board/generic_rl78_g15/hdwinit.h>

