#include "app.h"

#include <iostream>

using namespace std;

app::app(i2c_port_t port, gpio_num_t sda, gpio_num_t scl)
    : evts{}, nvs{}, sensor{port, sda, scl}, station{evts, nvs} {}

void app::run() {
  cout << sensor.measure() << endl;
  cout.flush();
}