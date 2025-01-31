#include <esp_log.h>

#include <cstddef>
#include <cstring>
#include <iostream>
#include <stdexcept>

#include "../config.h"
#include "app.h"
#include "mqtt_config.h"

using namespace std;

const char* const tag = "app";

// cold boot assures zero-init, deep sleep will preserve content in RTC RAM
RTC_DATA_ATTR uint8_t measurements[sizeof(app::buffer_t)];

extern "C" {
void app_main(void) {
  ESP_LOGI(tag, "temperature sensor app starting...");

  try {
    app{{I2C_NUM_0, SDA_PIN, SCL_PIN},
        NTP_SRV,
        *reinterpret_cast<app::buffer_t*>(measurements),
        mqtt_config{MQTT_BROKER_HOSTNAME, MQTT_TOPIC_ROOT}}
        .run();
  } catch (const exception& e) {
    ESP_LOGE(tag, "%s", e.what());
  }
}
}
