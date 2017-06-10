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
#include "juma_sensor.h"

#define UPDATE_INTERVAL 100

static void read_temperature(void* arg);
static void read_humidity(void* arg);
static void read_pressure(void* arg);
static void read_magenetometer(void* arg);
static void read_accelerometer(void* arg);
static void read_gyroscopic(void* arg);
static void led_on(void* arg);
static void led_off(void* arg);

const char* board_name = "Cannon STag";
static uint8_t running;
 
void jsensor_app_set_sensors(void)
{
    jsensor_app_set_sensor(JSENSOR_TYPE_HUMITY_TEMP);//��ʪ��
    jsensor_app_set_sensor(JSENSOR_TYPE_PRESSURE);//ѹ��
    jsensor_app_set_sensor(JSENSOR_TYPE_MOTION_6AXIS);//����
    jsensor_app_set_sensor(JSENSOR_TYPE_MAGNET);//������
}

void on_ready(void)
{
    uint8_t tx_power_level = 7;
    uint16_t adv_interval = 100;
    uint8_t bdAddr[6];
    char name[32];

    running = 0;
    BSP_LED_On(LED0);
    HCI_get_bdAddr(bdAddr);
    sprintf(name, "%s %01x%01x", board_name, bdAddr[0], bdAddr[1]);
    /*Config Adv Parameter And Ready to Adv*/
    ble_set_adv_param(name, bdAddr, tx_power_level, adv_interval);
    ble_device_start_advertising();
}

static void read_temperature(void* arg)
{
    int16_t humidity;
    int16_t temperature;
    JSensor_HUM_TEMP_Typedef tdef;

    if (!running) return;

    tdef.humidity = &humidity;
    tdef.temperature = &temperature;

    if (JSENSOR_OK == jsensor_app_read_sensor(JSENSOR_TYPE_HUMITY_TEMP, (void *)&tdef)) {
        ble_device_send(0x01, 2, (uint8_t *)&temperature);
    }

    run_after_delay(read_humidity, NULL, UPDATE_INTERVAL);
}

static void read_humidity(void* arg)
{
    int16_t humidity;
    int16_t temperature;
    JSensor_HUM_TEMP_Typedef tdef;

    if (!running) return;

    tdef.humidity = &humidity;
    tdef.temperature = &temperature;
    if (JSENSOR_OK == jsensor_app_read_sensor(JSENSOR_TYPE_HUMITY_TEMP, (void *)&tdef)) {
        ble_device_send(0x01, 2, (uint8_t *)&humidity);
    }

    run_after_delay(read_pressure, NULL, UPDATE_INTERVAL);
}

static void read_pressure(void* arg)
{
    JSensor_Press_Typedef tdef;
    int32_t pressure;

    if (!running) return;

    tdef.pressure = &pressure;

    if (JSENSOR_OK == jsensor_app_read_sensor(JSENSOR_TYPE_PRESSURE, (void *)&tdef)) {
        ble_device_send(0x02, 3, (uint8_t *)&pressure);
    }

    run_after_delay(read_magenetometer, NULL, UPDATE_INTERVAL);
}

static void read_magenetometer(void* arg)
{
    JSensor_MAG_Typedef tdef;
    int8_t  MAG[6];

    if (!running) return;

    tdef.MAG = MAG;

    if(JSENSOR_OK == jsensor_app_read_sensor(JSENSOR_TYPE_MAGNET, (void *)&tdef)) {
        ble_device_send(0x03, 6, (uint8_t*)MAG);
        //printf("%x,%x,%x,%x,%x,%x\n\r", MAG[0],MAG[1],MAG[2],MAG[3],MAG[4],MAG[5]);
    }

    run_after_delay(read_accelerometer, NULL, UPDATE_INTERVAL);
}

static void read_accelerometer(void* arg)
{
    JSensor_AXIS_Typedef tdef;
    int8_t ACC[6], GRO[6];

    if (!running) return;

    tdef.ACC = ACC;
    tdef.GRO = GRO;

    if (JSENSOR_OK == jsensor_app_read_sensor(JSENSOR_TYPE_MOTION_6AXIS, (void *)&tdef)) {
        ble_device_send(0x04, 6, (uint8_t*)ACC);
    }

    run_after_delay(read_gyroscopic, NULL, UPDATE_INTERVAL);
}

static void read_gyroscopic(void* arg)
{
    JSensor_AXIS_Typedef tdef;
    int8_t ACC[6], GRO[6];

    if (!running) return;

    tdef.ACC = ACC;
    tdef.GRO = GRO;

    if (JSENSOR_OK == jsensor_app_read_sensor(JSENSOR_TYPE_MOTION_6AXIS, (void *)&tdef)) {
        ble_device_send(0x05, 6, (uint8_t*)GRO);
    }

    run_after_delay(read_temperature, NULL, UPDATE_INTERVAL);
}

/* Device On Message */
void ble_device_on_message(uint8_t type, uint16_t length, uint8_t* value)
{
}

/* Device on connect */
void ble_device_on_connect(void)
{
    running = 1;
    run_after_delay(led_off, NULL, 150);
    run_after_delay(read_temperature, NULL, UPDATE_INTERVAL);
}

static void led_on(void* arg)
{
    BSP_LED_On(LED0);
    run_after_delay(led_off, NULL, 100);
}

static void led_off(void* arg)
{
    if (!running) return;

    BSP_LED_Off(LED0);
    run_after_delay(led_on, NULL, 150);
}

/* Device on disconnect */
void ble_device_on_disconnect(uint8_t reason)
{
    running = 0;
    /* Make the device connectable again. */
    ble_device_start_advertising();
}
