#include "wifi_setup.h"

#include <interaction_control.h>

#include <iostream>

using namespace std;

wifi_setup::wifi_setup(interaction &setup, wifi_station &station) noexcept
    : setup{setup}, station{station} {}

void wifi_setup::start(interaction_control &control) {
  cout << "WiFi setup.." << endl;
  cout << "s - select access point" << endl;
  cout << "q - quit" << endl;

  switch (cin.get()) {
    case 's':
      select_ap();
      return;
    case 'q':
      control.set(setup);
      return;
  }
}

void wifi_setup::select_ap() {}