/*
 * Start.cpp
 *
 *  Created on: Nov 20, 2022
 *      Author: Gabriel
 */

#include "Start.hpp"
#include "StaticFIFO.hpp"
#include "SerialDebug.hpp"

extern UART_HandleTypeDef huart2;

SerialDebug debug(&huart2, 32);

void start(){
	debug.setLevel(SerialDebug::DEBUG_LEVEL_DEBUG);
	while(true){
		debug.debug("Hello World");
		debug.debug("Hello World2");
		debug.debug("Hello World3");
		HAL_Delay(1000);
	}
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart) {
	if(huart == &huart2){
		debug.serialTxCpltCallback();
	}
}
