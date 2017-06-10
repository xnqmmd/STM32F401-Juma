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
#include "bsp_common.h"
#include "bluenrg_sdk_api.h"
#include "bluenrg_sdk_host_api.h"
#include "ble_status.h"
#include "bluenrg_gap.h"
#include "bluenrg_gatt_server.h"
#include "bluenrg_gap_aci.h"
#include "bluenrg_gatt_aci.h"
#include "hci_const.h"
#include "gp_timer.h"
#include "bluenrg_hal_aci.h"
#include "bluenrg_aci_const.h"
#include "hci.h"
#include "sm.h"

#if NO_PRINTF
#define printf(...)
#endif
extern BLE_RoleTypeDef BLE_Role;
extern uint16_t connection_handle;

ble_gap_scan_params_t host_scan_param;

uint16_t write_handle;
uint16_t notify_read_handle;
uint16_t write_without_rsp_handle;
uint16_t notify_handle;

volatile int host_connected = FALSE;
volatile uint8_t host_notification_enabled = FALSE;
volatile uint8_t start_read_write_char_handle = FALSE;
volatile uint8_t start_read_notify_read_char_handle = FALSE;
volatile uint8_t start_read_write_without_rsp_char_handle = FALSE;
volatile uint8_t start_read_notify_char_handle = FALSE;
volatile uint8_t end_read_write_char_handle = FALSE;
volatile uint8_t end_read_notify_read_char_handle = FALSE;
volatile uint8_t end_read_write_without_rsp_char_handle = FALSE;
volatile uint8_t end_read_notify_char_handle = FALSE;

uint8_t host_connect_init_flag = FALSE;

/*Host*/
__weak void ble_host_on_device_info(void* data) {}
__weak void ble_host_on_message(uint8_t type, uint16_t length, uint8_t* value) {}
__weak void ble_host_on_connect( void ) {}

/*Host*/
static void read_write_char_handle(void);
static void read_notify_read_char_handle(void);
static void read_write_without_rsp_char_handle(void);
static void read_notify_char_handle(void);
static void enableNotification(void);

void ble_host_set_scan_param(uint8_t tx_power_level, uint8_t* bdaddr, uint16_t scan_interval)
{
#ifdef CLIENT_ROLE
    tBleStatus ret;
    ble_address(bdaddr);
    ble_set_tx_power(tx_power_level);
    /*gatt and gap init*/
    ret = ble_init_bluenrg();
    if(ret){
        printf("ble_init_bluenrg\n");
    }
#endif
    /*scan_interval scan window*/
    host_scan_param.scan_interval = scan_interval;
    host_scan_param.scan_window = scan_interval;
    host_scan_param.fp = SCAN_FILTER_DUPLICATE_DISABLE;
}

void ble_host_start_scan(void* arg)
{
    tBleStatus ret;
#ifdef CLIENT_ROLE
    SCAN_Type scan_type = SCAN_PASSIVE;

    ret = aci_gap_start_general_conn_establish_proc(scan_type, SCAN_P,  SCAN_L, PUBLIC_ADDR, host_scan_param.fp);
#endif
#ifdef CLIENT_SERVER_ROLE
    ret = aci_gap_start_general_discovery_proc(host_scan_param.scan_interval+400, host_scan_param.scan_window, PUBLIC_ADDR, host_scan_param.fp);
#endif
    if(ret != BLE_STATUS_SUCCESS) {
        printf("scan failed\n");
        return ;
    }
    printf("start scanning \n\r");
}

tBleStatus ble_host_stop_scan(void)
{
    aci_gap_terminate_gap_procedure(GAP_GENERAL_DISCOVERY_PROC);
    return 0;
}

void ble_host_device_found( void* arg)
{
#ifdef CLIENT_ROLE
    scan_device_found_info device_info;
    uint8_t i;
    i = 25;
    le_advertising_info* adv_data = arg;

    while(adv_data->data_RSSI[i] == 0) {
        i--;
    }
    /*RSSI*/
    device_info.RSSI = adv_data->data_RSSI[i] - 255;
    /*bdaddr type*/
    device_info.bdaddr_type = adv_data->bdaddr_type;
    /*bdaddr*/
    memcpy(device_info.bdaddr, adv_data->bdaddr, 6);
    /*local name length*/
    device_info.local_name_len = adv_data->data_RSSI[3];
    /*local name*/
    memcpy(device_info.local_name, (adv_data->data_RSSI)+4, device_info.local_name_len);
    ble_host_on_device_info(&device_info);
#endif
#ifdef CLIENT_SERVER_ROLE
    ble_host_on_device_info(arg);
#endif
}

void ble_host_connect(tBDAddr bdaddr)
{
    if(host_connect_init_flag == FALSE) {
        tBleStatus ret;
        printf("Client Create Connection\n");
        BSP_LED_On(LED0);
        /*
          scan_interval, scan_window, peer_address_type, peer_address, own_address_type, conn_interval_min,
          conn_interval_max, conn_latency, supervision_timeout, conn_len_min, conn_len_max
          */
        ret = aci_gap_create_connection(SCAN_P, SCAN_L, RANDOM_ADDR, bdaddr, PUBLIC_ADDR, CONN_P1, CONN_P2, 0,
                                        SUPERV_TIMEOUT, CONN_L1 , CONN_L2);
        if (ret != 0) {
            printf("Error while starting connection.\n");
            Clock_Wait(100);
        } else {
            host_connect_init_flag = TRUE;
        }
        printf("connection init\n\r");
    }
}

