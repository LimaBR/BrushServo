/*
 * ADC.hpp
 *
 *  Created on: Dec 22, 2023
 *      Author: Gabriel
 */

#ifndef SRC_COMPONENTS_ADC_STM32_HPP_
#define SRC_COMPONENTS_ADC_STM32_HPP_

#include "main.h"

class ADC_STM32 {
public:
	ADC_STM32();
	virtual ~ADC_STM32();
	static ADC_STM32* getInstance();
	int32_t init();
	int32_t startScan();
	uint16_t getData(uint32_t rank);
private:
	static void convCpltCallbackStatic(ADC_HandleTypeDef* _hadc);
	void convCpltCallback();
	ADC_HandleTypeDef* hadc;
	uint16_t adcData[16];
};

#endif /* SRC_COMPONENTS_ADC_STM32_HPP_ */
