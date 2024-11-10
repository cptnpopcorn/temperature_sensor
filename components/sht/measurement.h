#ifndef D7B99FF4_6FF7_4240_8590_85CAD33533C5
#define D7B99FF4_6FF7_4240_8590_85CAD33533C5

#include <iostream>

struct measurement final {
  measurement() noexcept = default;
  measurement(float temperature, float humidity) noexcept;

  float temperature;
  float humidity;
};

std::ostream &operator<<(std::ostream &os, const measurement &m);

#endif /* D7B99FF4_6FF7_4240_8590_85CAD33533C5 */
