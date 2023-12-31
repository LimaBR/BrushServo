/*
 * BrushServo.cpp
 *
 *  Created on: Dec 24, 2023
 *      Author: Gabriel
 */

#include "BrushServo.hpp"

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim6;
extern UART_HandleTypeDef hlpuart1;

INA1X9 ina(ADC_STM32::getInstance(), 3, 0.005, 100000);
VinMeter vin(ADC_STM32::getInstance(), 2, 2200, 1000);
Potentiometer potentiometer(ADC_STM32::getInstance(), 1);

PWM_Pin_STM32 pwma(&htim1, TIM_CHANNEL_1, true);
PWM_Pin_STM32 pwmb(&htim1, TIM_CHANNEL_2, true);
Motor_IR4427 motor(&pwma, &pwmb);

BrushServo::BrushServo() {
	huart = &hlpuart1;
	hControlTimer = &htim6;
}

BrushServo::~BrushServo() {

}

BrushServo* BrushServo::getInstance(){
	static BrushServo brushServoSingleton;
	return &brushServoSingleton;
}

int32_t BrushServo::init() {
	initRam();
	motor.init();
	ina.init();
	vin.init();
	potentiometer.init();
	initControl();
	initUart();
	return 0;
}

void BrushServo::controlCallback() {
	if(!ramArea[64]){
		// Disabled
		motor.setPower(0);
		return;
	}
	float currentPosition = potentiometer.read();
	float goalPosition = (*(uint32_t*)&ramArea[116])/4096.0;
	float desiredPosition = goalPosition;	// TODO implementar profile com velocidade
	float kp = (*(uint16_t*)&ramArea[84])/128.0;
	float ki = (*(uint16_t*)&ramArea[82])/65536.0;
	float kd = (*(uint16_t*)&ramArea[80])/16.0;

	float lastError = error;
	error = desiredPosition - currentPosition;
	derror = (error-lastError)/deltaT;
	ierror += error*deltaT;
	if(ki*ierror > 1){		// Anti-windup (verificar possibilidades)
		ierror = 1/ki;
	}else if(ki*ierror < -1){
		ierror = -1/ki;
	}
	float pid = kp*error + ki*ierror + kd*derror;
	if(pid > 1){		// Clamp
		pid = 1;
	}else if(pid < -1){
		pid = -1;
	}
	motor.setPower(pid);
}

void BrushServo::UartTxCpltCallbackStatic(UART_HandleTypeDef *_huart) {
	getInstance()->UartTxCpltCallback();
}

void BrushServo::UartRxCpltCallbackStatic(UART_HandleTypeDef *_huart) {

}

void BrushServo::UartRxEventCallbackStatic(UART_HandleTypeDef *_huart, uint16_t _Pos) {
	getInstance()->UartRxCpltCallback();
	HAL_HalfDuplex_EnableReceiver(getInstance()->huart);
	HAL_StatusTypeDef status = HAL_UARTEx_ReceiveToIdle_DMA(getInstance()->huart, getInstance()->uartBuffer, UART_BUFFER_SIZE);
	if(status != HAL_OK){
		__NOP();
	}
}

void BrushServo::UartErrorCallbackStatic(UART_HandleTypeDef *_huart) {
	HAL_StatusTypeDef status = HAL_UARTEx_ReceiveToIdle_DMA(getInstance()->huart, getInstance()->uartBuffer, UART_BUFFER_SIZE);
}

void BrushServo::UartTxCpltCallback() {

}

void BrushServo::UartRxCpltCallback() {
	if(uartBuffer[0] != 0xFF || uartBuffer[1] != 0xFF){
		// Invalid header
		return;
	}
	if(uartBuffer[2] != ramArea[7]){
		// Not for this ID
		return;
	}
	uint32_t length = uartBuffer[3];
	if(length == 0){
		// Zero length
		return;
	}
	uint8_t calculatedChecksum = 0;
	for(uint32_t i = 2; i < length+3; i++){
		calculatedChecksum += uartBuffer[i];
	}
	calculatedChecksum = ~(calculatedChecksum);
	if(calculatedChecksum != uartBuffer[length+3]){
		// Checksum mismatch
		return;
	}
	switch(uartBuffer[4]){
	case 0x01:
		// Ping
		break;
	case 0x02:
		// Read
		break;
	case 0x03:
		// Write
		instructionWrite();
		break;
	case 0x04:
		// Reg write
		break;
	case 0x05:
		// Action
		break;
	case 0x06:
		// Factory reset
		break;
	case 0x08:
		// Reboot
		break;
	case 0x83:
		// Sync write
		break;
	case 0x92:
		// Bulk read
		break;
	default:
		break;
	}
}

