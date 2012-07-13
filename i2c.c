/*
 * i2c.c
 *
 *  Created on: 13.7.2012
 *      Author: kubanec
 */

#include "i2c.h"
#include "i2c_port.h"

#ifdef I2C_STUPID
i2c_status I2C_send_start(I2C_TypeDef * i2c, const i2c_requestTypedef * request)
{
	uint32_t timeout;

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

	return i2c_ok;
}

i2c_status I2C_send_array_stupid(I2C_TypeDef * i2c,
		const i2c_requestTypedef * request)
{
	uint32_t timeout;
	uint16_t length = request->length;
	i2c_status state;
	const uint8_t * data = request->data;

	state = I2C_send_start(i2c, request);
	if (state != i2c_ok)
		return state;

	//data sending
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

i2c_status I2C_read_byte_stupid(I2C_TypeDef * i2c, i2c_requestTypedef * request)
{
	uint32_t timeout;
	i2c_status state;
	uint8_t * data = request->data;

	state = I2C_send_start(i2c, request);
	if (state != i2c_ok)
		return state;

	/*!< Test on EV8 and clear it */
	timeout = TIMEOUT;
	while (I2C_GetFlagStatus(i2c, I2C_FLAG_BTF) == RESET)
	{
		if (timeout-- == 0)
			return i2c_repeatedStartFault;
	}

	//repeated start
	timeout = LONG_TIMEOUT;
	I2C_GenerateSTART(i2c, ENABLE);
	while (!I2C_CheckEvent(i2c, I2C_EVENT_MASTER_MODE_SELECT))
	{
		if (timeout-- == 0)
			return i2c_repeatedStartFault;
	}

	//read byte
	I2C_Send7bitAddress(i2c, request->address, I2C_Direction_Receiver);
	while (I2C_GetFlagStatus(i2c, I2C_FLAG_ADDR) == RESET)
	{
		if (timeout-- == 0)
			return i2c_repeatedStartFault;
	}

	I2C_AcknowledgeConfig(i2c, DISABLE);
	//will start reading to DR
	(void) i2c->SR2;

	I2C_GenerateSTOP(i2c, ENABLE);

	timeout = LONG_TIMEOUT;
	while (I2C_GetFlagStatus(i2c, I2C_FLAG_RXNE) == RESET)
	{
		if ((timeout--) == 0)
			return i2c_dataReadFault;
	}

	//read byte
	*data = I2C_ReceiveData(i2c);

	//check stop stop communication
	timeout = LONG_TIMEOUT;
	while (i2c->CR1 & I2C_CR1_STOP)
	{
		if ((timeout--) == 0)
			return i2c_stopReadFault;
	}

	/*!< Re-Enable Acknowledgement to be ready for another reception */
	I2C_AcknowledgeConfig(i2c, ENABLE);

	return i2c_ok;
}

i2c_status I2C_read_array_stupid(I2C_TypeDef * i2c,
		i2c_requestTypedef * request)
{
	uint32_t timeout;
	i2c_status state;
	uint16_t length = request->length;
	uint8_t * data = request->data;
	uint8_t temp;

	if (length < 2)
		return I2C_read_byte_stupid(i2c, request);

	state = I2C_send_start(i2c, request);
	if (state != i2c_ok)
		return state;

	/*!< Test on EV8 and clear it */
	timeout = TIMEOUT;
	while (I2C_GetFlagStatus(i2c, I2C_FLAG_BTF) == RESET)
	{
		if (timeout-- == 0)
			return i2c_repeatedStartFault;
	}

	//repeated start
	timeout = LONG_TIMEOUT;
	I2C_GenerateSTART(i2c, ENABLE);
	while (!I2C_CheckEvent(i2c, I2C_EVENT_MASTER_MODE_SELECT))
	{
		if (timeout-- == 0)
			return i2c_repeatedStartFault;
	}

	//repeated address
	timeout = LONG_TIMEOUT;
	I2C_Send7bitAddress(i2c, request->address, I2C_Direction_Receiver);
	while (!I2C_CheckEvent(i2c, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED))
	{
		if (timeout-- == 0)
			return i2c_repeatedAddressFault;
	}

	//data reading
	while (length--)
	{
		timeout = LONG_TIMEOUT;

		while (!I2C_CheckEvent(i2c, I2C_EVENT_MASTER_BYTE_RECEIVED))
		{
			if (timeout-- == 0)
				return i2c_dataReadFault;
		}

		temp = I2C_ReceiveData(i2c);
		*(data++) = temp;

		if (length == 1)
		{
			I2C_AcknowledgeConfig(i2c, DISABLE);
			I2C_GenerateSTOP(i2c, ENABLE);
		}
	}

	while (I2C_GetFlagStatus(i2c, I2C_FLAG_BUSY) == SET)
		;

	I2C_AcknowledgeConfig(i2c, ENABLE);
	return i2c_ok;
}

#endif
