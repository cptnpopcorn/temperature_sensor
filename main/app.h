#ifndef B3C11C8D_4E28_41F5_956E_A7ABD223F8B3
#define B3C11C8D_4E28_41F5_956E_A7ABD223F8B3

#include <event_loop.h>
#include <measurement_traits.h>
#include <sht_config.h>
#include <wifi_station.h>

#include "mqtt_config.h"

class nvs_access;

class app final
{
  public:
    using buffer_t = measurement_traits::buffer_t;

    app(const sht_config &shtcfg, const char *ntp_server_name, buffer_t &measurements, nvs_access &nvs,
        const mqtt_config &mqtt);

    app(const app &) = delete;
    app &operator=(const app &) = delete;

    void run();

  private:
    void setup();
    void prepare_console_input();
    event_loop evts;
    nvs_access &nvs;
    sht_config shtcfg;
    wifi_station station;
    const char *const ntp_srv;
    buffer_t &measurements;
    const mqtt_config mqtt;
};
#endif /* B3C11C8D_4E28_41F5_956E_A7ABD223F8B3 */
