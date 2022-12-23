/*
 * BrushServo.hpp
 *
 *  Created on: Dec 20, 2022
 *      Author: Gabriel
 */

#ifndef SRC_COMPONENTS_BRUSHSERVO_HPP_
#define SRC_COMPONENTS_BRUSHSERVO_HPP_

#include "main.h"
#include "BTS7960B.hpp"

class BrushServo : private BTS7960B {
public:
	BrushServo(TIM_HandleTypeDef* htim, __IO uint32_t* ina_ccr, __IO uint32_t* inb_ccr, GPIO_TypeDef* inha_gpio_port, uint16_t inha_gpio_pin, GPIO_TypeDef* inhb_gpio_port, uint16_t inhb_gpio_pin);
	// Public methods
	void controlCallback(uint32_t adcValue);
	void setPositionSpeed(float position, float speed);
	float getCurrentPosition();
	float getCurentSpeed();
	// Public attributes
private:
	// Private methods
	float angleFromAdc(uint32_t adcValue);
	// Private attributes
	float desiredPosition = 0;
	float desiredSpeed = 0;
	float currentPosition;
	const float degreesOfRotation = 200;
	const float calibrationDegrees = 0;
	const uint32_t adcMin = 100;
	const uint32_t adcMax = 3995;
	const float kp = 50;
	const float ki = 1;
	const float kd = 0.5;
	const float timerPeriod = 1.0/1000;	//Colocar dependendo do timer
	float error = 0;
	float ierror = 0;
	float derror = 0;
};

#endif /* SRC_COMPONENTS_BRUSHSERVO_HPP_ */
