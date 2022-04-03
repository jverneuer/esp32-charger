#include "esp_log.h"
#include "esp_system.h"
#include "driver/i2c.h"
#include <stdio.h>
#include "config/config.h"

static const char *TAG = "ina260";

static esp_err_t i2cInit(){
    int i2c_master_port = I2C_MASTER_NUM;
    i2c_config_t conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = I2C_MASTER_SDA_IO,
        .scl_io_num = I2C_MASTER_SCL_IO,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = I2C_MASTER_FREQ,
    };

    i2c_param_config(i2c_master_port, &conf);
    return i2c_driver_install(i2c_master_port, conf.mode, I2C_MASTER_RX_BUF_DISABLE, I2C_MASTER_TX_BUF_DISABLE, 0);
}

static void selectDeviceRegister(i2c_cmd_handle_t *cmd, inaAdress deviceAddr, InaRegisters registerSelect){
    //send device adress 
    i2c_master_write_byte(cmd, ( deviceAddr << 1 ), ACK_CHECK_EN);
    // send register we want
    i2c_master_write_byte(cmd, registerSelect, ACK_CHECK_EN);
    i2c_master_start(cmd);
    // now send device address with read flag
    i2c_master_write_byte(cmd, ( deviceAddr << 1 ) | READ_BIT, ACK_CHECK_EN);
}

static i2c_cmd_handle_t getI2cHandle(void){
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    return cmd;
}
esp_err_t i2cReadRaw(i2c_port_t i2c_num, inaAdress deviceAddr, InaRegisters registerToRead, uint8_t *data_rd, size_t size){
    i2c_cmd_handle_t cmd = getI2cHandle();
    selectDeviceRegister(cmd, deviceAddr, registerToRead);    
    if (size == 0) {
        return ESP_OK;
    }
    //execute the read
    i2c_master_read_byte(cmd, data_rd + size - 1, NACK_VAL);
    i2c_master_stop(cmd);
    //execute the queue
    esp_err_t ret = i2c_master_cmd_begin(i2c_num, cmd, 1000 / portTICK_RATE_MS);
    i2c_cmd_link_delete(cmd);
    if (ret == ESP_OK) {
        ESP_LOGI(TAG, "ESP OK on device 0x%02x, reading register 0x%02x", deviceAddr, registerToRead);
        ESP_LOGI(TAG, "Data Response: 0x%02x%02x ", data_rd[0], data_rd[1]);

    }
    else{
        ESP_LOGE(TAG, "%s on device 0x%02x, reading register 0x%02x", esp_err_to_name(ret), deviceAddr, registerToRead);
    }
    return ret;
}


//void startIna(void* pvParameters){
//    char data[2];
//    while(1) {
//        int len = *(&INA216ADDRESS + 1) - INA216ADDRESS;
//        for (int i = 0; i < len; i++) {
//            i2cReadRaw(I2C_MASTER_NUM, INA216ADDRESS[i], CONFIGURATION_REGISTER, data, INA260REGISTERSIZE);
//            ESP_LOGI(TAG, "Response: 0x%02x%02x from  0x%02x", data[0], data[1], INA216ADDRESS[i]);
//        }
//        
//        vTaskDelay(500 / portTICK_PERIOD_MS);
//    }
//}


void initI2c(){
    ESP_ERROR_CHECK(i2cInit());
    ESP_LOGI(TAG, "I2C initialized successfully");
}

static void initialize(int adress, OperatingMode opmode, AveragingMode avgmode, BusVoltageConversionTime vtime, CurrentConversionTime ctime){
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