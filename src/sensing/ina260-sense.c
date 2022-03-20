#include "ina260-sense.h"
#include "esp_log.h"
#include "esp_system.h"
#include "driver/i2c.h"
#include <stdio.h>

static const char *TAG = "ina260-sense";

static esp_err_t i2c_master_init(void){
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

static esp_err_t i2c_master_read_slave(i2c_port_t i2c_num, uint8_t deviceAddr, uint8_t registerToRead, uint8_t *data_rd, size_t size){
    if (size == 0) {
        return ESP_OK;
    }
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);

    //send device adress 
    i2c_master_write_byte(cmd, ( deviceAddr << 1 ), ACK_CHECK_EN);
    // send register we want
    i2c_master_write_byte(cmd, registerToRead, ACK_CHECK_EN);
    i2c_master_start(cmd);
    // now send device address with read flag
    i2c_master_write_byte(cmd, ( deviceAddr << 1 ) | READ_BIT, ACK_CHECK_EN);
    //execute the read
    if (size > 1) {
        i2c_master_read(cmd, data_rd, size - 1, ACK_VAL);
    }
    i2c_master_read_byte(cmd, data_rd + size - 1, NACK_VAL);
    
        //i2c_master_write_byte(cmd, (deviceAddr -1) | READ_BIT, ACK_CHECK_EN); //Select device
    //i2c_master_write_byte(cmd, registerToRead, false); //Select register

    i2c_master_stop(cmd);
    esp_err_t ret = i2c_master_cmd_begin(i2c_num, cmd, 1000 / portTICK_RATE_MS);
    i2c_cmd_link_delete(cmd);
    if (ret == ESP_OK) {
        ESP_LOGI(TAG, "ESP OK");
            printf("*******************\n");
            printf("*******************\n");
            //printf("data_h: %02x\n", &data_rd);
            //printf("sensor val: %.02f [Lux]\n", (sensor_data_h << 8 | sensor_data_l) / 1.2);
    }
    else{
        ESP_LOGE(TAG, "%s on device %d, reading register %d", esp_err_to_name(ret), deviceAddr, registerToRead);
    }
    return ret;
}


void startIna(void* pvParameters){
    ESP_ERROR_CHECK(i2c_master_init());
    ESP_LOGI(TAG, "I2C initialized successfully");
    uint8_t data[2];
    ESP_LOGI(TAG, "starting i2c");

    while(1) {
        printf("data_h : 0x%02x\n", MANUFACTURER_ID_REGISTER);
        i2c_master_read_slave(I2C_MASTER_NUM, 0x40, CONFIGURATION_REGISTER, data, INA260REGISTERSIZE);
         ESP_LOGI(TAG, "Response: 0x%02x%02x", data[0], data[1]);
        vTaskDelay(5000 / portTICK_PERIOD_MS);
    }
}



static void initialize(int adress, OperatingMode opmode, AveragingMode avgmode, BusVoltageConversionTime vtime, CurrentConversionTime ctime){
    //todo pass 
}

//TODO calculate correct voltages for the current purpose
static void initializeDefaults(int adress){
    initialize(adress, MODE_ISH_VBUS_CONTINUOUS, MODE_AVG_128, CONV_332US, ISHCT_332US);
}
static float readCurrent(int deviceID){
    return 1.0;
}
static float readVoltage(void){
    return 1.0;
}
static float readPower(void){
    return 1.0;
}
static void setOperatingMode(OperatingMode mode){

}   
static void setAveragingMode(AveragingMode mode){

}
static void setBusVoltageConversionTime(BusVoltageConversionTime time){

}
static void setCurrentConversionTime(CurrentConversionTime time){

}
