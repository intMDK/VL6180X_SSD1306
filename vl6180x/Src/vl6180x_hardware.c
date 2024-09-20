#include <vl6180x_hardware.h>

I2C_HandleTypeDef hi2c1;

void i2c_I2C1_GPIO_config(void)
{
	GPIO_InitTypeDef gpioInit = {0};

	__HAL_RCC_GPIOB_CLK_ENABLE();
	gpioInit.Pin = GPIO_PIN_6 | GPIO_PIN_7;
	gpioInit.Mode = GPIO_MODE_AF_OD;
	gpioInit.Pull = GPIO_NOPULL;
	gpioInit.Speed = GPIO_SPEED_FREQ_HIGH;
	gpioInit.Alternate = GPIO_AF4_I2C1;
	HAL_GPIO_Init(GPIOB, &gpioInit);
}
void i2c_config(void)
{
	__HAL_RCC_I2C1_CLK_ENABLE();
	hi2c1.Instance = I2C1;
	hi2c1.Init.Timing =0x00702991;
	hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLED;
	hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLED;
	hi2c1.Init.OwnAddress1 = 0;
	hi2c1.Init.OwnAddress2 = 0;
	hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
	HAL_I2C_Init(&hi2c1);

	/** Configure Analog filter
		  */
	 HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE);

	  /** Configure Digital filter
	  */
	  HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0);
}
void vl6180x_writebyte(uint16_t add, uint8_t data )
{
	uint8_t final_data[3];
	final_data[0] = (add>>8);
	final_data[1] = add;
	final_data[2] = data;

	HAL_I2C_Master_Transmit(&hi2c1, VL6180X_ADDR, final_data, 3, 10);
	HAL_Delay(10);
}
uint8_t vl6180x_randomread(uint16_t add)
{
	uint8_t final_data[2],Rdata;
	final_data[0] = (add>>8);
	final_data[1] = add;

	HAL_I2C_Master_Transmit(&hi2c1, VL6180X_ADDR, final_data, 2, 10);
	HAL_I2C_Master_Receive(&hi2c1, VL6180X_ADDR,(uint8_t*)&Rdata, 1, 10);
	HAL_Delay(10);
	return Rdata;
}







