#include "measurement.h"

measurement::measurement(float temperature, float humidity) noexcept
    : temperature{temperature}, humidity{humidity} {}

using namespace std;

ostream &operator<<(ostream &os, const measurement &m) {
  return os << m.temperature << " °C, " << m.humidity << " %";
}