/*
 * start.cpp
 *
 *  Created on: Dec 22, 2023
 *      Author: Gabriel
 */

#include "main.h"
#include "start.h"
#include "ADC_STM32.hpp"
#include "BrushServo.hpp"

extern TIM_HandleTypeDef htim6;

void controlTimer(TIM_HandleTypeDef* htim){
	uint32_t t0 = TIM2->CNT;
	BrushServo::getInstance()->controlCallback();
	ADC_STM32::getInstance()->startScan();
	uint32_t t1 = TIM2->CNT;
	uint32_t delta = t1 - t0;
}

void start(){
	htim6.PeriodElapsedCallback = controlTimer;
	ADC_STM32::getInstance()->init();
	ADC_STM32::getInstance()->startScan();
	BrushServo::getInstance()->init();
	HAL_TIM_Base_Start_IT(&htim6);
}
