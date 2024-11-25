#ifndef D94EF760_09CE_4814_B482_B4C111DE38E6
#define D94EF760_09CE_4814_B482_B4C111DE38E6

#include "wifi_config.h"
#include "wifi_scan_visitor.h"

class event_loop;
class nvs_access;
struct esp_netif_obj;
typedef struct esp_netif_obj esp_netif_t;

class wifi_station final {
 public:
  wifi_station(event_loop&, nvs_access&);

  wifi_station(const wifi_station&) = delete;
  wifi_station& operator=(const wifi_station&) = delete;

  void scan(wifi_scan_visitor& monitor);
  wifi_config get_config();
  void set_config(const wifi_config&);

  ~wifi_station();

 private:
  esp_netif_t* interface;
};

#endif /* D94EF760_09CE_4814_B482_B4C111DE38E6 */
