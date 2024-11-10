#include "app.h"

#include <iostream>

using namespace std;

app::app(i2c_port_t port, gpio_num_t sda, gpio_num_t scl)
    : sensor{port, sda, scl}, nvs{} {}

void app::run() {
  cout << sensor.measure() << endl;
  cout.flush();
}