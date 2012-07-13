/**
 * @file i2c_low_level.h
 * @author Kubanec
 * @brief low level I2C driver initialization - ports, clocks
 *
 */

#ifndef __I2C_low_level
#define __I2C_low_level

#ifdef __cplusplus
extern "C"
{
#endif

#include "stm32f4xx.h"
#include "i2c_port.h"

void i2c_LowLevel_DeInit(void);
void i2c_LowLevel_Init(void);


#ifdef __cplusplus
}
#endif

#endif

