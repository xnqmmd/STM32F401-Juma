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
#include "app.h"
#include "bsp_common.h"
#include "bluenrg_sdk_api.h"
#include "x_nucleo_iks01a1.h"
#include "x_nucleo_iks01a1_hum_temp.h"
#include "x_nucleo_iks01a1_pressure.h"
#include "x_nucleo_iks01a1_imu_6axes.h"
#include "hts221.h"
#include "lps25hb.h"
#include "lps25h.h"
#include "lsm6ds3.h"
#include "juma_sensor.h"

/*start adv*/
const char *name = "CANNON_TBox";
uint8_t adv_address[] = {0x0D, 0x05, 0x04, 0x03, 0x02, 0x02};	
uint8_t tx_power_level 	= 7;
uint16_t adv_interval 	= 48;
uint8_t g_func_com_en 	= 0;
uint8_t g_func_alt_en 	= 0;
uint8_t g_func_htm_en 	= 0;
uint8_t g_func_cub_en 	= 0;
uint8_t g_func_dfu_en 	= 0;

void jsensor_app_set_sensors(void)
{
	jsensor_app_set_sensor(JSENSOR_TYPE_HUMITY_TEMP);
	jsensor_app_set_sensor(JSENSOR_TYPE_PRESSURE);
	jsensor_app_set_sensor(JSENSOR_TYPE_MOTION_6AXIS);
	jsensor_app_set_sensor(JSENSOR_TYPE_MAGNET);
}
	
void on_ready(void)
{
	const char* name = "JUMA_ToolBox";
	/*Config Adv Parameter And Ready to Adv*/
	ble_set_adv_param((char *)name, adv_address, tx_power_level, adv_interval);
	ble_device_start_advertising();
}

/*********************************
*        �������̹��ܺ���        *
**********************************/
void func_com(void* args)
{
	int8_t data[12] = {0};
	if(g_func_com_en)
	{
		//sensor read magnetometer
		JSensor_MAG_Typedef mag_tdef;
		mag_tdef.MAG = data;
		
		if(JSENSOR_OK == jsensor_app_read_sensor(JSENSOR_TYPE_MAGNET, (void *)&mag_tdef)) 
		{
			// sensor read motion 6 AXIS
			JSensor_AXIS_Typedef axis_tdef;
			axis_tdef.ACC = &data[0]+6;
			if (JSENSOR_OK == jsensor_app_read_sensor(JSENSOR_TYPE_MOTION_6AXIS, (void *)&axis_tdef)) 
				ble_device_send(0x01, 12, (uint8_t*)data);
		}
			
		run_after_delay(func_com, NULL, 100);
	}
}

/*********************************
*        ���μƹ��ܺ���          *
**********************************/
void  func_alt(void* args)
{
	uint8_t data[5] = {0};
	if(g_func_alt_en)
	{
		int32_t pressure;
		int16_t temp;
		JSensor_Press_Typedef press_value;
		JSensor_HUM_TEMP_Typedef temp_value;
		press_value.pressure = &pressure;
		temp_value.temperature = &temp;
		
		if(JSENSOR_OK == jsensor_app_read_sensor(JSENSOR_TYPE_PRESSURE, (void *)&press_value)) {
			data[0] = pressure&0xFF;
			data[1] = (pressure>>8)&0xFF;
			data[2] = (pressure>>16)&0xFF;
		}
		if(JSENSOR_OK == jsensor_app_read_sensor(JSENSOR_TYPE_HUMITY_TEMP, (void *)&temp_value)){
			data[3] = temp&0xFF;
			data[4] = (temp>>8)&0xFF;
		}
		ble_device_send(0x02, 5, (uint8_t *)&data);
		
		run_after_delay(func_alt, NULL, 500);
	}
}

/*********************************
*          ��ʪ�ȹ��ܺ���        *
**********************************/
void func_htm(void* args)
{
	int16_t data[2] = {0};
	if(g_func_htm_en)
	{
		JSensor_HUM_TEMP_Typedef tdef;
		tdef.humidity = data;
		tdef.temperature = &data[0]+1;
		
		if (JSENSOR_OK == jsensor_app_read_sensor(JSENSOR_TYPE_HUMITY_TEMP, (void *)&tdef))
		{
			ble_device_send(0x03, 4, (uint8_t*)data);
		}
			
		run_after_delay(func_htm, NULL, 1000);
	}
}

/*********************************
*         �˶�ħ�����ܺ���       *
**********************************/
void func_cube(void* args)
{
	if(g_func_cub_en)
	{
		// sensor read motion 6 AXIS
		JSensor_AXIS_Typedef tdef;
		int8_t data[12];
		tdef.ACC = data;
		tdef.GRO = &data[6];
		
		if (JSENSOR_OK == jsensor_app_read_sensor(JSENSOR_TYPE_MOTION_6AXIS, (void *)&tdef)) {
			ble_device_send(0x04, 12, (uint8_t*)data);
		}
		
		run_after_delay(func_cube, NULL, 100);
	}
}

/*********************************
*         �����������ܺ���       *
**********************************/
void func_dfu(void* args)
{
}

void func_off()
{
	g_func_com_en 	= 0;
	g_func_alt_en 	= 0;
	g_func_htm_en 	= 0;
	g_func_cub_en 	= 0;
	g_func_dfu_en 	= 0;
}

/* Device On Message */
void ble_device_on_message(uint8_t type, uint16_t length, uint8_t* value)
{
	switch(value[0])
	{
		case 0x00: 
		{
			func_off();	
			break;
		}
		case 0x01:
		{
			if(!g_func_com_en)
			{
				g_func_com_en = 1;
				func_com(NULL);	
			}
			break;
		}
		case 0x02:	
		{
			if(!g_func_alt_en)
			{
				g_func_alt_en = 1;
				func_alt(NULL);
			}
			break;
		}
		case 0x03:	
		{		
			if(!g_func_htm_en)
			{
				g_func_htm_en = 1;
				func_htm(NULL);
			}
			break;
		}
		case 0x04:
		{
			if(!g_func_cub_en)
			{
				g_func_cub_en = 1;
				func_cube(NULL);		
			}
			break;
		}
		case 0x05:	
		{
			if(!g_func_dfu_en)
			{
				g_func_dfu_en = 1;
				func_dfu(NULL);	
			}
			break;
		}
		default:	break;
	}
}

/* Device on connect */
void ble_device_on_connect(void)
{
}

/* Device on disconnect */
void ble_device_on_disconnect(uint8_t reason)
{
	func_off();
	/* Make the device connectable again. */
	ble_device_start_advertising();
}