void ble_host_discover_char(void* arg)
{
    /* start tx handle characteristic dynamic discovery if not yet done */
    if (host_connected && !end_read_write_char_handle) {
        printf("1\n");
        read_write_char_handle();
    }
    else if (host_connected && !end_read_notify_read_char_handle) {
        read_notify_read_char_handle();
        printf("2\n");
    }
    else if (host_connected && !end_read_write_without_rsp_char_handle) {
        read_write_without_rsp_char_handle();
        printf("3\n");
    }
    else if (host_connected && !end_read_notify_char_handle) {
        read_notify_char_handle();
        printf("4\n");
    }

    if(host_connected && end_read_write_char_handle && end_read_notify_read_char_handle && end_read_write_without_rsp_char_handle && end_read_notify_char_handle && !host_notification_enabled) {
        enableNotification();
        printf("discover over\n\r");
    } else {
        printf("host_connected: %x, end_read_write_char_handle : %x\n", host_connected, end_read_write_char_handle);
    }
}

/*start read write char handle*/
static void read_write_char_handle(void)
{
    if (!start_read_write_char_handle)
    {
        printf("Start reading write_char_handle\n");
        const uint8_t charUuid128_TX[16] = { 0x8C, 0xF9, 0x97,0xA6, 0xEE, 0x94, 0xE3,0xBC,0xF8, 0x21, 0xB2, 0x60, 0x01, 0x80, 0x00, 0x00};
        aci_gatt_disc_charac_by_uuid(connection_handle, 0x0001, 0xFFFF, UUID_TYPE_128, charUuid128_TX);
        start_read_write_char_handle = TRUE;
    }
}

/*start read notify read char handle*/
static void read_notify_read_char_handle(void)
{
    if (!start_read_notify_read_char_handle)
    {
        printf("Start reading notify_read_char_handle\n");
        const uint8_t charUuid128_RX[16] = {0x8C, 0xF9, 0x97,0xA6, 0xEE, 0x94, 0xE3,0xBC,0xF8, 0x21, 0xB2, 0x60, 0x02, 0x80, 0x00, 0x00};
        aci_gatt_disc_charac_by_uuid(connection_handle, 0x0001, 0xFFFF, UUID_TYPE_128, charUuid128_RX);
        start_read_notify_read_char_handle = TRUE;
    }
}
/*start read write without rsp char handle*/
static void read_write_without_rsp_char_handle(void)
{
    if (!start_read_write_without_rsp_char_handle)
    {
        printf("Start reading write_without_rsp_char_handle\n");
        const uint8_t charUuid128_TX[16] = { 0x8C, 0xF9, 0x97,0xA6, 0xEE, 0x94, 0xE3,0xBC,0xF8, 0x21, 0xB2, 0x60, 0x03, 0x80, 0x00, 0x00};
        aci_gatt_disc_charac_by_uuid(connection_handle, 0x0001, 0xFFFF, UUID_TYPE_128, charUuid128_TX);
        start_read_write_without_rsp_char_handle = TRUE;
    }

}
/*start read notify char handle*/
static void read_notify_char_handle(void)
{
    if (!start_read_notify_char_handle)
    {
        printf("Start reading notify_char_handle\n");

        const uint8_t charUuid128_TX[16] = { 0x8C, 0xF9, 0x97,0xA6, 0xEE, 0x94, 0xE3,0xBC,0xF8, 0x21, 0xB2, 0x60, 0x04, 0x80, 0x00, 0x00};
        aci_gatt_disc_charac_by_uuid(connection_handle, 0x0001, 0xFFFF, UUID_TYPE_128, charUuid128_TX);
        start_read_notify_char_handle = TRUE;
    }
}

static void enableNotification(void)
{
    uint8_t client_char_conf_data[] = {0x01, 0x00};
    struct timer t;
    Timer_Set(&t, CLOCK_SECOND*10);

    while(aci_gatt_write_charac_descriptor(connection_handle, notify_read_handle+2, 2, client_char_conf_data)==BLE_STATUS_NOT_ALLOWED) {
        /* Radio is busy */
        if(Timer_Expired(&t)) break;
    }
    host_notification_enabled = TRUE;
    HAL_Delay(100);
    ble_host_on_connect();
    printf("notification enable\n\r");
}

/*host send message*/
tBleStatus ble_host_send(uint8_t type, uint32_t length, uint8_t* value)
{
    tBleStatus ret;
    uint8_t packet[20];
    if(host_notification_enabled == FALSE) {
        return BLE_WAIT_ENABLE_NOTIFY;
    }

    if (length > 18) length = 18;
    packet[0] = type;
    packet[1] = length;
    memcpy(packet + 2, value, length);
    ret = aci_gatt_write_charac_value(connection_handle, write_handle+1, packet[1]+2, packet);
    if (ret != BLE_STATUS_SUCCESS) {
        return BLE_STATUS_ERROR ;
    }
    return ret;
}
