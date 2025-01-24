#ifndef D3378230_454A_49A6_817E_EDBBD4F9E645
#define D3378230_454A_49A6_817E_EDBBD4F9E645

#include <interaction.h>

#include "measurements_setup.h"
#include "time_setup.h"
#include "wifi_setup.h"

class setup final : public interaction {
 public:
  setup(interaction& stop, wifi_station& station, const char* ntp_srv,
        measurement_traits::buffer_t& measurements, sht& sensor) noexcept;

  void start(interaction_control& control) override;

 private:
  interaction& stop;
  wifi_setup wifi;
  time_setup time;
  measurements_setup measurements;
};

#endif /* D3378230_454A_49A6_817E_EDBBD4F9E645 */
