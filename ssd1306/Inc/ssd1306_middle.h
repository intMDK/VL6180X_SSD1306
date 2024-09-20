
#ifndef INC_SSD1306_MIDDLE_H_
#define INC_SSD1306_MIDDLE_H_

#include "ssd1306_defs.h"
#include "fonts.h"


extern I2C_HandleTypeDef hi2c2;

typedef enum {
	SSD1306_COLOR_BLACK = 0x00,
	SSD1306_COLOR_WHITE = 0x01
} SSD1306_COLOR;

void SSD1306_SetPixel(uint8_t x, uint8_t y, uint8_t color) ;
void ssd1306_writebyte(uint16_t add, uint8_t data );
void ssd1306_init(void);
void SSD1306_SendCommand(uint8_t *commands);
void SSD1306_FillScreen(uint8_t color) ;
void test (uint8_t newValue );
void SSD1306_SendData(uint8_t data);
void gotoxy(uint8_t x, uint8_t y);
void SSD1306_Srectangle(uint8_t start_x, uint8_t start_y,uint8_t end_x, uint8_t end_y, uint8_t color);
void SSD1306_UpdateScreen(void);
void SSD1306_Putc (char ch, FontDef_t* Font, SSD1306_COLOR color);
char SSD1306_Puts(char* str, FontDef_t* Font, SSD1306_COLOR color);

#endif /* INC_SSD1306_MIDDLE_H_ */
