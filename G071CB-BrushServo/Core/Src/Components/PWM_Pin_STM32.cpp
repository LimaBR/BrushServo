/*
 * PWM_Pin_STM32.cpp
 *
 *  Created on: Dec 24, 2023
 *      Author: Gabriel
 */

#include "PWM_Pin_STM32.hpp"

PWM_Pin_STM32::PWM_Pin_STM32(TIM_HandleTypeDef *htim, uint32_t channel, bool enableComplimentary) :
		htim(htim), channel(channel), enableComplimentary(enableComplimentary) {
}

PWM_Pin_STM32::~PWM_Pin_STM32() {

}

int32_t PWM_Pin_STM32::init() {
	if(!IS_TIM_INSTANCE(htim->Instance)){
		// Timer doesn't exist
		return -1;
	}
	if (!IS_TIM_CCX_INSTANCE(htim->Instance, channel)) {
		// Channel doesn't exist
		return -1;
	}
	if (enableComplimentary && !IS_TIM_CCXN_INSTANCE(htim->Instance, channel)) {
		// Channel doesn't have a complimentary output
		return -1;
	}
	HAL_TIM_Base_Start(htim);
	HAL_TIM_PWM_Start(htim, channel);
	if (enableComplimentary) {
		HAL_TIMEx_PWMN_Start(htim, channel);
	}
	return 0;
}

void PWM_Pin_STM32::setCycle(float cycle) {
	uint32_t ccrValue = cycle * htim->Instance->ARR;
	switch (channel) {
	case TIM_CHANNEL_1:
		htim->Instance->CCR1 = ccrValue;
		break;
	case TIM_CHANNEL_2:
		htim->Instance->CCR2 = ccrValue;
		break;
	case TIM_CHANNEL_3:
		htim->Instance->CCR3 = ccrValue;
		break;
	case TIM_CHANNEL_4:
		htim->Instance->CCR4 = ccrValue;
		break;
	case TIM_CHANNEL_5:
		htim->Instance->CCR5 = ccrValue;
		break;
	case TIM_CHANNEL_6:
		htim->Instance->CCR6 = ccrValue;
		break;
	}
}
