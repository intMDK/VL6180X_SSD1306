#include "gpio.h"

GPIO_InitTypeDef gpioInit = {0};
void gpio_config(void)
{
	__HAL_RCC_GPIOA_CLK_ENABLE();
	gpioInit.Pin = GPIO_PIN_8 ;
	gpioInit.Mode = GPIO_MODE_OUTPUT_PP;
	gpioInit.Pull = GPIO_PULLUP;
	gpioInit.Speed = GPIO_SPEED_LOW;
	HAL_GPIO_Init(GPIOA, &gpioInit);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET);

}
