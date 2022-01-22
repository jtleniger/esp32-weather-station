#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_sleep.h"
#include "esp_log.h"
#include "i2cdev.h"

#include "ulp.h"
#include "mqtt.h"
#include "wifi.h"
#include "battery.h"
#include "thp.h"
#include "ext_temp.h"
#include "wind_dir.h"
#include "lux.h"

static const char *TAG = "WS_MAIN";

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

    ESP_LOGI(TAG, "initializing sensors");
    ESP_ERROR_CHECK(i2cdev_init());
    WS_THP::init();
    WS_LUX::init();
    ESP_LOGI(TAG, "done");

    ESP_LOGI(TAG, "reading sensors");
    float int_temp, pressure, humidity, voltage, ext_temp, wind_dir;
    WS_THP::read(&int_temp, &pressure, &humidity);
    voltage = WS_BATTERY::voltage();
    ext_temp = WS_EXT_TEMP::temp_f();
    wind_dir = WS_WIND_DIR::direction();
    std::string wind_data = WS_ULP::raw_wind_data();
    std::string rain_data = WS_ULP::raw_rain_data();
    uint16_t lux = WS_LUX::lux();
    ESP_LOGI(TAG, "done");
    
    ESP_LOGI(TAG, "publishing data");
    WS_MQTT::publish("battery",   std::to_string(voltage));
    WS_MQTT::publish("int_temp",  std::to_string(int_temp));
    WS_MQTT::publish("pressure",  std::to_string(pressure));
    WS_MQTT::publish("humidity",  std::to_string(humidity));
    WS_MQTT::publish("ext_temp",  std::to_string(ext_temp));
    WS_MQTT::publish("lux",       std::to_string(lux));
    WS_MQTT::publish("wind_dir",  std::to_string(wind_dir));
    WS_MQTT::publish("raw_wind",  wind_data);
    WS_MQTT::publish("raw_rain",  rain_data);
    ESP_LOGI(TAG, "done");
  }

  WS_ULP::start();
}
