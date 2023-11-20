/*
 * uart_communication.c
 *
 *  Created on: Nov 14, 2023
 *      Author: Admin
 */

#include"uart_communication.h"
void uart_communication_fsm(){
	switch(uart_status){
		case IDLE:
			if(command_flag==1){
				if(waitingok==1){
					uart_status=Check_OK;
				} else uart_status=Check_RST;
			}
			break;
		case Check_RST:
//			if(strncmp((const char*)command_data,"!RST#",5)==0){
//			if(command_data=="#RST!"){
			if(memcmp(command_data,"RST#",4)==0){
//				HAL_GPIO_TogglePin(LED_YELLOW_GPIO_Port, LED_YELLOW_Pin);
				uart_status=Send_ADC;
			} else {
				HAL_UART_Transmit(&huart2, command_data, sizeof(command_data), 1000);
				HAL_UART_Transmit(&huart2, "Invalid Request\n\r", 19, 1000);
				uart_status=IDLE;
			}
			command_flag=0;
//			memset(command_data,'\0',MAX_BUFFER_SIZE);
			break;
		case Send_ADC:
			if(waitingok==0){
				ADC_value = HAL_ADC_GetValue(&hadc1);
			}
			HAL_UART_Transmit(&huart2, "!ADC=", 5, 10);
			HAL_UART_Transmit(&huart2, (void*)str, sprintf(str,"%d#\n\r",ADC_value), 1000);
			uart_status=Check_OK;
			waitingok=1;
			setTimer(3000);
			break;
		case Check_OK:
//			HAL_UART_Transmit(&huart2, command_data, MAX_BUFFER_SIZE, 1000);
//			if(strncmp((const char*)command_data,"!OK#",4)==0){
//			if(command_data=="!OK#"){
			if(memcmp(command_data,"OK#",3)==0){
				uart_status=IDLE;
//				checkok=1;
				waitingok=0;
//				HAL_GPIO_TogglePin(LED_YELLOW_GPIO_Port, LED_YELLOW_Pin);
				HAL_UART_Transmit(&huart2, "Everything is done!\n\r", 29, 1000);
			} else {
				if(timer_flag==1){
					memset(buffer,'\0',sizeof(buffer));
					HAL_UART_Transmit(&huart2, command_data, MAX_BUFFER_SIZE, 1000);
					uart_status=Send_ADC;
					checkok=0;
				}
			}
			command_flag=0;
			break;
		default:
			break;
	}
}
