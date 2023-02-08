/*
 * CAda.cpp
 *
 *  Created on: 7 déc. 2022
 *      Author: rpa1labs
 */

#include "CAda.h"



int Init_Ada(SPIDevice dev){

	uint8_t register_write[] = { 0x80, 0xD3 };
	cs_reset(dev);
	HAL_Delay(100);
	cs_set(dev);
	while(HAL_SPI_GetState(dev.hspi) != HAL_SPI_STATE_READY);
	HAL_SPI_Transmit(dev.hspi, register_write, 2, 100);
	cs_reset(dev);

	uint8_t count = 0;

	while ( (Ada_Configuration_info(dev) & 0xF1) != (register_write[1] & 0xFD) ) {
			count++;

			cs_set(dev);
			while(HAL_SPI_GetState(dev.hspi) != HAL_SPI_STATE_READY);
			HAL_SPI_Transmit(dev.hspi, register_write, 2, 100);
			cs_reset(dev);

			HAL_Delay(100);

			if (count == 10) return 1;


		}
	return 0;

}


uint8_t Ada_Configuration_info(SPIDevice dev) {
	uint8_t read_data = 0x00;
	uint8_t configuration = 0x00;
	cs_set(dev);
	while(HAL_SPI_GetState(dev.hspi) != HAL_SPI_STATE_READY);
	HAL_SPI_Transmit(dev.hspi, &read_data, 1, 100);
	while(HAL_SPI_GetState(dev.hspi) != HAL_SPI_STATE_READY);
	HAL_SPI_Receive(dev.hspi, &configuration, 1, 100);
	cs_reset(dev);
	return configuration;
}

void displayTemp(UART_HandleTypeDef huart, double temp){

    char output[50];
    for(int i =0 ;i< 50;i++) output[i] = 0;

    int beforeDotTemp = (int)temp;
    int afterDotTemp = (double) ((temp - beforeDotTemp) * 100);
    if(temp < 0) afterDotTemp = -afterDotTemp;

    sprintf(output,"%d.%d\n", beforeDotTemp, afterDotTemp);

    HAL_UART_Transmit(&huart, (uint8_t*)&output, 50, 100);

}


void cs_set(SPIDevice dev){
	HAL_GPIO_WritePin(dev.gpio, dev.pin, GPIO_PIN_RESET);
	HAL_Delay(150);
}

void cs_reset(SPIDevice dev){
	HAL_Delay(150);
	HAL_GPIO_WritePin(dev.gpio, dev.pin, GPIO_PIN_SET);
}



double Get_Temperature(SPIDevice dev) {

	uint8_t read_address = 0x01;
	uint8_t buffer[7];

	cs_set(dev);
	while(HAL_SPI_GetState(dev.hspi) != HAL_SPI_STATE_READY);
	HAL_SPI_Transmit(dev.hspi, &read_address, 1, 100);
	while(HAL_SPI_GetState(dev.hspi) != HAL_SPI_STATE_READY);
	HAL_SPI_Receive(dev.hspi, buffer, 7, 100);
	cs_reset(dev);

	uint16_t sensorValue  = ((buffer[0] << 8) | buffer[1]) >> 1;

	uint8_t sensorStatus = buffer[6];

	if (sensorStatus > 0x00) return -999;

	double sensorResistance = ((double) sensorValue * 428.5 ) / (double) 32768.0;

	return Get_Temperature_math(sensorResistance);
}

double Get_Temperature_math(double sensorResistance) {

	double temperature = 0.0;

	if (sensorResistance >= (double) 100.0) {
		temperature = ((double) -0.0039083 + sqrt( (double) 0.00001527480889 - ((double) -0.00000231 * (1 - (sensorResistance / 100.0 ))) ) ) / (double) -0.000001155;
	} else {
		temperature = 	(double) 0.000000000270 * pow(sensorResistance, 5)
						  - (double) 0.000000066245 * pow(sensorResistance, 4)
						  - (double) 0.000000184636 * pow(sensorResistance, 3)
						  + (double) 0.002320232987 * pow(sensorResistance, 2)
						  + (double) 2.229927824035 * sensorResistance
						  - (double) 242.090854986215;
	}
	return temperature;
}

















