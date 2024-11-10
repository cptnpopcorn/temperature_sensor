#ifndef B3C11C8D_4E28_41F5_956E_A7ABD223F8B3
#define B3C11C8D_4E28_41F5_956E_A7ABD223F8B3

#include <event_loop.h>
#include <nvs_access.h>
#include <sht.h>
#include <wifi_station.h>

class app final {
 public:
  app(i2c_port_t port, gpio_num_t sda, gpio_num_t scl);
  app(const app&) = delete;
  app& operator=(const app&) = delete;
  void run();

 private:
  event_loop evts;
  nvs_access nvs;
  sht sensor;
  wifi_station station;
};
#endif /* B3C11C8D_4E28_41F5_956E_A7ABD223F8B3 */
