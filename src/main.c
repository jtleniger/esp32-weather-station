#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp32/ulp.h"
#include "esp_sleep.h"
#include "ulp_main.h"
#include "driver/rtc_io.h"

extern const uint8_t ulp_main_bin_start[] asm("_binary_ulp_main_bin_start");
extern const uint8_t ulp_main_bin_end[] asm("_binary_ulp_main_bin_end");

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

void init_ulp_vars()
{
  for (int i = 0; i < 10; i++)
  {
    (&ulp_rain_readings)[i] = 0;
    (&ulp_wind_readings)[i] = 0;
  }
}

void app_main(void)
{
  printf("\n");
  printf("good morno\n\n");
  print_wakeup_reason();

  esp_err_t err;
  
  err = rtc_gpio_init(25);
  ESP_ERROR_CHECK(err);

  err = gpio_set_pull_mode(25, GPIO_FLOATING);
  ESP_ERROR_CHECK(err);

  err = rtc_gpio_set_direction(25, RTC_GPIO_MODE_INPUT_ONLY);
  ESP_ERROR_CHECK(err);

  err = rtc_gpio_init(14);
  ESP_ERROR_CHECK(err);

  err = gpio_set_pull_mode(14, GPIO_FLOATING);
  ESP_ERROR_CHECK(err);

  err = rtc_gpio_set_direction(14, RTC_GPIO_MODE_INPUT_ONLY);
  ESP_ERROR_CHECK(err);

  if (esp_sleep_get_wakeup_cause() == ESP_SLEEP_WAKEUP_ULP)
  {
    for (int i = 0; i < 10; i++)
    {
      printf("second:\t%d\train:\t%d\twind:\t%d\n", i + 1, (uint16_t)(&ulp_rain_readings)[i], (uint16_t)(&ulp_wind_readings)[i]);
    }
  }

  printf("good night\n\n");
  fflush(stdout);

  err = ulp_load_binary(0, ulp_main_bin_start, (ulp_main_bin_end - ulp_main_bin_start) / sizeof(uint32_t));
  ESP_ERROR_CHECK(err);

  init_ulp_vars();

  ulp_set_wakeup_period(0, 500000);

  err = esp_sleep_enable_ulp_wakeup();
  ESP_ERROR_CHECK(err);

  err = ulp_run(&ulp_entry - RTC_SLOW_MEM);
  ESP_ERROR_CHECK(err);

  // vTaskDelay(11000 / portTICK_PERIOD_MS);

  // for (int i = 0; i < 10; i++)
  // {
  //   printf("second:\t%d\train:\t%d\twind:\t%d\n", i + 1, (uint16_t)(&ulp_rain_readings)[i], (uint16_t)(&ulp_wind_readings)[i]);
  // }
  
  esp_deep_sleep_start();
}
