/*
 * CAda.h
 *
 *  Created on: 7 déc. 2022
 *      Author: rpa1labs
 */


/**
 * SPI CONFIGURATION FOR THE STM32
 * Mode : Full-Duplex-Master
 * Hardware NSS Signal : disabled
 * Frame Format: Motorola
 * Data size : 8 bits
 * First Bit: MSB First
 * Prescaler : 256
 * Clock phase: 2 Edge
 */

#ifndef INC_CADA_LIB_H_
#define INC_CADA_LIB_H_

#include <main.h>
#include <math.h>

#include <math.h>
#include <stdio.h>
#include <stdint.h>


/**
 * Struct to get all sensor informations ( PIN of Chip Select and SPI port)
 */
typedef struct SPIDevice {
	SPI_HandleTypeDef* hspi; 	// Hardware SPI port
	GPIO_TypeDef* gpio;			// GPIO pool
	uint16_t pin;				// pin inside the pool
} SPIDevice;


/**
 * Functions
 */
double Get_Temperature_math(double);
void cs_reset(SPIDevice dev);
void cs_set(SPIDevice dev);
double Get_Temperature(SPIDevice dev);
int Init_Ada(SPIDevice dev);
uint8_t Ada_Configuration_info(SPIDevice dev);
void displayTemp(UART_HandleTypeDef huart,double temp);

#endif


