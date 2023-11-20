/*
 * command_parser.c
 *
 *  Created on: Nov 14, 2023
 *      Author: Admin
 */

#include "global.h"
#include"command_parser.h"
void clearbuffer(){
	memset(buffer,'\0',sizeof(buffer));
	index_buffer=0;
}
void StartUartFSM(){
	command_flag=1;
	uart_status=IDLE;
}
void command_parser_fsm(){
//	uint8_t exclamation="!";
//	uint8_t hash="#";
	char exclamation='!';
	char hash='#';
	switch(command_parse_status){
		case Parser_Start:
			if(temp!='!'){
				//change state
				if(temp=='#'){
					StartUartFSM();
				} else {
					command_parse_status=Store_Buffer;
				}
			} else {
				clearbuffer();
			}
			break;
//		case Check_Exclamation:
//			if(temp!='!'){
//				//change state
//				command_parse_status=Store_Buffer;
//			} else if(temp=='#'){
//
//			}
//			break;
		case Store_Buffer:
			if(temp=='!'){
				clearbuffer();
				command_parse_status=Parser_Start;
			} else if(temp=='#'){
				//set flag and copy input to command_data
				HAL_UART_Transmit(&huart2, temp, 1, 1000);
				memcpy(command_data,buffer,sizeof(buffer));
				clearbuffer();
	//			index_buffer=0;
				void *str="";
				HAL_UART_Transmit(&huart2, (void*) str, sprintf(str, "\n\r"), 50);

				//test
				HAL_GPIO_TogglePin(LED_YELLOW_GPIO_Port, LED_YELLOW_Pin);

				//change state
				StartUartFSM();
				command_parse_status=Parser_Start;
			}
			break;
		default:
			break;
	}
}
