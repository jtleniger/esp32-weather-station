#include <stdio.h>
#include <string.h>
#include "mqtt_client.h"
#include "esp_log.h"

#include "mqtt.h"

namespace
{
  static const char *TAG = "WS_MQTT";
}

void WS_MQTT::start()
{
  esp_mqtt_client_config_t mqtt_cfg = { };
  mqtt_cfg.uri = "mqtt://192.168.0.99";

  esp_mqtt_client_handle_t client = esp_mqtt_client_init(&mqtt_cfg);
  ESP_ERROR_CHECK(esp_mqtt_client_start(client));

  ESP_LOGI(TAG, "connected");
}