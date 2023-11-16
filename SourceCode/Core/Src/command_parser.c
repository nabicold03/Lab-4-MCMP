/*
 * command_parser.c
 *
 *  Created on: Nov 14, 2023
 *      Author: Admin
 */

#include "global.h"
#include"command_parser.h"
void copy(){
	for(int i=0; i<sizeof(buffer); i++){
		command_data[i]=buffer[i];
	}
}
void command_parser_fsm(){
//	uint8_t exclamation="!";
//	uint8_t hash="#";
	char exclamation='!';
	char hash='#';
	switch(command_parse_status){
		case Parser_Start:
			if(memcmp(temp,exclamation,1)==0){
				//change state
//				HAL_UART_Transmit(&huart2, &temp, 1, 50);
				HAL_GPIO_TogglePin(LED_YELLOW_GPIO_Port, LED_YELLOW_Pin);
				command_parse_status=Check_Exclamation;
			}
			break;
		case Check_Exclamation:
			if(memcmp(temp,exclamation,1)!=0){
				//change state
//				HAL_UART_Transmit(&huart2, &temp, 1, 50);
				HAL_GPIO_TogglePin(LED_YELLOW_GPIO_Port, LED_YELLOW_Pin);
				command_parse_status=Store_Buffer;
			}
			break;
		case Store_Buffer:
			if(memcmp(temp,hash,1)==0){
				//set flag and copy input to command_data
				command_flag=1;
				memcpy(command_data,buffer,sizeof(buffer));
//				HAL_UART_Transmit(&huart2, command_data, sizeof(command_data), 1000);
//				HAL_UART_Transmit(&huart2, buffer, sizeof(buffer), 1000);
				memset(buffer,'\0',sizeof(buffer));
				index_buffer=0;
				void *str="";
				HAL_UART_Transmit(&huart2, (void*) str, sprintf(str, "\n\r"), 50);

				//test
//				HAL_GPIO_TogglePin(LED_YELLOW_GPIO_Port, LED_YELLOW_Pin);

				//change state
				uart_status=IDLE;
				command_parse_status=Parser_Start;
			}
			break;
		default:
			break;
	}
}
