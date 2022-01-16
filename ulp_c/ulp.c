#include <ulp_c.h>

#define WIND_PIN 16
#define RAIN_PIN 6

#define CYCLES_PER_MS 8000
#define SAMPLES_PER_READING 999
#define MAX_READING 60

unsigned int rain_ticks = 0;
unsigned int next_rain_edge = 0;

unsigned int wind_ticks = 0;
unsigned int next_wind_edge = 1;

unsigned int rain_readings[300];
unsigned int wind_readings[300];

unsigned int reading = 0;
unsigned int sample = 0;

void entry()
{
    for (;;)
    {
        unsigned int wind = READ_RTC_REG(RTC_GPIO_IN_REG, RTC_GPIO_IN_NEXT_S + WIND_PIN, 1);
        unsigned int rain = READ_RTC_REG(RTC_GPIO_IN_REG, RTC_GPIO_IN_NEXT_S + RAIN_PIN, 1);

        if (rain == next_rain_edge) {
            
            /* RISING EDGE */
            if (next_rain_edge)
            {
                rain_ticks++;
            }

            next_rain_edge = !next_rain_edge;
        }

        if (wind == next_wind_edge)
        {
            /* FALLING EDGE */
            if (!next_wind_edge)
            {
                wind_ticks++;
            }

            next_wind_edge = !next_wind_edge;
        }

        wait(CYCLES_PER_MS);

        sample++;

        if (sample > SAMPLES_PER_READING)
        {
            sample = 0;

            wind_readings[reading] = wind_ticks;
            wind_ticks = 0;

            rain_readings[reading] = rain_ticks;
            rain_ticks = 0;

            reading++;
        }

        if (reading >= MAX_READING)
        {
            break;
        }
    }
    
    wake_when_ready();
}
