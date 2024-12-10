#include "wifi_connection.h"

#include <error.h>
#include <esp_wifi.h>

using namespace std;

wifi_connection::wifi_connection(wifi_station& sta) : sta{sta} {
  wifi_event_handle =
      register_event(WIFI_EVENT, ESP_EVENT_ANY_ID, this,
                     BOUNCE(wifi_connection, handle_wifi_event));
  ip_event_handle = register_event(IP_EVENT, IP_EVENT_STA_GOT_IP, this,
                                   BOUNCE(wifi_connection, handle_ip_event));
  check(esp_wifi_start(), "WiFi start");
}

future<void> wifi_connection::is_up() { return up.get_future(); }

wifi_connection::~wifi_connection() { check(esp_wifi_stop(), "WiFi stop"); }

void wifi_connection::handle_wifi_event(esp_event_base_t base, int32_t id,
                                        void* data) {
  switch (id) {
    case WIFI_EVENT_STA_START:
      check(esp_wifi_connect(), "WiFi connect");
      return;
  }
}

void wifi_connection::handle_ip_event(esp_event_base_t base, int32_t id,
                                      void* data) {
  up.set_value();
}
