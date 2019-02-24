/**************************************************************************************************************************
 *  @author : Utkarsh Bhatt                                                                                               *
 *  @date   : 12.02.2019                                                                                                  *
 *  @name   : Includes.hpp                                                                                                *
 *  @brief  : This file deals with the internal includes required by 'main.cpp'. This is done to keep the main code neat. *
 **************************************************************************************************************************/
#pragma once
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "freertos/FreeRTOS.h"
#include "freertos/portmacro.h"
#include "freertos/task.h"
#include "sdkconfig.h"

/*  Tasks  */
void taskFetchONE(void *ctx);
void taskFetchTWO(void *ctx);

/*  ISRs  */
IRAM_ATTR void mpuONE_THREEisr(TaskHandle_t taskHandle);
IRAM_ATTR void mpuTWO_FOURisr(TaskHandle_t taskHandle);