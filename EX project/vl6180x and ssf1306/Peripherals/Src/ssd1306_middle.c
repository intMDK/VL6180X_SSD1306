#include "ssd1306_middle.h"

uint8_t dcommands[3];
uint8_t scommands[2];
uint8_t localBuffer[128 *  8];

typedef struct {
	uint16_t X;
	uint16_t Y;
} SSD1306_t;
SSD1306_t SSD1306;

void SSD1306_setting(void)
{
	// Set Memory Addressing Mode to Horizontal
	dcommands[0] = 0;
	scommands[0] = 0;

	dcommands[1] = Set_Memory_Addressing;
	dcommands[2] = 0x10;
	SSD1306_SendCommand(dcommands);

	//Set Page Start Address for Page Addressing Mode,0-7
	scommands[1] = Set_Page_Start_Address;
	SSD1306_SendCommand(scommands);

	//---set low column address
	scommands[1] = Set_Lcolumn_Saddress;
	SSD1306_SendCommand(scommands);

	//---set high column address
	scommands[1] = Set_Hcolumn_Saddress;
	SSD1306_SendCommand(scommands);

	//Set_Multiplex_Ratio to 64

	dcommands[1] = Set_Multiplex_Ratio;
	dcommands[2] = 0x3F;
	SSD1306_SendCommand(dcommands);



	//Set_Display_Offset
	dcommands[1] = Set_Display_Offset;
	dcommands[2] = 0x00;
	SSD1306_SendCommand(dcommands);

	//Set Display Start Line
	scommands[1] = Set_Display_Start_Line_0;
	SSD1306_SendCommand(scommands);

	//Set Segment Re-map
	scommands[1] = Set_Segment_Remap_RtoL;
	SSD1306_SendCommand(scommands);

	//Set COM Output Scan Direction Bottom to Top
	scommands[1] = Set_COM_Output_Scan_Direction_BtoT;
	SSD1306_SendCommand(scommands);

	//Set COM Pins Hardware Configuration
	dcommands[1] = Set_COM_Pins_Hardware_Configuration;
	dcommands[2] = 0x12;
	SSD1306_SendCommand(dcommands);

	//Set Contrast Control
	dcommands[1] = Set_Contrast_Control;
	dcommands[2] = 0xFF;
	SSD1306_SendCommand(dcommands);

	//Disable Entire Display ON
	scommands[1] = Disable_Entire_Display_ON;
	SSD1306_SendCommand(scommands);

	//Set Normal Display
	scommands[1] = Set_Normal_Display;
	SSD1306_SendCommand(scommands);

	//Set Osc Frequency
	dcommands[1] = Set_Osc_Frequency;
	dcommands[2] = 0xF0;
	SSD1306_SendCommand(dcommands);

	//Enable_Charge_Pump_Regulator
	dcommands[1] = Enable_Charge_Pump_Regulator;
	dcommands[2] = 0x14;
	SSD1306_SendCommand(dcommands);

	//Display On
	scommands[1] = Display_On;
	SSD1306_SendCommand(scommands);
}
void ssd1306_init(void)
{
	i2c_I2C2_GPIO_config();
	i2c_I2C2_config();


	if(HAL_I2C_IsDeviceReady(&hi2c2, SSD1306_I2C_ADDRESS, 1, 20000)==HAL_OK)
	{
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, 0);
		SSD1306_setting();
	}
	SSD1306_FillScreen(0);

}
void SSD1306_FillScreen(uint8_t color)
{

    memset(localBuffer, color ? 0xFF : 0x00, sizeof(localBuffer));


    for (uint8_t page = 0; page < 8; page++)
    {
        SSD1306_SetPageAddress(page);
        SSD1306_SetColumnAddress(0);

        for (uint8_t col = 0; col < 128; col++)
        {
        	SSD1306_SendData(localBuffer[page * 128 + col]);
        }
    }
}

void SSD1306_SetColumnAddress(uint8_t col)
{
	uint8_t setColumnCmd[] = { 0x00, 0x21, col, 0x7F };
	SSD1306_SendCommand(setColumnCmd);
}

void SSD1306_SetPageAddress(uint8_t page)
{
	uint8_t setPageCmd[] = { 0x00, 0x22, page, 0x07 };
	SSD1306_SendCommand(setPageCmd);
}
void SSD1306_SendData(uint8_t data)
{
    uint8_t payload[2];
    payload[0] = 0x40;
    payload[1] = data;
    HAL_I2C_Master_Transmit(&hi2c2, SSD1306_I2C_ADDRESS, payload, 2, HAL_MAX_DELAY);
}

void gotoxy(uint8_t x, uint8_t y)
{
	SSD1306.X = x;
	SSD1306.Y = y;
}

void SSD1306_UpdateScreen(void)
{

	for (uint8_t page = 0; page < 8; page++)
	{
		//Set Page Start Address for Page Addressing Mode,0-7
		scommands[1] = (Set_Page_Start_Address+page);
		SSD1306_SendCommand(scommands);

		//---set low column address
		scommands[1] = Set_Lcolumn_Saddress;
		SSD1306_SendCommand(scommands);

		//---set high column address
		scommands[1] = Set_Hcolumn_Saddress;
		SSD1306_SendCommand(scommands);
		for(uint8_t col = 0; col < 128; col++)
		{
			SSD1306_SendData(localBuffer[col+(page*128)]);
		}

	}
}

void SSD1306_SetPixel(uint8_t x, uint8_t y, uint8_t color)
{
	if (x >= 128 || y >= 64)
	{
	   return;
	}
	uint16_t byteIndex = x + (y / 8) * 128;
	uint8_t bitMask = 1 << (y % 8);
	if (color)
	{
	    localBuffer[byteIndex] |= bitMask;
	}
	else
	{
	    localBuffer[byteIndex] &= ~bitMask;
	}
}
void SSD1306_Putc (char ch, FontDef_t* Font, SSD1306_COLOR color)
{
	uint16_t data;


	for(int i=0;i<=18;i++)
	{
		data = Font->data[(ch - 32) * 18 + i];
		for(int j=0;j<=11;j++)
		{
			if(data & (1 << (15 - j)))
			{
				SSD1306_SetPixel(SSD1306.X + j,SSD1306.Y + i, 1);
			}
			else
			{
				SSD1306_SetPixel(SSD1306.X + j,SSD1306.Y + i, 0);
			}
		}
	}
	SSD1306.X += 11;
}
char SSD1306_Puts(char* str, FontDef_t* Font, SSD1306_COLOR color)
{
	/* Write characters */
	while (*str)
	{
		/* Write character by character */
		SSD1306_Putc(*str, Font, color);

		/* Increase string pointer */
		str++;
	}

	/* Everything OK, zero should be returned */
	return *str;
}
void SSD1306_Srectangle(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t color)
{
	if (x + width > 128) {
	        width = 128 - x;
	    }
	    if (y + height > 64) {
	        height = 64 - y;
	    }
	for (uint8_t i = x; i < x + width; i++)
	{
	        for (uint8_t j = y; j < y + height; j++)
	        {
	            SSD1306_SetPixel(i, j, color);
	        }
	    }
	SSD1306_UpdateScreen();
}
void SSD1306_SendCommand(uint8_t *commands)
{
    HAL_I2C_Master_Transmit(&hi2c2, SSD1306_I2C_ADDRESS , commands, sizeof(commands), HAL_MAX_DELAY);
}
