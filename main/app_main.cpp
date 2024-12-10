#include <esp_log.h>

#include <stdexcept>

#include "../config.h"
#include "app.h"

using namespace std;

const char* const tag = "app";

extern "C" {
void app_main(void) {
  ESP_LOGI(tag, "temperature sensor app starting...");

  try {
    app{I2C_NUM_0, SDA_PIN, SCL_PIN, NTP_SRV}.run();
  } catch (const exception& e) {
    ESP_LOGE(tag, "%s", e.what());
  }
}
}
