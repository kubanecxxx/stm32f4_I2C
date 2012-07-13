/*
 * i2c_1.c
 *
 *  Created on: 13.7.2012
 *      Author: kubanec
 */

#include "i2c_low_level.h"
#include "stm32f4xx.h"
#include "i2c_init.h"

#if (defined(I2C1_USED) || defined(I2C2_USED) || defined(I2C3_USED))
void I2C_all_init()
{
	I2C_InitTypeDef I2C_InitStructure;

	i2c_LowLevel_DeInit();
	i2c_LowLevel_Init();

#ifdef I2C1_USED
	I2C_InitStructure.I2C_Mode = I2C1_MODE;
	I2C_InitStructure.I2C_DutyCycle = I2C1_DCL;
	I2C_InitStructure.I2C_OwnAddress1 = I2C1_SLAVE_ADDRESS7;
	I2C_InitStructure.I2C_Ack = I2C1_ACK;
	I2C_InitStructure.I2C_AcknowledgedAddress = I2C1_ACK_ADDRESS;
	I2C_InitStructure.I2C_ClockSpeed = I2C1_SPEED;

	I2C_Cmd(I2C1, ENABLE);
	I2C_Init(I2C1, &I2C_InitStructure);
#endif

#ifdef I2C2_USED
	I2C_InitStructure.I2C_Mode = I2C2_MODE;
	I2C_InitStructure.I2C_DutyCycle = I2C2_DCL;
	I2C_InitStructure.I2C_OwnAddress1 = I2C2_SLAVE_ADDRESS7;
	I2C_InitStructure.I2C_Ack = I2C2_ACK;
	I2C_InitStructure.I2C_AcknowledgedAddress = I2C2_ACK_ADDRESS;
	I2C_InitStructure.I2C_ClockSpeed = I2C2_SPEED;

	I2C_Cmd(I2C1, ENABLE);
	I2C_Init(I2C1, &I2C_InitStructure);
#endif

#ifdef I2C3_USED
	I2C_InitStructure.I2C_Mode = I2C3_MODE;
	I2C_InitStructure.I2C_DutyCycle = I2C3_DCL;
	I2C_InitStructure.I2C_OwnAddress1 = I2C3_SLAVE_ADDRESS7;
	I2C_InitStructure.I2C_Ack = I2C3_ACK;
	I2C_InitStructure.I2C_AcknowledgedAddress = I2C3_ACK_ADDRESS;
	I2C_InitStructure.I2C_ClockSpeed = I2C3_SPEED;

	I2C_Cmd(I2C1, ENABLE);
	I2C_Init(I2C1, &I2C_InitStructure);
#endif
}
#endif

