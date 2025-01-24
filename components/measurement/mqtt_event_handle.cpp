#include "mqtt_event_handle.h"

#include <error.h>

#include <utility>

mqtt_event_handle::mqtt_event_handle(esp_mqtt_client_handle_t client,
                                     esp_mqtt_event_id_t event,
                                     esp_event_handler_t event_handler) noexcept
    : client{client}, event{event}, event_handler{event_handler} {}

mqtt_event_handle::mqtt_event_handle(mqtt_event_handle&& o) noexcept {
  swap(o);
}

mqtt_event_handle& mqtt_event_handle::operator=(
    mqtt_event_handle&& o) noexcept {
  mqtt_event_handle tmp{std::move(o)};
  swap(tmp);
  return *this;
}

mqtt_event_handle::~mqtt_event_handle() {
  if (client == nullptr) return;
  check(esp_mqtt_client_unregister_event(client, event, event_handler),
        "unregister MQTT event handler");
}

void mqtt_event_handle::swap(mqtt_event_handle& o) noexcept {
  std::swap(client, o.client);
  std::swap(event, o.event);
  std::swap(event_handler, o.event_handler);
}

mqtt_event_handle mqtt_register_event(esp_mqtt_client_handle_t client,
                                      esp_mqtt_event_id_t event, void* arg,
                                      esp_event_handler_t event_handler) {
  check(esp_mqtt_client_register_event(client, event, event_handler, arg),
        "register MQTT event");
  return {client, event, event_handler};
}
