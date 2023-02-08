/*
 * rn2483.h
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

/*
RN2483 1.0.1 Dec 15 2015 09:38:09
ok
ok
ok
ok
ok
ok
ok
ok
ok
ok
ok
ok
denied
ok
accepted
ok
mac_tx_ok
invalid_param
invalid_param
ok
mac_tx_ok
ok
mac_tx_ok
ok
mac_tx_ok
ok
mac_tx_ok
ok
mac_tx_ok
ok
mac_tx_ok
ok
mac_tx_ok
ok
mac_tx_ok
ok
mac_tx_ok
ok
mac_tx_ok
ok
mac_tx_ok
ok
mac_tx_ok
ok
mac_tx_ok
ok
mac_tx_ok
ok
mac_tx_ok
invalid_param
invalid_param
ok
mac_tx_ok
ok
mac_tx_ok
invalid_param
ok
mac_err
ok
mac_err
ok
mac_err
ok
busy
mac_tx_ok
ok
mac_tx_ok
ok
busy
mac_err
ok
mac_err
RN2483 1.0.1 Dec 15 2015 09:38:09
invalid_param
ok
denied
ok
denied
ok
denied
no_free_ch
no_free_ch
no_free_ch
no_free_ch
no_free_ch
no_free_ch
no_free_ch
no_free_ch
no_free_ch
no_free_ch
no_free_ch
no_free_ch
RN2483 1.0.1 Dec 15 2015 09:38:09
ok
accepted
ok
busy
mac_err
ok
mac_err
ok
mac_err
ok
mac_err
ok
busy
mac_err
ok
mac_err
ok
mac_err
ok
mac_err

 */

#ifndef INC_RN2483_H_
#define INC_RN2483_H_

#define DEV_ADDR "F5A00802"
#define DEV_EUI  "0004A30B001A661B"
#define APP_EUI  "FF00000FF0000001"
#define APP_KEY  "2964A451A352CA45A620396685591557"
#define NWKS_KEY "2964A451A352CA45A620396685591557"
#define APPS_KEY "2964A451A352CA45A620396685591557"

#include "main.h"

void init_rn2483(UART_HandleTypeDef* huart);

void send_rn2483(UART_HandleTypeDef* huart, unsigned int channel, char* payload, unsigned int size);

#endif /* INC_RN2483_H_ */
