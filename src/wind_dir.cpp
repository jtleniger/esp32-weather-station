#include "driver/adc.h"
#include "esp_adc_cal.h"

#include "wind_dir.h"

namespace
{
  static const adc1_channel_t CHANNEL = ADC1_CHANNEL_7;
}

float WS_WIND_DIR::direction()
{
  esp_err_t err;

  err = adc1_config_width(ADC_WIDTH_BIT_12);
  ESP_ERROR_CHECK(err);

  err = adc1_config_channel_atten(CHANNEL, ADC_ATTEN_DB_11);
  ESP_ERROR_CHECK(err);

  int raw = adc1_get_raw(CHANNEL);

  float dir;

  if (raw < 150) dir = 202.5f;
  else if (raw < 300) dir = 180.0f;
  else if (raw < 400) dir = 247.5f;
  else if (raw < 600) dir = 225.0f;
  else if (raw < 900) dir = 292.5f;
  else if (raw < 1100) dir = 270.0f;
  else if (raw < 1500) dir = 112.5f;
  else if (raw < 1700) dir = 135.0f;
  else if (raw < 2250) dir = 337.5f;
  else if (raw < 2350) dir = 315.0f;
  else if (raw < 2700) dir = 67.5f;
  else if (raw < 3000) dir = 90.0f;
  else if (raw < 3200) dir = 22.5f;
  else if (raw < 3400) dir = 45.0f;
  else if (raw < 4000) dir = 0.0f;
  else dir = 0.0f;

  return dir;
}