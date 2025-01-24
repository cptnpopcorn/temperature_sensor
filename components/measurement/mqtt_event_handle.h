#ifndef C3B991B9_F59F_4926_9618_C254AE070411
#define C3B991B9_F59F_4926_9618_C254AE070411

#include <mqtt_client.h>

class mqtt_event_handle final {
 public:
  mqtt_event_handle() noexcept = default;
  mqtt_event_handle(esp_mqtt_client_handle_t client, esp_mqtt_event_id_t event,
                    esp_event_handler_t event_handler) noexcept;
  mqtt_event_handle(mqtt_event_handle&&) noexcept;
  mqtt_event_handle& operator=(mqtt_event_handle&&) noexcept;
  ~mqtt_event_handle();

 private:
  void swap(mqtt_event_handle&) noexcept;
  esp_mqtt_client_handle_t client{};
  esp_mqtt_event_id_t event{};
  esp_event_handler_t event_handler{};
};

mqtt_event_handle mqtt_register_event(esp_mqtt_client_handle_t client,
                                      esp_mqtt_event_id_t event, void* arg,
                                      esp_event_handler_t event_handler);

#endif /* C3B991B9_F59F_4926_9618_C254AE070411 */
