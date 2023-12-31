/*
 * BrushServo.hpp
 *
 *  Created on: Dec 24, 2023
 *      Author: Gabriel
 */

#ifndef SRC_COMPONENTS_BRUSHSERVO_HPP_
#define SRC_COMPONENTS_BRUSHSERVO_HPP_

#include "main.h"
#include "INA1X9.hpp"
#include "VinMeter.hpp"
#include "Potentiometer.hpp"
#include "Motor_IR4427.hpp"

#define UART_BUFFER_SIZE 256

class BrushServo {
public:
	static BrushServo* getInstance();
	int32_t init();
	void controlCallback();
private:
	BrushServo();
	virtual ~BrushServo();
	static void UartTxCpltCallbackStatic(UART_HandleTypeDef* _huart);
	void UartTxCpltCallback();
	static void UartRxCpltCallbackStatic(UART_HandleTypeDef* _huart);
	void UartRxCpltCallback();
	static void UartRxEventCallbackStatic(UART_HandleTypeDef* _huart, uint16_t _Pos);
	static void UartErrorCallbackStatic(UART_HandleTypeDef* _huart);
	void initUart();
	void initControl();
	void initRam();
	void instructionWrite();
	TIM_HandleTypeDef* hControlTimer;
	UART_HandleTypeDef* huart;
	uint8_t uartBuffer[UART_BUFFER_SIZE];
	uint8_t ramArea[662];
	float error;
	float derror;
	float ierror;
	float deltaT;
};

#endif /* SRC_COMPONENTS_BRUSHSERVO_HPP_ */
