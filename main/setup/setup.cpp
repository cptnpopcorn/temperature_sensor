#include "setup.h"

#include <driver/uart.h>
#include <driver/uart_vfs.h>
#include <error.h>
#include <esp_task.h>
#include <interaction_control.h>
#include <sdkconfig.h>

#include <iostream>
#include <string>

using namespace std;

setup::setup(interaction& stop, wifi_station& station) noexcept
    : stop{stop}, wifi{*this, station} {}

void setup::start(interaction_control& control) {
  cout << "sensor setup.." << endl;
  cout << "w - WiFi" << endl;
  cout << "q - quit" << endl;

  switch (cin.get()) {
    case 'w':
      control.set(wifi);
      return;
    case 'q':
      control.set(stop);
      return;
  }
}