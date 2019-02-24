#include "includes.hpp"
#include "MPU_essentials.h"
#include "GPIO_essesntials.h"
/*
THIS IS JUST ADDED TO PUSH THE CHANGES TO GITHUB. ZILCH :D
*/
/*   Declarations   */
extern TaskHandle_t fetchOne, fetchTwo, printOne, printTwo;

// MPU Definitions.
MPU_t mpuONE, mpuTWO, mpuTHREE, mpuFOUR;

/*  Tasks   */
void taskFetchONE(void *ctx){
    //Initialising MPU one and three.
    mpuOneInit();
    mpuThreeInit();

    //Calibrate
    mpuCalibrate(mpuONE);
    mpuCalibrate(mpuTHREE);

    //Configure
    mpuScaleConfig(mpuONE);
    mpuScaleConfig(mpuTHREE);

    //Setup FIFO
    mpuFIFoSetup(mpuONE);
    mpuFIFoSetup(mpuTHREE);

    //Intr Setup
    mpuONE_THREEintrInit();

    // Ready to start reading
    ESP_ERROR_CHECK(mpuONE.resetFIFO());
    ESP_ERROR_CHECK(mpuTHREE.resetFIFO());

    while(true){
            //Populate
    }
    vTaskDelete(NULL);
}

void taskFetchTWO(void *ctx){
    //Initialising MPU two and four.
    mpuTwoInit();
    mpuFourInit();

    //Calibrate
    mpuCalibrate(mpuTWO);
    mpuCalibrate(mpuFOUR);

    //Config
    mpuScaleConfig(mpuTWO);
    mpuScaleConfig(mpuFOUR);

    //Setup FIFO
    mpuFIFoSetup(mpuTWO);
    mpuFIFoSetup(mpuFOUR);

    //Intr Setup
    mpuTWO_FOURintrInit();
    
    // Ready to start reading
    ESP_ERROR_CHECK(mpuTWO.resetFIFO());
    ESP_ERROR_CHECK(mpuFOUR.resetFIFO());
    
    while(true){
            //Populate
    }
    vTaskDelete(NULL);
}