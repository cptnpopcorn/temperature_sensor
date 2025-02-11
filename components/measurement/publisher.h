#ifndef CDACBA4B_D388_466A_B067_47BDC8E72930
#define CDACBA4B_D388_466A_B067_47BDC8E72930

#include <mqtt_event_handle.h>

#include <condition_variable>
#include <cstdint>
#include <future>
#include <mutex>
#include <span>
#include <string>

class compressed_measurement;
class wifi_connection;

class publisher final {
 public:
  publisher(const std::string& broker_host, const std::string& topic,
            const std::span<const uint8_t>& ca_cert,
            const std::span<const uint8_t>& client_cert,
            const std::span<const uint8_t>& client_key);

  std::future<void> is_connected() noexcept;
  bool publish(const compressed_measurement&);
  ~publisher();

 private:
  void handle_event(esp_event_base_t base, int32_t id, void* data);
  std::promise<void> connected;
  esp_mqtt_client_handle_t client;
  mqtt_event_handle event_handle;
  std::string topic;
  std::mutex tx_lock;
  std::condition_variable tx_cond;
  int publish_id;
};

#endif /* CDACBA4B_D388_466A_B067_47BDC8E72930 */
