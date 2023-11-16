/*
 * global.c
 *
 *  Created on: Nov 14, 2023
 *      Author: Admin
 */

#include"global.h"
uint8_t temp;
uint8_t buffer[MAX_BUFFER_SIZE];
uint8_t index_buffer=0;
uint8_t buffer_flag=0;
uint8_t command_parse_status=Parser_Start;
uint8_t command_data[MAX_BUFFER_SIZE];
uint8_t command_flag=0;
uint8_t checkok=1;
uint32_t ADC_value;
uint8_t str[20]="";
uint8_t waitingok=0;
