#include "i2c_bus.h"
#include "ip5306.h"


const char* TAG = "I2c example of BMS (IP5306)";

static i2c_bus_device_handle_t ip5306;

void app_main(void)
{


    // initialise i2c bus for ip5306.

    // set the port number
    i2c_port_t i2c_master_port = I2C_NUM_0;
    i2c_config_t conf;

    // set the i2c mode as master
    conf.mode = I2C_MODE_MASTER;

    // set the i2c sda pin
    conf.sda_io_num = (gpio_num_t)47;
    conf.sda_pullup_en = GPIO_PULLUP_ENABLE;

    // set the i2c scl pin
    conf.scl_io_num = (gpio_num_t)48;
    conf.scl_pullup_en = GPIO_PULLUP_ENABLE;

    // set the i2c  clk speed
    conf.master.clk_speed = 100000; //2000000
    conf.clk_flags =0;

    //create the i2c bus.
    i2c_bus_handle_t i2c_bus = i2c_bus_create(i2c_master_port, &conf);
    assert(i2c_bus != NULL);

    //add the devixe to the i2c bus 0x75 is the address of ip5306
    ip5306 =i2c_bus_device_create(i2c_bus, 0x75, 0);
    assert(ip5306 != NULL);

    //configuring the IP5306 driver
    reg_SYS_CTL0_t.reg_byte = ip5306_read(SYS_CTL0);
	reg_SYS_CTL1_t.reg_byte = ip5306_read(SYS_CTL1);
	reg_SYS_CTL2_t.reg_byte = ip5306_read(SYS_CTL2);
	reg_Charger_CTL0_t.reg_byte = ip5306_read(Charger_CTL0);
	reg_Charger_CTL1_t.reg_byte = ip5306_read(Charger_CTL1);
    reg_Charger_CTL2_t.reg_byte = ip5306_read(Charger_CTL2);
    reg_Charger_CTL3_t.reg_byte = ip5306_read(Charger_CTL3);

    set_battery_voltage(BATT_VOLTAGE_4v2);
    vTaskDelay(pdMS_TO_TICKS(100));

    charger_under_voltage(VOUT_5);
    vTaskDelay(pdMS_TO_TICKS(100));

    end_charge_current(CURRENT_200);
    vTaskDelay(pdMS_TO_TICKS(100));

    set_charging_stop_voltage(CUT_OFF_VOLTAGE_3);
    vTaskDelay(pdMS_TO_TICKS(100));

    set_light_load_shutdown_time(SHUTDOWN_64s);
    vTaskDelay(pdMS_TO_TICKS(100));

    low_battery_shutdown(ENABLE);
    vTaskDelay(pdMS_TO_TICKS(100));

    boost_after_vin(ENABLE);
    vTaskDelay(pdMS_TO_TICKS(100));

    power_on_load(ENABLE);
    vTaskDelay(pdMS_TO_TICKS(100));

    set_charge_current(CURRENT_250MA);
    vTaskDelay(pdMS_TO_TICKS(100));

    charger_mode(ENABLE);
    vTaskDelay(pdMS_TO_TICKS(100));

    boost_mode(ENABLE);
    vTaskDelay(pdMS_TO_TICKS(100));

}
