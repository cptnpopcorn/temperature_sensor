#include "ntp_sync.h"

#include <error.h>
#include <esp_netif_sntp.h>
#include <esp_sntp.h>

ntp_sync::ntp_sync(const char* ntp_server_name) {
  esp_sntp_config_t config = ESP_NETIF_SNTP_DEFAULT_CONFIG(ntp_server_name);
  config.start = true;
  config.smooth_sync = false;
  check(esp_netif_sntp_init(&config), "NTP init");
}

ntp_sync::~ntp_sync() { esp_netif_sntp_deinit(); }
