/*
 * VinMeter.hpp
 *
 *  Created on: Dec 23, 2023
 *      Author: Gabriel
 */

#ifndef SRC_COMPONENTS_VINMETER_HPP_
#define SRC_COMPONENTS_VINMETER_HPP_

#include "main.h"

#include "ADC_STM32.hpp"

class VinMeter {
public:
	VinMeter(ADC_STM32* adc, uint32_t adcRank, float rh, float rl);
	virtual ~VinMeter();
	int32_t init();
	float read();
private:
	ADC_STM32* adc;
	uint32_t adcRank;
	float rh;
	float rl;
};

#endif /* SRC_COMPONENTS_VINMETER_HPP_ */
