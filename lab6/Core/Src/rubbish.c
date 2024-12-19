//
//
////		if(abs(ext_encoder - prev_ext_encoder) > 10000) {
////			ext_encoder = abs(ext_encoder - 65535);
////			prev_ext_encoder = abs(prev_ext_encoder - 65535);
////		}
////
////		if(ext_dir == 0) {
////			ext_encoder = 2*prev_ext_encoder - ext_encoder;
////		} else {
////			ext_encoder = prev_ext_encoder + ext_encoder;
////		}
//
//		if (ext_encoder > MAX_SPEED)
//		{
//			ext_encoder = MAX_SPEED;
//			__HAL_TIM_SET_COUNTER(&htim4, MAX_SPEED);
//		}
//		else if (ext_encoder < -MAX_SPEED)
//		{
//			ext_encoder = -MAX_SPEED;
//			__HAL_TIM_SET_COUNTER(&htim4, -MAX_SPEED);
//		}
//
//		speed = encoder - prev_encoder;
//		e = ext_encoder - speed;
//
//		u = pid(1, 1, 0.4, e, speed-prev_speed);
//
////		if(u > MAX_VAL)
////			u = MAX_VAL;
////		else if(u < -MAX_VAL)
////			u = -MAX_VAL;
//
//		e_sum += e;
//		e_prev = e;
//
//		if(u > 0)
//			wanted_dir = 0;
//		else
//			wanted_dir = 1;
//
//		prev_encoder = encoder;
//		prev_ext_encoder = ext_encoder;
//		prev_speed = speed;
//
////		if((abs(e) < PRESICION) && (ext_encoder - prev_ext_encoder) == 0) {
////			e = 0;
////			e_sum = 0;
////			prev_encoder = encoder;
////		}
//
//		uint32_t answer[6] = {0xAAAAAAAA, ext_encoder, ext_dir, speed, dir, e};
//
////		if((encoder == MAX_VAL) || (ext_encoder == MAX_VAL)) {
////			__HAL_TIM_SET_COUNTER(&htim4, 0);
////			__HAL_TIM_SET_COUNTER(&htim5, 0);
////		}

//		ext_encoder = __HAL_TIM_GET_COUNTER(&htim4); //extrenal
//		ext_dir = __HAL_TIM_IS_TIM_COUNTING_DOWN(&htim4);
//		encoder = __HAL_TIM_GET_COUNTER(&htim2);
//		dir = __HAL_TIM_IS_TIM_COUNTING_DOWN(&htim2);
//
//		if(ext_encoder - prev_ext_encoder > 10000) {
//			ext_encoder = 65535 - ext_encoder;
//			prev_ext_encoder = ext_encoder + 1;
//		}
//		else if(prev_ext_encoder - ext_encoder > 10000) {
//			ext_encoder = ext_encoder - 4294967295;
//			prev_ext_encoder = ext_encoder + 1;
//		}
//
//		if(encoder - prev_encoder > 10000) {
//			encoder = 4294967295 - encoder;
//			prev_encoder = encoder - ext_encoder;
//		}
//		else if(prev_encoder - encoder > 10000) {
//			encoder = encoder - 4294967295;
//			prev_encoder = encoder - ext_encoder;
//		}
//
//		if(ext_dir)
//			speed = encoder - prev_encoder;
//		else
//			speed = prev_encoder - encoder;
//
//		e = ext_encoder - speed;
//		u = pid(3, 2, 1, e, e-e_prev);
//
//		if(e > 0)
//			wanted_dir = 1;
//		else
//			wanted_dir = 0;
//
//		if((e < PRESICION) && (prev_ext_encoder - ext_encoder) == 0) {
//			u = 0;
//			e = 0;
//			e_sum = 0;
//		}
//
//		e_sum += e;
//		e_prev = e;
//		prev_encoder = encoder;
//		prev_ext_encoder = ext_encoder;
//
//		uint32_t answer[6] = {0xAAAAAAAA, ext_encoder, ext_dir, encoder, dir, e};
//
//		HAL_GPIO_WritePin(DIR1_GPIO_Port, DIR1_Pin, wanted_dir);
//		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, (uint32_t) abs(u));
//		HAL_UART_Transmit_IT(&huart2, answer, 24);
