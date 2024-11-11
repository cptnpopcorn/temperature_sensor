#ifndef B37F705B_B5B7_48B1_B907_26A0650EC187
#define B37F705B_B5B7_48B1_B907_26A0650EC187

#include <string>

struct wifi_scan_result final {
  wifi_scan_result(std::string ssid) noexcept;
  std::string ssid;
};

#endif /* B37F705B_B5B7_48B1_B907_26A0650EC187 */
