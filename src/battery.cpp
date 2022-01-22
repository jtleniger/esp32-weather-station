#include "stdint.h"
#include "driver/adc.h"
#include "esp_adc_cal.h"

#include "battery.h"

namespace
{
  static const adc1_channel_t CHANNEL = ADC1_CHANNEL_5;
  static constexpr float R1 = 27000.00; // resistance of R1 (27K)
  static constexpr float R2 = 100000.00; // resistance of R2 (100K)
}

float WS_BATTERY::voltage()
{
  esp_err_t err;

  err = adc1_config_width(ADC_WIDTH_BIT_12);
  ESP_ERROR_CHECK(err);

  err = adc1_config_channel_atten(CHANNEL, ADC_ATTEN_DB_11);
  ESP_ERROR_CHECK(err);

  int raw = adc1_get_raw(CHANNEL);

  float vOut = (raw * 3.3 ) / 4095.0;

  return vOut * (R2 + R1) / R2;
}
    