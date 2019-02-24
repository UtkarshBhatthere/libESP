/**************************************************************************************************************************
 *  @author : Utkarsh Bhatt                                                                                               *
 *  @date   : 12.02.2019                                                                                                  *
 *  @name   : MPU_essentials.h                                                                                            *
 *  @brief  : This file deals with essential definitions for the GPIO pins required for the MPU operation.                *
 **************************************************************************************************************************/
#pragma once
#include "driver/gpio.h"
#include "MPU_essentials.h"

// Interrupt Pins
constexpr int mpuOneInterruptPin         =   GPIO_NUM_0;
constexpr int mpuTwoInterruptPin         =   GPIO_NUM_0;
constexpr int mpuThreeInterruptPin       =   GPIO_NUM_0;
constexpr int mpuFourInterruptPin        =   GPIO_NUM_0;

/*     API's     */

void gpioMPUIntrConfig(void);