void BrushServo::initUart() {
	huart->TxCpltCallback = UartTxCpltCallbackStatic;
	huart->RxCpltCallback = UartRxCpltCallbackStatic;
	huart->RxEventCallback = UartRxEventCallbackStatic;
	huart->ErrorCallback = UartErrorCallbackStatic;
	HAL_HalfDuplex_EnableReceiver(huart);
	// FIXME Verificar se tem forma melhor de detectar fim do pacote (usar header?)
	HAL_UARTEx_ReceiveToIdle_DMA(huart, uartBuffer, UART_BUFFER_SIZE);
}

void BrushServo::initControl() {
	deltaT = (hControlTimer->Instance->ARR + 1) * (hControlTimer->Instance->PSC + 1)/(float)HAL_RCC_GetPCLK1Freq();
}

void BrushServo::initRam() {
	// Model Number
	ramArea[0] = 30;
	// Model Information
	// Cortex M0 doesn't support unaligned access
	*(uint16_t*)&ramArea[2] = 0;
	*(uint16_t*)&ramArea[4] = 0;
	// Firmware Version
	ramArea[6] = 1;
	// ID
	ramArea[7] = 1;
	// Baud Rate
	ramArea[8] = 1;
	// Return Delay Time
	ramArea[9] = 250;
	// Drive mode
	ramArea[10] = 0;
	// Operating mode
	ramArea[11] = 3;
	// Secondary(Shadow) ID
	ramArea[12] = 255;
	// Protocol Type
	ramArea[13] = 2;
	// Homing Offset
	*(uint32_t*)&ramArea[20] = 0;
	// Moving Threshold
	*(uint32_t*)&ramArea[24] = 10;
	// Temperature Limit
	ramArea[31] = 80;
	// Max Voltage Limit
	*(uint16_t*)&ramArea[32] = 160;
	// Min Voltage Limit
	*(uint16_t*)&ramArea[34] = 95;
	// PWM Limit
	*(uint16_t*)&ramArea[36] = 885;
	// Acceleration Limit
	*(uint32_t*)&ramArea[40] = 32767;
	// Velocity Limit
	*(uint32_t*)&ramArea[44] = 230;
	// Max Position Limit
	*(uint32_t*)&ramArea[48] = 4095;
	// Min Position Limit
	*(uint32_t*)&ramArea[52] = 0;
	// Shutdown
	ramArea[63] = 52;

	// Torque Enable
	ramArea[64] = 0;
	// LED
	ramArea[65] = 0;
	// Status Return Level
	ramArea[68] = 2;
	// Registered Instruction
	ramArea[69] = 0;
	// Hardware Error Status
	ramArea[70] = 0;
	// Velocity I Gain
	*(uint16_t*)&ramArea[76] = 1920;
	// Velocity P Gain
	*(uint16_t*)&ramArea[78] = 100;
	// Position D Gain
	*(uint16_t*)&ramArea[80] = 0;
	// Position I Gain
	*(uint16_t*)&ramArea[82] = 0;
	// Position P Gain
	*(uint16_t*)&ramArea[84] = 850;
	// Feedforward 2nd Gain
	*(uint16_t*)&ramArea[88] = 0;
	// Feedforward 1st Gain
	*(uint16_t*)&ramArea[90] = 0;
	// BUS Watchdog
	ramArea[98] = 0;
	// Goal PWM
	*(uint16_t*)&ramArea[100] = 0;
	// Goal Velocity
	*(uint32_t*)&ramArea[104] = 0;
	// Profile Acceleration
	*(uint32_t*)&ramArea[108] = 0;
	// Profile Velocity
	*(uint32_t*)&ramArea[112] = 0;
	// Goal Position
	*(uint32_t*)&ramArea[116] = 2048;
	// Realtime Tick
	*(uint16_t*)&ramArea[120] = 0;
	// Moving
	ramArea[122] = 0;
	// Moving Status
	ramArea[123] = 0;
	// Present PWM
	*(uint16_t*)&ramArea[124] = 0;
	// Present Load
	*(uint16_t*)&ramArea[126] = 0;
	// Present Velocity
	*(uint32_t*)&ramArea[128] = 0;
	// Present Position
	*(uint32_t*)&ramArea[132] = 0;
	// Velocity Trajectory
	*(uint32_t*)&ramArea[136] = 0;
	// Position Trajectory
	*(uint32_t*)&ramArea[140] = 0;
	// Present Input Voltage
	*(uint16_t*)&ramArea[144] = 0;
	// Present Temperature
	ramArea[146] = 0;
}

void BrushServo::instructionWrite() {
	uint32_t numberOfBytes = uartBuffer[3] - 3;
	uint32_t startingAddress = uartBuffer[5];
	for(uint32_t i = 0; i<numberOfBytes; i++){
		ramArea[i + startingAddress] = uartBuffer[i + 6];
	}
}
