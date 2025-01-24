#include "event_handle.h"

#include <error.h>

#include <utility>

event_handle::event_handle(esp_event_base_t event_base, int32_t event_id,
                           esp_event_handler_instance_t instance) noexcept
    : event_base{event_base}, event_id{event_id}, instance{instance} {}

event_handle::event_handle(event_handle &&other) noexcept { swap(other); }

event_handle &event_handle::operator=(event_handle &&other) noexcept {
  event_handle tmp(std::move(other));
  swap(tmp);
  return *this;
}

event_handle::~event_handle() {
  if (instance == nullptr) return;
  check(esp_event_handler_instance_unregister(event_base, event_id, instance),
        "unregister handle");
}

void event_handle::swap(event_handle &other) noexcept {
  std::swap(event_base, other.event_base);
  std::swap(event_id, other.event_id);
  std::swap(instance, other.instance);
}

event_handle register_event(esp_event_base_t base, int32_t id, void *arg,
                            esp_event_handler_t handler) {
  esp_event_handler_instance_t instance{};
  check(esp_event_handler_instance_register(base, id, handler, arg, &instance),
        "register event handler");
  return {base, id, instance};
}