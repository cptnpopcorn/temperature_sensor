#include "measurements_setup.h"

#include <interaction_control.h>
#include <sht.h>

#include <chrono>
#include <iostream>

using namespace std;
using namespace std::chrono;

measurements_setup::measurements_setup(interaction& setup,
                                       buffer_t& measurements,
                                       sht& sensor) noexcept
    : setup{setup}, measurements{measurements}, sensor{sensor} {}

void measurements_setup::start(interaction_control& control) {
  cout << "Measurements setup (" << measurements.size()
       << " measurements present).." << endl;
  cout << "l - list measurements" << endl;
  cout << "a - add measurement now" << endl;
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
      const auto m = sensor.measure();
      cout << "measured " << m << endl;
      measurements.write({system_clock::now(), m.temperature, m.humidity});
    }
      return;

    case 'q':
      control.set(setup);
      return;
  }
}
