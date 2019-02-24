#if 1
#include "includes.hpp"
#include "GPIO_essesntials.h"

/*     Interrupt Setup for MPU     */

constexpr mpud::int_config_t gpioIntrConfig{
    .level = mpud::INT_LVL_ACTIVE_HIGH,
    .drive = mpud::INT_DRV_PUSHPULL,
    .mode  = mpud::INT_MODE_PULSE50US,
    .clear = mpud::INT_CLEAR_STATUS_REG
};

constexpr gpio_config_t mpuONEIntrConfig{
    .pin_bit_mask = ((uint64_t)mpuOneInterruptPin) || \
                    ((uint64_t)mpuTwoInterruptPin) || \
                    ((uint64_t)mpuThreeInterruptPin) || \
                    ((uint64_t)mpuFourInterruptPin),
    .mode         = GPIO_MODE_INPUT,
    .pull_up_en   = GPIO_PULLUP_DISABLE,
    .pull_down_en = GPIO_PULLDOWN_ENABLE,
    .intr_type    = GPIO_INTR_POSEDGE
};

/*     API's     */

void gpioMPUIntrConfig(void){
    gpio_config(&mpuONEIntrConfig);
    gpio_install_isr_service(ESP_INTR_FLAG_IRAM);

    gpio_isr_handler_add((gpio_num_t)mpuOneInterruptPin, mpuONE_THREEisr, xTaskGetCurrentTaskHandle());
    gpio_isr_handler_add((gpio_num_t)mpuTwoInterruptPin, mpuTWO_FOURisr, xTaskGetCurrentTaskHandle());
    gpio_isr_handler_add((gpio_num_t)mpuThreeInterruptPin, mpuONE_THREEisr, xTaskGetCurrentTaskHandle());
    gpio_isr_handler_add((gpio_num_t)mpuFourInterruptPin, mpuTWO_FOURisr, xTaskGetCurrentTaskHandle());    
}

void mpuONE_THREEintrInit(void){
    //MpU ONE
    ESP_ERROR_CHECK(mpuONE.setInterruptConfig(gpioIntrConfig));
    ESP_ERROR_CHECK(mpuONE.setInterruptEnabled(mpud::INT_EN_RAWDATA_READY));
    //MPU THREE
    ESP_ERROR_CHECK(mpuTHREE.setInterruptConfig(gpioIntrConfig));
    ESP_ERROR_CHECK(mpuTHREE.setInterruptEnabled(mpud::INT_EN_RAWDATA_READY));

}

void mpuTWO_FOURintrInit(void){
    //MPU TWO
    ESP_ERROR_CHECK(mpuTWO.setInterruptConfig(gpioIntrConfig));
    ESP_ERROR_CHECK(mpuTWO.setInterruptEnabled(mpud::INT_EN_RAWDATA_READY));
    //MPU FOUR
    ESP_ERROR_CHECK(mpuFOUR.setInterruptConfig(gpioIntrConfig));
    ESP_ERROR_CHECK(mpuFOUR.setInterruptEnabled(mpud::INT_EN_RAWDATA_READY));
}

#endif