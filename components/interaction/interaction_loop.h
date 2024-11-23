#ifndef F481D526_B920_4A00_A6DC_3924A0C17FF1
#define F481D526_B920_4A00_A6DC_3924A0C17FF1

#include <interaction.h>

#include "interaction_control.h"

class interaction_loop final : private interaction_control {
 public:
  interaction_loop() noexcept;

  void set(interaction& next) override;
  void start();
  interaction& stop() noexcept;

 private:
  class stop_interaction final : public interaction {
   public:
    stop_interaction(interaction_loop&) noexcept;
    stop_interaction(const stop_interaction&) = delete;
    stop_interaction& operator=(const stop_interaction&) = delete;

    void start(interaction_control&) override;

   private:
    interaction_loop& loop;
  };

  friend class stop_interaction;

  bool stop_loop;
  interaction* next;
  stop_interaction stop_interaction;
};

#endif /* F481D526_B920_4A00_A6DC_3924A0C17FF1 */
