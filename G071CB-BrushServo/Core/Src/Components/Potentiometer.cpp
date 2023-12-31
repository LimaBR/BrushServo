/*
 * Potentiometer.cpp
 *
 *  Created on: Dec 28, 2023
 *      Author: Gabriel
 */

#include "Potentiometer.hpp"

Potentiometer::Potentiometer(ADC_STM32* adc, uint32_t adcRank) : adc(adc), adcRank(adcRank) {

}

Potentiometer::~Potentiometer() {

}

int32_t Potentiometer::init() {
	return 0;
}

float Potentiometer::read() {
	return adc->getData(adcRank)/4096.0;
}
