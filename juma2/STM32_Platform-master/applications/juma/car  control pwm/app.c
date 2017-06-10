/*
 *
 *  JUMA.IO - JUMA SDK for STM families
 *
 *  Copyright (C) 2013-2016  JUMA Technology
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the Apache V2 License as published by
 *  the Free Software Foundation.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */
//#include "app.h"
//#include "bsp_common.h"
//#include "bluenrg_sdk_api.h"
//#include "juma_sensor.h"
//#include "pixy.h"
//#include "stm32f4xx_hal_uart.h"
//#include "stm32f4xx_hal_msp.h"

//#define UPDATE_INTERVAL 100

//void on_ready(void);
//static void read_temperature(void* arg);//温度
//static void read_humidity(void* arg);//湿度
//static void read_pressure(void* arg);//压力
//static void read_accelerometer(void* arg);//加速度
//static void read_magenetometer(void* arg);//磁力计
////static void read_gyroscopic(void* arg);//陀螺仪
//static void read_coordinate(void* arg);//坐标
//static void led_on(void* arg);
//static void led_off(void* arg);
//static void stop(void* arg);
//   TIM_HandleTypeDef htim2;
/*start adv*/

//char *name = "Pixy_car 315";
//uint8_t adv_address[] = {0x08, 0x05, 0x04, 0x03, 0x02, 0x04};	
//uint8_t tx_power_level = 7;
//uint16_t adv_interval = 100;


//static uint8_t running;

//void jsensor_app_set_sensors(void)
//{
//    jsensor_app_set_sensor(JSENSOR_TYPE_HUMITY_TEMP);
//    jsensor_app_set_sensor(JSENSOR_TYPE_PRESSURE);
//	  jsensor_app_set_sensor(JSENSOR_TYPE_MOTION_6AXIS);
//	  jsensor_app_set_sensor(JSENSOR_TYPE_MAGNET);
//	  jsensor_app_set_sensor(JSENSOR_TYPE_XYWH);
//}

//void PA1_Init(void)
//{
//		TIM_MasterConfigTypeDef sMasterConfig;
//		TIM_OC_InitTypeDef sConfigOC;
//		GPIO_InitTypeDef GPIO_InitStruct;
//	
//		__HAL_RCC_GPIOC_CLK_ENABLE();
//		__HAL_RCC_GPIOA_CLK_ENABLE();
//		__HAL_RCC_TIM2_CLK_ENABLE();
//	
//		htim2.Instance = TIM2;
//		htim2.Init.Prescaler = 83;
//		htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
//		htim2.Init.Period = 999;
//		htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
//		if (HAL_TIM_PWM_Init(&htim2) != HAL_OK)
//		{
//			Error_Handler();
//		}

//  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
//  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
//  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
//  {
//      Error_Handler();
//  }

//  sConfigOC.OCMode = TIM_OCMODE_PWM1;
//  sConfigOC.Pulse = 300;
//  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
//  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
//  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
//  {
//    Error_Handler();
//  }
//	HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_2);
//	
//	HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_1);
//	
//	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);

//		GPIO_InitStruct.Pin = GPIO_PIN_1|GPIO_PIN_0;
//		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
//		GPIO_InitStruct.Pull = GPIO_NOPULL;
//		GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
//		GPIO_InitStruct.Alternate = GPIO_AF1_TIM2;
//		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
//	
//	GPIO_InitTypeDef GPIO_InitStruct2;
//	__HAL_RCC_GPIOC_CLK_ENABLE();
//	__HAL_RCC_GPIOB_CLK_ENABLE();

//	GPIO_InitStruct2.Pin= GPIO_PIN_5|GPIO_PIN_13;
//	GPIO_InitStruct2.Mode= GPIO_MODE_OUTPUT_PP;
//	GPIO_InitStruct2.Pull = GPIO_NOPULL;
//	GPIO_InitStruct2.Speed= GPIO_SPEED_FAST;
//	HAL_GPIO_Init(GPIOC,&GPIO_InitStruct2);
//	
//	GPIO_InitStruct2.Pin= GPIO_PIN_0|GPIO_PIN_8;
//	GPIO_InitStruct2.Mode= GPIO_MODE_OUTPUT_PP;
//	GPIO_InitStruct2.Pull = GPIO_NOPULL;
//	GPIO_InitStruct2.Speed= GPIO_SPEED_FAST;
//	HAL_GPIO_Init(GPIOB,&GPIO_InitStruct2);
//	
//}



//  static void read_temperature(void* arg)
//{
//    int16_t humidity;
//    int16_t temperature;
//    JSensor_HUM_TEMP_Typedef tdef;

//    if (!running) return;

//    tdef.humidity =&humidity;
//    tdef.temperature = &temperature;

//    if (JSENSOR_OK == jsensor_app_read_sensor(JSENSOR_TYPE_HUMITY_TEMP, (void *)&tdef)) {
//        ble_device_send(0x00, 2, (uint8_t *)&temperature);
//    }

//    run_after_delay(read_humidity, NULL, UPDATE_INTERVAL);
//}

//    static void read_humidity(void* arg)
//{
//    int16_t humidity;
//    int16_t temperature;
//    JSensor_HUM_TEMP_Typedef tdef;

//    if (!running) return;

//    tdef.humidity = &humidity;
//    tdef.temperature = &temperature;
//    if (JSENSOR_OK == jsensor_app_read_sensor(JSENSOR_TYPE_HUMITY_TEMP, (void *)&tdef)) {
//        ble_device_send(0x01, 2, (uint8_t *)&humidity);
//    }

