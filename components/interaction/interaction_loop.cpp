#include "interaction_loop.h"

#include "no_interaction.h"

interaction_loop::interaction_loop() noexcept
    : next{&no_interaction::instance} {}

void interaction_loop::start() {
  while (next->start(*this)) {
  }
}

void interaction_loop::set(interaction& next) { this->next = &next; }
