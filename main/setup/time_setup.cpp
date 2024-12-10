#include "time_setup.h"

#include <esp_task.h>
#include <interaction_control.h>
#include <ntp_sync.h>
#include <wifi_connection.h>

#include <ctime>
#include <iostream>

using namespace std;

time_setup::time_setup(interaction& setup, wifi_station& station,
                       const char* ntp_srv) noexcept
    : setup{setup}, station{station}, ntp_srv{ntp_srv} {}

void time_setup::start(interaction_control& control) {
  cout << "Time setup.." << endl;
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
  wifi_connection connection{};
  cout << "connecting to WiFi AP.." << endl;
  auto is_up = connection.is_up();
  for ([[maybe_unused]] auto i = 10; i != 0; --i) {
    if (is_up.wait_for(1s) == future_status::ready) {
      cout << "IP address sucessfully assigned, synchronizing with NTP server"
           << endl;
      ntp_sync ntp{ntp_srv};
      for (auto i = 0; i < 20; ++i) {
        const auto t = time(nullptr);
        cout << "time " << ctime(&t) << endl;
        vTaskDelay(1000 / portTICK_PERIOD_MS);
      }
      return;
    }
    cout << '.';
    cout.flush();
  }
  cout << "timeout reached" << endl;
}
