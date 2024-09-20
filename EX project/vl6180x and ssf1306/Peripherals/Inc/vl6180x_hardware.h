
#ifndef INC_VL6180X_HARDWARE_H_
#define INC_VL6180X_HARDWARE_H_

#include "main.h"
#include "vl6180x_defs.h"
void i2c_I2C1_GPIO_config(void);
void i2c_config(void);
void vl6180x_writebyte(uint16_t add, uint8_t data );
uint8_t vl6180x_randomread(uint16_t add);
uint16_t vl6180x_multread(uint16_t add);


#endif /* INC_VL6180X_HARDWARE_H_ */
