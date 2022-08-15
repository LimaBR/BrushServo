/*
 * UARTDebug.cpp
 *
 *  Created on: Feb 28, 2022
 *      Author: Gabriel
 */

#include "SerialDebug.hpp"

SerialDebug::SerialDebug(UART_HandleTypeDef* huartptr)
: huartptr(huartptr)
{
	fifo = new StaticFIFO(8);
}

SerialDebug::~SerialDebug(){
	delete fifo;
}

void SerialDebug::sendNext(){
	uint8_t numChars;
	if(fifo->pop(&uartSendBuf, &numChars, 64)){
		HAL_UART_Transmit_DMA(huartptr, uartSendBuf, (uint16_t)numChars);
	}else{
		transmitting = false;
	}
}

void SerialDebug::setLevel(uint32_t level)
{
	debugLevel = level;
}

void SerialDebug::debug(const char* data){
	if (debugLevel <= DEBUG_LEVEL_DEBUG){
		int numChars;
		//while (huartptr->gState != HAL_UART_STATE_READY);	//Trava se estiver ocupado durante um interrupt que manda debug
		numChars = sprintf((char*)uartBuf, "[%13lu] DBG: %.42s\r\n", HAL_GetTick(), data);
		if(numChars > 0){
			//HAL_UART_Transmit_DMA(huartptr, uartBuf, (uint16_t)numChars);
			fifo->push(uartBuf, numChars);
			if(!transmitting){
				transmitting = true;
				sendNext();
			}
		}
	}
}

void SerialDebug::info(const char* data){
	if (debugLevel <= DEBUG_LEVEL_INFO){
		int numChars;
		//while (huartptr->gState != HAL_UART_STATE_READY);
		numChars = sprintf((char*)uartBuf, "[%13lu] INF: %.40s\r\n", HAL_GetTick(), data);
		if(numChars > 0){
			//HAL_UART_Transmit_DMA(huartptr, uartBuf, (uint16_t)numChars);
			fifo->push(uartBuf, numChars);
			if(!transmitting){
				transmitting = true;
				sendNext();
			}
		}
	}
}

void SerialDebug::warn(const char* data){
	if (debugLevel <= DEBUG_LEVEL_WARN){
		int numChars;
		//while (huartptr->gState != HAL_UART_STATE_READY);
		numChars = sprintf((char*)uartBuf, "[%13lu] WRN: %.42s\r\n", HAL_GetTick(), data);
		if(numChars > 0){
			//HAL_UART_Transmit_DMA(huartptr, uartBuf, (uint16_t)numChars);
			fifo->push(uartBuf, numChars);
			if(!transmitting){
				transmitting = true;
				sendNext();
			}
		}
	}
}

void SerialDebug::error(const char* data){
	if (debugLevel <= DEBUG_LEVEL_ERROR){
		int numChars;
		//while (huartptr->gState != HAL_UART_STATE_READY);
		numChars = sprintf((char*)uartBuf, "[%13lu] ERR: %.42s\r\n", HAL_GetTick(), data);
		if(numChars > 0){
			//HAL_UART_Transmit_DMA(huartptr, uartBuf, (uint16_t)numChars);
			fifo->push(uartBuf, numChars);
			if(!transmitting){
				transmitting = true;
				sendNext();
			}
		}
	}
}
