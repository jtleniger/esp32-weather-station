#include <ulp_c.h>

#define DEBOUNCE_COUNT 10
#define CYCLES_PER_MS 8000
#define SAMPLES_PER_READING 999
#define MAX_READING 299

unsigned int rainTicks = 0;
unsigned int nextRainEdge = 0;
unsigned int rainDebounceCounter = DEBOUNCE_COUNT;

unsigned int windTicks = 0;
unsigned int nextWindEdge = 0;
unsigned int windDebounceCounter = DEBOUNCE_COUNT;

unsigned int rainBuckets[300];
unsigned int windBuckets[300];

unsigned int reading = 0;
unsigned int sample = 0;

void entry()
{
    // Loop at 1000Hz

    for (;;)
    {
        /* READ GPIO REGISTERS AND INC COUNTERS */
        unsigned int rain = READ_RTC_REG(RTC_GPIO_IN_REG, RTC_GPIO_IN_NEXT_S + 16, 2) >> (25 - 16);
        unsigned int wind = READ_RTC_REG(RTC_GPIO_IN_REG, RTC_GPIO_IN_NEXT_S, 16) >> 14;

        rain &= 1;
        wind &= 1;

        if (rain != nextRainEdge) {
            rainDebounceCounter = DEBOUNCE_COUNT;
        }
        else
        {
            if (rainDebounceCounter)
            {
                rainDebounceCounter--;
            }
            else
            {
                /* EDGE DETECTED */
                rainDebounceCounter = DEBOUNCE_COUNT;

                if (nextRainEdge)
                {
                    rainTicks++;
                }

                nextRainEdge = !nextRainEdge;
            }
        }

        if (wind != nextWindEdge)
        {
            windDebounceCounter = DEBOUNCE_COUNT;
        }
        else
        {
            if (windDebounceCounter)
            {
                windDebounceCounter--;
            }
            else
            {
                /* EDGE DETECTED */
                windDebounceCounter = DEBOUNCE_COUNT;

                if (!nextWindEdge)
                {
                    windTicks++;
                }

                nextWindEdge = !nextWindEdge;
            }
        }

        wait(CYCLES_PER_MS);

        sample++;

        if (sample > SAMPLES_PER_READING)
        {
            sample = 0;

            windBuckets[reading] = windTicks;
            windTicks = 0;

            rainBuckets[reading] = rainTicks;
            rainTicks = 0;

            reading++;
        }

        if (reading >= MAX_READING)
        {
            break;
        }
    }
    
    wake_when_ready();
}
