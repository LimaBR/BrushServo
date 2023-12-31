/*
 * INA1X9.hpp
 *
 *  Created on: Dec 22, 2023
 *      Author: Gabriel
 */

#ifndef SRC_COMPONENTS_INA1X9_HPP_
#define SRC_COMPONENTS_INA1X9_HPP_

#include "main.h"

#include "ADC_STM32.hpp"

class INA1X9 {
public:
	INA1X9(ADC_STM32* adc, uint32_t adcRank, float rs, float rl);
	virtual ~INA1X9();
	int32_t init();
	float read();
private:
	ADC_STM32* adc;
	uint32_t adcRank;
	float rs;
	float rl;
};

#endif /* SRC_COMPONENTS_INA1X9_HPP_ */
