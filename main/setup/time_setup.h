#ifndef C9B4CC57_21FB_48C8_A654_FB52227B1E01
#define C9B4CC57_21FB_48C8_A654_FB52227B1E01

#include <interaction.h>

class wifi_station;

class time_setup final : public interaction {
 public:
  time_setup(interaction& setup, wifi_station&, const char* ntp_srv) noexcept;
  void start(interaction_control&) override;

 private:
  void get_time();
  interaction& setup;
  wifi_station& station;
  const char* ntp_srv;
};

#endif /* C9B4CC57_21FB_48C8_A654_FB52227B1E01 */
