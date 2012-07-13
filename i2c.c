/*
 * i2c.c
 *
 *  Created on: 13.7.2012
 *      Author: kubanec
 */

#include "i2c.h"

#define TIMEOUT 0x1000
#define LONG_TIMEOUT (10 * TIMEOUT)

i2c_status I2C_send_array_stupid(I2C_TypeDef * i2c,
		const i2c_requestTypedef * request)
{
	uint32_t timeout;
	uint16_t length = request->length;
	const uint8_t * data = request->data;

	timeout = TIMEOUT;
	while (I2C_GetFlagStatus(i2c, I2C_FLAG_BUSY))
	{
		if (timeout-- == 0)
			return i2c_busy;
	}

	timeout = LONG_TIMEOUT;
	I2C_GenerateSTART(i2c, ENABLE);
	while (!I2C_CheckEvent(i2c, I2C_EVENT_MASTER_MODE_SELECT))
	{
		if (timeout-- == 0)
			return i2c_startError;
	}

	timeout = LONG_TIMEOUT;
	I2C_Send7bitAddress(i2c, request->address, I2C_Direction_Transmitter);
	while (!I2C_CheckEvent(i2c, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
	{
		if (timeout-- == 0)
			return i2c_addressSendFault;
	}

	timeout = LONG_TIMEOUT;
	I2C_SendData(i2c, request->subaddress);
	while (!I2C_CheckEvent(i2c, I2C_EVENT_MASTER_BYTE_TRANSMITTING))
	{
		if (timeout-- == 0)
			return i2c_dataSubaddressFault;
	}

	while (length--)
	{
		timeout = LONG_TIMEOUT;
		I2C_SendData(i2c, *(data++));
		while (!I2C_CheckEvent(i2c, I2C_EVENT_MASTER_BYTE_TRANSMITTING))
		{
			if (timeout-- == 0)
				return i2c_dataSendFault;
		}
	}

	I2C_GenerateSTOP(i2c, ENABLE);
	while (I2C_GetFlagStatus(i2c, I2C_FLAG_BUSY))
		;
	return i2c_ok;
}

