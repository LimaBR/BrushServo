/*
 * Start.cpp
 *
 *  Created on: Nov 20, 2022
 *      Author: Gabriel
 */

#include "Start.hpp"
#include "SerialDebug.hpp"
#include "BrushServo.hpp"

extern UART_HandleTypeDef huart2;
extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim10;
extern ADC_HandleTypeDef hadc1;

SerialDebug debug(&huart2, 32);
BrushServo motor(&htim1, &(TIM1->CCR1), &(TIM1->CCR2), GPIOE, GPIO_PIN_8, GPIOE, GPIO_PIN_10);

uint32_t pData[64];

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	if (htim==&htim10){
		HAL_ADC_Start_DMA(&hadc1, pData, 1);
		motor.controlCallback(*pData);
	}
}

void start(){
	debug.setLevel(SerialDebug::DEBUG_LEVEL_DEBUG);
	debug.info("-----Init-----");
	debug.debug("Timer init begin");
	HAL_TIM_Base_Start(&htim1);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
	HAL_TIM_Base_Start_IT(&htim10);
	debug.debug("Timer init end");
	while(true){
		motor.setPositionSpeed(-60, 0);
		HAL_Delay(10000);
		motor.setPositionSpeed(60, 0);
		HAL_Delay(10000);
	}
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart) {
	if(huart == &huart2){
		debug.serialTxCpltCallback();
	}
}

