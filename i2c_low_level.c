#include "i2c_low_level.h"

#if (defined(I2C1_USED) || defined(I2C2_USED) || defined(I2C3_USED))
void i2c_LowLevel_DeInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
#ifdef I2C1_USED
	/* 2C Peripheral Disable */
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
#endif

#ifdef I2C2_USED
	/* I2C Peripheral Disable */
	I2C_Cmd(I2C_2, DISABLE);

	/* I2C DeInit */
	I2C_DeInit(I2C_2);

	/*!< I2C Periph clock disable */
	RCC_APB1PeriphClockCmd(I2C2_CLK, DISABLE);

	/*!< GPIO configuration */
	/*!< Configure I2C pins: SCL */
	GPIO_InitStructure.GPIO_Pin = I2C2_SCL_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(I2C2_SCL_GPIO_PORT, &GPIO_InitStructure);

	/*!< Configure I2C pins: SDA */
	GPIO_InitStructure.GPIO_Pin = I2C2_SDA_PIN;
	GPIO_Init(I2C2_SDA_GPIO_PORT, &GPIO_InitStructure);
#endif

#ifdef I2C3_USED
	/* I2C Peripheral Disable */
	I2C_Cmd(I2C_3, DISABLE);

	/* I2C DeInit */
	I2C_DeInit(I2C_3);

	/*!< I2C Periph clock disable */
	RCC_APB1PeriphClockCmd(I2C3_CLK, DISABLE);

	/*!< GPIO configuration */
	/*!< Configure I2C pins: SCL */
	GPIO_InitStructure.GPIO_Pin = I2C3_SCL_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(I2C3_SCL_GPIO_PORT, &GPIO_InitStructure);

	/*!< Configure I2C pins: SDA */
	GPIO_InitStructure.GPIO_Pin = I2C3_SDA_PIN;
	GPIO_Init(I2C3_SDA_GPIO_PORT, &GPIO_InitStructure);
#endif
}

void i2c_LowLevel_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

#ifdef I2C1_USED
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
#endif

#ifdef I2C2_USED
	/*!< I2C Periph clock enable */
	RCC_APB1PeriphClockCmd(I2C2_CLK, ENABLE);

	/*!< I2C_SCL_GPIO_CLK and I2C_SDA_GPIO_CLK Periph clock enable */
	RCC_AHB1PeriphClockCmd(I2C2_SCL_GPIO_CLK | I2C2_SDA_GPIO_CLK, ENABLE);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

	/* Reset I2C IP */
	RCC_APB1PeriphResetCmd(I2C2_CLK, ENABLE);

	/* Release reset signal of I2C IP */
	RCC_APB1PeriphResetCmd(I2C2_CLK, DISABLE);

	/*!< GPIO configuration */
	/* Connect PXx to I2C_SCL*/
	GPIO_PinAFConfig(I2C2_SCL_GPIO_PORT, I2C2_SCL_SOURCE, I2C2_SCL_AF);
	/* Connect PXx to I2C_SDA*/
	GPIO_PinAFConfig(I2C2_SDA_GPIO_PORT, I2C2_SDA_SOURCE, I2C2_SDA_AF);

	/*!< Configure I2C pins: SCL */
	GPIO_InitStructure.GPIO_Pin = I2C2_SCL_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(I2C2_SCL_GPIO_PORT, &GPIO_InitStructure);

	/*!< Configure I2C pins: SDA */
	GPIO_InitStructure.GPIO_Pin = I2C2_SDA_PIN;
	GPIO_Init(I2C2_SDA_GPIO_PORT, &GPIO_InitStructure);

#endif

#ifdef I2C3_USED
	/*!< I2C Periph clock enable */
	RCC_APB1PeriphClockCmd(I2C3_CLK, ENABLE);

	/*!< I2C_SCL_GPIO_CLK and I2C_SDA_GPIO_CLK Periph clock enable */
	RCC_AHB1PeriphClockCmd(I2C3_SCL_GPIO_CLK | I2C3_SDA_GPIO_CLK, ENABLE);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

	/* Reset I2C IP */
	RCC_APB1PeriphResetCmd(I2C3_CLK, ENABLE);

	/* Release reset signal of I2C IP */
	RCC_APB1PeriphResetCmd(I2C3_CLK, DISABLE);

	/*!< GPIO configuration */
	/* Connect PXx to I2C_SCL*/
	GPIO_PinAFConfig(I2C3_SCL_GPIO_PORT, I2C3_SCL_SOURCE, I2C3_SCL_AF);
	/* Connect PXx to I2C_SDA*/
	GPIO_PinAFConfig(I2C3_SDA_GPIO_PORT, I2C3_SDA_SOURCE, I2C3_SDA_AF);

	/*!< Configure I2C pins: SCL */
	GPIO_InitStructure.GPIO_Pin = I2C3_SCL_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(I2C3_SCL_GPIO_PORT, &GPIO_InitStructure);

	/*!< Configure I2C pins: SDA */
	GPIO_InitStructure.GPIO_Pin = I2C3_SDA_PIN;
	GPIO_Init(I2C3_SDA_GPIO_PORT, &GPIO_InitStructure);

#endif
}
#endif

