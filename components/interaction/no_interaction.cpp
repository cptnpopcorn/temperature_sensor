#include "no_interaction.h"

no_interaction no_interaction::instance{};

bool no_interaction::start(interaction_control& control) { return false; }