#include "ssd1306_hardware.h"





void i2c_I2C2_GPIO_config(void)
{
	GPIO_InitTypeDef gpioInitstruct = {0};

	__HAL_RCC_GPIOB_CLK_ENABLE();
	gpioInitstruct.Pin = GPIO_PIN_10|GPIO_PIN_11;
	gpioInitstruct.Mode = GPIO_MODE_AF_OD;
	gpioInitstruct.Pull = GPIO_NOPULL;
	gpioInitstruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	gpioInitstruct.Alternate = GPIO_AF4_I2C2;
	HAL_GPIO_Init(GPIOB, &gpioInitstruct);
}
void i2c_I2C2_config(void)
{
	__HAL_RCC_I2C2_CLK_ENABLE();
	hi2c2.Instance = I2C2;
	hi2c2.Init.Timing = 0x00702991;
	hi2c2.Init.OwnAddress1 = 0;
	hi2c2.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	hi2c2.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	hi2c2.Init.OwnAddress2 = 0;
	hi2c2.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
	hi2c2.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	hi2c2.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
	HAL_I2C_Init(&hi2c2);

	/** Configure Analog filter
		  */
	 HAL_I2CEx_ConfigAnalogFilter(&hi2c2, I2C_ANALOGFILTER_ENABLE);

	  /** Configure Digital filter
	  */
	  HAL_I2CEx_ConfigDigitalFilter(&hi2c2, 0);
}





