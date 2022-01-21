#include "esp32/ulp.h"
#include "esp_sleep.h"
#include "ulp_main.h"
#include "driver/rtc_io.h"
#include "esp_log.h"

#include "ulp.h"

namespace
{
  static const char *TAG = "ULP";

  const uint16_t ULP_READINGS = 300;

  const gpio_num_t WIND_SPEED_PIN = GPIO_NUM_14;
  const gpio_num_t RAIN_PIN = GPIO_NUM_25;

  extern const uint8_t ulp_main_bin_start[] asm("_binary_ulp_main_bin_start");
  extern const uint8_t ulp_main_bin_end[] asm("_binary_ulp_main_bin_end");

  void set_rtc_gpio_floating_input(gpio_num_t pin)
  {
    esp_err_t err = rtc_gpio_init(pin);
    ESP_ERROR_CHECK(err);

    err = gpio_set_pull_mode(pin, GPIO_FLOATING);
    ESP_ERROR_CHECK(err);

    err = rtc_gpio_set_direction(pin, RTC_GPIO_MODE_INPUT_ONLY);
    ESP_ERROR_CHECK(err);
  }

  void init_pins()
  {
    set_rtc_gpio_floating_input(WIND_SPEED_PIN);
    set_rtc_gpio_floating_input(RAIN_PIN);
  }

  void clear_readings()
  {
    for (int i = 0; i < ULP_READINGS; i++)
    {
      (&ulp_rain_readings)[i] = 0;
      (&ulp_wind_readings)[i] = 0;
    }
  }
}

void ULP::start()
{
  ESP_LOGV(TAG, "Loading ULP binary");
  esp_err_t err = ulp_load_binary(0, ulp_main_bin_start, (ulp_main_bin_end - ulp_main_bin_start) / sizeof(uint32_t));
  ESP_ERROR_CHECK(err);

  ESP_LOGV(TAG, "Setting pin modes and wakeup settings");
  init_pins();
  clear_readings();

  ulp_set_wakeup_period(0, 500000);

  err = esp_sleep_enable_ulp_wakeup();
  ESP_ERROR_CHECK(err);

  ESP_LOGV(TAG, "Starting ULP");
  err = ulp_run(&ulp_entry - RTC_SLOW_MEM);
  ESP_ERROR_CHECK(err);

  ESP_LOGI(TAG, "Entering sleep");
  esp_deep_sleep_start();
}

void ULP::print_readings()
{
  for (int i = 0; i < ULP_READINGS; i++)
  {
    printf("second:\t%d\train:\t%d\twind:\t%d\n", i + 1, (uint16_t)(&ulp_rain_readings)[i], (uint16_t)(&ulp_wind_readings)[i]);
  }

  fflush(stdout);
}
