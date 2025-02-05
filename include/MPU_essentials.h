/**************************************************************************************************************************
 *  @author : Utkarsh Bhatt                                                                                               *
 *  @date   : 12.02.2019                                                                                                  *
 *  @name   : MPU_essentials.h                                                                                            *
 *  @brief  : This file deals with essential definitions for the MPU's.                                                   *
 **************************************************************************************************************************/
#pragma once
#include "I2C_essential.h"
#include "esp_err.h"
#include "esp_log.h"
#include "MPU.hpp"
#include "mpu/math.hpp"
#include "mpu/types.hpp"

/*     MPU Configuration     */

// Setup config values.

constexpr int                SampleRate    = 250;
constexpr mpud::accel_fs_t   AccelFS       = mpud::ACCEL_FS_16G;
constexpr mpud::gyro_fs_t    GyroFS        = mpud::GYRO_FS_500DPS;
constexpr mpud::dlpf_t       DLPF          = mpud::DLPF_98HZ;

//Debug Tags
#define mpuONE_TAG       "MPU ONE"
#define mpuTWO_TAG       "MPU TWO"
#define mpuTHREE_TAG     "MPU THREE"
#define mpuFOUR_TAG      "MPU FOUR"

// MPU Definitions.
extern MPU_t mpuONE, mpuTWO, mpuTHREE, mpuFOUR;

/*     API's     */
void mpuOneInit(void);
void mpuTwoInit(void);
void mpuThreeInit(void);
void mpuFourInit(void);
void mpuCalibrate(MPU_t mpu);
void mpuScaleConfig(MPU_t mpu);
void mpuFIFoSetup(MPU_t mpu);