#include <compressed_measurement.h>

#include "unity.h"

using namespace std;
using namespace std::chrono;
using namespace std::chrono_literals;

TEST_CASE("test compressed measurement", "sht") {
  const auto time = sys_days({November / 11 / 2026}) + 7h + 15min + 47s;

  const auto temperature = 27.6015625f;
  const auto humidity = 11.677729457541771572442206454566f;
  const compressed_measurement c{time, temperature, humidity};
  const auto serialized = c.serialize();

  const auto seconds_since_2000 =
      duration_cast<seconds>(time - sys_days{January / 1 / 2000}).count();

  const auto degrees_128 = static_cast<int16_t>(temperature * 128);
  const auto humidity_frac = static_cast<uint16_t>(humidity * 655.35);

  TEST_ASSERT(serialized >> 32 == seconds_since_2000);
  TEST_ASSERT(static_cast<int16_t>(serialized >> 16) == degrees_128);
  TEST_ASSERT(static_cast<uint16_t>(serialized) == humidity_frac);

  const compressed_measurement cprime{serialized};

  TEST_ASSERT(cprime.time() == time);
  TEST_ASSERT(cprime.temperature() == temperature);
  TEST_ASSERT(cprime.humidity() == humidity);
}