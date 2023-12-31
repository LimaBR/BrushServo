/*
 * PWM_Pin_STM32.hpp
 *
 *  Created on: Dec 24, 2023
 *      Author: Gabriel
 */

#ifndef SRC_COMPONENTS_PWM_PIN_STM32_HPP_
#define SRC_COMPONENTS_PWM_PIN_STM32_HPP_

#include "main.h"

class PWM_Pin_STM32 {
public:
	PWM_Pin_STM32(TIM_HandleTypeDef* htim, uint32_t channel, bool enableComplimentary);
	virtual ~PWM_Pin_STM32();
	int32_t init();
	void setCycle(float cycle);
private:
	TIM_HandleTypeDef* htim;
	uint32_t channel;
	bool enableComplimentary;
};

#endif /* SRC_COMPONENTS_PWM_PIN_STM32_HPP_ */
