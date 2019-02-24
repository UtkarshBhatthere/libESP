#if 1

#include "MPU_essentials.h"

mpud::raw_axes_t accelBias, gyroBias;

/*     Static API's for unexposed operation     */

// @brief : Use this to config the MPU to certain I2C ports and ADDR.
// Use 0 addr for LOW operation and any other value (typically 1) for HIGH addr.
static void mpuSetup(MPU_t mpu, I2C_t sel_i2c, int address){
    mpu.setBus(sel_i2c);
    if(address == 0)
        mpu.setAddr(mpud::MPU_I2CADDRESS_AD0_LOW);
    else
        mpu.setAddr(mpud::MPU_I2CADDRESS_AD0_HIGH);    
}

// @brief : Use this to verify the connection to the MPU.
static void mpuVerify(MPU_t mpu, const char *mpuTag){
    while(esp_err_t err = mpu.testConnection()){
        ESP_LOGE(mpuTag, "Connection failed, err=%#X", err);
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
    ESP_LOGI(mpuTag, "Connection Succeeded!");
}

// @brief   : Use this to test the Gyro and Accelerometers of the MPU.
// @warning : It is recommended that the MPU's be as horizontal as possible
//            facing upwards.
static void mpuSelfTest(MPU_t mpu, char *mpuTag){
    mpud::selftest_t retSelfTest;
    while(esp_err_t err = mpu.selfTest(&retSelfTest)){
        ESP_LOGE(mpuTag, "Test Failed, err=%#X", err);
        vTaskDelay(100/portTICK_PERIOD_MS);
    }
    ESP_LOGI(mpuTag, "Self Test Result: Gyro=%s Accel=%s", //
            ( retSelfTest & mpud::SELF_TEST_GYRO_FAIL ? "FAIL" : "OK"),
            ( retSelfTest & mpud::SELF_TEST_ACCEL_FAIL ? "FAIL" : "OK"));
}

/*     API's     */

/*************************************************************************************************************************
 * @brief : API's for initialising the MPU's setup of I2c PERIPH and verification.                                       *
 *************************************************************************************************************************/
void mpuOneInit(void){
    mpuSetup(mpuONE, i2c0, 0);
    mpuVerify(mpuONE, mpuONE_TAG);
    ESP_ERROR_CHECK(mpuONE.initialize());
    mpuSelfTest(mpuONE, mpuONE_TAG);
}
void mpuTwoInit(void){
    mpuSetup(mpuTWO, i2c0, 1);
    mpuVerify(mpuTWO, mpuTWO_TAG);
    ESP_ERROR_CHECK(mpuTWO.initialize());
    mpuSelfTest(mpuTWO, mpuTWO_TAG);
} 
void mpuThreeInit(void){
    mpuSetup(mpuTHREE, i2c1, 0);
    mpuVerify(mpuTHREE, mpuTHREE_TAG);
    ESP_ERROR_CHECK(mpuTHREE.initialize());
    mpuSelfTest(mpuTHREE, mpuTHREE_TAG);
} 
void mpuFourInit(void){
    mpuSetup(mpuFOUR, i2c1, 1);
    mpuVerify(mpuFOUR, mpuFOUR_TAG);
    ESP_ERROR_CHECK(mpuFOUR.initialize());
    mpuSelfTest(mpuFOUR, mpuFOUR_TAG);
}

void mpuCalibrate(MPU_t mpu){
    
    ESP_ERROR_CHECK(mpu.computeOffsets(&accelBias, &gyroBias));
    ESP_ERROR_CHECK(mpu.setAccelOffset(accelBias));
    ESP_ERROR_CHECK(mpu.setGyroOffset(gyroBias));
    ESP_LOGI("MPU Calibration", "Calibration Done!");
}

void mpuScaleConfig(MPU_t mpu){
    ESP_ERROR_CHECK(mpu.setAccelFullScale(AccelFS));
    ESP_ERROR_CHECK(mpu.setGyroFullScale(GyroFS));
    ESP_ERROR_CHECK(mpu.setSampleRate(SampleRate));
    ESP_ERROR_CHECK(mpu.setDigitalLowPassFilter(DLPF));
}

void mpuFIFoSetup(MPU_t mpu){
    ESP_ERROR_CHECK(mpu.setFIFOConfig(mpud::FIFO_CFG_ACCEL | mpud::FIFO_CFG_GYRO));
    ESP_ERROR_CHECK(mpu.setFIFOEnabled(true));
}

#endif