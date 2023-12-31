/*
 * Potentiometer.hpp
 *
 *  Created on: Dec 28, 2023
 *      Author: Gabriel
 */

#ifndef SRC_COMPONENTS_POTENTIOMETER_HPP_
#define SRC_COMPONENTS_POTENTIOMETER_HPP_

#include "main.h"
#include "ADC_STM32.hpp"

class Potentiometer {
public:
	Potentiometer(ADC_STM32* adc, uint32_t adcRank);
	virtual ~Potentiometer();
	int32_t init();
	float read();
private:
	ADC_STM32* adc;
	uint32_t adcRank;
};

#endif /* SRC_COMPONENTS_POTENTIOMETER_HPP_ */
