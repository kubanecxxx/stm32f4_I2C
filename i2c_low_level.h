#ifndef __I2C_low_level
#define __I2C_low_level

#ifdef __cplusplus
extern "C"
{
#endif

#include "stm32f4xx.h"
#include "i2c_port.h"

#ifdef I2C1_USED
void i2c_1_LowLevel_DeInit(void);
void i2c_1_LowLevel_Init(void);
#endif


#ifdef __cplusplus
}
#endif

#endif

