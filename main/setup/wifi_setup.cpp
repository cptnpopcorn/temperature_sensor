#include "wifi_setup.h"

#include <interaction_control.h>

#include <iostream>

#include "ap_selection.h"
#include "console_input.h"
#include "wifi_connection.h"
#include "wifi_station.h"

using namespace std;
using namespace std::literals;

wifi_setup::wifi_setup(interaction &setup, wifi_station &station) noexcept
    : setup{setup}, sta{station} {}

void wifi_setup::start(interaction_control &control) {
  cout << "WiFi setup.." << endl;
  cout << "c - show current config" << endl;
  cout << "s - select access point" << endl;
  cout << "t - test wifi connection" << endl;
  cout << "q - quit" << endl;

  switch (cin.get()) {
    case 'c':
      show_config();
      return;

    case 's':
      select_ap();
      return;

    case 't':
      test_connect();
      return;

    case 'q':
      control.set(setup);
      return;
  }
}

void wifi_setup::show_config() {
  const auto config = sta.get_config();
  cout << "current WiFi is [" << config.ssid << "] with password ["
       << config.passwd << ']' << endl;
}

void wifi_setup::select_ap() {
  cout << "scanning for access points..." << endl;
  ap_selection selection{};
  sta.scan(selection);
  selection.flush();

  auto ssid = selection.get_selected_ssid();
  if (ssid.empty()) {
    cout << "no access point was selected" << endl;
    return;
  }

  cout << "WiFi password: ";
  auto config = sta.get_config();
  config.ssid = ssid;
  config.passwd = console_read_line();
  cout << endl;

  sta.set_config(config);
}

void wifi_setup::test_connect() {
  cout << "connecting WiFi.." << endl;
  wifi_connection connection{sta};

  cout << "getting IP address.." << endl;
  auto is_up = connection.is_up();
  for ([[maybe_unused]] auto i = 10; i != 0; --i) {
    if (is_up.wait_for(1s) == future_status::ready) {
      cout << "address sucessfully assigned" << endl;
      return;
    }
    cout << '.';
    cout.flush();
  }
  cout << "timeout reached" << endl;
}
