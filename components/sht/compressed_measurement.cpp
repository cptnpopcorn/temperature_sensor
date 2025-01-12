#include "compressed_measurement.h"

#include <cmath>

using namespace std;
using namespace std::chrono;
using namespace std::literals;

constexpr uint64_t compress(uint32_t seconds_since_2000,
                            int16_t temperature_frac128_deg,
                            uint16_t humidity_frac) noexcept {
  return static_cast<uint64_t>(seconds_since_2000) << 32 |
         static_cast<uint64_t>(temperature_frac128_deg) << 16 |
         static_cast<uint64_t>(humidity_frac);
}

constexpr uint32_t extract_seconds_since_2000(uint64_t compressed) noexcept {
  return static_cast<uint32_t>(compressed >> 32);
}

constexpr int16_t extract_temparature_frac128_deg(
    uint64_t compressed) noexcept {
  return static_cast<int16_t>(compressed >> 16);
}

constexpr uint16_t extract_humidity_frac(uint64_t compressed) {
  return static_cast<uint16_t>(compressed);
}

compressed_measurement::compressed_measurement(const time_t& time,
                                               float temperature,
                                               float humidity) noexcept
    : compressed{compress(
          static_cast<uint32_t>(
              duration_cast<seconds>(time - sys_days{January / 1 / 2000})
                  .count()),
          static_cast<int16_t>(round(temperature * 128)),
          static_cast<uint16_t>(
              round(humidity * (numeric_limits<uint16_t>::max() / 100.0f))))} {}

compressed_measurement::compressed_measurement(uint64_t serialized) noexcept
    : compressed{serialized} {}

uint64_t compressed_measurement::serialize() const noexcept {
  return compressed;
}

compressed_measurement::time_t compressed_measurement::time() const noexcept {
  return sys_days{January / 1 / 2000} +
         seconds(extract_seconds_since_2000(compressed));
}

float compressed_measurement::temperature() const noexcept {
  return extract_temparature_frac128_deg(compressed) * (1.0f / 128);
}

float compressed_measurement::humidity() const noexcept {
  return extract_humidity_frac(compressed) *
         (100.f / numeric_limits<uint16_t>::max());
}
