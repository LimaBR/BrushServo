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

SerialDebug debug(&huart1);
BTS7960B motor0(&(TIM3->CCR1), &(TIM3->CCR2), GPIOA, GPIO_PIN_4, GPIOA, GPIO_PIN_5);

char adcprintbuf[64];
uint32_t adcresult = 0;

void HAL_UART_TxCpltCallback(UART_HandleTypeDef* huart){
	debug.sendNext();
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc){
	sprintf(adcprintbuf, "ADC: %lu", adcresult);
	debug.debug(adcprintbuf);
}

void Start(){
	debug.setLevel(SerialDebug::DEBUG_LEVEL_DEBUG);
	while(true){
		HAL_ADC_Start_DMA(&hadc1, &adcresult, 1);
		HAL_Delay(2);
		debug.debug("512");
		motor0.setSpeed(512);
		HAL_Delay(500);
		debug.debug("-512");
		motor0.setSpeed(-512);
		HAL_Delay(500);
	}
}
