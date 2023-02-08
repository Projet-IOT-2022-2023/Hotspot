/*
 * Anemometer.h
 *
 *  Created on: Dec 27, 2022
 *      Author: rpa1labs
 */

#ifndef INC_ANEMOMETER_H_
#define INC_ANEMOMETER_H_

#include "main.h"

void Anemometer_init(ADC_HandleTypeDef *adc);
double getWindSpeed();

#endif /* INC_ANEMOMETER_H_ */
