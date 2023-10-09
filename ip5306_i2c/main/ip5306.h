#ifndef _IP5306_H_
#define _IP5306_H_

#include "driver/i2c.h"
#include "i2c_bus.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"


#define ENABLE    1
#define DISABLE   0

#define IP5306_ADDR             0x75

#define SYS_CTL0       0x00
#define SYS_CTL1       0x01
#define SYS_CTL2       0x02

#define Charger_CTL0   0x20
#define Charger_CTL1   0x21
#define Charger_CTL2   0x22
#define Charger_CTL3   0x23

#define CHG_DIG_CTL0   0x24

#define REG_READ0      0x70
#define REG_READ1      0x71
#define REG_READ2      0x72
#define REG_READ3      0x77


#define IP5306_REG_UNKNOW       0x78  // bat level


#define SHUTDOWN_8s                                 0
#define SHUTDOWN_32s                                1
#define SHUTDOWN_16s                                2
#define SHUTDOWN_64s                                3


#define CUT_OFF_VOLTAGE_0                                   0     // 4.14/4.26/4.305/4.35  V
#define CUT_OFF_VOLTAGE_1                                   1     // 4.17/4.275/4.32/4.365 V
#define CUT_OFF_VOLTAGE_2                                   2     // 4.185/4.29/4.335/4.38 V
#define CUT_OFF_VOLTAGE_3                                   3     // 4.2/4.305/4.35/4.395  V

#define CURRENT_200                                 0
#define CURRENT_400                                 1
#define CURRENT_500                                 2
#define CURRENT_600                                 3

#define VOUT_0                                0   //4.45   
#define VOUT_1                                1   //4.5  
#define VOUT_2                                2   //4.55 
#define VOUT_3                                3   //4.6
#define VOUT_4                                4   //4.65
#define VOUT_5                                5   //4.7 
#define VOUT_6                                6   //4.75
#define VOUT_7                                7   //4.8 

#define BATT_VOLTAGE_4V4                        3  //4.4
#define BATT_VOLTAGE_4v35                        2  //4.35
#define BATT_VOLTAGE_4v3                        1  //4.3
#define BATT_VOLTAGE_4v2                        0  //4.2

/*Voltage Pressure setting*/
#define Pressurized_42                          3 
#define Pressurized_28                          2
#define Pressurized_14                          1
#define Not_pressurized                         0




/* charging current */
#define CURRENT_50MA 0
#define CURRENT_150MA 1
#define CURRENT_250MA 2
#define CURRENT_350MA 3
#define CURRENT_450MA 4
#define CURRENT_550MA 5
#define CURRENT_650MA 6
#define CURRENT_750MA 7
#define CURRENT_850MA 8
#define CURRENT_950MA 9
#define CURRENT_1A05 10
#define CURRENT_1A15 11
#define CURRENT_1A25 12
#define CURRENT_1A35 13
#define CURRENT_1A45 14
#define CURRENT_1A55 15
#define CURRENT_1A65 16
#define CURRENT_1A75 17
#define CURRENT_1A85 18
#define CURRENT_1A95 19
#define CURRENT_2A05 20

static const char *IP5306 = "IP5306"; 

/*SYS_CTL0*/
union{
    struct{
     uint8_t BUTTON_SHUTDOWN             : 1; //0
     uint8_t SET_BOOST_OUTPUT_ENABLE     : 1; 
     uint8_t POWER_ON_LOAD               : 1;
     uint8_t RSVD                        : 1;
     uint8_t CHARGER_ENABLE              : 1;
     uint8_t BOOST_ENABLE                : 1;
     uint8_t RSVD2                       : 2;
       
    }bits;

    uint8_t reg_byte;

}reg_SYS_CTL0_t;


/*SYS_CTL1*/
union{
    struct{
       uint8_t LOW_BATTERY_SHUTDOWN_ENABLE          : 1;
       uint8_t RSVD                                 : 1;
       uint8_t BOOST_AFTER_VIN                      : 1;
       uint8_t RSVD2                                : 2;
       uint8_t SHORT_PRESS_BOOST_SWITCH_ENABLE      : 1;
       uint8_t FLASHLIGHT_CTRL_SIGNAL_SELECTION     : 1;
       uint8_t BOOST_CTRL_SIGNAL_SELECTION          : 1;   
    }bits;

    uint8_t reg_byte;

}reg_SYS_CTL1_t;

