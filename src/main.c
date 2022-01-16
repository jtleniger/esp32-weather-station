#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp32/ulp.h"
#include "esp_sleep.h"
#include "ulp_main.h"
#include "driver/gpio.h"

extern const uint8_t ulp_main_bin_start[] asm("_binary_ulp_main_bin_start");
extern const uint8_t ulp_main_bin_end[] asm("_binary_ulp_main_bin_end");

extern uint32_t ulp_wind_readings;
extern uint32_t ulp_rain_readings;
extern uint32_t ulp_reading;
extern uint32_t ulp_sample;

void print_wakeup_reason()
{
  esp_sleep_wakeup_cause_t wakeup_reason;

  wakeup_reason = esp_sleep_get_wakeup_cause();

  switch (wakeup_reason)
  {
  case ESP_SLEEP_WAKEUP_EXT0:
    printf("Wakeup caused by external signal using RTC_IO\n");
    break;
  case ESP_SLEEP_WAKEUP_EXT1:
    printf("Wakeup caused by external signal using RTC_CNTL\n");
    break;
  case ESP_SLEEP_WAKEUP_TIMER:
    printf("Wakeup caused by timer\n");
    break;
  case ESP_SLEEP_WAKEUP_TOUCHPAD:
    printf("Wakeup caused by touchpad\n");
    break;
  case ESP_SLEEP_WAKEUP_ULP:
    printf("Wakeup caused by ULP program\n");
    break;
  default:
    printf("Wakeup was not caused by deep sleep: %d\n", wakeup_reason);
    break;
  }
}

const gpio_config_t config = {
    .pin_bit_mask = 1ULL << 25 | 1ULL << 14,
    .mode = GPIO_MODE_INPUT,
    .intr_type = GPIO_INTR_DISABLE,
    .pull_down_en = GPIO_PULLDOWN_DISABLE,
    .pull_up_en = GPIO_PULLUP_DISABLE};

void app_main(void)
{
  printf("\n");
  printf("good morno\n\n");
  print_wakeup_reason();

  esp_err_t err = gpio_config(&config);
  ESP_ERROR_CHECK(err);

  if (esp_sleep_get_wakeup_cause() == ESP_SLEEP_WAKEUP_ULP)
  {
    ulp_reading = 0;
    ulp_sample = 0;

    for (int i = 0; i < 30; i++)
    {
      printf("second:\t%d\train:\t%d\twind:\t%d\n", i + 1, (uint16_t)(&ulp_rain_readings)[i], (uint16_t)(&ulp_wind_readings)[i]);
    }
  }

  printf("good night\n\n");
  fflush(stdout);

  err = ulp_load_binary(0, ulp_main_bin_start, (ulp_main_bin_end - ulp_main_bin_start) / sizeof(uint32_t));
  ESP_ERROR_CHECK(err);

  ulp_set_wakeup_period(0, 20000);

  err = esp_sleep_enable_ulp_wakeup();
  ESP_ERROR_CHECK(err);

  err = ulp_run(&ulp_entry - RTC_SLOW_MEM);
  ESP_ERROR_CHECK(err);

  esp_deep_sleep_start();
}
