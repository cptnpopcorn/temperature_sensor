#ifndef C62B6660_F29E_4277_A20C_3DECCE57925B
#define C62B6660_F29E_4277_A20C_3DECCE57925B

#include <event_handle.h>

#include <future>

class wifi_station;

class wifi_connection final {
 public:
  wifi_connection(wifi_station&);
  wifi_connection(const wifi_connection&) = delete;
  wifi_connection& operator=(wifi_connection&) = delete;
  std::future<void> is_up();
  ~wifi_connection();

 private:
  void handle_wifi_event(esp_event_base_t base, int32_t id, void* data);
  void handle_ip_event(esp_event_base_t base, int32_t id, void* data);
  event_handle wifi_event_handle;
  event_handle ip_event_handle;
  std::promise<void> up;
  wifi_station& sta;
};

#endif /* C62B6660_F29E_4277_A20C_3DECCE57925B */
