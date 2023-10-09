#include <stdio.h>
#include <string.h>
#include "driver/i2c.h"
#include "esp_attr.h"
#include "esp_log.h"
#include "soc/gpio_periph.h"
#include "soc/i2c_periph.h"
#include "esp_system.h"
#include "soc/uart_struct.h"
#include "esp_private/periph_ctrl.h"
#include "esp_rom_gpio.h"
#include "hal/gpio_hal.h"
#include "hal/uart_ll.h"
#include "hal/i2c_types.h"

#define DATA_LENGTH          512  /*!<Data buffer length for test buffer*/
#define RW_TEST_LENGTH       129  /*!<Data length for r/w test, any value from 0-DATA_LENGTH*/

#define I2C_SLAVE_SCL_IO     1     /*!<gpio number for i2c slave clock  */
#define I2C_SLAVE_SDA_IO     2     /*!<gpio number for i2c slave data */

#define I2C_SLAVE_NUM I2C_NUM_0    /*!<I2C port number for slave dev */
#define I2C_SLAVE_TX_BUF_LEN  (2*DATA_LENGTH) /*!<I2C slave tx buffer size */
#define I2C_SLAVE_RX_BUF_LEN  (2*DATA_LENGTH) /*!<I2C slave rx buffer size */


#define I2C_MASTER_SCL_IO     3     /*!<gpio number for i2c master clock  */
#define I2C_MASTER_SDA_IO     4     /*!<gpio number for i2c master data */

#define I2C_MASTER_NUM I2C_NUM_1   /*!< I2C port number for master dev */
#define I2C_MASTER_TX_BUF_DISABLE   0   /*!< I2C master do not need buffer */
#define I2C_MASTER_RX_BUF_DISABLE   0   /*!< I2C master do not need buffer */
#define I2C_MASTER_FREQ_HZ    100000     /*!< I2C master clock frequency */

#define ESP_SLAVE_ADDR 0x28         /*!< ESP32 slave address, you can set any 7bit value */
#define WRITE_BIT  I2C_MASTER_WRITE /*!< I2C master write */
#define READ_BIT   I2C_MASTER_READ  /*!< I2C master read */
#define ACK_CHECK_EN   0x1     /*!< I2C master will check ack from slave*/



#define ACK_VAL 0
#define NACK_VAL 1


static void disp_buf(uint8_t *buf, int len)
{
    int i;
    for (i = 0; i < len; i++) {
        printf("%02x ", buf[i]);
        if (( i + 1 ) % 16 == 0) {
            printf("\n");
        }
    }
    printf("\n");
}

static esp_err_t i2c_master_write_slave(i2c_port_t i2c_num, uint8_t *data_wr, size_t size)
{
    esp_err_t ret = ESP_OK;
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    ret |= i2c_master_start(cmd);
    ret |= i2c_master_write_byte(cmd, ( ESP_SLAVE_ADDR << 1 ) | WRITE_BIT, ACK_CHECK_EN);
    ret |= i2c_master_write(cmd, data_wr, size, ACK_CHECK_EN);
    ret |= i2c_master_stop(cmd);
    ret |= i2c_master_cmd_begin(i2c_num, cmd, portMAX_DELAY);
    i2c_cmd_link_delete(cmd);
    return ret;
}

static esp_err_t i2c_master_init(void)
{
    esp_err_t ret = ESP_OK;
    i2c_config_t conf_master = {
        .mode = I2C_MODE_MASTER,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = I2C_MASTER_FREQ_HZ,
        .sda_io_num = I2C_MASTER_SDA_IO,
        .scl_io_num = I2C_MASTER_SCL_IO,
        .clk_flags = 0,
    };

    ret |= i2c_param_config(I2C_MASTER_NUM, &conf_master);

    ret |= i2c_driver_install(I2C_MASTER_NUM, I2C_MODE_MASTER,
                                   I2C_MASTER_RX_BUF_DISABLE,
                                   I2C_MASTER_TX_BUF_DISABLE, 0);
    return ret;
}



static esp_err_t i2c_slave_init(void)
{
    esp_err_t ret = ESP_OK;
    i2c_config_t conf_slave = {
        .mode = I2C_MODE_SLAVE,
        .sda_io_num = I2C_SLAVE_SDA_IO,
        .scl_io_num = I2C_SLAVE_SCL_IO,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .slave.addr_10bit_en = 0,
        .slave.slave_addr = ESP_SLAVE_ADDR,
    };

    ret |= i2c_param_config( I2C_SLAVE_NUM, &conf_slave);
    ret |= i2c_driver_install(I2C_SLAVE_NUM, I2C_MODE_SLAVE,
                                   I2C_SLAVE_RX_BUF_LEN,
                                   I2C_SLAVE_TX_BUF_LEN, 0);
    return ret;
}



static esp_err_t i2c_master_write_data(void)
{
    esp_err_t ret = ESP_OK;
    
    uint8_t *data_wr = (uint8_t *) malloc(DATA_LENGTH);
    int i;

    ret |= i2c_master_init();
    
    for (i = 0; i < DATA_LENGTH / 2; i++) {
        data_wr[i] = i;
    }
    while (1)
    {
        ret |= i2c_master_write_slave(I2C_MASTER_NUM, data_wr, DATA_LENGTH / 2);
        disp_buf(data_wr, i + 1);
    }
    
    
    free(data_wr);
    ret |= i2c_driver_delete(I2C_MASTER_NUM);
    return ret;
}

static esp_err_t i2c_slave_read_data(void)
{
    esp_err_t ret = ESP_OK;

    uint8_t *data_rd = (uint8_t *) malloc(DATA_LENGTH);
    int size_rd = 0;
    int len = 0;

    ret |=  i2c_slave_init();
    
    while (1) {
        len = i2c_slave_read_buffer( I2C_SLAVE_NUM, data_rd, DATA_LENGTH, portMAX_DELAY);
        disp_buf(data_rd, len);
    }
   
    free(data_rd);
    ret |= i2c_driver_delete(I2C_SLAVE_NUM);
    return ret;
}


void app_main(void)
{

    i2c_master_write_data();

}
