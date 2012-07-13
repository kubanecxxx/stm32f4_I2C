/*
 * i2c.h
 *
 *  Created on: 13.7.2012
 *      Author: kubanec
 */

#ifndef I2C_H_
#define I2C_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "stm32f4xx.h"

typedef struct i2c_requestTypedef
{
	uint8_t * data;
	uint16_t length;
	uint8_t address;
	uint8_t subaddress;
} i2c_requestTypedef;

typedef enum i2c_status
{
	i2c_ok,
	i2c_busy,
	i2c_startError,
	i2c_addressSendFault,
	i2c_dataSubaddressFault,
	i2c_dataSendFault
} i2c_status;

i2c_status I2C_send_array_stupid(I2C_TypeDef * i2c,
		const i2c_requestTypedef * request);

#ifdef __cplusplus
}
#endif

#endif /* I2C_H_ */
