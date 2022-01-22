#include "stdint.h"
#include "driver/gpio.h"
#include "driver/adc.h"


#include "battery.h"

namespace
{
  static const adc1_channel_t CHANNEL = ADC1_CHANNEL_5;
  static constexpr float R1 = 27000.00; // resistance of R1 (27K)
  static constexpr float R2 = 100000.00; // resistance of R2 (100K)
}

float WS_BATTERY::voltage()
{
  int raw = adc1_get_raw(CHANNEL);

  float vOut = (raw * 3.3 ) / 4095.0;

  return vOut * (R2 + R1) / R2;
}
    