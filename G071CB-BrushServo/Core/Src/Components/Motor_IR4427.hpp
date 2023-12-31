/*
 * Motor_IR4427.hpp
 *
 *  Created on: Dec 24, 2023
 *      Author: Gabriel
 */

#ifndef SRC_COMPONENTS_MOTOR_IR4427_HPP_
#define SRC_COMPONENTS_MOTOR_IR4427_HPP_

#include "main.h"
#include "PWM_Pin_STM32.hpp"

class Motor_IR4427 {
public:
	Motor_IR4427(PWM_Pin_STM32* pwma, PWM_Pin_STM32* pwmb);
	virtual ~Motor_IR4427();
	int32_t init();
	void setEnabled(bool enabled);
	void setPower(float power);
private:
	PWM_Pin_STM32* pwma;
	PWM_Pin_STM32* pwmb;
};

#endif /* SRC_COMPONENTS_MOTOR_IR4427_HPP_ */
