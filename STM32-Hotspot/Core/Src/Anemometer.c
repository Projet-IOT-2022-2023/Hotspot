/*
 * Anemometer.c
 *
 *  Created on: Dec 27, 2022
 *      Author: rpa1labs
 */

#include "Anemometer.h"

const double MIN_VOLTAGE = 0.4;
const double MAX_VOLTAGE = 2.0;

const double MIN_WIND_SPEED = 0.0;
const double MAX_WIND_SPEED = 32.0;

const double MIN_RAW = (MIN_VOLTAGE+0.06)*4096/3.3;

const double ADC_TO_WIND_RATIO =  (MAX_WIND_SPEED - MIN_WIND_SPEED)/(MAX_VOLTAGE - MIN_VOLTAGE)*3.3/4096;

ADC_HandleTypeDef *hadcanem;

void Anemometer_init(ADC_HandleTypeDef *adc){
	hadcanem = adc;
}


double getWindSpeed(){
	HAL_ADC_Start(hadcanem);
	HAL_ADC_PollForConversion(hadcanem, HAL_MAX_DELAY);
	uint32_t raw = HAL_ADC_GetValue(hadcanem);

	double windspeed = ( (double) raw - MIN_RAW ) * (double) ADC_TO_WIND_RATIO;

	if(windspeed < 0) windspeed = 0;

	return windspeed;

}
