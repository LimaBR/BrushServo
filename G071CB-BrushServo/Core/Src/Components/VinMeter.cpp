/*
 * VinMeter.cpp
 *
 *  Created on: Dec 23, 2023
 *      Author: Gabriel
 */

#include "VinMeter.hpp"

VinMeter::VinMeter(ADC_STM32* adc, uint32_t adcRank, float rh, float rl) : adc(adc), adcRank(adcRank), rh(rh), rl(rl) {

}

VinMeter::~VinMeter() {

}

int32_t VinMeter::init() {
	return 0;
}

float VinMeter::read(){
	float vref = 3.0*(*(uint16_t*)0x1FFF75AA)/adc->getData(0);
	return adc->getData(adcRank)*(rh+rl)*vref/(4096*rl);
}