/*SYS_CTL2*/
union{
    struct{
       uint8_t RSVD                              : 2;
       uint8_t LIGHT_LOAD_SHUTDOWN_TIME          : 2;
       uint8_t LONG_PRESS_TIME                   : 1;
       uint8_t RSVD2                             : 3;  
    }bits;

    uint8_t reg_byte;
}reg_SYS_CTL2_t;

/*Charger_CTL0*/
union{
     struct{
       uint8_t CHARGING_FULL_STOP_VOLTAGE      : 2;
       uint8_t RSVD                            : 6;
     }bits;

     uint8_t reg_byte;
}reg_Charger_CTL0_t;


/*Charger_CTL1*/
union{
    struct{
       uint8_t RSVD                             : 2;
       uint8_t CHARGE_UNDER_VOLTAGE_LOOP        : 3;
       uint8_t RSVD2                            : 1;
       uint8_t END_CHARGE_CURRENT_DETECTION     : 2;
    }bits;

    uint8_t reg_byte;
}reg_Charger_CTL1_t;


/*Charger_CTL2*/
union{
     struct{
       uint8_t  VOLTAGE_PRESSURE              : 2;
       uint8_t  BATTERY_VOLTAGE               : 2;
       uint8_t  RSVD                          : 4;
     }bits;

     uint8_t reg_byte;
}reg_Charger_CTL2_t;

/*Charger_CTL3*/     
union{
     struct{
       uint8_t  RSVD                          : 5;
       uint8_t  CHARGE_CC_LOOP                : 1;
       uint8_t  RSVD2                         : 2;
     }bits;

     uint8_t reg_byte; 
}reg_Charger_CTL3_t;           


/*CHG_DIG_CTL0*/
union{
     struct{
       uint8_t  VIN_CURRENT                   : 5;
       uint8_t  RSVD                          : 3;
     }bits;

     uint8_t reg_byte;
}reg_CHG_DIG_CTL0_t;


/*REG_READ0*/
union{ 
      struct{
       uint8_t   RSVD                         : 3;
       uint8_t   CHARGE_ENABLE                : 1;
       uint8_t   RSVD2                        : 4;
      }bits;

      uint8_t  reg_byte;
}reg_READ0_t;

/*REG_READ1*/

union{ 
      struct{
       uint8_t   RSVD                          : 3;
       uint8_t   BATTERY_STATUS                : 1;
       uint8_t   RSVD2                         : 4;
      }bits;

      uint8_t  reg_byte;
}reg_READ1_t;


/*REG_READ2*/
union{ 
      struct{
       uint8_t   RSVD                         : 2;
       uint8_t   LOAD_LEVEL                   : 1;
       uint8_t   RSVD2                        : 5;
      }bits;

      uint8_t  reg_byte;
}reg_READ2_t;

/*REG_READ3*/
// union{ 
//       struct{
//        uint8_t   SHORT_PRESS_DETECT           : 1;
//        uint8_t   LONG_PRESS_DETECT            : 1;
//        uint8_t   DOUBLE_PRESS_DETECT          : 1;
//        uint8_t   RSVD                         : 5;
//       }bits;

//       uint8_t  reg_byte;
// }reg_READ3_t;


typedef struct {
    i2c_bus_device_handle_t i2c_dev;
    uint8_t dev_addr;
    uint32_t timeout;
} ip5306_dev_t;

typedef void *ip5306_handle_t;


#ifdef __cplusplus
extern "C"
{
#endif


ip5306_handle_t ip5306_create(i2c_bus_handle_t bus, uint8_t dev_addr);



uint8_t ip5306_read(uint8_t reg_addr);


esp_err_t ip5306_write(uint8_t reg_addr,uint8_t val);


uint8_t get_battery_level();

void set_battery_voltage(uint8_t voltage_val);


void charger_under_voltage(uint8_t voltage_val);


void end_charge_current(uint8_t current_val);


void set_charging_stop_voltage(uint8_t voltage_val);


void set_light_load_shutdown_time(uint8_t shutdown_time);


void boost_after_vin(uint8_t val);

void power_on_load(uint8_t power_on_en);

void low_battery_shutdown(uint8_t shutdown_en);

void boost_mode(uint8_t boost_en);

uint8_t battery_charge_status(void);

uint8_t get_battery_charging_status(void);


uint8_t check_load_level(void);

void charger_mode(uint8_t charger_en);

void set_charge_current(uint8_t current);


void ip5306_start(i2c_bus_handle_t bus);



#ifdef __cplusplus
}
#endif

#endif