#ifndef F7D4BD4A_C0D5_4C88_8C82_EE087512AB85
#define F7D4BD4A_C0D5_4C88_8C82_EE087512AB85

#include <interaction.h>
#include <measurement_traits.h>

class sht;

class measurements_setup : public interaction {
 public:
  using buffer_t = measurement_traits::buffer_t;
  measurements_setup(interaction& setup, buffer_t& measurements,
                     sht& sensor) noexcept;
  void start(interaction_control&) override;

 private:
  interaction& setup;
  buffer_t& measurements;
  sht& sensor;
};

#endif /* F7D4BD4A_C0D5_4C88_8C82_EE087512AB85 */
