#pragma once

#include <string>

namespace WS_MQTT
{
  void start();
  void hello();
  void publish(std::string topic, std::string data);
}
