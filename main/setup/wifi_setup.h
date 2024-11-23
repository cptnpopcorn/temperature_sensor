#ifndef FA04B43A_69A4_4113_89A4_6CAB2F488BED
#define FA04B43A_69A4_4113_89A4_6CAB2F488BED

#include <interaction.h>

class wifi_station;

class wifi_setup final : public interaction {
 public:
  wifi_setup(interaction&, wifi_station&) noexcept;
  void start(interaction_control&);

 private:
  void select_ap();
  interaction& setup;
  wifi_station& station;
};

#endif /* FA04B43A_69A4_4113_89A4_6CAB2F488BED */
