#include <stdio.h>
#include "main.h"
#include "stm32f4xx_hal.h"
#include <math.h>

#define MAX_SPEED 70
#define MAX_VAL_EXT 65535
#define MAX_VAL 4294967295
#define COUNTER_PERIOD 200
#define PRESICION 2

extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim7;
extern UART_HandleTypeDef huart2;

float u = 0;
float e = 0;
float e_prev = 0;
float e_sum = 0;

int16_t ext_encoder = 0;
int16_t prev_ext_encoder = 0;
int16_t ext_dir = 0;
int16_t prev_ext_dir = 0;
int16_t prev_prev_ext_dir = 0;

int32_t encoder = 0;
int32_t prev_encoder = 0;
int32_t dir = 0;
int32_t wanted_dir = 0;

uint32_t speed = 0;
uint32_t prev_speed = 0;

uint8_t flag = 1;

float pid(float k1, float k2, float k3, float e, float e_diff) {
	return k1*e + k2*e_sum*0.0001 + k3*e_diff*1000.0f;
}

void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == TIM3) {
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, u/5);
	}
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == TIM7) {

		ext_encoder = __HAL_TIM_GET_COUNTER(&htim4); //extrenal
		ext_dir = __HAL_TIM_IS_TIM_COUNTING_DOWN(&htim4);
		encoder = __HAL_TIM_GET_COUNTER(&htim2);
		dir = __HAL_TIM_IS_TIM_COUNTING_DOWN(&htim2);

//		if((ext_encoder > 10000) && (speed < PRESICION) && (ext_dir != prev_ext_dir)) {
//			wanted_dir = 1;
//		}
//		else if((ext_encoder < 10000) && (speed < PRESICION) && (ext_dir != prev_ext_dir)){
//			wanted_dir = 0;
//		}

//		if(ext_encoder > 10000) {
//			ext_encoder = MAX_VAL_EXT - ext_encoder;
//		}
//		if(MAX_VAL - encoder < 10000) {
//			encoder = MAX_VAL - encoder;
//			(&htim2)->Instance->CR1 = 0;
//		}
		if(ext_encoder < 0)
			wanted_dir = 1;
		else
			wanted_dir = 0;

		if(ext_encoder > 100) {
			__HAL_TIM_SET_COUNTER(&htim4, 100);
			ext_encoder = 100;
		}
		else if(encoder > 100) {
			__HAL_TIM_SET_COUNTER(&htim2, 100);
			encoder = 100;
		}
		else if(ext_encoder < -100) {
			__HAL_TIM_SET_COUNTER(&htim4, -100);
			ext_encoder = -100;
		}
		else if(encoder < -100) {
			__HAL_TIM_SET_COUNTER(&htim2, -100);
			encoder = -100;
		}

		if((encoder < 100)) {
			speed = abs(encoder - prev_encoder);
		} else {
			speed = 9;
		}

		e = (float)ext_encoder - (float)speed;

		if(e < 0)
			e *= -1;

		u = pid(1, 1, 0.008, e, e-e_prev);

		if(u < 0)
			u = 0;
		else if(u > 1000)
			u = 1000;

		if((abs((int32_t) e) < PRESICION) && (prev_ext_encoder == ext_encoder)) {
			e_sum = 0;
			u = 0;
		}

		e_sum += e;
		e_prev = e;
		prev_encoder = encoder;
		prev_ext_encoder = ext_encoder;
		prev_prev_ext_dir = prev_ext_dir;
		prev_ext_dir = ext_dir;

		uint32_t answer[8] = {0xAAAAAAAA, ext_encoder, ext_dir, encoder, dir, abs((int32_t)speed), abs((int32_t) e), abs((int32_t) u)};

		HAL_GPIO_WritePin(DIR1_GPIO_Port, DIR1_Pin, wanted_dir);
		HAL_UART_Transmit(&huart2, answer, 32, 20);
	}
}
