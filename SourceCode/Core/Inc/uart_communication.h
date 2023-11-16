/*
 * uart_communication.h
 *
 *  Created on: Nov 14, 2023
 *      Author: Admin
 */

#ifndef INC_UART_COMMUNICATION_H_
#define INC_UART_COMMUNICATION_H_
#include"global.h"
#include<string.h>
#include<global.h>
#include"main.h"
#include"software_timer.h"
ADC_HandleTypeDef hadc1;

UART_HandleTypeDef huart2;
void uart_communication_fsm();

#endif /* INC_UART_COMMUNICATION_H_ */
