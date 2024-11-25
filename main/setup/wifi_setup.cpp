#include "wifi_setup.h"

#include <interaction_control.h>

#include <iostream>

#include "ap_selection.h"
#include "console_input.h"
#include "wifi_station.h"

using namespace std;

wifi_setup::wifi_setup(interaction &setup, wifi_station &station) noexcept
    : setup{setup}, station{station} {}

void wifi_setup::start(interaction_control &control) {
  cout << "WiFi setup.." << endl;
  cout << "c - show current config" << endl;
  cout << "s - select access point" << endl;
  cout << "q - quit" << endl;

  switch (cin.get()) {
    case 'c':
      show_config();
      return;
    case 's':
      select_ap();
      return;
    case 'q':
      control.set(setup);
      return;
  }
}

void wifi_setup::show_config() {
  const auto config = station.get_config();
  cout << "current WiFi is [" << config.ssid << "] with password ["
       << config.passwd << ']' << endl;
}

void wifi_setup::select_ap() {
  cout << "scanning for access points..." << endl;
  ap_selection selection{};
  station.scan(selection);
  selection.flush();

  auto ssid = selection.get_selected_ssid();
  if (ssid.empty()) {
    cout << "no access point was selected" << endl;
    return;
  }

  cout << "WiFi password: ";
  auto config = station.get_config();
  config.ssid = ssid;
  config.passwd = console_read_line();
  cout << endl;

  station.set_config(config);
}
