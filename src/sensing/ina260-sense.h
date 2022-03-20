#ifndef CHARGERINA260
    #define CHARGERINA260
    #include <stdint.h>

    //TODO: add missing polarity and alert latch options options 



    //defaulting to the Adafruit boards default adress as that's probably the most commonly used one 
    //out in the wild
    #define INA260_I2CADDR_DEFAULT 0x40;

    //register adress settings (see datasheet)
    #define CONFIGURATION_REGISTER 0x00
    #define CURRENT_REGISTER 0x01
    #define BUS_VOLTAGE_REGISTER 0x02
    #define POWER_REGISTER 0x03
    #define MASK_ENABLE_REGISTER 0x06
    #define ALERT_LIMIT_REGISTER 0x07
    #define MANUFACTURER_ID_REGISTER 0xFE
    #define DIE_ID_REGISTER 0xFF
    #define INA260REGISTERSIZE 2 // the size of the radable registers INA Registeres are 2byte 

    //I2C config
    #define I2C_MASTER_SCL_IO 22        // GPIO number used for I2C master clock */
    #define I2C_MASTER_SDA_IO 21        // GPIO number used for I2C master data  */
    #define I2C_MASTER_NUM 0            // I2C master i2c port number, the number of i2c peripheral interfaces available will depend on the chip */
    #define I2C_MASTER_FREQ 100000
    #define I2C_MASTER_TX_BUF_DISABLE 0 // I2C master doesn't need buffer */
    #define I2C_MASTER_RX_BUF_DISABLE 0 // I2C master doesn't need buffer */
    #define I2C_MASTER_TIMEOUT_MS 1000 //timeout in ms
    #define WRITE_BIT I2C_MASTER_WRITE              /*!< I2C master write */
    #define READ_BIT I2C_MASTER_READ                /*!< I2C master read */
    #define ACK_CHECK_EN 0x1                        /*!< I2C master will check ack from slave*/
    #define ACK_CHECK_DIS 0x0                       /*!< I2C master will not check ack from slave */
    #define ACK_VAL 0x0                             /*!< I2C ack value */
    #define NACK_VAL 0x1                            /*!< I2C nack value */
    // Selects continuous, triggered, or power-down mode of operation. These bits default to
    // continuous shunt and bus measurement mode. The following shows mode settings.
    // MODE2 = 0, MODE1 = 0, MODE0 = 0, mode = Power-Down (or Shutdown)
    // MODE2 = 0, MODE1 = 0, MODE0 = 1, mode = Shunt Current, Triggered
    // MODE2 = 0, MODE1 = 1, MODE0 = 0, mode = Bus Voltage, Triggered
    // MODE2 = 0, MODE1 = 1, MODE0 = 1, mode = Shunt Current and Bus Voltage,Triggered
    // MODE2 = 1, MODE1 = 0, MODE0 = 0, mode = Power-Down (or Shutdown)
    // MODE2 = 1, MODE1 = 0, MODE0 = 1, mode = Shunt Current, Continuous
    // MODE2 = 1, MODE1 = 1, MODE0 = 0, mode = Bus Voltage, Continuous
    // MODE2 = 1, MODE1 = 1, MODE0 = 1, mode = Shunt Current and Bus Voltage, Continuous
    // See datasheet

    //Configuration register bit 0-2 Operating Mode
    typedef enum OperatingMode {
      MODE_POWER_DOWN1 = 0x00, //shut down
      MODE_ISH_TRIGGERED = 0x01, //triggered single shoot current
      MODE_VBUS_TRIGGERED = 0x02, //triggered single shoot bus voltage
      MODE_ISH_VBUS_TRIGGERED = 0x03, //triggered one shoot Shunt Current and Bus Voltage 
      MODE_POWER_DOWN2 = 0x04, //shut down
      MODE_ISH_CONTINUOUS = 0x05, //continiously mesurement of current
      MODE_VBUS_CONTINUOUS = 0x06, //continiously mesurement of bus voltage
      MODE_ISH_VBUS_CONTINUOUS = 0x07, // Shunt Current and Bus Voltage Continuous (default setting in Adafruit library)
    } OperatingMode;


    //Shunt Current Conversion Time  config register bit 3-5
    typedef enum CurrentConversionTime {
         ISHCT_140US = 0x00,
         ISHCT_204US = 0x01,
         ISHCT_332US = 0x02,
         ISHCT_588US = 0x03,
         ISHCT_1100US = 0x04,
         ISHCT_2116US = 0x05,
         ISHCT_4156US = 0x06,
         ISHCT_8244US = 0x07,
    } CurrentConversionTime;

    // Bus Voltage Conversion Time, config register 6-8
    // Sets the conversion time for the bus voltage measurements. See datasheet
    typedef enum BusVoltageConversionTime {
        CONV_140US = 0x00,
        CONV_204US = 0x01,
        CONV_332US = 0x02,
        CONV_588US = 0x03,
        CONV_1100US = 0x04,
        CONV_2116US = 0x05,
        CONV_4156US = 0x06,
        CONV_8244US = 0x07,
    } BusVoltageConversionTime;

    //Averaging Mode, config register bits 9-11
    //Determines the number of samples that are collected and averaged. See data sheet
    typedef enum AveragingMode {
        MODE_AVG_1 = 0x00,
        MODE_AVG_4 = 0x01,
        MODE_AVG_16 = 0x02,
        MODE_AVG_64 = 0x03,
        MODE_AVG_128 = 0x04,
        MODE_AVG_256 = 0x05,
        MODE_AVG_512 = 0x06,
        MODE_AVG_1024 = 0x07,
    } AveragingMode;
    void startIna(void* pvParameters);
        
    // struct Ina260;
    // static void initializeDefaults(int adress);
    // void initialize(int adress, OperatingMode opmode, AveragingMode avgmode, BusVoltageConversionTime vtime, CurrentConversionTime ctime);
    // float readCurrent(void);
    // float readVoltage(void);
    // float readPower(void);
    // void setOperatingMode(OperatingMode mode);   
    // void setAveragingMode(AveragingMode mode);
    // void setBusVoltageConversionTime(BusVoltageConversionTime time);
    // void setCurrentConversionTime(CurrentConversionTime time);

#endif

//void inaTask(void* pvParameters);
//#endif