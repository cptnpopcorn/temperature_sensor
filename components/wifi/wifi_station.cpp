#include "wifi_station.h"

#include <error.h>
#include <esp_wifi.h>
#include <guard.h>

#include <algorithm>
#include <array>
#include <string>

using namespace std;

wifi_station::wifi_station(event_loop&, nvs_access&) : interface{} {
  check(esp_netif_init(), "network interface initialization");

  interface = esp_netif_create_default_wifi_sta();
  if (interface == nullptr) error("WiFi station interface creation");

  wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
  check(esp_wifi_init(&cfg), "WiFi driver initialization");
}

void wifi_station::scan(wifi_scan_visitor& monitor) {
  check(esp_wifi_start(), "WiFi start");
  auto stop_scan = [] {
    check(esp_wifi_clear_ap_list(), "WiFi clear scan list");
    check(esp_wifi_stop(), "WiFi stop after scan");
  };
  auto stop_guard = make_guard(stop_scan);
  check(esp_wifi_scan_start(nullptr, true), "WiFi scan");

  wifi_ap_record_t record{};
  while (true) {
    const auto err = esp_wifi_scan_get_ap_record(&record);
    if (err == ESP_FAIL) break;
    check(err, "WiFi scan results");
    if (monitor.continue_with_result(
            wifi_scan_result{reinterpret_cast<const char*>(record.ssid)}))
      continue;
    return;
  }
}

wifi_config wifi_station::get_config() {
  wifi_config_t config{};
  check(esp_wifi_get_config(WIFI_IF_STA, &config), "WiFi get config");

  const auto ssid = to_array(config.sta.ssid);
  const auto pw = to_array(config.sta.password);

  return {{ssid.cbegin(), ssid.cend()}, {pw.cbegin(), pw.cend()}};
}

void wifi_station::set_config(const wifi_config& config) {
  wifi_config_t nc{};
  nc.sta.threshold.authmode = WIFI_AUTH_WPA2_PSK;
  nc.sta.sae_pwe_h2e = WPA3_SAE_PWE_HUNT_AND_PECK;

  const auto ssid = config.ssid.substr(0, size(nc.sta.ssid));
  fill(copy(ssid.cbegin(), ssid.cend(), begin(nc.sta.ssid)), end(nc.sta.ssid),
       0);

  const auto pw = config.passwd.substr(0, size(nc.sta.password));
  fill(copy(pw.cbegin(), pw.cend(), begin(nc.sta.password)),
       end(nc.sta.password), 0);

  check(esp_wifi_set_config(WIFI_IF_STA, &nc), "WiFi set config");
}

wifi_station::~wifi_station() {
  check(esp_wifi_deinit(), "WiFi driver release");
  if (interface != nullptr) esp_netif_destroy(interface);
}
