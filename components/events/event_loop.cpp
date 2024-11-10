#include "event_loop.h"

#include <error.h>
#include <esp_event.h>

event_loop::event_loop() { check(esp_event_loop_create_default()); }