//    run_after_delay(read_pressure, NULL, UPDATE_INTERVAL);
//}

//static void read_pressure(void* arg)
//{
//    JSensor_Press_Typedef tdef;
//    int32_t pressure;
//    if (!running) return;

//    tdef.pressure = &pressure;

//    if (JSENSOR_OK == jsensor_app_read_sensor(JSENSOR_TYPE_PRESSURE, (void *)&tdef)) {
//        ble_device_send(0x02,3, (uint8_t *)&pressure);
//    }

//    run_after_delay(read_magenetometer, NULL, UPDATE_INTERVAL);
//}
//static void read_magenetometer(void* arg)
//{
//    JSensor_MAG_Typedef tdef;
//    int8_t  MAG[6];

//    if (!running) return;

//    tdef.MAG = MAG;

//    if(JSENSOR_OK == jsensor_app_read_sensor(JSENSOR_TYPE_MAGNET, (void *)&tdef)) {
//        ble_device_send(0x03, 6, (uint8_t*)MAG);
//    }

//    run_after_delay(read_accelerometer, NULL, UPDATE_INTERVAL);
//}
//static void read_accelerometer(void* arg)
//{
//    JSensor_AXIS_Typedef tdef;
//    int8_t ACC[6], GRO[6];

//    if (!running) return;

//    tdef.ACC = ACC;
//    tdef.GRO = GRO;

//    if (JSENSOR_OK == jsensor_app_read_sensor(JSENSOR_TYPE_MOTION_6AXIS, (void *)&tdef)) {
//        ble_device_send(0x04,6, (uint8_t*)ACC);
//    }

//    run_after_delay(read_coordinate, NULL, UPDATE_INTERVAL);
//}
////static void read_gyroscopic(void* arg)
////{
////    JSensor_AXIS_Typedef tdef;
////    int8_t ACC[6], GRO[6];

////    if (!running) return;

////    tdef.ACC = ACC;
////    tdef.GRO = GRO;

////    if (JSENSOR_OK == jsensor_app_read_sensor(JSENSOR_TYPE_MOTION_6AXIS, (void *)&tdef)) {
////        ble_device_send(0x05, 6, (uint8_t*)GRO);
////    }

////    run_after_delay(read_temperature, NULL, UPDATE_INTERVAL);
////}
//static void read_coordinate(void* arg)
//{
//    JSensor_XYWH_Typedef tdef;
//    int16_t x[6];

//    if (!running) return;

//    tdef.XYWH = x;

//    if (JSENSOR_OK == jsensor_app_read_sensor(JSENSOR_TYPE_XYWH, (void *)&tdef)) {
//        ble_device_send(0x05,6, (uint8_t*)x);
//    }

//    run_after_delay(read_temperature, NULL, UPDATE_INTERVAL);
//}



//void on_ready(void)
//{
//	PA1_Init();
//	/*Config Adv Parameter And Ready to Adv*/
//	ble_set_adv_param(name, adv_address, tx_power_level, adv_interval);
//	ble_device_start_advertising();
//}

///* Device On Message */

//				
//void ble_device_on_message(uint8_t type, uint16_t length, uint8_t* value)
//{
//	static uint8_t speed=0;
//	BSP_LED_On(LED0);
//	/*echo data*/
//	if(*value == 0x01){
//		if(++speed>=10)
//			speed=1;
//		htim2.Instance->CCR2=(speed*100);
//		htim2.Instance->CCR1=(speed*100);
//		//ble_device_send(0, 1, &speed);
//	}
//	else if(*value == 0x02){
//	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_8, GPIO_PIN_SET);
//	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13|GPIO_PIN_5,GPIO_PIN_RESET);
//}
//	else if(*value == 0x03){
//		if(--speed<=0)
//			  speed=10;
//		htim2.Instance->CCR2=(speed*100);
//		htim2.Instance->CCR1=(speed*100);
//		//ble_device_send(0, 1, &speed);
//	}
//	else if(*value == 0x04){
//	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);
//	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13,GPIO_PIN_SET);
//	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_SET);
//	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5,GPIO_PIN_RESET);
//	    run_after_delay(stop,NULL,500);
//	}
//	else if(*value == 0x05){
//		    run_after_delay(stop,NULL,0);
//	}
//	else if(*value == 0x06){
//	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);
//	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13,GPIO_PIN_RESET);
//	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_RESET);
//	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5,GPIO_PIN_SET);
//	    run_after_delay(stop,NULL,500);
//	}
//	else if(*value == 0x07){
//      htim2.Instance->CCR2=300;
//      htim2.Instance->CCR1=300;
//	 }
//	
//	else if(*value == 0x08){
//	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);
//	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13,GPIO_PIN_SET);
//	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_RESET);
//	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5,GPIO_PIN_SET);	
//	}
//	
//}

//void ble_device_on_connect(void)
//{
//         running = 1;
//         run_after_delay(read_temperature, NULL, UPDATE_INTERVAL);
//}

///* Device on disconnect */
//void ble_device_on_disconnect(uint8_t reason)
//{
//	/* Make the device connectable again. */
//					running = 0;
//					BSP_LED_Off(LED0);
//					ble_device_start_advertising();

//}
//static void led_on(void* arg)
//{
//          BSP_LED_On(LED0);
//}

//static void led_off(void* arg)
//{
//          BSP_LED_Off(LED0);
//}
//static void stop(void* arg)
//{
//	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_8, GPIO_PIN_RESET);
//	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13|GPIO_PIN_5,GPIO_PIN_RESET);
//}

