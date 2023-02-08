/*
 * rn2483.c
 *
 *  Created on: Jan 21, 2023
 *      Author: rpa1labs
 */


/*
sys reset

mac set pwridx 1

mac set dr 5

mac set deveui 0004A30B001A661B

mac set appeui FF00000FF0000001

mac set appkey 2964A451A352CA45A620396685591557

mac set adr on

mac set devaddr F5A00802

mac set nwkskey 2964A451A352CA45A620396685591557

mac set appskey 2964A451A352CA45A620396685591557

mac save


mac join otaa

mac tx uncnf 1 54
 */

#include "rn2483.h"


unsigned int is_equal(unsigned int length, char* data1, char* data2){
	for(int i=0; i<length; i++) if(data1[i] != data2[i]) return 0;
	return 1;
}


unsigned int wait_for_response(unsigned int length, char* data, unsigned int timeout, UART_HandleTypeDef* huart){
	timeout /= 100;

	unsigned int* buffer;
	buffer = malloc(length*sizeof(unsigned int));

	for(int i=0; i<timeout; i++){

		//HAL_TIMEOUT

		HAL_StatusTypeDef status = HAL_UART_Receive(&huart, buffer, length, 100);

		if(status != HAL_TIMEOUT){
			if(is_equal(length, buffer, data)) return 1;
			HAL_Delay(100);
		}



	}


	return 0;

}

void init_rn2483(UART_HandleTypeDef* huart){

	HAL_UART_Transmit(&huart, "sys reset\n\r", 11, 100);
	HAL_Delay(5000);

	HAL_UART_Transmit(&huart, "mac set dr 5\n\r", 14, 100);
	HAL_Delay(100);

	HAL_UART_Transmit(&huart, "mac set deveui 0004A30B001A661B\n\r", 33, 100);
	HAL_Delay(100);

	HAL_UART_Transmit(&huart, "mac set appeui FF00000FF0000001\n\r", 33, 100);
	HAL_Delay(100);

	HAL_UART_Transmit(&huart, "mac set appkey 2964A451A352CA45A620396685591557\n\r", 49, 100);
	HAL_Delay(100);

	HAL_UART_Transmit(&huart, "mac set adr on\n\r", 16, 100);
	HAL_Delay(100);

	HAL_UART_Transmit(&huart, "mac set devaddr F5A00802\n\r", 27, 100);
	HAL_Delay(100);

	HAL_UART_Transmit(&huart, "mac set nwkskey 2964A451A352CA45A620396685591557\n\r", 50, 100);
	HAL_Delay(100);

	HAL_UART_Transmit(&huart, "mac set appskey 2964A451A352CA45A620396685591557\n\r", 50, 100);
	HAL_Delay(100);

	HAL_UART_Transmit(&huart, "mac save\n\r", 10, 100);
	HAL_Delay(5000);

}

void send_rn2483(UART_HandleTypeDef* huart, unsigned int channel, char* payload, unsigned int size){
	/*
	 * unsigned int message2[10] = "Sensor 2: ";
	 * HAL_UART_Transmit(&huart1, message2, 10, 100);
	 */

	for(int i=0; i<5;i++){
		HAL_UART_Transmit(&huart, "mac join otaa\n\r", 15, 100);
		HAL_Delay(10000);
	}

	HAL_UART_Transmit(&huart, "mac tx uncnf 1 54\n\r", 19, 100);
}
