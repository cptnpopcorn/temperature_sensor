#include "ntp_sync.h"

#include <bounce.h>
#include <error.h>
#include <esp_netif_sntp.h>
#include <esp_sntp.h>

using namespace std;

ntp_sync* instance{};

ntp_sync::ntp_sync(const char* ntp_server_name) {
  esp_sntp_config_t config = ESP_NETIF_SNTP_DEFAULT_CONFIG(ntp_server_name);
  config.start = true;
  config.smooth_sync = false;
  config.sync_cb = bounce_synchronized;
  check(esp_netif_sntp_init(&config), "NTP init");
  instance = this;
}

void ntp_sync::bounce_synchronized(timeval* tv) {
  if (instance != nullptr) instance->synchronized(tv);
}

void ntp_sync::synchronized(timeval* tv) { up.set_value(); }

future<void> ntp_sync::is_synchronized() { return up.get_future(); }

ntp_sync::~ntp_sync() {
  esp_netif_sntp_deinit();
  instance = {};
}
