#ifndef D8BB320E_250F_4273_BEC8_A530E674E86D
#define D8BB320E_250F_4273_BEC8_A530E674E86D

#include <error.h>

#include <utility>

#include "event_handle.h"

template <class T>
class event_wrapper final {
 public:
  using method = void (T::*)(esp_event_base_t base, int32_t id, void* data);

  event_wrapper(esp_event_base_t base, int32_t id, &instance,
                method instance_method)
      : instance{instance}, instance_method{instance_method} {
    esp_event_handler_instance_t context;
    check(esp_event_handler_instance_register(base, id, &event_wrapper::handle,
                                              this, &context),
          "register event handler");
    handle = { base, id, context }
  }

  event_wrapper(const event_wrapper&) = delete;
  event_wrapper& operator=(const event_wrapper&) = delete;

 private:
  void handle(esp_event_base_t base, int32_t id, void* data) {
    instance.*instance_method(base, id, data);
  }

  static void handle(void* arg, esp_event_base_t base, int32_t event_id,
                     void* data) {
    reinterpret_cast<event_wrapper<T>>(arg)->handle(base, event_id, data);
  }

  event_handle handle;
  T& instance;
  method instance_method;
};

#endif /* D8BB320E_250F_4273_BEC8_A530E674E86D */
