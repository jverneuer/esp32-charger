#ifndef DRIVERSINA260
#define DRIVERSINA260

//TODO: add missing polarity and alert latch options options 


#include <stdint.h>

#define INA260_I2CADDR_DEFAULT 0x40
#define CONFIGURATION_REGISTER = 0x00
#define CURRENT_REGISTER = 0x01
#define BUS_VOLTAGE_REGISTER = 0x02
#define POWER_REGISTER = 0x03
#define MASK_ENABLE_REGISTER = 0x06
#define ALERT_LIMIT_REGISTER = 0x07
#define MANUFACTURER_ID_REGISTER = 0xFE
#define DIE_ID_REGISTER = 0xFF

enum OpterationMode;


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

typedef enum OperatingMode {
  MODE_POWER_DOWN1 = 0x00,
  MODE_ISH_TRIGGERED = 0x01,
  MODE_VBUS_TRIGGERED = 0x02,
  MODE_ISH_VBUS_TRIGGERED = 0x03,
  MODE_POWER_DOWN2 = 0x04,
  MODE_ISH_CONTINUOUS = 0x05,
  MODE_VBUS_CONTINUOUS = 0x06,
  MODE_ISH_VBUS_CONTINUOUS = 0x07, //default setting in Adafruit library (continious mesurenment)
} OperatingMode;


//Averaging Mode
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

// Bus Voltage Conversion Time
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

//Shunt Current Conversion Time 

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



struct drv_ina260;



enum AddressPin {
    ADDR_GND = 0b00,
    ADDR_VS = 0b01,
    ADDR_SDA = 0b10,
    ADDR_SCL = 0b11,
};

struct drv_ina260* drv_ina260__create(int p1, int P2);  































  

//   union ConfigurationRegister {
//     struct __attribute__((packed)) {
//       uint16_t mode : 3;
//       uint16_t ishct : 3;
//       uint16_t vbusct : 3;
//       uint16_t avg : 3;
//       uint16_t : 3;
//       uint16_t rst : 1;
//     };
//     uint16_t rawValue;
//   };


// #endif // INA260_H



//     void inaTask(void* pvParameters);
#endif