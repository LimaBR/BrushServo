/*
 * INA1X9.cpp
 *
 *  Created on: Dec 22, 2023
 *      Author: Gabriel
 */

#include "INA1X9.hpp"

INA1X9::INA1X9(ADC_STM32* adc, uint32_t adcRank, float rs, float rl) : adc(adc), adcRank(adcRank), rs(rs), rl(rl) {

}

INA1X9::~INA1X9() {

}

int32_t INA1X9::init() {
	return 0;
}

float INA1X9::read(){
	// TODO soldar capacitor de 47nF em paralelo com R9
	float vref = 3.0*(*(uint16_t*)0x1FFF75AA)/adc->getData(0);
	return adc->getData(adcRank)*vref*1000/(4096*rs*rl);
}
