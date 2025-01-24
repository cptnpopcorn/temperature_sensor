#include "publisher.h"

#include <compressed_measurement.h>
#include <error.h>
#include <wifi_connection.h>

#include <sstream>

using namespace std;

publisher::publisher(const std::string &broker_uri, const std::string &topic)
    : client{nullptr}, topic{topic} {
  esp_mqtt_client_config_t config{};
  config.broker.address.uri = broker_uri.c_str();
  client = esp_mqtt_client_init(&config);
  if (client == nullptr) throw runtime_error("MQTT client creation");
  event_handle = mqtt_register_event(client, MQTT_EVENT_ANY, this,
                                     BOUNCE(publisher, handle_event));
  check(esp_mqtt_client_start(client), "MQTT start");
}

future<void> publisher::is_connected() noexcept {
  return connected.get_future();
}

bool publisher::publish(const compressed_measurement &m) {
  // TODO: format measurement as JSON
  ostringstream msg;
  const auto time = m.time();
  msg << R"({"time":")" << time << R"(","temp":)" << m.temperature()
      << R"(,"hum":)" << m.humidity() << R"(})";
  const auto str = msg.str();
  return esp_mqtt_client_publish(client, topic.c_str(), str.c_str(),
                                 str.length(), 0, 0) >= 0;
}

publisher::~publisher() {
  check(esp_mqtt_client_stop(client), "stop mqtt client");
  event_handle = {};
  check(esp_mqtt_client_destroy(client), "release mqtt client");
}

void publisher::handle_event(esp_event_base_t base, int32_t id, void *data) {
  switch (static_cast<esp_mqtt_event_id_t>(id)) {
    case MQTT_EVENT_CONNECTED:
      connected.set_value();
      return;
    default:
      return;
  }
}
