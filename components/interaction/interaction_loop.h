#ifndef F481D526_B920_4A00_A6DC_3924A0C17FF1
#define F481D526_B920_4A00_A6DC_3924A0C17FF1

#include "interaction_control.h"

class interaction_loop final : private interaction_control {
 public:
  interaction_loop() noexcept;
  void set(interaction& next) override;
  void start();

 private:
  interaction* next;
};

#endif /* F481D526_B920_4A00_A6DC_3924A0C17FF1 */
