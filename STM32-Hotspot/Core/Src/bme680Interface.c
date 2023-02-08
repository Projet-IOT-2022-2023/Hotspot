/*
 * bme680Interface.c
 *
 *  Created on: Dec 27, 2022
 *      Author: rpa1labs
 */

#include "bme680Interface.h"

struct bme680_dev gas_sensor;
char i2c_reading_buf[100];
int8_t rslt = BME680_OK;
I2C_HandleTypeDef *hi2cbme;


int8_t bme680I2cRead(uint8_t dev_id, uint8_t reg_addr, uint8_t *reg_data, uint16_t len);
int8_t bme680I2cWrite(uint8_t dev_id, uint8_t reg_addr, uint8_t *reg_data, uint16_t len);

uint8_t bme680_interface_init(I2C_HandleTypeDef *i2c){

	  hi2cbme = i2c;

	  gas_sensor.dev_id = BME680_I2C_ADDR_PRIMARY;
	  gas_sensor.intf = BME680_I2C_INTF;
	  gas_sensor.read = bme680I2cRead;
	  gas_sensor.write = bme680I2cWrite;
	  gas_sensor.delay_ms = HAL_Delay;
	  gas_sensor.amb_temp = 25;

	  // Initialize the driver
	  if (bme680_init(&gas_sensor) != BME680_OK) {
	    return 1;
	  }

	  // Select desired oversampling rates
	  gas_sensor.tph_sett.os_hum = BME680_OS_2X;
	  gas_sensor.tph_sett.os_pres = BME680_OS_4X;
	  gas_sensor.tph_sett.os_temp = BME680_OS_8X;

	  // Set sensor to "always on"
	  gas_sensor.power_mode = BME680_FORCED_MODE;

	  // Set oversampling settings
	  uint8_t required_settings = (BME680_OST_SEL | BME680_OSP_SEL | BME680_OSH_SEL);
	  rslt = bme680_set_sensor_settings(required_settings, &gas_sensor);

	  // Set sensor mode
	  rslt = bme680_set_sensor_mode(&gas_sensor);

	  // Query minimum sampling period
	  uint16_t min_sampling_period;
	  bme680_get_profile_dur(&min_sampling_period, &gas_sensor);

	  return 0;
}

void getTemperatureHumidity(float *temperature, float *humidity){
	// Request the next sample
		  if (gas_sensor.power_mode == BME680_FORCED_MODE) {
		 	    rslt = bme680_set_sensor_mode(&gas_sensor);
		 	  }

	// Sampling results variable
	struct bme680_field_data data;

	rslt = bme680_get_sensor_data(&data, &gas_sensor);

		  // Format results into a human readable string
	for(int i =0 ;i< 100;i++){
		i2c_reading_buf[i] = 0;
	}

	*temperature = data.temperature / 100;
	*humidity = data.humidity / 1000;

}

void printTemperatureHumidity(float temperature, float humidity, UART_HandleTypeDef *huart){
	sprintf(i2c_reading_buf,"T: %u.%u degC, H %u.%u %%rH\r\n",(unsigned int)temperature,(unsigned int)(temperature*100) % 100,(unsigned int)humidity,(unsigned int)(humidity*1000) % 1000);
	// Publish result to connected PC
	HAL_UART_Transmit(huart, (uint8_t*)&i2c_reading_buf, 50, 100);
}

int8_t bme680I2cRead(uint8_t dev_id, uint8_t reg_addr, uint8_t *reg_data, uint16_t len) {
  int8_t result;

  while(HAL_I2C_GetState(hi2cbme) != HAL_I2C_STATE_READY);

  if (HAL_I2C_Master_Transmit(hi2cbme, (dev_id << 1), &reg_addr, 1, HAL_MAX_DELAY) != HAL_OK) {
    result = -1;
    return result;
  }

  while(HAL_I2C_GetState(hi2cbme) != HAL_I2C_STATE_READY);

  if (HAL_I2C_Master_Receive (hi2cbme, (dev_id << 1) | 0x01, reg_data, len, HAL_MAX_DELAY) != HAL_OK) {
    result = -1;
  } else {
    result = 0;
  }

  return result;
}

int8_t bme680I2cWrite(uint8_t dev_id, uint8_t reg_addr, uint8_t *reg_data, uint16_t len) {
  int8_t result;
  int8_t *buf;

  // Allocate and load I2C transmit buffer
  buf = malloc(len + 1);
  buf[0] = reg_addr;
  memcpy(buf + 1, reg_data, len);

  while(HAL_I2C_GetState(hi2cbme) != HAL_I2C_STATE_READY);

  if (HAL_I2C_Master_Transmit(hi2cbme, (dev_id << 1), (uint8_t *) buf, len + 1, HAL_MAX_DELAY) != HAL_OK) {
    result = -1;
  } else {
    result = 0;
  }

  free(buf);
  return result;
}

