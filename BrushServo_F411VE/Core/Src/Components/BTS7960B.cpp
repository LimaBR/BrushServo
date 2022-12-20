/*
 * BTS7960B.cpp
 *
 *  Created on: Dec 29, 2021
 *      Author: Gabriel
 */

#include "BTS7960B.hpp"

BTS7960B::BTS7960B(TIM_HandleTypeDef* htim, __IO uint32_t* ina_ccr, __IO uint32_t* inb_ccr, GPIO_TypeDef* inha_gpio_port, uint16_t inha_gpio_pin, GPIO_TypeDef* inhb_gpio_port, uint16_t inhb_gpio_pin)
 : htim(htim), ina(ina_ccr), inb(inb_ccr), inha_port(inha_gpio_port), inha_pin(inha_gpio_pin), inhb_port(inhb_gpio_port), inhb_pin(inhb_gpio_pin){

}

void BTS7960B::setPower(int32_t power){
	if(power > (int32_t)htim->Instance->ARR){
		power = (int32_t)htim->Instance->ARR;
	}else if(power < -(int32_t)htim->Instance->ARR){
		power = -(int32_t)htim->Instance->ARR;
	}
	if(power > 0){
		HAL_GPIO_WritePin(inha_port, inha_pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(inhb_port, inhb_pin, GPIO_PIN_SET);
		*ina = power;
		*inb = 0;
	}else if(power < 0){
		HAL_GPIO_WritePin(inha_port, inha_pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(inhb_port, inhb_pin, GPIO_PIN_SET);
		*ina = 0;
		*inb = -power;
	}else{
		HAL_GPIO_WritePin(inha_port, inha_pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(inhb_port, inhb_pin, GPIO_PIN_RESET);
	}
}
