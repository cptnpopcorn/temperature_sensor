#include "wifi_station.h"

#include <error.h>
#include <esp_wifi.h>
#include <guard.h>

#include <string>

using namespace std;

wifi_station::wifi_station(event_loop&, nvs_access&) : interface{} {
  check(esp_netif_init(), "network interface initialization");

  interface = esp_netif_create_default_wifi_sta();
  if (interface == nullptr) error("WiFi station interface creation");

  wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
  check(esp_wifi_init(&cfg), "WiFi driver initialization");
  // check(esp_wifi_set_mode(WIFI_MODE_STA), "WiFi set AP mode");
  check(esp_wifi_start(), "WiFi start");
}

void wifi_station::scan(wifi_scan_monitor& monitor) {
  auto stop_scan = [] { esp_wifi_clear_ap_list(); };
  auto stop_guard = make_guard(stop_scan);
  check(esp_wifi_scan_start(nullptr, true), "WiFi scan");

  wifi_ap_record_t record{};
  while (true) {
    const auto err = esp_wifi_scan_get_ap_record(&record);
    if (err == ESP_FAIL) break;
    check(err, "WiFi scan results");
    monitor.add_result(
        wifi_scan_result{reinterpret_cast<const char*>(record.ssid)});
  }
}

wifi_station::~wifi_station() {
  check(esp_wifi_stop(), "WiFi stop");
  check(esp_wifi_deinit(), "WiFi driver release");
  if (interface != nullptr) esp_netif_destroy(interface);
}
