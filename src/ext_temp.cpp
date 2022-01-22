#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <ds18x20.h>
#include <esp_log.h>

#include "ext_temp.h"

namespace
{
  static const char *TAG = "WS_EXT_TEMP";

  static const gpio_num_t PIN = GPIO_NUM_4;
  static const ds18x20_addr_t SENSOR_ADDR = 0x3800000001982928;
}

float WS_EXT_TEMP::temp_f()
{
  float temp_c;
  esp_err_t err = ds18x20_measure_and_read(PIN, SENSOR_ADDR, &temp_c);

  if (err != ESP_OK)
  {
    ESP_LOGE(TAG, "Could not read from sensor %08x%08x: %d (%s)",
      (uint32_t)(SENSOR_ADDR >> 32), (uint32_t)SENSOR_ADDR, err, esp_err_to_name(err));
  }

  return (temp_c * 1.8) + 32;
}