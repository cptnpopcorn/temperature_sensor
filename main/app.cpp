#include "app.h"

#include <driver/usb_serial_jtag.h>
#include <esp_log.h>
#include <esp_system.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include <iostream>
#include <stdexcept>

using namespace std;
const char *tag = "app";

extern "C" {
void app_main(void) {
  ESP_LOGI(tag, "temperature sensor app starting...");

  if (usb_serial_jtag_is_connected())
    ESP_LOGI(tag, "board is connected via USB");

  try {
    app{I2C_NUM_0, GPIO_NUM_19, GPIO_NUM_20}.run();
  } catch (const exception &e) {
    ESP_LOGE(tag, "%s", e.what());
  }
}
}

app::app(i2c_port_t port, gpio_num_t sda, gpio_num_t scl)
    : sensor{port, sda, scl} {}

void app::run() {
  cout << sensor.measure() << endl;
  cout.flush();
}