/*
 * debug_comm.c
 *
 *  Created on: Aug 6, 2019
 *      Author: V
 */
#include <string.h>

#include "main.h"
#include "debug_comm.h"

extern UART_HandleTypeDef 	huart1;

uint8_t        			buf[128];
uint32_t	   		cnt = 0;

void log_comm( const char* info) {
	snprintf((char *)buf, sizeof(buf)-1, "%s\n\r", info);
	HAL_UART_Transmit(&huart1, buf, strlen((const char *)buf), 100);
/*	if ( HAL_OK != HAL_UART_Transmit(&huart1, buf, strlen((const char *)buf), 100)) {
		cnt--;
	}
*/
}











