/*
 * bme680Interface.h
 *
 *  Created on: Dec 27, 2022
 *      Author: rpa1labs
 */

#ifndef INC_BME680INTERFACE_H_
#define INC_BME680INTERFACE_H_

#include "main.h"

#include "bme680.h"



uint8_t bme680_interface_init(I2C_HandleTypeDef *i2c);
void getTemperatureHumidity(float *temperature, float *humidity);
void printTemperatureHumidity(float temperature, float humidity, UART_HandleTypeDef *huart);

#endif /* INC_BME680INTERFACE_H_ */
