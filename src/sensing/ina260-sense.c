#include "ina260-sense.h"
#include "esp_log.h"
#include "esp_system.h"
#include "driver/i2c.h"
#include <stdio.h>
#include "config/config.h"
#include "drivers/ina260/ina260.h"

static const char *TAG = "ina260-sense";

void startIna(void* pvParameters){
    initI2c();
    ESP_LOGI(TAG, "I2C initialized successfully");
    uint8_t data[2];

    while(1) {
        int len = *(&INA216ADDRESS + 1) - INA216ADDRESS;
        for (int i = 0; i < len; i++) {
            i2cReadRaw(I2C_MASTER_NUM, INA216ADDRESS[i], CONFIGURATION_REGISTER, data, INA260REGISTERSIZE);
            ESP_LOGI(TAG, "Response: 0x%02x%02x from  0x%02x", data[0], data[1], INA216ADDRESS[i]);
        }
        
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
}

static void initialize(int adress, OperatingMode opmode, AveragingMode avgmode, BusVoltageConversionTime vtime, CurrentConversionTime ctime){
    //todo pass 
}

//TODO calculate correct voltages for the current purpose
//static void initializeDefaults(int adress){
//    initialize(adress, MODE_ISH_VBUS_CONTINUOUS, MODE_AVG_128, CONV_332US, ISHCT_332US);
//}
//static float readCurrent(int deviceID){
//    return 1.0;
//}
//static float readVoltage(void){
//    return 1.0;
//}
//static float readPower(void){
//    return 1.0;
//}
//static void setOperatingMode(OperatingMode mode){
//
//}   
//static void setAveragingMode(AveragingMode mode){
//
//}
//static void setBusVoltageConversionTime(BusVoltageConversionTime time){
//
//}
//static void setCurrentConversionTime(CurrentConversionTime time){
//
//}