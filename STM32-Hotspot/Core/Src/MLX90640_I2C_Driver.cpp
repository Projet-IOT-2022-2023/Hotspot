/**
 * @copyright (C) 2017 Melexis N.V.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */
#include <stdio.h>
//#include "i2c.h"
#include "MLX90640_I2C_Driver.h"


I2C_HandleTypeDef *hi2cmlx;


void MLX90640_I2CInit(I2C_HandleTypeDef *i2c)
{   
	hi2cmlx = i2c;
}


int MLX90640_I2CRead(uint8_t slaveAddr, uint16_t startAddress, uint16_t nMemAddressRead, uint16_t *data)
{

	uint8_t* bp = (uint8_t*) data;

    int ack = 0;                               
    int cnt = 0;
    
    while(HAL_I2C_GetState(hi2cmlx) != HAL_I2C_STATE_READY);

    ack = HAL_I2C_Mem_Read(hi2cmlx, (slaveAddr<<1), startAddress, I2C_MEMADD_SIZE_16BIT, bp, nMemAddressRead*2, 500);

    if (ack != HAL_OK)
    {
        return -1;
    }
    
    for(cnt=0; cnt < nMemAddressRead*2; cnt+=2) {
    	uint8_t tmpbytelsb = bp[cnt+1];
    	bp[cnt+1] = bp[cnt];
    	bp[cnt] = tmpbytelsb;
    }


    
    return 0;   
} 

int MLX90640_I2CWrite(uint8_t slaveAddr, uint16_t writeAddress, uint16_t data)
{

    uint8_t sa;
    int ack = 0;
    uint8_t cmd[2];
    static uint16_t dataCheck;

    sa = (slaveAddr << 1);

    cmd[0] = data >> 8;
    cmd[1] = data & 0x00FF;

    while(HAL_I2C_GetState(hi2cmlx) != HAL_I2C_STATE_READY);

    ack = HAL_I2C_Mem_Write(hi2cmlx, sa, writeAddress, I2C_MEMADD_SIZE_16BIT, cmd, sizeof(cmd), 500);

    if (ack != HAL_OK)
    {
        return -1;
    }         
    
    MLX90640_I2CRead(slaveAddr,writeAddress,1, &dataCheck);
    
    if ( dataCheck != data)
    {
        return -2;
    }    
    
    return 0;
}

