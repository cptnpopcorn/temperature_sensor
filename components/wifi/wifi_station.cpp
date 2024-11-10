#include "wifi_station.h"

#include <error.h>
#include <esp_wifi.h>

wifi_station::wifi_station(event_loop&, nvs_access&) : interface{} {
  check(esp_netif_init(), "network interface initialization");
  interface = esp_netif_create_default_wifi_sta();
  if (interface == nullptr) error("WiFi station creation");
}

wifi_station::~wifi_station() noexcept {
  if (interface != nullptr) esp_netif_destroy(interface);
}
