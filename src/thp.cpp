#include <string.h>
#include <bmp280.h>
#include "esp_log.h"

#include "thp.h"

namespace
{
  static const char *TAG = "WS_THP";

  static const gpio_num_t SDA = GPIO_NUM_21;
  static const gpio_num_t SCL = GPIO_NUM_22;
}

void WS_THP::read(float *temperature, float *pressure, float *humidity)
{
  bmp280_params_t params;
  bmp280_init_default_params(&params);
  bmp280_t dev;
  memset(&dev, 0, sizeof(bmp280_t));

  ESP_LOGI(TAG, "attempting to init BME280");
  ESP_ERROR_CHECK(bmp280_init_desc(&dev, BMP280_I2C_ADDRESS_0, 0, SDA, SCL));
  ESP_ERROR_CHECK(bmp280_init(&dev, &params));
  ESP_LOGI(TAG, "done");

  bool bme280p = dev.id == BME280_CHIP_ID;
  ESP_LOGI(TAG, "BMP280: found %s\n", bme280p ? "BME280" : "BMP280");

  ESP_ERROR_CHECK(bmp280_read_float(&dev, temperature, pressure, humidity));
}