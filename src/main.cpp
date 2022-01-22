#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_sleep.h"
#include "esp_log.h"

#include "ulp.h"
#include "mqtt.h"
#include "wifi.h"
#include "battery.h"
#include "thp.h"
#include "ext_temp.h"
#include "wind_dir.h"

static const char *TAG = "WS_MAIN";

extern "C"
{
  void app_main(void);
}

void app_main(void)
{
  // WS_THP::init();

  for (;;)
  {
    vTaskDelay(1000 / portTICK_PERIOD_MS);

    ESP_LOGI(TAG, "v: %.1f", WS_WIND_DIR::direction());

    // ESP_LOGI(TAG, "v: %f", WS_BATTERY::voltage());

    // float pressure, temperature, humidity;

    // WS_THP::read(&temperature, &pressure, &humidity);

    // ESP_LOGI(TAG, "temp: %f pres: %f hum: %f", temperature, pressure, humidity);
  }
  

  // if (esp_sleep_get_wakeup_cause() == ESP_SLEEP_WAKEUP_ULP)
  // {
  //   WS_WIFI::init_nvs();
  //   WS_WIFI::connect_wifi();
  //   WS_MQTT::start();
  //   WS_MQTT::hello();
    
  //   ESP_LOGI(TAG, "publishing data");
  //   WS_MQTT::publish("battery", std::to_string(WS_BATTERY::voltage()));
  //   WS_MQTT::publish("wind", WS_ULP::raw_wind_data());
  //   WS_MQTT::publish("rain", WS_ULP::raw_rain_data());
  //   ESP_LOGI(TAG, "done");
  // }

  // WS_ULP::start();
}
