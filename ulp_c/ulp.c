#include <ulp_c.h>

#define WIND_PIN 16
#define RAIN_PIN 6

#define RTC_CNTL_TIME0_1_SEC 0x249F
#define RTC_CNTL_TIME0_START_BIT 4
#define RTC_CNTL_TIME0_WIDTH 14
#define MAX_READING 300

unsigned int rain_edges = 0;
unsigned int wind_edges = 0;

unsigned int wind_ticks[MAX_READING];

unsigned int wind_value = 0;
unsigned int last_wind_value = 0xFFFF;
unsigned int rain_value = 0;
unsigned int last_rain_value = 0xFFFF;

unsigned int reading = 0;
unsigned int last_sample_at;
unsigned int this_sample_at;

void entry()
{
  // Initialize to now.
  WRITE_RTC_FIELD(RTC_CNTL_TIME_UPDATE_REG, RTC_CNTL_TIME_UPDATE, 1);
  while (READ_RTC_FIELD(RTC_CNTL_TIME_UPDATE_REG, RTC_CNTL_TIME_VALID) == 0);
  last_sample_at = READ_RTC_REG(RTC_CNTL_TIME0_REG, RTC_CNTL_TIME0_START_BIT, RTC_CNTL_TIME0_WIDTH);

  for (;;)
  {
    if (reading >= MAX_READING)
    {
      break;
    }

    wind_value = READ_RTC_REG(RTC_GPIO_IN_REG, RTC_GPIO_IN_NEXT_S + WIND_PIN, 1);
    rain_value = READ_RTC_REG(RTC_GPIO_IN_REG, RTC_GPIO_IN_NEXT_S + RAIN_PIN, 1);

    if (last_rain_value != 0xFFFF && rain_value != last_rain_value)
    {
      rain_edges++;
    }

    last_rain_value = rain_value;

    if (last_wind_value != 0xFFFF && wind_value != last_wind_value)
    {
      wind_edges++;
    }

    last_wind_value = wind_value;

    WRITE_RTC_FIELD(RTC_CNTL_TIME_UPDATE_REG, RTC_CNTL_TIME_UPDATE, 1);
    while (READ_RTC_FIELD(RTC_CNTL_TIME_UPDATE_REG, RTC_CNTL_TIME_VALID) == 0);
    this_sample_at = READ_RTC_REG(RTC_CNTL_TIME0_REG, RTC_CNTL_TIME0_START_BIT, RTC_CNTL_TIME0_WIDTH);

    if ((this_sample_at - last_sample_at) >= RTC_CNTL_TIME0_1_SEC)
    {
      last_sample_at = this_sample_at;

      wind_ticks[reading] = wind_edges >> 1;
      wind_edges = 0;

      reading++;
    }
  }

  wake_when_ready();
}
