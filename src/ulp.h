#pragma once

#include <string>

namespace WS_ULP
{
  void start();
  void print_readings();
  std::string raw_rain_data();
  std::string raw_wind_data();
}