#ifndef B3C11C8D_4E28_41F5_956E_A7ABD223F8B3
#define B3C11C8D_4E28_41F5_956E_A7ABD223F8B3

#include <compressed_measurement.h>
#include <event_loop.h>
#include <nvs_access.h>
#include <ringbuffer.h>
#include <sht.h>
#include <wifi_station.h>

class app final {
 public:
  using buffer_t = ringbuffer<compressed_measurement, 512>;

  app(i2c_port_t port, gpio_num_t sda, gpio_num_t scl,
      const char* ntp_server_name, buffer_t& measurements) noexcept;

  app(const app&) = delete;
  app& operator=(const app&) = delete;

  void run();

 private:
  void prepare_console_input();
  void setup();
  event_loop evts;
  nvs_access nvs;
  sht sensor;
  wifi_station station;
  const char* const ntp_srv;
  buffer_t& measurements;
};
#endif /* B3C11C8D_4E28_41F5_956E_A7ABD223F8B3 */
