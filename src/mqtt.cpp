#include <stdio.h>
#include <string>
#include <string.h>
#include "mqtt_client.h"
#include "esp_log.h"

#include "mqtt.h"

namespace
{
  static const char *TAG = "WS_MQTT";
  static const std::string BASE_TOPIC = "weather/";
  esp_mqtt_client_handle_t client;
}

void WS_MQTT::start()
{
  esp_mqtt_client_config_t mqtt_cfg = { };
  mqtt_cfg.uri = "mqtt://192.168.0.99";

  client = esp_mqtt_client_init(&mqtt_cfg);
  ESP_ERROR_CHECK(esp_mqtt_client_start(client));

  ESP_LOGI(TAG, "connected");
}

void WS_MQTT::hello()
{
  ESP_LOGD(TAG, "sending hello");

  std::string topic = "hello";
  std::string data = "hello";
  
  publish(topic, data);
}

void WS_MQTT::publish(std::string topic, std::string data)
{
  esp_mqtt_client_publish(client, (BASE_TOPIC + topic).c_str(), data.c_str(), 0, 1, false);
}