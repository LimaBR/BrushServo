/*
 * BrushServo.cpp
 *
 *  Created on: Dec 20, 2022
 *      Author: Gabriel
 */

#include "BrushServo.hpp"

BrushServo::BrushServo(TIM_HandleTypeDef* htim, __IO uint32_t* ina_ccr, __IO uint32_t* inb_ccr, GPIO_TypeDef* inha_gpio_port, uint16_t inha_gpio_pin, GPIO_TypeDef* inhb_gpio_port, uint16_t inhb_gpio_pin)
					: BTS7960B(htim, ina_ccr, inb_ccr, inha_gpio_port, inha_gpio_pin, inhb_gpio_port, inhb_gpio_pin) {

}

void BrushServo::controlCallback(uint32_t adcValue){
	currentPosition = angleFromAdc(adcValue);
	float lastError = error;
	error = currentPosition - desiredPosition;
	ierror = ierror + error*timerPeriod;
	if (ierror > htim->Instance->ARR){
		ierror = htim->Instance->ARR;
	}else if (ierror < -(htim->Instance->ARR)){
		ierror = -htim->Instance->ARR;
	}
	derror = (error - lastError)/timerPeriod;
	float power = kp * error + ki*ierror + kd*derror;
	setPower(-power);
}

void BrushServo::setPositionSpeed(float position, float speed){
	desiredPosition = position;
	desiredSpeed = speed;
}

float BrushServo::getCurrentPosition(){
	return currentPosition;
}

float BrushServo::getCurentSpeed(){
	return 0;
}

float BrushServo::angleFromAdc(uint32_t adcValue){
	return degreesOfRotation*(adcValue - adcMin)/(adcMax - adcMin) - degreesOfRotation/2 + calibrationDegrees;
}