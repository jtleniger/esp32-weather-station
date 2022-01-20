#include <ulp_c.h>

#define WIND_PIN 16
#define RAIN_PIN 6

#define SAMPLES_PER_READING 32000
#define MAX_READING 30

unsigned int rain_edges = 0;
unsigned int wind_edges = 0;

unsigned int rain_readings[MAX_READING];
unsigned int wind_readings[MAX_READING];

unsigned int wind_value = 0;
unsigned int last_wind_value = 0xFFFF;
unsigned int rain_value = 0;
unsigned int last_rain_value = 0xFFFF;

unsigned int reading = 0;
unsigned int sample = 0;

void entry()
{
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

        sample++;

        if (sample >= SAMPLES_PER_READING)
        {
            sample = 0;

            wind_readings[reading] = wind_edges >> 1;
            wind_edges = 0;

            rain_readings[reading] = rain_edges >> 1;
            rain_edges = 0;

            reading++;
        }    
    }
    
    wake_when_ready();
}
