#include "time_setup.h"

#include <esp_task.h>
#include <interaction_control.h>
#include <ntp_sync.h>
#include <wifi_connection.h>

#include <chrono>
#include <iostream>

using namespace std;
using namespace std::chrono;

time_setup::time_setup(interaction& setup, wifi_station& station,
                       const char* ntp_srv) noexcept
    : setup{setup}, station{station}, ntp_srv{ntp_srv} {}

void time_setup::start(interaction_control& control) {
  const auto time = system_clock::now();
  cout << "Time setup.. " << time << endl;
  cout << "t - get NTP time" << endl;
  cout << "q - quit" << endl;

  switch (cin.get()) {
    case 't':
      get_time();
      return;
    case 'q':
      control.set(setup);
      return;
  }
}

void time_setup::get_time() {
  wifi_connection connection{station};
  cout << "connecting to WiFi AP.." << endl;
  auto is_up = connection.is_up();

  for ([[maybe_unused]] auto i = 20; i != 0; --i) {
    if (is_up.wait_for(1s) == future_status::ready) {
      cout << "IP address sucessfully assigned, synchronizing with NTP server"
           << endl;
      ntp_sync ntp{ntp_srv};
      auto is_synced = ntp.is_synchronized();

      for ([[maybe_unused]] auto i = 0; i < 40; ++i) {
        if (is_synced.wait_for(1s) == future_status::ready) {
          const auto time = system_clock::now();
          cout << "time server contacted, current time is " << time << endl;
          return;
        }
        cout << '.';
        cout.flush();
      }
      cout << "time server could not be contacted" << endl;
      return;
    }
    cout << '.';
    cout.flush();
  }

  cout << "timeout reached" << endl;
}
