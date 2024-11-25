#ifndef A286E833_2778_4E75_8522_DAC08FFD52BE
#define A286E833_2778_4E75_8522_DAC08FFD52BE

#include <string>

struct wifi_config final {
  wifi_config(const std::string& ssid, const std::string& passwd);
  wifi_config(const std::string&& ssid, const std::string&& passwd) noexcept;
  std::string ssid;
  std::string passwd;
};

#endif /* A286E833_2778_4E75_8522_DAC08FFD52BE */
