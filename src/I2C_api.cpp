#if 1 
#include "I2C_essential.h"

/*     Static API's for unexposed operation.     */

// I2C One Initialisation API's.
static void i2cONE_init(void){
    i2c0.begin(i2cOne_SDA, i2cOne_SCL, CLOCK_SPEED);
}

static void i2cTWO_init(void){
    i2c1.begin(i2cTwo_SDA, i2cTwo_SCL, CLOCK_SPEED);
}

/*     API's     */
void i2c_Init(void){
    i2cONE_init();
    i2cTWO_init();
}
#endif