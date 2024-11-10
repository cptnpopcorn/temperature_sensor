#include <driver/usb_serial_jtag.h>
#include <esp_log.h>

#include <stdexcept>

#include "../config.h"
#include "app.h"

using namespace std;

const char *tag = "app";

extern "C" {
void app_main(void) {
  ESP_LOGI(tag, "temperature sensor app starting...");

  if (usb_serial_jtag_is_connected())
    ESP_LOGI(tag, "board is connected via USB");

  try {
    app{I2C_NUM_0, SDA_PIN, SCL_PIN}.run();
  } catch (const exception &e) {
    ESP_LOGE(tag, "%s", e.what());
  }
}
}
