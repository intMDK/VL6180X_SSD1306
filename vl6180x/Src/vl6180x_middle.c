#include "vl6180x_middle.h"

////////////////////////////////////////////////////////////ALS///////////////////////////////////////////////////////

void vl6180x_ALS_start(void)
{
	uint8_t Rvalue;

	Rvalue =  vl6180x_randomread(SYSTEM__INTERRUPT_CONFIG_GPIO);
	Rvalue &= 0b11000111;
	Rvalue |= (1<<5);
	vl6180x_writebyte(SYSTEM__INTERRUPT_CONFIG_GPIO, Rvalue);
	vl6180x_writebyte(SYSALS__INTEGRATION_PERIOD, 0x00);
	vl6180x_writebyte(0x0041, 0x31); // wasn't mention in datasheet

	vl6180x_writebyte(SYSALS__START, 0b1);
}
uint16_t vl6180x_ALS_read(void)
{

	char data[2];
	char als_status,read;

	vl6180x_ALS_start();
	// check the status
	als_status = vl6180x_randomread(RESULT__INTERRUPT_STATUS_GPIO);
	als_status &= 0x38;

	// wait for new measurement ready status
	while (als_status != 0x20)
	{
		als_status = vl6180x_randomread(RESULT__INTERRUPT_STATUS_GPIO);
		als_status &= 0x38;
	}

	// ALS data is 16 bit
	data[0]=vl6180x_randomread(RESULT__ALS_VAL);
	data[1]=vl6180x_randomread(RESULT__ALS_VAL + 0x1);

	uint16_t ALS_count = (data[0] << 8 ) | (data[1] );


	read =  vl6180x_randomread(SYSTEM__INTERRUPT_CLEAR);
	read |= 0b00000110;
	vl6180x_writebyte(SYSTEM__INTERRUPT_CLEAR, read);

	return ((int)ALS_count * 0.64);
}

void VL6180X_SetAlsIntegrationTime(uint16_t integration_time_ms)
{
    // Convert the desired integration time (in ms) to the corresponding register value
    uint8_t integration_period = integration_time_ms / 1.67;  // Register value = time (ms) / 1.67ms

    // Write the new integration period to the ALS integration register (0x0040)
    uint8_t data = integration_period;
    vl6180x_writebyte(0x40, data);
}


uint8_t vl6180_Als_ReadGain(void)
{
	uint8_t Gain;
	float lookupTable[8]={20,10,5,2.5,1.67,1.25,1,40};
	Gain = vl6180x_randomread(0x03F);
	Gain &= 0x7;
	Gain = lookupTable[Gain];
	return Gain;

}

//////////////////////////////////////////////////////TOF/////////////////////////////////////////////////////////////
void vl6180x_TOF_start(void)
{
	uint8_t Rvalue;

	Rvalue =  vl6180x_randomread(SYSTEM__INTERRUPT_CONFIG_GPIO);
	Rvalue &= 0b11111000;
	Rvalue |= (1<<2);
	vl6180x_writebyte(SYSTEM__INTERRUPT_CONFIG_GPIO, Rvalue);

	vl6180x_writebyte(SYSRANGE__START, 0b1);
}
uint8_t vl6180x_TOF_read(void)
{
	uint8_t read,Rvalue;
	char range_status;

	vl6180x_TOF_start();

	// check the status
	range_status = vl6180x_randomread(RESULT__INTERRUPT_STATUS_GPIO);
	range_status &= 0x07;

	// wait for new measurement ready status
	while (range_status != 0x04)
	{
		range_status = vl6180x_randomread(RESULT__INTERRUPT_STATUS_GPIO);
		range_status &= 0x07;
	}

	Rvalue =  vl6180x_randomread(RESULT__RANGE_VAL);

	read =  vl6180x_randomread(SYSTEM__INTERRUPT_CLEAR);
	read |= 0b00000101;
	vl6180x_writebyte(SYSTEM__INTERRUPT_CLEAR, read);
	return Rvalue;
}



void vl6180x_setting(void)
{
	vl6180x_writebyte(0x0207, 0x01);
	vl6180x_writebyte(0x0208, 0x01);
	vl6180x_writebyte(0x0133, 0x01);
	vl6180x_writebyte(0x0096, 0x00);
	vl6180x_writebyte(0x0097, 0xFD);
	vl6180x_writebyte(0x00e3, 0x00);
	vl6180x_writebyte(0x00e4, 0x04);
	vl6180x_writebyte(0x00e5, 0x02);
	vl6180x_writebyte(0x00e6, 0x01);
	vl6180x_writebyte(0x00e7, 0x03);
	vl6180x_writebyte(0x00f5, 0x02);
	vl6180x_writebyte(0x00D9, 0x05);
	vl6180x_writebyte(0x00DB, 0xCE);
	vl6180x_writebyte(0x00DC, 0x03);
	vl6180x_writebyte(0x00DD, 0xF8);
	vl6180x_writebyte(0x009f, 0x00);
	vl6180x_writebyte(0x00a3, 0x3c);
	vl6180x_writebyte(0x00b7, 0x00);
	vl6180x_writebyte(0x00bb, 0x3c);
	vl6180x_writebyte(0x00b2, 0x09);
	vl6180x_writebyte(0x00ca, 0x09);
	vl6180x_writebyte(0x0198, 0x01);
	vl6180x_writebyte(0x01b0, 0x17);
	vl6180x_writebyte(0x01ad, 0x00);
	vl6180x_writebyte(0x00FF, 0x05);
	vl6180x_writebyte(0x0100, 0x05);
	vl6180x_writebyte(0x0199, 0x05);
	vl6180x_writebyte(0x0109, 0x07);
	vl6180x_writebyte(0x010a, 0x30);
	vl6180x_writebyte(0x003f, 0x46);
	vl6180x_writebyte(0x01a6, 0x1b);
	vl6180x_writebyte(0x01ac, 0x3e);
	vl6180x_writebyte(0x01a7, 0x1f);
	vl6180x_writebyte(0x0103, 0x01);
	vl6180x_writebyte(0x0030, 0x00);
	vl6180x_writebyte(0x001b, 0x0A);
	vl6180x_writebyte(0x003e, 0x0A);
	vl6180x_writebyte(0x0131, 0x04);
	vl6180x_writebyte(0x0011, 0x10);
	vl6180x_writebyte(0x0014, 0x24);
	vl6180x_writebyte(0x0031, 0xFF);
	vl6180x_writebyte(0x00d2, 0x01);
	vl6180x_writebyte(0x00f2, 0x01);
}
void vl6180x_init(void)
{
	uint8_t reset;
	i2c_I2C1_GPIO_config();
	i2c_config();
	reset =  vl6180x_randomread(SYSTEM__FRESH_OUT_OF_RESET);
	if(reset == 0x01)
	{
		vl6180x_setting();
		vl6180x_writebyte(SYSTEM__FRESH_OUT_OF_RESET, 0x00);
	}
}
