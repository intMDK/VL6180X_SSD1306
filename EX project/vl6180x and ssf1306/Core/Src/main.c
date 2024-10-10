#include "main.h"
#include "rcc.h"
#include "gpio.h"
#include "vl6180x_middle.h"
#include "ssd1306_middle.h"
#include "fonts.h"
#include "stdio.h"


uint16_t als_result;
uint8_t tof_result;
char str[128];
int main(void)
{

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();
  /* Configure the system clock */
  rcc_config();

  /* Initialize all configured peripherals */
  gpio_config();

  vl6180x_init();

  ssd1306_init();

  while (1)
  {

	  als_result = vl6180x_ALS_read();
	  tof_result = (0.5*tof_result) + (0.5 * (vl6180x_TOF_read()));


	  sprintf(str,"Range:%d ",tof_result);
	  gotoxy(0,0);
	  SSD1306_Puts(str,&Font_11x18, SSD1306_COLOR_WHITE);
	  sprintf(str,"ALS  :%d    ",als_result);
  	  gotoxy(0, 20);
  	  SSD1306_Puts(str,&Font_11x18, SSD1306_COLOR_WHITE);

  	  SSD1306_UpdateScreen();

  }
}

