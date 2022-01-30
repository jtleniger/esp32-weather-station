#pragma once

#include <string>

namespace WS_ULP
{
  void start();
  void print_readings();
  uint16_t rain_data();
  std::string raw_wind_data();
}