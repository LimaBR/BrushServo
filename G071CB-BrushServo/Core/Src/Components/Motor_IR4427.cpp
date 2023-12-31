/*
 * Motor_IR4427.cpp
 *
 *  Created on: Dec 24, 2023
 *      Author: Gabriel
 */

#include "Motor_IR4427.hpp"

Motor_IR4427::Motor_IR4427(PWM_Pin_STM32* pwma, PWM_Pin_STM32* pwmb) : pwma(pwma), pwmb(pwmb) {

}

Motor_IR4427::~Motor_IR4427() {

}

int32_t Motor_IR4427::init() {
	pwma->init();
	pwmb->init();
	return 0;
}

void Motor_IR4427::setEnabled(bool enabled) {

}

void Motor_IR4427::setPower(float power) {
	if(power<0){
		pwma->setCycle(0);
		pwmb->setCycle(-power);
	}else{
		pwma->setCycle(power);
		pwmb->setCycle(0);
	}
}
