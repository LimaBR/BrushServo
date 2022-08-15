/*
 * Start.cpp
 *
 *  Created on: Aug 14, 2022
 *      Author: Gabriel
 */

#include "Start.hpp"

#include "SerialDebug.hpp"
#include "BTS7960B.hpp"

extern UART_HandleTypeDef huart1;
extern ADC_HandleTypeDef hadc1;
extern TIM_HandleTypeDef htim6;

SerialDebug debug(&huart1);
BTS7960B motor0(&(TIM3->CCR1), &(TIM3->CCR2), GPIOA, GPIO_PIN_4, GPIOA, GPIO_PIN_5);

char adcprintbuf[64];
uint32_t adcresult = 0;

void HAL_UART_TxCpltCallback(UART_HandleTypeDef* huart){
	if(huart == &huart1){
		debug.sendNext();
	}
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc){
	sprintf(adcprintbuf, "ADC: %lu", adcresult);
	debug.debug(adcprintbuf);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim){
	if(htim == &htim6){
		HAL_ADC_Start_DMA(&hadc1, &adcresult, 1);
	}
}

void Start(){
	debug.setLevel(SerialDebug::DEBUG_LEVEL_DEBUG);
	while(true){
		debug.debug("512");
		motor0.setSpeed(1024);
		HAL_Delay(500);
		debug.debug("-512");
		motor0.setSpeed(-1024);
		HAL_Delay(500);
	}
}
