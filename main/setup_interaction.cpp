#include "setup_interaction.h"

#include <driver/uart.h>
#include <driver/uart_vfs.h>
#include <error.h>
#include <esp_task.h>
#include <sdkconfig.h>

#include <iostream>
#include <string>

using namespace std;

bool setup_interaction::start(interaction_control& control) {
  cout << "sensor setup.." << endl;
  cout << "q - quit" << endl;

  switch (cin.get()) {
    case 'q':
      return false;
    default:
      return true;
  }
}