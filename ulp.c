#include <ulp_c.h>

#define DEBOUNCE_COUNT 10

unsigned int rainTicks = 0;
unsigned int nextRainEdge = 0;
unsigned int rainDebounceCounter = DEBOUNCE_COUNT;

unsigned int windTicks = 0;
unsigned int nextWindEdge = 0;
unsigned int windDebounceCounter = DEBOUNCE_COUNT;

unsigned int rainBuckets[300];
unsigned int windBuckets[300];

void entry()
{
    /**
     * 1. Read RTC registers
     * 2. Increment counts if necessary (this should be debounced.)
     * 3. If enough time has elapsed, flush to memory & reset counters.
     * */

    for (;;)
    {
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
        
    }
    
}
