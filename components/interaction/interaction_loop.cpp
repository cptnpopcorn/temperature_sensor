#include "interaction_loop.h"

#include "no_interaction.h"

interaction_loop::interaction_loop() noexcept
    : stop_loop{}, next{&no_interaction::instance}, stop_interaction{*this} {}

void interaction_loop::start() {
  for (stop_loop = false; !stop_loop;) {
    next->start(*this);
  }
}

interaction& interaction_loop::stop() noexcept { return stop_interaction; }

void interaction_loop::set(interaction& next) { this->next = &next; }

interaction_loop::stop_interaction::stop_interaction(
    interaction_loop& loop) noexcept
    : loop{loop} {}

void interaction_loop::stop_interaction::start(interaction_control&) {
  loop.stop_loop = true;
}
