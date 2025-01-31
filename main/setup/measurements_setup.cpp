#include "measurements_setup.h"

#include <interaction_control.h>
#include <publisher.h>
#include <sht.h>
#include <wifi_connection.h>

#include <chrono>
#include <iostream>

#include "../mqtt_config.h"

using namespace std;
using namespace std::chrono;

measurements_setup::measurements_setup(interaction& setup,
                                       buffer_t& measurements,
                                       const sht_config& shtcfg,
                                       const mqtt_config& mqtt,
                                       wifi_station& wifi) noexcept
    : setup{setup},
      measurements{measurements},
      shtcfg{shtcfg},
      mqtt{mqtt},
      sta{wifi} {}

void measurements_setup::start(interaction_control& control) {
  cout << "Measurements setup (" << measurements.size()
       << " measurements present).." << endl;
  cout << "l - list measurements" << endl;
  cout << "a - add measurement now" << endl;
  cout << "m - show mqtt config" << endl;
  cout << "p - publish measurements" << endl;
  cout << "q - quit" << endl;

  switch (cin.get()) {
    case 'l':
      for (const auto& m : measurements) {
        const auto t = m.time();
        cout << t << ' ' << m.temperature() << " deg " << m.humidity() << " %"
             << endl;
      }
      return;

    case 'a': {
      sht sensor{shtcfg};
      const auto m = sensor.measure();
      cout << "measured " << m << endl;
      measurements.write({system_clock::now(), m.temperature, m.humidity});
    }
      return;

    case 'm':
      cout << "broker URI: " << mqtt.broker_host << endl;
      cout << "topic root: " << mqtt.topic_root << endl;
      return;

    case 'p':
      publish_measurements();
      return;

    case 'q':
      control.set(setup);
      return;
  }
}

void measurements_setup::publish_measurements() {
  cout << "connecting WiFi";
  wifi_connection connection{sta};

  auto is_wifi_up = connection.is_up();
  for ([[maybe_unused]] auto i = 10; i != 0; --i) {
    if (is_wifi_up.wait_for(1s) == future_status::ready) {
      cout << endl << "WiFi connected" << endl;
      const auto topic = mqtt.topic_root + "/setup";
      cout << "connecting to MQTT broker for topic " << topic;
      publisher pub{mqtt.broker_host, topic};

      auto is_mqtt_connected = pub.is_connected();
      for ([[maybe_unused]] auto j = 10; j != 0; --j) {
        if (is_mqtt_connected.wait_for(1s) == future_status::ready) {
          cout << endl << "MQTT connected" << endl;
          cout << "Publishing stored measurements" << endl;
          for (const auto& m : measurements) {
            if (!pub.publish(m)) {
              cout << "error while publishing" << endl;
              return;
            }
          }
          return;
        }
        cout << '.';
        cout.flush();
      }
      cout << endl << "MQTT connection timeout reached" << endl;
      return;
    }
    cout << '.';
    cout.flush();
  }
  cout << endl << "WiFi connection timeout reached" << endl;
}
