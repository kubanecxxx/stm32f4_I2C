#include "i2c_low_level.h"

#ifdef I2C1_USED

void i2c_1_LowLevel_DeInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	/* sEE_I2C Peripheral Disable */
	I2C_Cmd(I2C_1, DISABLE);

	/* I2C DeInit */
	I2C_DeInit(I2C_1);

	/*!< I2C Periph clock disable */
	RCC_APB1PeriphClockCmd(I2C1_CLK, DISABLE);

	/*!< GPIO configuration */
	/*!< Configure I2C pins: SCL */
	GPIO_InitStructure.GPIO_Pin = I2C1_SCL_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(I2C1_SCL_GPIO_PORT, &GPIO_InitStructure);

	/*!< Configure I2C pins: SDA */
	GPIO_InitStructure.GPIO_Pin = I2C1_SDA_PIN;
	GPIO_Init(I2C1_SDA_GPIO_PORT, &GPIO_InitStructure);
}

void i2c_1_LowLevel_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	/*!< I2C Periph clock enable */
	RCC_APB1PeriphClockCmd(I2C1_CLK, ENABLE);

	/*!< I2C_SCL_GPIO_CLK and I2C_SDA_GPIO_CLK Periph clock enable */
	RCC_AHB1PeriphClockCmd(I2C1_SCL_GPIO_CLK | I2C1_SDA_GPIO_CLK, ENABLE);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

	/* Reset I2C IP */
	RCC_APB1PeriphResetCmd(I2C1_CLK, ENABLE);

	/* Release reset signal of I2C IP */
	RCC_APB1PeriphResetCmd(I2C1_CLK, DISABLE);

	/*!< GPIO configuration */
	/* Connect PXx to I2C_SCL*/
	GPIO_PinAFConfig(I2C1_SCL_GPIO_PORT, I2C1_SCL_SOURCE, I2C1_SCL_AF);
	/* Connect PXx to I2C_SDA*/
	GPIO_PinAFConfig(I2C1_SDA_GPIO_PORT, I2C1_SDA_SOURCE, I2C1_SDA_AF);

	/*!< Configure I2C pins: SCL */
	GPIO_InitStructure.GPIO_Pin = I2C1_SCL_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(I2C1_SCL_GPIO_PORT, &GPIO_InitStructure);

	/*!< Configure I2C pins: SDA */
	GPIO_InitStructure.GPIO_Pin = I2C1_SDA_PIN;
	GPIO_Init(I2C1_SDA_GPIO_PORT, &GPIO_InitStructure);
}

#endif
