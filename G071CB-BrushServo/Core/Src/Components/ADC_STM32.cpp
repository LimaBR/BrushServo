/*
 * ADC.cpp
 *
 *  Created on: Dec 22, 2023
 *      Author: Gabriel
 */

#include "ADC_STM32.hpp"

extern ADC_HandleTypeDef hadc1;

ADC_STM32 adcSingleton;

ADC_STM32::ADC_STM32() {
	hadc = &hadc1;
}

ADC_STM32::~ADC_STM32() {

}

ADC_STM32* ADC_STM32::getInstance() {
	return &adcSingleton;
}

int32_t ADC_STM32::init(){
	hadc->ConvCpltCallback = convCpltCallbackStatic;
	return 0;
}

int32_t ADC_STM32::startScan() {
	return HAL_ADC_Start_DMA(hadc, (uint32_t*)adcData, hadc->Init.NbrOfConversion);
}

uint16_t ADC_STM32::getData(uint32_t rank) {
	// TODO Verificar estado do DMA e retornar erro se a conversão não estiver finalizada
	return adcData[rank];
}

void ADC_STM32::convCpltCallbackStatic(ADC_HandleTypeDef *_hadc) {
	adcSingleton.convCpltCallback();
}

void ADC_STM32::convCpltCallback() {

}
