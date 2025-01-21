#ifndef D79F3AD3_EFA1_4DC5_B3C0_1302E444E006
#define D79F3AD3_EFA1_4DC5_B3C0_1302E444E006

#include <chrono>
#include <cstdint>

class compressed_measurement final {
 public:
  using time_t = std::chrono::system_clock::time_point;

  compressed_measurement() = default;

  compressed_measurement(const time_t& time, float temperature,
                         float humidity) noexcept;

  compressed_measurement(uint64_t serialized) noexcept;

  time_t time() const noexcept;
  float temperature() const noexcept;
  float humidity() const noexcept;
  uint64_t serialize() const noexcept;

 private:
  uint64_t compressed;
};

#endif /* D79F3AD3_EFA1_4DC5_B3C0_1302E444E006 */
