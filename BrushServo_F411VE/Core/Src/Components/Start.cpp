/*
 * Start.cpp
 *
 *  Created on: Nov 20, 2022
 *      Author: Gabriel
 */

#include "Start.hpp"
#include "SerialDebug.hpp"
#include "BTS7960B.hpp"

extern UART_HandleTypeDef huart2;
extern TIM_HandleTypeDef htim1;

SerialDebug debug(&huart2, 32);
BTS7960B motor(&(TIM1->CCR1), &(TIM1->CCR2), GPIOE, GPIO_PIN_8, GPIOE, GPIO_PIN_10);

void start(){
	debug.setLevel(SerialDebug::DEBUG_LEVEL_DEBUG);
	debug.info("-----Init-----");
	debug.debug("Timer init begin");
	HAL_TIM_Base_Start(&htim1);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
	debug.debug("Timer init end");
	while(true){
		motor.setSpeed(512);
		HAL_Delay(1000);
		motor.setSpeed(-512);
		HAL_Delay(1000);
	}
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart) {
	if(huart == &huart2){
		debug.serialTxCpltCallback();
	}
}
