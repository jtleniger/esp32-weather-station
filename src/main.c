#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp32/ulp.h"
#include "esp_sleep.h"
#include "ulp_main.h"

#include "esp_system.h"
#include "esp_spi_flash.h"

extern const uint8_t ulp_main_bin_start[] asm("_binary_ulp_main_bin_start");
extern const uint8_t ulp_main_bin_end[]   asm("_binary_ulp_main_bin_end");

extern uint32_t ulp_rainBuckets;
extern uint32_t ulp_windBuckets;

extern uint32_t ulp_reading;
extern uint32_t ulp_sample;

void app_main(void)
{
    // /* Print array values */
    // printf("Rain readings:");

    // for (int i = 0; i < 300; i++)
    // {
    //     printf("minute: %d ticks: %d\n", i + 1, (uint16_t)(&ulp_rainBuckets)[i]);
    // }

    // printf("Wind readings:");

    // for (int i = 0; i < 300; i++)
    // {
    //     printf("minute: %d ticks: %d\n", i + 1, (uint16_t)(&ulp_windBuckets)[i]);
    // }

    /* Load ULP Binary */
    // esp_err_t err = ulp_load_binary(0, ulp_main_bin_start, (ulp_main_bin_end - ulp_main_bin_start) / sizeof(uint32_t));
    // ESP_ERROR_CHECK(err);

    // /* Set ULP wake up period to T = 20ms. */
    // ulp_set_wakeup_period(0, 20000);

    // err = esp_sleep_enable_ulp_wakeup();
    // ESP_ERROR_CHECK(err);

    // /* Start ULP program */
    // err = ulp_run(&ulp_entry - RTC_SLOW_MEM);
    // ESP_ERROR_CHECK(err);
}