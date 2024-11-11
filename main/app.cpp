#include "app.h"

#include <esp_task.h>

#include <iostream>

using namespace std;

app::app(i2c_port_t port, gpio_num_t sda, gpio_num_t scl)
    : evts{}, nvs{}, sensor{port, sda, scl}, station{evts, nvs} {}

void app::run() {
  while (true) {
    cout << sensor.measure() << endl;
    cout.flush();
    vTaskDelay(4000 / portTICK_PERIOD_MS);
  }
}