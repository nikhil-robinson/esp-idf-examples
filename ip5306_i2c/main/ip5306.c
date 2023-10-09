
#include "ip5306.h"


static i2c_bus_handle_t i2c_bus_ip5306;
static i2c_bus_device_handle_t ip5306;


ip5306_handle_t ip5306_create(i2c_bus_handle_t bus, uint8_t dev_addr)
{
    ip5306_dev_t *sens = (ip5306_dev_t *) calloc(1, sizeof(ip5306_dev_t));
    sens->i2c_dev = i2c_bus_device_create(bus, dev_addr, i2c_bus_get_current_clk_speed(bus));
    if (sens->i2c_dev == NULL) {
        free(sens);
        return NULL;
    }
    sens->dev_addr = dev_addr;
    sens->timeout = 1000;
    ip5306 = sens->i2c_dev;
    return (ip5306_handle_t) sens;
}



uint8_t ip5306_read(uint8_t reg_addr)
{
    uint8_t data=0;
    esp_err_t ret = i2c_bus_read_byte(ip5306, reg_addr,&data);
    //if (ret == ESP_OK){ESP_LOGI(IP5306," read sucess read value %d from register %d \n",data,reg_addr);}
    //else 
    if (ret == ESP_FAIL){ESP_LOGE(IP5306, "Sending command error, slave doesn't ACK the transfer\n");}
    else if (ret == ESP_ERR_INVALID_ARG){ESP_LOGE(IP5306,"parameter error \n");}
    else if (ret ==ESP_ERR_INVALID_STATE){ESP_LOGE(IP5306, "I2C driver not installed or not in master mode\n");}
    else if (ret == ESP_ERR_TIMEOUT){ESP_LOGE(IP5306,"Operation timeout because the bus is busy\n");}
    return data;
}

esp_err_t ip5306_write(uint8_t reg_addr,uint8_t val)
{
    esp_err_t ret = i2c_bus_write_byte(ip5306, reg_addr,val);
    // if (ret == ESP_OK)
    // {
    //     ESP_LOGI(IP5306, "write to address %d with value %d sucess \n",reg_addr,val);
    // }
    //else 
    if (ret == ESP_FAIL){ESP_LOGE(IP5306, "Sending command error, slave doesn't ACK the transfer\n");}
    else if (ret == ESP_ERR_INVALID_ARG){ESP_LOGE(IP5306,"parameter error \n");}
    else if (ret ==ESP_ERR_INVALID_STATE){ESP_LOGE(IP5306, "I2C driver not installed or not in master mode\n");}
    else if (ret == ESP_ERR_TIMEOUT){ESP_LOGE(IP5306,"Operation timeout because the bus is busy\n");}
    return ret;
}

uint8_t get_battery_level()
{
    uint8_t data = ip5306_read(IP5306_REG_UNKNOW);
    switch (data & 0xF0) {
    case 0xE0: return 25;
    case 0xC0: return 50;
    case 0x80: return 75;
    case 0x00: return 100;
    default: return 0;
    } 

}

void set_battery_voltage(uint8_t voltage_val)
{
    reg_Charger_CTL2_t.bits.BATTERY_VOLTAGE = voltage_val;
    ip5306_write(Charger_CTL2,reg_Charger_CTL2_t.reg_byte);
}

void charger_under_voltage(uint8_t voltage_val)
{
    reg_Charger_CTL1_t.bits.CHARGE_UNDER_VOLTAGE_LOOP = voltage_val;
    ip5306_write(Charger_CTL1,reg_Charger_CTL1_t.reg_byte);
}

void end_charge_current(uint8_t current_val)
{
    reg_Charger_CTL1_t.bits.END_CHARGE_CURRENT_DETECTION = current_val;
    ip5306_write(Charger_CTL1,reg_Charger_CTL1_t.reg_byte);
}

void set_charging_stop_voltage(uint8_t voltage_val)
{
    reg_Charger_CTL0_t.bits.CHARGING_FULL_STOP_VOLTAGE = voltage_val;
    ip5306_write(Charger_CTL0,reg_Charger_CTL0_t.reg_byte);
}

void set_light_load_shutdown_time(uint8_t shutdown_time)
{
    reg_SYS_CTL2_t.bits.LIGHT_LOAD_SHUTDOWN_TIME = shutdown_time;
    ip5306_write(SYS_CTL2,reg_SYS_CTL2_t.reg_byte);
}

void boost_after_vin(uint8_t val)
{
    reg_SYS_CTL1_t.bits.BOOST_AFTER_VIN = val;
    ip5306_write(SYS_CTL1,reg_SYS_CTL1_t.reg_byte);

}

void power_on_load(uint8_t power_on_en)
{
    reg_SYS_CTL0_t.bits.POWER_ON_LOAD = power_on_en;
    ip5306_write(SYS_CTL0,reg_SYS_CTL0_t.reg_byte);
}

void low_battery_shutdown(uint8_t shutdown_en)
{
    reg_SYS_CTL1_t.bits.LOW_BATTERY_SHUTDOWN_ENABLE = shutdown_en;
    ip5306_write(SYS_CTL1,reg_SYS_CTL1_t.reg_byte);

}

void boost_mode(uint8_t boost_en)
{
    reg_SYS_CTL0_t.bits.BOOST_ENABLE = boost_en;
    ip5306_write(SYS_CTL0,reg_SYS_CTL0_t.reg_byte);

}

uint8_t battery_charge_status(void)
{
    reg_READ1_t.reg_byte = ip5306_read(REG_READ1);
    return reg_READ1_t.bits.BATTERY_STATUS;
}

uint8_t get_battery_charging_status(void)
{
    reg_READ0_t.reg_byte = ip5306_read(REG_READ0);
    return reg_READ0_t.bits.CHARGE_ENABLE;
}


uint8_t check_load_level(void)
{
    reg_READ2_t.reg_byte = ip5306_read(REG_READ2);
    return reg_READ2_t.bits.LOAD_LEVEL;
}

void charger_mode(uint8_t charger_en)
{
    reg_SYS_CTL0_t.bits.CHARGER_ENABLE = charger_en;
    ip5306_write(SYS_CTL0,reg_SYS_CTL0_t.reg_byte);
}

void set_charge_current(uint8_t current)
{
    reg_CHG_DIG_CTL0_t.bits.VIN_CURRENT = current;
    ip5306_write(CHG_DIG_CTL0,reg_CHG_DIG_CTL0_t.reg_byte);
}


void ip5306_start(i2c_bus_handle_t bus)
{

    i2c_bus_ip5306 = bus;
    assert(i2c_bus_ip5306 != NULL);
    ip5306 =i2c_bus_device_create(i2c_bus_ip5306, 0x75, 0);
    assert(ip5306 != NULL);
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