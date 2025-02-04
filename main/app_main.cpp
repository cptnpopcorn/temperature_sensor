#include <esp_log.h>
#include <sdkconfig.h>

#include <cstddef>
#include <cstring>
#include <iostream>
#include <stdexcept>

#include "app.h"
#include "mqtt_config.h"

using namespace std;

const char* const tag = "app";

// cold boot assures zero-init, deep sleep will preserve content in RTC RAM
RTC_DATA_ATTR uint8_t measurements[sizeof(app::buffer_t)];

#ifdef CONFIG_MQTT_USE_TLS
extern "C" {
extern const uint8_t _binary_ca_crt_start[] asm("_binary_ca_crt_start");
extern const uint8_t _binary_ca_crt_end[] asm("_binary_ca_crt_end");
}
span<const uint8_t> get_ca_crt() {
  return {&_binary_ca_crt_start[0], &_binary_ca_crt_end[0]};
}
#else
span<const uint8_t> get_ca_crt() { return {}; }
#endif

extern "C" {
void app_main(void) {
  ESP_LOGI(tag, "temperature sensor app starting...");

  try {
    app{{I2C_NUM_0, static_cast<gpio_num_t>(CONFIG_SDA_PIN),
         static_cast<gpio_num_t>(CONFIG_SCL_PIN)},
        CONFIG_NTP_SRV,
        *reinterpret_cast<app::buffer_t*>(measurements),
        mqtt_config{CONFIG_MQTT_BROKER_HOSTNAME, CONFIG_MQTT_TOPIC_ROOT,
                    get_ca_crt()}}
        .run();
  } catch (const exception& e) {
    ESP_LOGE(tag, "%s", e.what());
  }
}
}
