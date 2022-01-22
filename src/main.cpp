#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_sleep.h"

#include "ulp.h"
#include "mqtt.h"
#include "wifi.h"

extern "C"
{
  void app_main(void);
}

void app_main(void)
{
  if (esp_sleep_get_wakeup_cause() == ESP_SLEEP_WAKEUP_ULP)
  {
    WS_WIFI::init_nvs();
    WS_WIFI::connect_wifi();
    WS_MQTT::start();
    WS_MQTT::hello();
    
    WS_MQTT::publish("wind", WS_ULP::raw_wind_data());
    WS_MQTT::publish("rain", WS_ULP::raw_rain_data());
  }

  WS_ULP::start();
}
