#include <bh1750.h>
#include <string.h>
#include "esp_log.h"

#include "lux.h"

namespace
{
  static const char *TAG = "WS_LUX";

  static const gpio_num_t SDA = GPIO_NUM_21;
  static const gpio_num_t SCL = GPIO_NUM_22;

  static const uint8_t ADDR = BH1750_ADDR_LO;

  i2c_dev_t dev;
}

void WS_LUX::init()
{
  memset(&dev, 0, sizeof(i2c_dev_t)); // Zero descriptor

  ESP_LOGI(TAG, "attempting to init bh1750");
  ESP_ERROR_CHECK(bh1750_init_desc(&dev, ADDR, 0, SDA, SCL));
  ESP_ERROR_CHECK(bh1750_setup(&dev, BH1750_MODE_CONTINUOUS, BH1750_RES_HIGH));
  ESP_LOGI(TAG, "done");
}

uint16_t WS_LUX::lux()
{
  uint16_t lux;

  ESP_LOGI(TAG, "reading bh1750");
  ESP_ERROR_CHECK(bh1750_read(&dev, &lux));
  ESP_LOGI(TAG, "done");

  return lux;
}