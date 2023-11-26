/*
 * uart_communication.c
 *
 *  Created on: Nov 14, 2023
 *      Author: Admin
 */

#include"uart_communication.h"
int compareRST(){
	if(command_data[0]!='R' || command_data[1]!='S' || command_data[2]!='T' || command_data[3]!='#'){
		return 0;
	}
	return 1;
}
int compareOK(){
	if(command_data[0]!='O' || command_data[1]!='K' || command_data[2]!='#'){
		return 0;
	}
	return 1;
}
void uart_communication_fsm(){
	switch(uart_status){
		case IDLE:
			if(command_flag==1){		//if command_flag is set => new data comes
				if(waitingok==1){		//if the uart is waiting for "OK" message => jump to Check_OK stage
					uart_status=Check_OK;
				} else uart_status=Check_RST;	//if not waiting for ok => change to check_RST
			}
			break;
		case Check_RST:
//			if(memcmp(command_data,"RST#",4)==0){	//in case I can use supported function
			if(compareRST()==1){
				uart_status=Send_ADC;	//if rst is matched => change to Send_ADC stage
			} else {
				HAL_UART_Transmit(&huart2, "Invalid Request\n\r", 19, 1000);	//if not matched => print invalid request
				uart_status=IDLE;	//comeback to stage IDLE
			}
			command_flag=0;
			break;
		case Send_ADC:
			if(waitingok==0){	//if not waiting for ok => get new value
				ADC_value = HAL_ADC_GetValue(&hadc1);
			}
			HAL_UART_Transmit(&huart2, "!ADC=", 5, 10);
			HAL_UART_Transmit(&huart2, (void*)str, sprintf(str,"%d#\n\r",ADC_value), 1000);

			//change to next stage with setting waitingok to 1
			uart_status=Check_OK;
			waitingok=1;
			setTimer(3000);	//setTimer 3s for resending ADC value
			break;
		case Check_OK:
//			if(memcmp(command_data,"OK#",3)==0){	//in case I can use supported function
			if(compareOK()==1){	//if matching OK => Print done and comeback to IDLE stage
				uart_status=IDLE;
				waitingok=0;	//here reset waitingok to 0
				HAL_UART_Transmit(&huart2, "Everything is done!\n\r", 29, 1000);
			} else {
				if(timer_flag==1){	//in case user not input OK => wait for timer and then comeback to Send_ADC stage to resend value
					memset(buffer,'\0',sizeof(buffer));
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
