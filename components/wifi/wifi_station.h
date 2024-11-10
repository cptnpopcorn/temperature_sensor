#ifndef D94EF760_09CE_4814_B482_B4C111DE38E6
#define D94EF760_09CE_4814_B482_B4C111DE38E6

class event_loop;
class nvs_access;
struct esp_netif_obj;
typedef struct esp_netif_obj esp_netif_t;

class wifi_station final {
 public:
  wifi_station(event_loop&, nvs_access&);
  wifi_station(const wifi_station&) = delete;
  wifi_station& operator=(const wifi_station&) = delete;
  ~wifi_station() noexcept;

 private:
  esp_netif_t* interface;
};

#endif /* D94EF760_09CE_4814_B482_B4C111DE38E6 */
