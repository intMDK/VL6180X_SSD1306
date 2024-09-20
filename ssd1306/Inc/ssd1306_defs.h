
#ifndef INC_SSD1306_DEFS_H_
#define INC_SSD1306_DEFS_H_

#define SSD1306_I2C_ADDRESS 0x78
#define Set_Multiplex_Ratio 0xA8
#define	Set_Display_Offset	0xD3
#define Set_Display_Start_Line_0 0x40
#define Set_Segment_Remap_LtoR 0xA0
#define Set_Segment_Remap_RtoL 0xA1
#define Set_COM_Output_Scan_Direction_BtoT  0xC8
#define Set_COM_Output_Scan_Direction_TtoB  0xC0
#define Set_COM_Pins_Hardware_Configuration  0xDA
#define Set_Contrast_Control 0x81
#define Disable_Entire_Display_ON  0xA4
#define Set_Normal_Display 0xA6
#define Set_Inverse_Display 0xA7
#define Set_Osc_Frequency 0xD5
#define Enable_Charge_Pump_Regulator 0x8D
#define Display_On 0XAF
#define Set_Memory_Addressing 0x20
#define Set_Page_Start_Address 0xB0
#define Set_Lcolumn_Saddress 0x00
#define Set_Hcolumn_Saddress 0x10
#endif /* INC_SSD1306_DEFS_H_ */
