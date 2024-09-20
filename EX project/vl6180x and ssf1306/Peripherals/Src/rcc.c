#include "rcc.h"

RCC_OscInitTypeDef rccOscInit = {0};
RCC_ClkInitTypeDef rccClkInit = {0};
void rcc_config(void)
{
	HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1);

	rccOscInit.OscillatorType = RCC_OSCILLATORTYPE_MSI;
	rccOscInit.MSIState = RCC_MSI_ON;
	rccOscInit.MSICalibrationValue =0;
	rccOscInit.MSIClockRange = RCC_MSIRANGE_6;
	rccOscInit.PLL.PLLState = RCC_PLL_ON;
	rccOscInit.PLL.PLLSource = RCC_PLLSOURCE_MSI;
	rccOscInit.PLL.PLLM = 1;
	rccOscInit.PLL.PLLN = 40;
	rccOscInit.PLL.PLLP = RCC_PLLP_DIV7;
	rccOscInit.PLL.PLLQ = RCC_PLLQ_DIV2;
	rccOscInit.PLL.PLLR = RCC_PLLR_DIV2;
	HAL_RCC_OscConfig(&rccOscInit);

	rccClkInit.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
            |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
	rccClkInit.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	rccClkInit.AHBCLKDivider = RCC_SYSCLK_DIV1;
	rccClkInit.APB1CLKDivider = RCC_SYSCLK_DIV1;
	rccClkInit.APB2CLKDivider = RCC_SYSCLK_DIV1;
	HAL_RCC_ClockConfig(&rccClkInit, FLASH_LATENCY_4);
}
