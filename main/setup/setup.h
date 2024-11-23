#ifndef D3378230_454A_49A6_817E_EDBBD4F9E645
#define D3378230_454A_49A6_817E_EDBBD4F9E645

#include <interaction.h>

#include "wifi_setup.h"

class setup final : public interaction {
 public:
  setup(interaction&, wifi_station&) noexcept;
  void start(interaction_control& control) override;

 private:
  interaction& stop;
  wifi_setup wifi;
};

#endif /* D3378230_454A_49A6_817E_EDBBD4F9E645 */
