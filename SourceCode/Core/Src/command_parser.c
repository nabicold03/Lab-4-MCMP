/*
 * command_parser.c
 *
 *  Created on: Nov 14, 2023
 *      Author: Admin
 */

#include "global.h"
#include"command_parser.h"

//function to clear the buffer array
void clearbuffer(){
	memset(buffer,'\0',sizeof(buffer));
	index_buffer=0;
}

//set environment for UART FSM
void StartUartFSM(){
	command_flag=1;
	uart_status=IDLE;
}

void command_parser_fsm(){
	switch(command_parse_status){
		case Parser_Start:
			if(temp!='!'){
				//change state
				if(temp=='#'){	//if user input !!!!!! then # => send data to UART FSM
					StartUartFSM();
				} else {
					command_parse_status=Store_Buffer;	//else change state to start storing data into the buffer
				}
			} else {
				clearbuffer();	//if user input ! => clear this
			}
			break;
		case Store_Buffer:
			if(temp=='!'){		//if user type ! => comeback to Parser_Start above
				clearbuffer();	//clear the buffer before coming back
				command_parse_status=Parser_Start;
			} else if(temp=='#'){		//Now if user type in the hash symbol
				//set flag and copy input to command_data
				memcpy(command_data,buffer,sizeof(buffer));
				clearbuffer();

				//Enter to new line
				void *str="";
				HAL_UART_Transmit(&huart2, (void*) str, sprintf(str, "\n\r"), 50);

				//test
				HAL_GPIO_TogglePin(LED_YELLOW_GPIO_Port, LED_YELLOW_Pin);

				//change state
				StartUartFSM();		//set command_flag to 1 and uart_status to IDLE (1st stage)
				command_parse_status=Parser_Start;
			}
			break;
		default:
			break;
	}
}
