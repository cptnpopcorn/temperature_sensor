#include "publisher.h"

#include <compressed_measurement.h>
#include <error.h>
#include <wifi_connection.h>

#include <sstream>

using namespace std;

publisher::publisher(const string &broker_host, const string &topic,
                     const span<const uint8_t> &ca_cert)
    : client{nullptr}, topic{topic} {
  esp_mqtt_client_config_t config{};
  config.broker.address.hostname = broker_host.c_str();
  config.broker.address.port = ca_cert.size() == 0 ? 1883 : 8883;
  config.broker.address.transport = MQTT_TRANSPORT_OVER_TCP;

  if (ca_cert.size() != 0) {
    config.broker.address.port = 8883;
    config.broker.address.transport = MQTT_TRANSPORT_OVER_SSL;
    config.broker.verification.certificate =
        reinterpret_cast<const char *>(ca_cert.data());
    config.broker.verification.certificate_len = ca_cert.size();
  } else {
    config.broker.address.port = 1883;
    config.broker.address.transport = MQTT_TRANSPORT_OVER_TCP;
  }

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
  ostringstream msg;
  const auto time = m.time();

  msg << R"({"time":")" << time << R"(","temp":)" << m.temperature()
      << R"(,"hum":)" << m.humidity() << R"(})";

  const auto str = msg.str();
  const auto id = esp_mqtt_client_publish(client, topic.c_str(), str.c_str(),
                                          str.length(), 1, 1);
  if (id < 0) return false;

  {
    unique_lock l{tx_lock};
    return tx_cond.wait_for(l, 1s, [&] { return publish_id == id; });
  }
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
    case MQTT_EVENT_PUBLISHED: {
      lock_guard guard{tx_lock};
      publish_id =
          (reinterpret_cast<const esp_mqtt_event_handle_t>(data))->msg_id;
    }
      tx_cond.notify_one();
      return;
    default:
      return;
  }
}
