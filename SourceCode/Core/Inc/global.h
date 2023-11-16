/*
 * global.h
 *
 *  Created on: Nov 14, 2023
 *      Author: Admin
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_
#include<stdio.h>
#include<string.h>
#define MAX_BUFFER_SIZE 	30
#define Parser_Start		1
#define Check_Exclamation	2
#define Store_Buffer		3
#define IDLE				22
#define Check_RST			23
#define Send_ADC			24
#define Check_OK			25
uint8_t command_data[MAX_BUFFER_SIZE];
uint8_t command_flag;
extern uint8_t temp;
extern uint8_t buffer[MAX_BUFFER_SIZE];
extern uint8_t index_buffer;
extern uint8_t buffer_flag;
extern uint8_t str[20];
uint8_t command_parse_status;
uint8_t uart_status;
uint8_t checkok;
uint8_t waitingok;
uint32_t ADC_value;

#endif /* INC_GLOBAL_H_ */
