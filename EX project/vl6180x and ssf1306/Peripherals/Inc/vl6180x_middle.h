
#ifndef INC_VL6180X_MIDDLE_H_
#define INC_VL6180X_MIDDLE_H_
#include "main.h"
#include "vl6180x_hardware.h"
void vl6180x_init(void);
uint8_t vl6180x_TOF_read(void);
uint16_t vl6180x_ALS_read(void);
uint8_t vl6180_Als_ReadGain(void);
void VL6180X_SetAlsIntegrationTime(uint16_t integration_time_ms);

#endif /* INC_VL6180X_MIDDLE_H_ */
